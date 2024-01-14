#pragma once
#ifndef SALE_H
#define SALE_H

#include <string>
#include <vector>
#include "DBConnection.h"

class sale
{
public:
	int vehicleId, value ,vehicleRate;
	std::string  startDate, endDate , date;


	sale(sql::ResultSet* data);
	////since sale data is computed from database, it does not need normal constructor
	////it will not exist without result set 


	static std::vector<sale> salesReport(std::string startDate , std::string endDate , bool sortByDate ,bool ascending);


	~sale() {/*you can also define blank/simple method here,
		//since we do not have anything to do in destructor yet
		//we just declare empty method here*/
	}
};


#endif
