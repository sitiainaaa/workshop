#include "customer.h"
#include <vector>
#include <ctime>
#include <iomanip>
#include "DBConnection.h"
using namespace std;

customer::customer() {
    // Initialize member variables
    custId = 0;
    c_firstName = "";
    c_lastName = "";
    c_gender = "";
    c_address = "";
    c_phoneNo = "";
   
}
customer::customer(sql::ResultSet* data)
{
    custId = data->getInt("custId");
    c_firstName = data->getString("c_firstName");
    c_lastName = data->getString("c_lastName");
    c_gender = data->getString("c_gender");
    c_address = data->getString("c_address");
    c_phoneNo = data->getString("c_phoneNo");
   
}
// Constructor definition
customer::customer(int custId,  std::string c_firstName, std::string c_lastName, std::string c_gender, std::string c_address , std::string c_phoneNo) {
    this->custId = custId;
    this->c_firstName = c_firstName;
    this->c_lastName = c_lastName;
    this->c_gender = c_gender;
    this->c_address = c_address;
    this->c_phoneNo = c_phoneNo;
    

}



void customer::insert() {
    DBConnection db; // instantiate
    db.prepareStatement("Insert into customer ( c_firstName, c_lastName, c_gender , c_address , c_phoneNo) VALUES (?, ?, ?, ?, ?)");
    db.stmt->setString(1, c_firstName);
    db.stmt->setString(2, c_lastName);
    db.stmt->setString(3, c_gender);
    db.stmt->setString(4, c_address);
    db.stmt->setString(5, c_phoneNo);
    db.QueryStatement();
    db.~DBConnection();
}

void customer::update() {
    DBConnection db;
    db.prepareStatement("UPDATE into customer ( c_firstName, c_lastName, c_gender , c_address , c_phoneNo) VALUES (?, ?, ?, ?, ?)");
    db.stmt->setString(1, c_firstName);
    db.stmt->setString(2, c_lastName);
    db.stmt->setString(3, c_gender);
    db.stmt->setString(4, c_address);
    db.stmt->setString(5, c_phoneNo);
    db.QueryStatement();
}

void customer::remove() {
    DBConnection db;
    db.prepareStatement("DELETE FROM customer WHERE custId=?");
    db.stmt->setInt(1, custId);
    db.QueryStatement();
    db.~DBConnection();
}
customer customer::selectCustomer(int custId)
{
    DBConnection db;
    db.prepareStatement("SELECT * FROM customer WHERE custId=?");
    db.stmt->setInt(1, custId);
    db.QueryResult();

    customer result;
    if (db.res->rowsCount() == 1)
    {
        while (db.res->next())
        {
            customer found(db.res);
            result = found;
        }
    }
   
}

vector<customer>customer::findCustomer(string c_firstName, string c_lastName , string c_gender , bool ascending)
{
    string query = "SELECT * FROM customer WHERE "
        " c_firstName LIKE ? AND c_lastName LIKE ? AND c_gender LIKE ? "
        " ORDER BY c_firstName ";

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
    db.stmt->setString(1, "%" + c_firstName + "%");
    db.stmt->setString(2, "%" + c_lastName + "%");
    db.stmt->setString(3, "%" + c_gender + "%");

    vector<customer> customers;

    db.QueryResult();

    if (db.res->rowsCount() > 0)
    {
        while (db.res->next())
        {
            customer tmpCustomer(db.res);
            customers.push_back(tmpCustomer);

        }
        db.~DBConnection();
        return customers;
    }

}

customer::~customer() {
}