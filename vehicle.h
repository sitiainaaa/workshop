#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
#include <vector>
#include "DBConnection.h"

class vehicle
{
public:
    // Member variables
    int vehicleId,vehicleRate;
    std::string vehicleType, noPlate, model , year ;
    //std::vector<std::pair<maintenance, int>> items;



    // Constructor methods
    vehicle(); // default constructor
    vehicle(int vehicleId, std::string vehicleType, std::string noPlate, std::string model, std::string year, int vehicleRate);
    vehicle(sql::ResultSet* data);
    // Member functions

   // Declare the insert function
   
    void InsertVehicle();
    void update(); // Provide implementation if needed
    void remove();
   

    // Destructor method
    ~vehicle();

    static vehicle selectVehicle(int vehicleId);

   static std :: vector <vehicle> findVehicle( std :: string vehicleType,std:: string noPlate, std :: string model, bool ascending);
};

#endif
