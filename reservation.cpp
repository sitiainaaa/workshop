#include "reservation.h"
#include "vehicle.h"
#include <ctime>
#include <vector>
#include <iomanip>
#include "DBConnection.h"
using namespace std;

reservation::reservation() {
	// Initialize member variables
	vehicleId  = 0;
	rentalId = 0;
	noPerday = 0;
	startDate = "";
	endDate = "";
}

reservation::reservation(sql::ResultSet* data)
{
	vehicleId = data->getInt("vehicleId");
	rentalId = data->getInt("rentalId");
	startDate = data->getString("startDate");
	endDate = data->getString("endDate");
	noPerday = data->getInt("noPerday");

}

reservation::reservation(int vehicleId, int rentalId , std::string startDate, std::string endDate, int noPerday) {
	// Initialize member variables
	this->vehicleId = vehicleId;
	this->rentalId = rentalId;
	this->startDate = startDate;
	this->endDate = endDate;
	this->noPerday = noPerday;

}


void reservation::insert()
{
	DBConnection db;  // Instantiate DBConnection

	// Prepare the SQL statement
	db.prepareStatement("INSERT INTO reservation (vehicleId, rentalId , startDate, endDate , noPerday) VALUES (?,?,?,?,?)");

	// Set parameters for the prepared statement
	db.stmt->setInt(1, vehicleId);
	db.stmt->setInt(2, rentalId);
	db.stmt->setString(3, startDate);
	db.stmt->setString(4, endDate);
	db.stmt->setInt(5, noPerday);

	// Execute the update statement
	//db.stmt->executeUpdate();

	 db.QueryStatement(); // It's not clear what this function does, you might need to uncomment and implement it if necessary
	 rentalId = db.getGeneratedId();
	// Note: It's generally better not to explicitly call the destructor unless necessary,
	// as the object will be automatically destroyed when it goes out of scope.
	 db.~DBConnection(); // Avoid calling the destructor like this
}

void reservation::update() {

	DBConnection db;
	db.prepareStatement("UPDATE reservation SET ( vehicleId, rentalId, startDate, endDate, noPerday) VALUES (?,?,?,?,?)");
	db.stmt->setInt(1, vehicleId);
	db.stmt->setInt(2, rentalId);
	db.stmt->setString(3, startDate);
	db.stmt->setString(4, endDate);
	db.stmt->setInt(5, noPerday);
	db.QueryStatement();
	db.~DBConnection();

}
void reservation::remove() {
	DBConnection db;
	db.prepareStatement("DELETE FROM reservation WHERE vehicleId=?");
	db.stmt->setInt(1, vehicleId);
	db.QueryStatement();
	db.~DBConnection();
}



 
vector<reservation>reservation::findReservation(int vehicleId, int rentalId , bool ascending)
{
	string query = "SELECT * FROM reservation WHERE "
		" vehicleId = ? AND rentalId = ?  "
		" ORDER BY vehicleId ";

	if (ascending)
	{
		query += "ASC";
	}
	else 
	{
		query += "DESC";
	}

	DBConnection db;
	db.prepareStatement(query);
	db.stmt->setInt(1,  vehicleId );
	db.stmt->setInt(2, rentalId );
	

	vector<reservation> reservations;

	db.QueryResult();

	if (db.res->rowsCount() > 0)
	{
		while (db.res->next())
		{
			reservation tmpReservation(db.res);
			reservations.push_back(tmpReservation);

		}
		db.~DBConnection();
		return reservations;
	}

}

// Define the reservationExists function
bool reservationExists(int vehicleId, const std::string& startDate) {
	// Placeholder implementation, replace with your actual logic
	// Check if there is a reservation for the given vehicleId on the specified start date
	// Return true if reservation exists, false otherwise
	// For example, if you have a reservation data structure or database table,
	// check if there is a record with the given vehicleId and the specified start date
	return false; // Replace this line with your actual implementation
}

reservation::~reservation() {

}