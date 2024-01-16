#include "staff.h"
#include <vector>
#include <ctime>
#include <conio.h>
#include <iomanip>
#include "DBConnection.h"
using namespace std;

staff::staff() {
    // Initialize member variables
    staffId = 0;
    s_username = "";
    s_firstName = "";
    s_lastName = "";
    s_email = "";
    s_password = "";
    s_phoneNo = "";
    s_address = "";
}

staff::staff(sql::ResultSet* data)
{
    staffId = data->getInt("staffId");
    s_username = data->getString("s_username");
    s_firstName = data->getString("s_firstName");
    s_lastName = data->getString("s_lastName");
    s_email = data->getString("s_email");
    s_password = data->getString("s_password");
    s_phoneNo = data->getString("s_phoneNo");
    s_address = data->getString("s_address");
}



// Constructor definition
staff::staff(int staffId, std::string s_username, std::string s_firstName, std::string s_lastName, std::string s_email, std::string s_password, std::string s_phoneNo, std::string s_address) {
    this->staffId = staffId;
    this->s_username = s_username;
    this->s_firstName = s_firstName;
    this->s_lastName = s_lastName;
    this->s_email = s_email;
    this->s_password = s_password;
    this->s_phoneNo = s_phoneNo;
    this->s_address = s_address;

}

bool staff::Login() 
{
    DBConnection db;
    db.prepareStatement("SELECT * FROM staff WHERE s_username=? AND s_password=?");
    db.stmt->setString(1, s_username);
    db.stmt->setString(2, s_password);

    db.QueryResult();

    if (db.res->rowsCount() == 1) 
    {
        while (db.res->next()) 
        {
            staffId = db.res->getInt("staffId");
            s_username = db.res->getString("s_username");
            s_firstName = db.res->getString("s_firstName");
            s_lastName = db.res->getString("s_lastName");
            s_email = db.res->getString("s_email");
            s_password = db.res->getString("s_password");
            s_phoneNo = db.res->getString("s_phoneNo");
            s_address = db.res->getString("s_address");

        }
        db.~DBConnection();
        return true;
    }
    else 
    {
        db.~DBConnection();
        return false;
    }
}



void staff::insert() {
    DBConnection db; // instantiate
    db.prepareStatement("Insert into staff ( s_username,  s_firstName, s_lastName, s_email, s_password, s_phoneNo ,s_address) VALUES (?, ?, ?, ?, ?, ?, ?)");
    db.stmt->setString(1, s_username);
    db.stmt->setString(2, s_firstName);
    db.stmt->setString(3, s_lastName);
    db.stmt->setString(4, s_email);
    db.stmt->setString(5, s_password);
    db.stmt->setString(6, s_phoneNo);
    db.stmt->setString(7, s_address);
    db.QueryStatement();
    db.~DBConnection();
}

void staff::update() {
    DBConnection db;
    db.prepareStatement("UPDATE staff SET s_username = ?,  s_firstName = ?, s_lastName =?, s_email =? , s_password =?, s_phoneNo = ? ,s_address =?  WHERE staffId = ? ");
    db.stmt->setString(1, s_username);
    db.stmt->setString(2, s_firstName);
    db.stmt->setString(3, s_lastName);
    db.stmt->setString(4, s_email);
    db.stmt->setString(5, s_password);
    db.stmt->setString(6, s_phoneNo);
    db.stmt->setString(7, s_address);
    db.stmt->setInt(8, staffId);
    db.QueryStatement();
    db.~DBConnection();
}

void staff::remove() {
    DBConnection db;
    db.prepareStatement("DELETE FROM staff WHERE staffId=?");
    db.stmt->setInt(1, staffId);
    db.QueryStatement();
    db.~DBConnection();
}

staff staff::selectStaff(int staffId)
{
    DBConnection db;
    db.prepareStatement("SELECT * FROM staff WHERE staffId=?");
    db.stmt->setInt(1, staffId);
    db.QueryResult();

    staff result;
    if (db.res->rowsCount() == 1)
    {
        while (db.res->next())
        {

            staff found(db.res);
            result = found;
        }

    }
    db.~DBConnection();
    return result;
}

vector<staff>staff::findStaff(string username , string s_firstName, string s_lastName , bool ascending)
{
    string query = "SELECT * FROM staff WHERE "
        " s_username LIKE ? AND s_firstName LIKE ? AND s_lastName LIKE ? "
        " ORDER BY s_username ";

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
    db.stmt->setString(1, "%" + username + "%");
    db.stmt->setString(2, "%" + s_firstName + "%");
    db.stmt->setString(3, "%" + s_lastName + "%");

    vector<staff> staffs;

    db.QueryResult();

    if (db.res->rowsCount() > 0)
    {
        while (db.res->next())
        {
           staff tmpStaff(db.res);
            staffs.push_back(tmpStaff);
            
        }
        db.~DBConnection();
        return staffs;
    }
       
 }

std::string staff::getMaskedInput(const std::string& prompt)
{
    std::string input;
    std::cout << prompt;

    char c;
    while (true)
    {
        c = _getch();

        if (c == 13 || c == 10) // Enter key
            break;
        else if (c == 8) // Backspace key
        {
            if (!input.empty())
            {
                std::cout << "\b \b"; // Move the cursor back and erase the character
                input.pop_back(); // Remove the last character from the string
            }
        }
        else
        {
            std::cout << '*';
            input += c;
        }
    }

    std::cout << std::endl; // Move to the next line after entering the password
    return input;
}


staff::~staff() 
{
}






    

