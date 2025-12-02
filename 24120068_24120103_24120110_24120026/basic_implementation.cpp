#include <iostream>
#include <vector>
#include <string>

#define RED "\033[31m"
#define YELLOW "\033[33m"
#define GREEN "\033[32m"
#define RESET "\033[0m"

class Bacteria{
private:
    std::string dna_;
    std::vector<std::string> resistanceList_;
    std::vector<std::string> mutationHistory_;
    int generation_;
public:
    /// @brief : Default constructor
    Bacteria() : dna_(""), resistanceList_({}), mutationHistory_({}), generation_(0){
        std::cout << "\n[INFO] Initialize a " << RED << "'bacteria'" << RESET << " object via " << 
                YELLOW << "'default constructor'" << RESET << '\n';
    } 
    /// @brief : Copy constructor using Deep Copy
    Bacteria(const Bacteria& other){
        dna_ = other.dna_;
        resistanceList_ = other.resistanceList_;
        mutationHistory_ = other.mutationHistory_;
        generation_ = other.generation_;

        std::cout << "\n[INFO] Initialize a " << RED << "'bacteria'" << RESET << " object via " << 
                YELLOW << "'copy constructor'" << RESET << '\n';
    }
    /// @brief : Destructor
    ~Bacteria(){
        std::cout << "\n[INFO] Deleting the" << RED << "'bacteria'" << RESET << " object\n";
    }
    /// @brief : Clone method
    Bacteria* clone() {
        std::cout << "Cloning " << RED << "'bacteria'" << RESET << " object via " 
                << YELLOW << "'clone()'" << RESET << "method\n"; 

        Bacteria* newBacteria = new Bacteria(*this);

        newBacteria->generation_ = this->generation_ + 1;

        return newBacteria;
    }

    ///< @brief : Mutating 
    void mutate(const std::string& resistanceSubstance) {
        this->dna_ += "_Mutated";
        this->resistanceList_.push_back("Resist-" + resistanceSubstance);
        this->mutationHistory_.push_back("Mutate-" + resistanceSubstance);
    }

    void printInfo() {
        std::cout << "--- Bacteria Info ---" << "\n";
        std::cout << "Gen: " << dna_ << "\n";
        std::cout << "Generation: " << generation_ << "\n";
        std::cout << "Resistance: ";
        for (const auto& r : resistanceList_) std::cout << r << " ";
        std::cout << "\n" << "\n";
    }
};
int main()
{
    std::ios_base::sync_with_stdio(false);

    Bacteria* mother = new Bacteria();

    mother->mutate("Penicillin");      
    mother->mutate("Ampicillin");     
    mother->mutate("Tetracycline");    
    mother->mutate("Streptomycin");    

    std::cout << "Mother after mutated:" << std::endl;
    mother->printInfo();

    std::cout << "Child cloned from Mother:" << std::endl;
    Bacteria* child = mother->clone();

    child->mutate("Chloramphenicol");

    child->printInfo();

    delete child;
    delete mother;

    return 0;
}