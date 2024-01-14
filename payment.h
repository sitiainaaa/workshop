#ifndef PAYMENT_H
#define PAYMENT_H

#include <string>
#include <vector>
#include "DBConnection.h"

class payment {
public:
    // Member variables
    int paymentId,rentalId,value; // numerical attributes
    std::string  payment_Date ;

    // Constructor methods
    payment(); // default constructor
    payment(int paymentId, int rentalId, int value , std::string payment_Date );
    payment(sql::ResultSet* data);

    // Member functions
    /*bool Login();*/
    void insert();
    void update(); // Provide implementation if needed
    void remove();

    // Destructor method
    ~payment();

    static payment selectPayment(int paymentId);

    //// Declare find payment only once
    //static std::vector<payment> findPayment(std::string c_firstName, std::string c_lastName, std::string c_gender, bool ascending);

   static std::vector<payment>report(const std::string& startDate, const std::string& endDate, bool ascending);
};

#endif
