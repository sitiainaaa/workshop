#pragma once
#ifndef ADMIN_H
#define ADMIN_H

#include <string>

class admin {
public:
    // Member variables
    int adminId ; // numerical attributes
    std::string  a_username , a_password, a_email, a_address, a_firstName, a_lastName, a_phoneNo; // text attributes

    // Constructor methods
    admin(); // default constructor
    admin(int adminId, std::string a_username, std::string a_firstName, std::string a_lastName, std::string a_email, std::string a_password, std::string a_phone_No , std::string a_address );

    // Member functions
    bool Login();
    void insert();
    void update(); // Provide implementation if needed
    void remove();

    static std::string getMaskedInput(const std::string& prompt);

    // Destructor method
    ~admin();
};

#endif


