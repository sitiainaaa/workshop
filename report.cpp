#include "report.h"
#include "DBConnection.h"  // Make sure to include the header file for DBConnection

using namespace std;
using namespace sql;


report::report(sql::ResultSet* data)
{
	NoPerday = data->getInt("NoPerday");
	vehicle_rate = data->getInt("vehicle_rate");

}


vector<report>report::paymentReport(int custID)
{
	string query = "SELECT  v.vehicleRate as vehicle_rate , p.noPerday as NoPerday  "
		"FROM vehicle v"
		"JOIN reservation p ON v.vehicleId = p.vehicleId"
		"JOIN rental r ON p.rentalId = r.rentalId"
		"WHERE r.customerId = ?" ;


	DBConnection db;
	db.prepareStatement(query);
	

	vector<report> reports;

	db.stmt->setInt(1,custID);
	db.QueryResult();

	if (db.res->rowsCount() > 0)
	{
		while (db.res->next())
		{
			report tmpReport(db.res);
			reports.push_back(tmpReport);

		}
		
	}
	db.~DBConnection();
	return reports;
}



