#include "vehicle.h"
#include <ctime>
#include "DBConnection.h"  // Make sure to include the header file for DBConnection

using namespace std;

vehicle::vehicle() {
	// Initialize member variables
	vehicleId = 0;
	vehicleRate = 0;
	vehicleType = "";
	noPlate = "";
	model = "";
	year = "";
	
	

}
vehicle::vehicle(sql::ResultSet* data)
{
	vehicleId = data->getInt("vehicleId");
	vehicleType = data->getString("vehicleType");
	noPlate = data->getString("noPlate");
	model = data->getString("model");
	year = data->getString("year");
	vehicleRate = data->getInt("vehicleRate");

}
vehicle::vehicle(int vehicleId, std::string vehicleType, std::string noPlate, std::string model , std:: string year , int vehicleRate) {
	// Initialize member variables
	this->vehicleId = vehicleId;
	this->vehicleType = vehicleType;
	this->noPlate = noPlate;
	this->model = model;
	this->year = year;
	this->vehicleRate = vehicleRate;
}

void vehicle::InsertVehicle() {
	DBConnection db;  // Instantiate DBConnection

	// Prepare the SQL statement
	db.prepareStatement("insert INTO vehicle ( vehicleType, noPlate, model , year , vehicleRate ) VALUES (?,?,?,?,?)");

	// Set parameters for the prepared statement
	db.stmt->setString(1, vehicleType);
	db.stmt->setString(2, noPlate);
	db.stmt->setString(3, model);
	db.stmt->setString(4, year);
	db.stmt->setInt(5, vehicleRate);

	// Execute the update statement
	//db.stmt->executeUpdate();

	db.QueryStatement(); // It's not clear what this function does, you might need to uncomment and implement it if necessary

	// Note: It's generally better not to explicitly call the destructor unless necessary,
	// as the object will be automatically destroyed when it goes out of scope.
	db.~DBConnection(); // Avoid calling the destructor like this
}

void vehicle::update() {

	DBConnection db;
	db.prepareStatement("UPDATE vehicle SET ( vehicleId, vehicleType, noPlate, model , year , vehicleRate) VALUES (?,?,?,?,?,?)");
	db.stmt->setInt(1, vehicleId);
	db.stmt->setString(2, vehicleType);
	db.stmt->setString(3, noPlate);
	db.stmt->setString(4, model);
	db.stmt->setString(5, year);
	db.stmt->setInt(6, vehicleRate);

	db.QueryStatement();
	db.~DBConnection();

}
void vehicle::remove() {
	DBConnection db;
	db.prepareStatement("DELETE FROM vehicle WHERE vehicleId=?");
	db.stmt->setInt(1, vehicleId);
	db.QueryStatement();
	db.~DBConnection();
}
vehicle vehicle::selectVehicle(int vehicleId)
{
	DBConnection db;
	db.prepareStatement("SELECT * FROM vehicle WHERE vehicleId=?");
	db.stmt->setInt(1, vehicleId);
	db.QueryResult();

	vehicle result;
	if (db.res->rowsCount() == 1)
	{
		while (db.res->next())
		{
		
		vehicle found(db.res);
		result = found;
	    }
			
	}
	db.~DBConnection();
	return result;
}


vector<vehicle>vehicle::findVehicle(string vehicleType, string noPlate, string model, bool ascending)
{
	string query = "SELECT * FROM vehicle WHERE "
		" vehicleType LIKE ? AND noPlate LIKE ? AND model LIKE ? "
		" ORDER BY vehicleType ";

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
	db.stmt->setString(1, "%" + vehicleType + "%");
	db.stmt->setString(2, "%" + noPlate + "%");
	db.stmt->setString(3, "%" + model + "%");

	vector<vehicle> vehicles;

	db.QueryResult();

	if (db.res->rowsCount() > 0)
	{
		while (db.res->next())
		{
			vehicle tmpVehicle(db.res);
			vehicles.push_back(tmpVehicle);

		}
		db.~DBConnection();
		return vehicles;
	}

}



vehicle::~vehicle() {

}

