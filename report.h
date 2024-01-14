#pragma once
#ifndef REPORT_H
#define REPORT_H

#include <vector>
#include <string>
#include "DBConnection.h"


class report
{
public:
    // Member variables
    int vehicle_rate , NoPerday;
   
    // Declare the insert function


   
    report(sql::ResultSet* data);
    // Member functions



    // Declare findReservation only once
    static std::vector<report> paymentReport(int custID);

    ~report()
    {

    }

};

#endif


