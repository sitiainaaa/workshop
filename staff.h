#ifndef STAFF_H
#define STAFF_H

#include <string>
#include <vector>
#include "DBConnection.h"

class staff {
public:
    // Member variables
    int staffId; // numerical attributes
    std::string s_username, s_password, s_email, s_address, s_firstName, s_lastName, s_phoneNo; // text attributes

    // Constructor methods
    staff(); // default constructor
    staff(int staffId, std::string s_username, std::string s_firstName, std::string s_lastName, std::string s_email, std::string s_password, std::string s_phoneNo, std::string s_address);
    staff(sql::ResultSet* data);
    // Member functions
    bool Login();
    void insert();
    void update(); // Provide implementation if needed
    void remove();

    // Destructor method
    ~staff();

    static std::string getMaskedInput(const std::string& prompt);

    static staff selectStaff(int staffId);

    // Declare findStaff only once
    static std::vector<staff> findStaff(std::string username, std::string s_firstName, std::string s_lastName, bool ascending);
};

#endif
