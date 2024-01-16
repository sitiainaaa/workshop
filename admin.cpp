#include "Admin.h"
#include <ctime>
#include "DBConnection.h"
#include <conio.h>
using namespace std;

admin::admin() {
    // Initialize member variables
    adminId = 0;
    a_username = "";
    a_firstName = "";
    a_lastName = "";
    a_email = "";
    a_password = "";
    a_phoneNo = "";
    a_address = "";
    
}

// Constructor definition
admin::admin(int adminId, std::string a_username, std::string a_firstName, std::string a_lastName, std::string a_email, std::string a_password, std::string a_phoneNo, std::string a_address) {
    this->adminId = adminId;
    this->a_username = a_username;
    this->a_firstName = a_firstName;
    this->a_lastName = a_lastName;
    this->a_email = a_email;
    this->a_password = a_password;
    this->a_phoneNo = a_phoneNo;
    this->a_address = a_address;
    

    
}

bool admin::Login() {
    DBConnection db;
    db.prepareStatement("SELECT * FROM admin WHERE a_username=? AND a_password=?");
    db.stmt->setString(1, a_username);
    db.stmt->setString(2, a_password);

    db.QueryResult();

    if (db.res->rowsCount() == 1) {
        while (db.res->next()) {
            adminId = db.res->getInt("adminId");
            a_username = db.res->getString("a_username");
            a_firstName = db.res->getString("a_firstName");
            a_lastName = db.res->getString("a_lastName");
            a_email = db.res->getString("a_email");
            a_password = db.res->getString("a_password");
            a_phoneNo = db.res->getString("a_phoneNo");
            a_address = db.res->getString("a_address");
        
        }
        db.~DBConnection();
        return true;
    }
    else {
        db.~DBConnection();
        return false;
    }
}



void admin::insert() {
    DBConnection db; // instantiate
    db.prepareStatement("Insert into admin ( a_username, a_email, a_password, a_firstName, a_lastName, a_phoneNo, a_address) VALUES ( ?, ?, ?, ?, ?, ?, ?)");
    db.stmt->setString(1, a_username);
    db.stmt->setString(2, a_email);
    db.stmt->setString(3, a_password);
    db.stmt->setString(4, a_firstName);
    db.stmt->setString(5, a_lastName);
    db.stmt->setString(6, a_phoneNo);
    db.stmt->setString(7, a_address);                                                                                                                               
    db.QueryStatement();
    db.~DBConnection();
}

void admin::update() {
    DBConnection db;
    db.prepareStatement("UPDATE admin SET  a_username = ?, a_email = ? , a_password = ? , a_firstName = ? , a_lastName = ?, a_phoneNo = ? ,a_address = ? WHERE adminId = ? ");
 
    db.stmt->setString(1, a_username);
    db.stmt->setString(2, a_email);
    db.stmt->setString(3, a_password);
    db.stmt->setString(4, a_firstName);
    db.stmt->setString(5, a_lastName);
    db.stmt->setString(6, a_phoneNo);
    db.stmt->setString(7, a_address);
    db.stmt->setInt(8, adminId);
    db.QueryStatement();
    db.~DBConnection();

}

void admin::remove() {
    DBConnection db;
    db.prepareStatement("DELETE FROM admin WHERE adminId=?");
    db.stmt->setInt(1, adminId);
    db.QueryStatement();
    db.~DBConnection();
}

std::string admin::getMaskedInput(const std::string& prompt)
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

admin::~admin() {
}
