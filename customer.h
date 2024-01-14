#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <vector>
#include "DBConnection.h"

class customer {
public:
    // Member variables
    int custId; // numerical attributes
    std::string  c_firstName,c_lastName, c_gender, c_address, c_phoneNo;

    // Constructor methods
    customer(); // default constructor
    customer(int custId, std::string c_firstName, std::string c_lastName, std::string c_gender, std::string s_address, std::string s_phoneNo);
    customer(sql::ResultSet* data);

    // Member functions
    /*bool Login();*/
    void insert();
    void update(); // Provide implementation if needed
    void remove();

    // Destructor method
    ~customer();

    static customer selectCustomer(int custId);

    // Declare findStaff only once
    static std::vector<customer> findCustomer(std::string c_firstName, std::string c_lastName, std::string c_gender , bool ascending);
};

#endif

