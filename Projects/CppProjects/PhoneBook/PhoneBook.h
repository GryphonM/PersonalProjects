#pragma once
#include <string>
#include <vector>
#include <deque>

struct PhoneEntry
{
    std::string name;
    std::string last_name;
    std::string email;
    int region;
    int number;

    PhoneEntry(std::string name_, std::string last_name_,
        std::string email_, int region_, int number_);

};

class PhoneBook
{
public:
    PhoneBook(std::string filename_);
    PhoneBook(const PhoneBook &copy_);
    PhoneBook & operator= (const PhoneBook & rhs_);
    
    void Save(std::string filename_) const;
    friend std::ostream & operator<<(std::ostream & os_, 
                                     const PhoneBook & phonebook_);
	
	// NOT REQUIRED
    //friend std::istream & operator>>(std::istream & os_, 
                                     //PhoneBook & phonebook_);

    void AddEntry(const std::string &name_,
                  const std::string &last_name_,
                  const std::string &email_,
                  int region_, int number_);

    void SortByName();
    void RemoveEntriesByName(std::string subString_);
    
    ~PhoneBook();

private:

    std::vector<PhoneEntry *> entries;
    //std::deque<PhoneEntry *> entries;
};

std::ostream & operator<<(std::ostream & os_, const PhoneBook & phonebook_);

// NOT REQUIRED
//std::istream & operator>>(std::istream & os_, const PhoneBook & phonebook_);
