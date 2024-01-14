#include "sale.h"
using namespace std;
using namespace sql;

sale::sale(ResultSet* data) {

	value = data->getInt("value");
	date = data->getString("date");
	
}

vector<sale> sale::salesReport(string startDate, string endDate ,bool sortByDate, bool ascending) {


	string sql = " SELECT p.payment_Date as date, SUM(p.value) as value "
		" FROM payment p ";
		


	sql += " WHERE p.payment_Date >= ? AND p.payment_Date <= ? ";

	sql += "GROUP BY ";
	
	sql += " CAST(MONTH(p.payment_Date) AS VARCHAR(2)) + '-' + CAST(YEAR(p.payment_Date) AS VARCHAR(4)) ";

	sql += " ORDER BY ";
	if (sortByDate) {

		sql += " p.payment_Date";
	}
	else {

		sql += " value ";
	}

	if (ascending) {
		sql += " ASC ";
	}
	else {
		sql += " DESC ";
	}

	vector <sale> salesReport;

	DBConnection db;

	db.prepareStatement(sql);

	int index = 1;

	db.stmt->setString(index, startDate);
	index++;
	db.stmt->setString(index, endDate);
	db.QueryResult();

	if (db.res->rowsCount() > 0) {

		while (db.res->next()) {
			sale tmpsale(db.res);
			salesReport.push_back(tmpsale);
		}
	}

	db.~DBConnection();
	return salesReport;



}