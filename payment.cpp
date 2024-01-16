#include "payment.h"
#include <vector>
#include <ctime>
#include <iomanip>
#include "DBConnection.h"
using namespace std;

payment::payment() {
    // Initialize member variables
    paymentId = 0;
    rentalId = 0;
    value = 0;
    payment_Date = "";
    
  
}
payment::payment(sql::ResultSet* data)
{
    paymentId = data->getInt("paymentId");
    rentalId = data->getInt("rentalId");
    value = data->getInt("value");
    payment_Date = data->getString("payment_Date");
    
   

}
// Constructor definition
payment::payment(int paymentId, int rentalId,int value ,std::string payment_Date ) {
    this->paymentId = paymentId;
    this->rentalId = rentalId;
    this->value = value;
    this->payment_Date = payment_Date;
    
 
}


void payment::insert( int rentID) {
    DBConnection db; // instantiate
    db.prepareStatement("INSERT INTO payment ( rentalId, value ) VALUES (?, ?)");
   
    db.stmt->setInt(1, rentID);
    db.stmt->setInt(2, value);
    db.QueryStatement();
    db.~DBConnection();
}

void payment::update() {
    DBConnection db;
    db.prepareStatement("UPDATE INTO payment ( paymentId,rentalId, value, payment_Date  ) VALUES (?,?, ?, ?, )");
    db.stmt->setInt(1, paymentId);
    db.stmt->setInt(2, rentalId);
    db.stmt->setInt(3, value);
    db.stmt->setString(4, payment_Date);
    
    db.QueryStatement();
}

void payment::remove() {
    DBConnection db;
    db.prepareStatement("DELETE FROM payment WHERE paymentId=?");
    db.stmt->setInt(1, paymentId);
    db.QueryStatement();
    db.~DBConnection();
}
payment payment::selectPayment(int paymentId)
{
    DBConnection db;
    db.prepareStatement("SELECT * FROM payment WHERE paymentId=?");
    db.stmt->setInt(1, paymentId);
    db.QueryResult();

    payment result;
    if (db.res->rowsCount() == 1)
    {
        while (db.res->next())
        {
            payment found(db.res);
            result = found;
        }
    }

}

//vector<customer>customer::findCustomer(string c_firstName, string c_lastName, string c_gender, bool ascending)
//{
//    string query = "SELECT * FROM customer WHERE "
//        " c_firstName LIKE ? AND c_lastName LIKE ? AND c_gender LIKE ? "
//        " ORDER BY c_firstName ";
//
//    if (ascending)
//    {
//        query += "ASC";
//    }
//    else
//    {
//        query += "DESC";
//    }
//
//    DBConnection db;
//    db.prepareStatement(query);
//    db.stmt->setString(1, "%" + c_firstName + "%");
//    db.stmt->setString(2, "%" + c_lastName + "%");
//    db.stmt->setString(3, "%" + c_gender + "%");
//
//    vector<payment> payments;
//
//    db.QueryResult();
//
//    if (db.res->rowsCount() > 0)
//    {
//        while (db.res->next())
//        {
//            payment tmpPayment(db.res);
//            payments.push_back(tmpPayment);
//
//        }
//        db.~DBConnection();
//        return customers;
//    }
//
//}

std::vector<payment> payment::report(const std::string& startDate, const std::string& endDate, bool ascending)
{
    string query = "SELECT * FROM Payment p "
        //" JOIN Treatment t "
        " WHERE p.Payment_Date BETWEEN ? AND ? "
        " ORDER BY TreatmentID ";
    if (ascending)
    {
        query += " ASC";
    }
    else
    {
        query += " DESC";
    }

    DBConnection db;
    db.prepareStatement(query);
    //db.stmt->setString(1, "%" + NameT + "%");
    db.stmt->setString(1, startDate);
    db.stmt->setString(2, endDate);


    vector<payment> pays;
    db.QueryResult();

    if (db.res->rowsCount() > 0)
    {
        while (db.res->next())
        {
            payment tmpPay(db.res);
            pays.push_back(tmpPay);
        }
    }

    db.~DBConnection();
    return pays;
}

payment::~payment() {
}