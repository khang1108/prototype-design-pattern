#include <iostream>
#include <string>
#include <map>
#include <thread>
#include <chrono>
#include <map>
#include <vector>

#define RED "\033[31m"
#define YELLOW "\033[33m"
#define GREEN "\033[32m"
#define RESET "\033[0m"

class ServerPrototype
{
public:
    ///< @brief: Pure virtual allowing each subclass to define its own method
    virtual ServerPrototype* clone() const = 0;
    virtual void showConfig() = 0;
    virtual ~ServerPrototype() {}
};

class LinuxServer : public ServerPrototype {
private:
    std::string name_;
    std::string osVersion_;
    int ramGB_;
    std::vector<std::string>* installedPackages_;
public:
    LinuxServer(std::string name, int ram) : name_(name), ramGB_(ram) {
        this->osVersion_ = "Linux 6.17.4-arch2-1";
        installedPackages_ = new std::vector<std::string>{"nginx", "mysql", "php"};

        std::cout << "[System] Installing OS for Prototype " << name_ 
                << "via " << RED << "'default  constructor'" << RESET << '\n';
    }

    LinuxServer(const LinuxServer& other){
        name_ = other.name_;
        osVersion_ = other.osVersion_;
        ramGB_  =  other.ramGB_;
        installedPackages_ =  new std::vector<std::string>(*other.installedPackages_);
        std::cout << "[System] Installing OS for Prototype " << name_ 
                << "via " << RED << "'copy  constructor'" << RESET << '\n';
    }

    ServerPrototype* clone() const override {
        return new LinuxServer(*this);
    }

    void showConfig() override {
        std::cout << "Server: " << name_ << " | OS: " << osVersion_ << " | RAM: " << ramGB_ << "GB" << std::endl;
    }

    ~LinuxServer(){
        delete installedPackages_;
    }
};

class ServerRegistry
{
private:
    std::map<std::string,  ServerPrototype*> templates;

public:
    ServerRegistry() {
        std::cout <<  "=== STARTING REGISTRY ===" << std::endl;

        templates["Standard"] = new LinuxServer("Standard_VPS", 4);
        templates["HighMem"] = new LinuxServer("HighMem_VPS", 64);

        std::cout << "=== COMPLETED INITIALIZATION ===" << std::endl;
    }

    ~ServerRegistry() {
        for (auto const& [key, val] : templates) {
            delete val;
        }
        templates.clear();
    }

    ServerPrototype* createServer(std::string type){
        if(templates.find(type) != templates.end()){
            return templates[type]->clone();
        }
        return nullptr;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);

    ServerRegistry registry;

    std::cout << "[INFO] Create a " << RED << "'Standard'" << RESET 
            << " server\n";
    ServerPrototype* standardServer = registry.createServer("Standard");
    if(standardServer) standardServer->showConfig();

    std::cout << "[INFO] Create a " << RED << "'HigMem'" << RESET 
            << " server\n";
    ServerPrototype* highMem = registry.createServer("HighMem");
    if(highMem) highMem->showConfig();

    std::cout << "[INFO] Create a " << RED << "'Standard'" << RESET 
            << " server\n";
    ServerPrototype* standardServer2 = registry.createServer("Standard");
    if(standardServer2) standardServer2->showConfig();

    delete standardServer;
    delete highMem;
    delete standardServer2;

    return 0;
}