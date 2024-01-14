#pragma once
#ifndef RESERVATION_H
#define RESERVATION_H

#include <vector>
#include <string>
#include "DBConnection.h"


class reservation
{
public:
    // Member variables
    int vehicleId,rentalId,noPerday;
    std::string startDate, endDate;
    //std::vector<std::pair<maintenance, int>> items;

    // Declare the insert function

   
    void insert();
    void update(); // Provide implementation if needed
    void remove();
    


    // Constructor methods
    reservation(); // default constructor
    reservation(int vehicleId, int rentalId , std::string startDate, std::string endDate,int noPerday);
    reservation(sql::ResultSet* data);
    // Member functions
    

    // Destructor method
    ~reservation();

    // Declare findReservation only once
    static std::vector<reservation> findReservation(int vehicleId, int rentalId, bool ascending);

    

};

#endif

