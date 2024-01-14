#include "rental.h"
#include <ctime> 
#include "DBConnection.h"
using namespace std;


rental::rental() {
	rentalId = 0;
	custId = 0;
	staffId = 0;
	rentalDate = "";
}

rental::rental(int rentalId, int custId, int staffId, std::string rentalDate) {
	// Initialize member variables
	this->rentalId = rentalId;
	this->custId = custId;
	this->staffId = staffId;
	this->rentalDate = rentalDate;	

}


void rental::InsertRental() {
	DBConnection db;  // Instantiate DBConnection

	// Prepare the SQL statement
	db.prepareStatement("insert INTO rental (rentalId, custId , staffId, rentalDate ) VALUES (?,?,?,?)");

	// Set parameters for the prepared statement
	db.stmt->setInt(1, rentalId);
	db.stmt->setInt(2, custId);
	db.stmt->setInt(3, staffId);
	db.stmt->setString(4, rentalDate);

	// Execute the update statement
	//db.stmt->executeUpdate();

	 db.QueryStatement(); // It's not clear what this function does, you might need to uncomment and implement it if necessary

	 
	// Note: It's generally better not to explicitly call the destructor unless necessary,
	// as the object will be automatically destroyed when it goes out of scope.
	 db.~DBConnection(); // Avoid calling the destructor like this
}

void rental::update() {

	DBConnection db;
	db.prepareStatement("UPDATE rental SET ( rentalId, custId, staffId, rentalDate ) VALUES (?,?,?,?)");
	db.stmt->setInt(1, rentalId);
	db.stmt->setInt(2, custId);
	db.stmt->setInt(3, staffId);
	db.stmt->setString(4, rentalDate);	
	db.QueryStatement();
	db.~DBConnection();

}
void rental::remove() {
	DBConnection db;
	db.prepareStatement("DELETE FROM rental WHERE rentalId=?");
	db.stmt->setInt(1, rentalId);
	db.QueryStatement();
	db.~DBConnection();
}

rental::rental(sql::ResultSet* data) {
	rentalId = data->getInt("rentalId");
	custId = data->getInt("custId");
	staffId = data->getInt("staffId");
	rentalDate = data->getString("rentalDate");	
}


rental rental::findrental(int productId) {
	DBConnection db;
	db.prepareStatement("SELECT * FROM product WHERE productId=?");
	db.stmt->setInt(1, productId);
	db.QueryResult();

	rental result;
	if (db.res->rowsCount() == 1) {
		while (db.res->next()) {
			rental found(db.res);
			result = found;
		}
	}
	db.~DBConnection();
	return result;


}vector<rental>rental::findRental(string rentalDate, bool ascending)
{
	string query = "SELECT * FROM rental WHERE "
		" rentalDate LIKE ? "
		" ORDER BY rentalDate ";

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
	db.stmt->setString(1, "%" + rentalDate + "%");

	
	vector<rental> rentals;

	db.QueryResult();

	if (db.res->rowsCount() > 0)
	{
		while (db.res->next())
		{
			rental tmpRental(db.res);
			rentals.push_back(tmpRental);

		}
		db.~DBConnection();
		return rentals;
	}

}



rental::~rental() {

}