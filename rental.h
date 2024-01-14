#pragma once
#ifndef RENTAL_H
#define RENTAL_H

#include <string>
#include <vector>
#include "DBConnection.h"

class rental
{
public:
	int rentalId, custId, staffId;
	std::string rentalDate;

	void InsertRental();
	void update();
	void remove();

	rental();
	rental(int rentalId, int custId , int staffId, std::string rentalDate);
	rental(sql::ResultSet* data);

	~rental();

	static rental findrental(int rentalId);

	

	// Declare findRental only once
	static std::vector<rental> findRental(std::string rentalDate, bool ascending);

};


#endif