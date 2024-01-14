#include <iostream>
#include <conio.h>
#include <iomanip>
#include <sstream>
#include <regex>
#include<chrono>
#include<ctime>
#include<string>

////// advanced
////// include our custom class
#include "ArrowMenu.h"
#include "admin.h" 
#include "menu.h"
#include "staff.h"
#include "customer.h"
#include "rental.h"
#include "vehicle.h"
#include "reservation.h"
#include "payment.h"
#include "report.h"
#include "sale.h"

using namespace std;

//void Register();
void Registerstaff();
void Login();
void Loginstaff();
void adminPage();
void staffPage();
void adhome(admin auser);
admin adprofile(admin auser);
void sthome(staff suser);
staff stfprofile(staff suser);
void stmanage(staff suser);
void staffInfo(staff suser);
void custmanage(customer cuser);
void Registercust();
void ViewAllCust();
customer DeleteCustomer(customer cuser);
void ViewAllStaff();
staff DeleteStaff(staff suser);
void Rental(payment pays, rental ruser,  customer cuser, staff suser, reservation reuser, vehicle vehicles);
void InsertRental(rental ruser, customer cuser, staff suser);
void ViewAllRental(payment pays, rental ruser, customer cuser, staff suser, reservation reuser, vehicle vehicles);
void vehiclePage();
vehicle InsertVehicle(vehicle vehicles);
void ViewAllVehicle();
void UpdateVehicle();
vehicle DeleteVehicle(vehicle auser);
//void insertReservation();
//void ViewAllReservation(reservation reuser, vehicle vehicles , rental ruser);
payment rentReservation (payment pays, rental ruser, reservation reuser, vehicle vehicles);
bool reservationExists(int vehicleId, const std::string& startDate);
void paymentTrans(int rentalId, rental ruser , reservation reuser ,vehicle vehicles );
void SaleReportMenu(admin auser);
bool validateDate(const std::string& date);
  

//admin

int main() {

    ArrowMenu mainmenu;
    mainmenu.header = "\n\t\t----Welcome to UTeM Rental Vehicle System----- \n\n\t\t Choose your role: ";
    mainmenu.addOption("Admin");
    mainmenu.addOption("Staff");
    mainmenu.addOption("Exit");

    mainmenu.footer = "\t\tUse Up / Down key to move selection and press enter to select\n\t\tPress Escape to go back";

    while (1) {
        switch (mainmenu.prompt())
        {
        case -1:
            return 0;
            break;
        case 0:
            adminPage();
            break;
        case 1:
            staffPage();
            break;
        case 2:
            exit(0);
            break;
        default:
            break;
        }
    }
}

void adminPage()
{
    ArrowMenu Rolemenu;
    Rolemenu.header = "\n\n\t\t-------------------ADMIN PAGE----------------------\n\n\t\t Select Option: ";

    Rolemenu.addOption("Login");
  /*  Rolemenu.addOption("Register Admin");*/
    Rolemenu.addOption("Exit");

    Rolemenu.footer = "\t\tUse Up / Down key to move selection and press enter to select\n\t\tPress Escape to go back";

    while (1) {
        switch (Rolemenu.prompt())
        {
        case -1:
            return ;
            break;
        case 0:
            Login();
       /* case 1:
            Register();
            break;*/
        case 1:
            main();
        default:
            break;
        }
    }

}

void Login() {
    Menu loginMenu;
    loginMenu.header = "\t\t ===================== Admin Login =============================\n";
    loginMenu.addOption("username");
    loginMenu.addOption("password");
    loginMenu.addOption("Login");
    loginMenu.addOption("Back\n");
    loginMenu.footer = "\t\tFill in the details, then press Enter after each input.\n\t\tEnter '4' to go back.";
        

    admin auser;

    while (1) {
        switch (loginMenu.prompt())
        {
        case 1:
            cout << "Insert username:";
            cin >> auser.a_username;
            loginMenu.setValue(0, auser.a_username);
            break;
        case 2:
            cout << "Insert Password:";
            auser.a_password = admin::getMaskedInput("");
            loginMenu.setValue(1, std::string(auser.a_password.length(), '*'));
           /* loginMenu.setValue(1, auser.a_password);*/
            break;
        case 3:
            if (auser.Login()) {
                adhome(auser);
            }
            else {
                cout << "Invalid Login";
                _getch();
            }
            break;
        case 4:
            adminPage();
            break;
        default:
            break;
        }

    }
}

void adhome(admin auser) {

    ArrowMenu adhomeMenu;
    adhomeMenu.header = "\t\t\t\t Welcome " + auser.a_username;

    adhomeMenu.addOption("Admin Profile");
    adhomeMenu.addOption("Manage Staff");
    adhomeMenu.addOption("Manage Vehicle");
    adhomeMenu.addOption("Sale Report");
    adhomeMenu.addOption("Logout\n");

    adhomeMenu.footer = "\t\tUse Up / Down key to move selection and press enter to select\n\t\tPress Escape to go back";

    staff suser;
    while (1) {
        switch (adhomeMenu.prompt())
        {
        case -1:
            return;
            break;
        case 0:
            adprofile(auser);
            break;
        case 1:
            stmanage(suser);
            break;
        case 2:
            vehiclePage();
            break;
        case 3:
            SaleReportMenu(auser);
            break;
        case 4:
            Login();
            //return;
            break;
        default:
            break;
        }
    }
}

admin adprofile(admin auser) {

    admin temp = auser; // copy the object

    Menu adprofileMenu;
    adprofileMenu.header = "\t\t -------------------- Your profile -----------------------\n";
    adprofileMenu.addOption("admin ID");
    adprofileMenu.addOption("username");
    adprofileMenu.addOption("password");
    adprofileMenu.addOption("email");
    adprofileMenu.addOption("phone no");
    adprofileMenu.addOption("address");
    adprofileMenu.addOption("Save");
    adprofileMenu.addOption("Back");
    adprofileMenu.addOption("Delete Account");
    adprofileMenu.footer = "\t\tFill in the details, then press Enter after each input.\n\t\tEnter '8' to go back.";

    char confirm;
    string tmpInput;
    while (1) {
        adprofileMenu.setValue(0, to_string(temp.adminId));
        adprofileMenu.setValue(1, temp.a_username);
        adprofileMenu.setValue(2, temp.a_password);
        adprofileMenu.setValue(3, temp.a_email);
        adprofileMenu.setValue(4, temp.a_phoneNo);
        adprofileMenu.setValue(5, temp.a_address);



        switch (adprofileMenu.prompt())
        {
        case 1:
            cout << "ID cannot changed. ";
            _getch();
            break;
        case 2:
            cout << "Insert new username:";
            cin >> temp.a_username;
            break;
        case 3:
            cout << "Insert new password:";
            cin >> temp.a_password;
            cin >> tmpInput;
            if (tmpInput.length() < 6)
            {
                cout << "\n\n\t Password must be at least 6 character long \n\n\t Press any key to continue. ";
                _getch();
            }
            else
            {
                temp.a_password = tmpInput;
            }
            break;
        case 4:
            cout << "Insert email:";
            cin >> temp.a_email;
            break;
        case 5:
            cout << "Insert phone no:";
            getline(cin, temp.a_phoneNo);
            break;
        case 6:
            cout << "Insert address:";
            getline(cin, temp.a_address);
            break;
        case 7:
            cout << "\n\n\tUpdate your account? (y/n)";
             char confirm;
            confirm = _getch();
            if (confirm == 'Y' || confirm == 'y')
            {
                auser = temp;
                auser.update();
                cout << "\n\nInformation updated.";
                _getch();
            }
            break;
        case 8:
            auser = temp;
            auser.update();
            cout << "Updated";
            _getch();
        case 9:
            return auser;
            break;
        case 10:
            cout << "Delete your account? (y/n)";
            
            confirm = _getch();
            if (confirm == 'Y' || confirm == 'y') {
                auser = temp;
                auser.remove();
                main();
            }
            break;
        default:
            break;
        }
    }
}




//staff

void staffPage()
{
    ArrowMenu Rolemenu;
    Rolemenu.header = "\n\t\t--------------------- STAFF PAGE ------------------\n\n\t\t ";
    Rolemenu.addOption("Login");
    Rolemenu.addOption("Exit\n");

    Rolemenu.footer = "\t\tUse Up / Down key to move selection and press enter to select\n\t\tPress Escape to go back";



    while (1) {
        switch (Rolemenu.prompt())
        {
        case -1:
            return;
            break;
        case 0:
            Loginstaff();
            break;
        case 1:
            main();
            break;
        }
    }
}

void Registerstaff() {
    staff newacc;

    Menu rgMenu;
    rgMenu.header = "\t\t====================== Staff Registration ========================\n";

    rgMenu.addOption("Username");
    rgMenu.addOption("First Name");  
    rgMenu.addOption("Last Name");
    rgMenu.addOption("Email");
    rgMenu.addOption("Password");
    rgMenu.addOption("Phone no");
    rgMenu.addOption("Address");
    rgMenu.addOption("Register");
    rgMenu.addOption("Back");
    rgMenu.footer ="\t\tFill in the details, then press Enter after each input.\n\t\tEnter '9' to go back.";

    staff suser;
    string tmpinput;
    bool valid = true;
    while (1) {
        switch (rgMenu.prompt()) {

        case 1:
            cout << "Username:";
            cin >> newacc.s_username;  // Use a separate variable for the first name
            rgMenu.setValue(0, newacc.s_username);
            break;
        case 2:
            cout << "Insert first name:";
            getline(cin, newacc.s_firstName);  // Use a separate variable for the first name
            rgMenu.setValue(1, newacc.s_firstName);
            break;
        case 3:
            cout << "Insert last name:";
            getline(cin, newacc.s_lastName);  // Use a separate variable for the last name
            rgMenu.setValue(2, newacc.s_lastName);
            break;
        case 4:
            cout << "Insert email:";
            cin >> newacc.s_email;
            rgMenu.setValue(3, newacc.s_email);
            break;
        case 5:
            cout << "Insert password:";
            cin >> tmpinput;
            if (tmpinput.length() < 6) {
                cout << "Password must be at least 6 characters long";
                _getch();
            }
            else {
                newacc.s_password = tmpinput;
                rgMenu.setValue(4, newacc.s_password);
                /*newacc.s_password = staff::getMaskedInput("");
                rgMenu.setValue(4, std::string(suser.s_password.length(), '*'));*/
            }
            break;
        case 6:
            cout << "Insert phone no:";
            getline(cin, newacc.s_phoneNo);
            rgMenu.setValue(5, newacc.s_phoneNo);
            break;
        case 7:
            cout << "Insert address:";
            getline(cin, newacc.s_address);
            rgMenu.setValue(6, newacc.s_address);
            break;
        case 8:
            valid = true;
            newacc.insert();
            cout << "Registered";
            _getch();
            break;  // Add this break statement
        case 9:
            return;

        default:
            break;
        }
    }
}

void Loginstaff() {
    Menu loginMenu;
    loginMenu.header = "\t\t======================== Staff Login ========================\n";
    loginMenu.addOption("username");
    loginMenu.addOption("password");
    loginMenu.addOption("Login");
    loginMenu.addOption("Back");
    loginMenu.footer = "\t\tFill in the details, then press Enter after each input.\n\t\tEnter '4' to go back.";

    staff suser;

    while (1) {
        switch (loginMenu.prompt())
        {
        case 1:
            cout << "Insert username:";
            cin >> suser.s_username;
            loginMenu.setValue(0, suser.s_username);
            break;
        case 2:
            cout << "Insert Password:";
            suser.s_password = staff::getMaskedInput("");
            loginMenu.setValue(1, std::string(suser.s_password.length(), '*'));
           /* cin >> suser.s_password;
            loginMenu.setValue(1, suser.s_password);*/
            break;
        case 3:
            if (suser.Login()) {
                sthome(suser);
            }
            else {
                cout << "Invalid Login";
                _getch();
            }
            break;
        case 4:
            staffPage();
            break;
        }
    }
}

void sthome(staff suser) 
{
    ArrowMenu sthomeMenu;
    sthomeMenu.header = "\t\t\t\t Welcome " + suser.s_username;
    sthomeMenu.addOption("Staff Profile");
    sthomeMenu.addOption("Rental");
    sthomeMenu.addOption("Manage Customer");
    sthomeMenu.addOption("Reservation");
    sthomeMenu.addOption("Logout\n");

    sthomeMenu.footer = "\t\tUse Up / Down key to move selection and press enter to select\n\t\tPress Escape to go back";

    customer cuser;
    rental ruser;
    reservation reuser;
    payment pays;
    vehicle vehicles;

    while (1) {
         
         sthomeMenu.header = "\n =============== Welcome " + suser.s_username + " ( Your ID: " + std::to_string(suser.staffId) + ")==========================";

        switch (sthomeMenu.prompt())
        {
        case -1:
            return;
            break;
        case 0:
            suser = stfprofile(suser);
            break;
        case 1:
           Rental(pays, ruser,  cuser,suser ,reuser ,vehicles);
           break;
        case 2:
            custmanage(cuser);
            break;
        case 3:
            rentReservation( pays,  ruser,  reuser,  vehicles);
            break;
        case 4:
            Loginstaff();
            
            break;
        default:
            break;
        }
    }
    
}

staff stfprofile(staff suser)
{
    staff temp = suser; // copy the object
    Menu stprofileMenu;
    stprofileMenu.header = "\t\t -------------------- Your profile -----------------------\n";
    stprofileMenu.addOption("username");
    stprofileMenu.addOption("password");
    stprofileMenu.addOption("email");
    stprofileMenu.addOption("phone no");
    stprofileMenu.addOption("address");
    stprofileMenu.addOption("Reset");
    stprofileMenu.addOption("Save");
    stprofileMenu.addOption("Back");
    stprofileMenu.footer = "\t\tFill in the details, then press Enter after each input.\n\t\tEnter '8' to go back.";
  

    string tmpInput;
    while (1)
    {
        stprofileMenu.setValue(0, temp.s_username);
        stprofileMenu.setValue(1, temp.s_password);
        stprofileMenu.setValue(2, temp.s_email);
        stprofileMenu.setValue(3, temp.s_phoneNo);
        stprofileMenu.setValue(4, temp.s_address);



        switch (stprofileMenu.prompt())
        {
        case 1:
            cout << "Insert username:";
            cin >> temp.s_username;
            break;
        case 2:
            cout << "Insert password:";
            cin >> temp.s_password;
            break;
        case 3:
            cout << "Insert email:";
            cin >> temp.s_email;
            break;
        case 4:
            cout << "Insert s_phoneNo:";
            getline(cin, temp.s_phoneNo);
            break;
        case 5:
            cout << "Insert s_address:";
            getline(cin, temp.s_address);
            break;
        case 6:
            temp = suser;
            break;
        case 7:
            suser = temp;
            suser.update();
            cout << "Updated";
            _getch();
            break;
        case 8:
            return suser;
            break;
       
        default:
            break;
        }

    }
}

void stmanage(staff suser)
    {
        ArrowMenu stmanageMenu;
        stmanageMenu.header = "\t\t ====================== MANAGE STAFF =========================\n";

        stmanageMenu.addOption("register staff");
        stmanageMenu.addOption("staff info");
        stmanageMenu.addOption("back\n");

        stmanageMenu.footer = "\t\tUse Up / Down key to move selection and press enter to select\n\t\tPress Escape to go back";

        admin(auser);

        while (1) {
            switch (stmanageMenu.prompt())
            {
            case -1:
                return ;
                break;
            case 0:
                Registerstaff();
                break;
            case 1:
                staffInfo(suser);
                break;
            case 2:
                adhome(auser);
                
                break;
            default:
                break;
            }
        }
    }

void staffInfo(staff suser) 
    {
        // Function implementation
        staff temp = suser;
        ArrowMenu viewMenu;
        viewMenu.header = "\t\t -------------------- Staff Information -----------------------\n";
        viewMenu.addOption("View All Staff");
        viewMenu.addOption("Delete Staff");
        viewMenu.addOption("logout\n");

        viewMenu.footer = "\t\tUse Up / Down key to move selection and press enter to select\n\t\tPress Escape to go back";

        string tmpInput, sql;

        while (1) {
            switch (viewMenu.prompt()) {
            case -1:
                return;
                break;
            case 0:
                ViewAllStaff();
                break;
            case 1:
                DeleteStaff(suser);
                break;
            case 2:
                main();
                break;
            default:
                break;
            }
        }
    }

void ViewAllStaff()
    {
        vector<staff> staffs;
        staff sels;
        string dispS = "";
    
        int staffId=0;
        string user = "", s_firstName = "", s_lastName = "", s_email="" , s_phoneNo ="", s_address="";
        bool asc = true;
    
        ArrowMenu sList;
        sList.header = "Search Staff : ";
        sList.addOption("username");
        sList.addOption("s_firstName");
        sList.addOption("s_lastName");
        sList.addOption("sorting");
        sList.addOption("search");
        sList.addOption("back  ");
        sList.footer = "\t\tFill in the details, then press Enter after each input.\n\t\tEnter '6' to go back.";
    
    
        while (1)
        {
            if (asc)
            {
                sList.setValue(3, "Ascending");
            }
            else
            {
                sList.setValue(3, "Descending");
            }
    
    
            if (dispS == "")
            {
                dispS = "\nResult:\n\n";
                stringstream tmpS;
                tmpS << setw(4) << "ID" << "|" << setw(15) << "Username" << "|" << setw(10) << "First Name" << "|" << setw(10) << "Last Name" << "|" 
                    << setw(20) << "Email" << "|" << setw(10) << "Phone No" << "|" << setw(20) << "Address" << "|" << endl;
                
                for (int i = 0; i < staffs.size(); i++)
                {
                    tmpS << setw(4) << staffs[i].staffId << "|" << setw(15) << staffs[i].s_username << "|" << setw(10) << staffs[i].s_firstName << "|" << setw(10) << staffs[i].s_lastName << "|" << setw(20) << staffs[i].s_email << "|" 
                        << setw(10) << staffs[i].s_phoneNo << "|" << setw(20) << staffs[i].s_address << "|" << endl;
                }
                dispS += tmpS.str();
             }
            sList.footer = dispS;

            
            switch (sList.prompt())
            {
            case -1:
                return;
                break;
            case 0:
                cout << "\nInsert Username : ";
                getline (cin, user ) ;
                 sList.setValue(0, user ) ;
                break;

            case 1:
                cout << "Insert First Name : ";
                getline(cin, s_firstName);
                sList.setValue(1, s_firstName );
                break;

            case 2:
                cout << "Insert Last Name : ";
                getline(cin, s_lastName);
                sList.setValue(2, s_lastName);
                break;

            case 3:
                asc = !asc;
                break;

            case 4:
                staffs = staff::findStaff(user , s_firstName ,s_lastName  , asc);
                dispS = "";
                break;
            case 5:
                return;


            }
        }
       
    
    
    }
    
staff DeleteStaff(staff suser)
    {
        staff temp = suser;
        Menu stDelete;
        system("cls");
        stDelete.header = "\n\n\t -------------------------------------------------- DELETE STAFF MENU ---------------------------------------------- \n\n";
        stDelete.addOption("Staff ID : ");
        stDelete.addOption("Back");
        stDelete.footer = "\t\tFill in the details, then press Enter after each input.\n\t\tEnter '2' to go back.";
       
        char confirm;
        string tmpInput;
        stringstream ss;

          while (1)
          {
              switch (stDelete.prompt()) 
              {
              case 1:
                  cout << "Insert Staff ID:";
                  cin >> temp.staffId;  // Use a separate variable for the first name
                  stDelete.setValue(0, to_string(temp.staffId));

                  suser.staffId == temp.staffId;
                  
                    suser = temp;
                    _getch();

                    cout << "\n\n\t Are you sure want to delete staff account ? (y/n)";
                    confirm = _getch();
                    if (confirm == 'Y' || confirm == 'y')
                    {
                        suser = temp;
                        suser.remove();
                        cout << "\n\n\t Staff account deleted.";
                        _getch();
                    }
                    else
                    {
                        cout << "\n\n\t Staff account saved.";
                    }
                    system("cls");
                    break;
              case 2:
                  return suser;
                  system("cls");
                  break;
              default:
                  break;
               }
           }

    }
       
    


       // customer
void custmanage(customer cuser)
    {
        ArrowMenu cmanageMenu;
        cmanageMenu.header = "\t\t ====================== MANAGE CUSTOMER =========================\n";

        cmanageMenu.addOption("register customer");
        cmanageMenu.addOption("view customer");
        cmanageMenu.addOption("delete customer");
        cmanageMenu.addOption("back");

        cmanageMenu.footer = "\t\tUse Up / Down key to move selection and press enter to select\n\t\tPress Escape to go back";

        staff suser;
        while (1) {
            switch (cmanageMenu.prompt())
            {
            case -1:
                return;
                break;
            case 0:
                Registercust();
                break;
            case 1:
                ViewAllCust();// Add code for view customer
                break;
            case 2:
                DeleteCustomer( cuser);// Add code for delete customer
                break;
            case 3:
                sthome(suser);
                break;
            default:
                break;
            }
        }
    }

void Registercust()
    {
        customer newacc;

        Menu rgMenu;
        rgMenu.header = "\t\t ================= Customer Registration =========================\n";


        rgMenu.addOption("First Name");  // Change the label to "First Name"
        rgMenu.addOption("Last Name");
        rgMenu.addOption("Gender");// Add an option for the last name
        rgMenu.addOption("Address");
        rgMenu.addOption("Phone No");
        rgMenu.addOption("Register");
        rgMenu.addOption("Back\n");

        rgMenu.footer = "\t\tFill in the details, then press Enter after each input.\n\t\tEnter '7' to go back.";

        customer cuser;
        string tmpinput;
        bool valid = true;
        while (1) {
            switch (rgMenu.prompt()) {


            case 1:
                cout << "Insert first name:";
                getline(cin, newacc.c_firstName);  // Use a separate variable for the first name
                rgMenu.setValue(0, newacc.c_firstName);
                break;
            case 2:
                cout << "Insert last name:";
                getline(cin, newacc.c_lastName);// Use a separate variable for the last name
                rgMenu.setValue(1, newacc.c_lastName);
                break;
            case 3:
                cout << "Insert gender:";
                getline(cin, newacc.c_gender);  // Use getline to read the entire line
                rgMenu.setValue(2, newacc.c_gender);
                break;

            case 4:
                cout << "Insert address:";
                getline(cin, newacc.c_address);
                rgMenu.setValue(3, newacc.c_address);
                break;
                // Inside the case 5 block:
            case 5:
                cout << "Insert phone no:";
                getline(cin, newacc.c_phoneNo);

                rgMenu.setValue(4, newacc.c_phoneNo);
                break;

            case 6:
                valid = true;
                newacc.insert();
                cout << "Registered";
                _getch();
                break;  // Add this break statement
            case 7:
                custmanage(cuser);
            default:
                break;
            }
        }
    }

void ViewAllCust()
    {
        vector<customer> customers;
        customer selC;
        string dispC = "";

        int custId = 0;
        string c_firstName = "", c_lastName = "", c_gender = "";
        bool asc = true;

        Menu cList;
        cList.header = "Search customer : ";
        cList.addOption("First Name");
        cList.addOption("Last Name");
        cList.addOption("Gender");
        cList.addOption("sorting");
        cList.addOption("search");
        cList.addOption("back");

        cList.footer = "\t\tFill in the details, then press Enter after each input.\n\t\tEnter '6' to go back.";



        while (1)
        {
            if (asc)
            {
                cList.setValue(3, "Ascending");
            }
            else
            {
                cList.setValue(3, "Descending");
            }


            if (dispC== "")
            {
                dispC = "\nResult:\n\n";
                stringstream tmpC;
                tmpC << setw(4) << "ID" << "|" << setw(20) << "First Name" << "|" << setw(20) << "Last Name" << "|" << setw(10) << "Gender" << "|" << endl;

                for (int i = 0; i < customers.size(); i++)
                {
                    tmpC << setw(4) << customers[i].custId << "|" << setw(20) << customers[i].c_firstName << "|" << setw(20) << customers[i]. c_lastName << "|" << setw(10) << customers[i].c_gender << "|" << endl;
                }
                dispC += tmpC.str();
            }
            cList.footer = dispC;


            switch (cList.prompt())
            {
            case 1:
                cout << "\nInsert First Name : ";
                getline(cin, c_firstName );
                cList.setValue(0, c_firstName);
                break;

            case 2:
                cout << "Insert Last Name : ";
                getline(cin, c_lastName);
                cList.setValue(1, c_lastName);
                break;
            case 3:
                cout << "Insert Gender : ";
                getline(cin, c_gender);
                cList.setValue(2, c_gender);
                break;

            case 4:
                asc = !asc;
                break;

            case 5:
                customers = customer::findCustomer(c_firstName, c_lastName, c_gender, asc);
                dispC = "";
                break;
            case 6:
                return;


            }
        }


    }

customer DeleteCustomer(customer cuser)
    {
        customer temp = cuser;
        Menu cuDelete;
        system("cls");
        cuDelete.header = "\n\n\t -------------------------------------------------- DELETE STAFF MENU ---------------------------------------------- \n\n";
        cuDelete.addOption("Staff ID : ");
        cuDelete.addOption("Back");

        cuDelete.footer = "\t\tFill in the details, then press Enter after each input.\n\t\tEnter '2' to go back.";

        char confirm;
        string tmpInput;
        stringstream ss;

        while (1)
        {
            switch (cuDelete.prompt())
            {
            case 1:
                cout << "Insert Customer ID:";
                cin >> temp.custId;  // Use a separate variable for the first name
                cuDelete.setValue(0, to_string(temp.custId));

                cuser.custId == temp.custId;

                cuser = temp;
                _getch();

                cout << "\n\n\t Are you sure want to delete customer account ? (y/n)";
                confirm = _getch();
                if (confirm == 'Y' || confirm == 'y')
                {
                    cuser = temp;
                    cuser.remove();
                    cout << "\n\n\t Customer account deleted.";
                    _getch();
                }
                else
                {
                    cout << "\n\n\t Customer account saved.";
                }
                system("cls");
                break;
            case 2:
                return cuser;
                system("cls");
                break;
            default:
                break;
            }
        }
    }



    //rental 

void Rental(payment pays, rental ruser, customer cuser, staff suser, reservation reuser, vehicle vehicles) {
        ArrowMenu rMenu;
        rMenu.header = "\n\t\t========================= RENTAL PAGE ============================\n "  ;
        rMenu.addOption("insert rental");
        rMenu.addOption("update rental");
        rMenu.addOption("delete rental");
        rMenu.addOption("view rental");
        rMenu.addOption("Back");

        rMenu.footer = " \t\tUse Up / Down key to move selection and press enter to select\n\t\tPress Escape to go back";

              
            while (true) {
                         
            int choice = rMenu.prompt();
            switch (choice) {
            case -1 :
                return;
                break;
            case 0:
                InsertRental( ruser,  cuser, suser);
                break;
            case 1:
                
                _getch();
                //UpdateRental();
                break;
            case 2:
                //DeleteRental();
                break;
            case 3:
                ViewAllRental(pays, ruser, cuser, suser, reuser, vehicles);
                break;
            case 4:
                sthome(suser);
                break;
            default:
                break;
            }
        }

    	
    }

void InsertRental(rental ruser , customer cuser , staff suser)
    {

        rental temp = ruser;
        temp.custId = cuser.custId;
        temp.staffId = suser.staffId;
        ArrowMenu Radd;
        string tmpInput;


        Radd.header = "\n\t\t========================= INSERT RENTAL PAGE ============================\n";
        Radd.addOption("custId");
        Radd.addOption("rentalDate");
        Radd.addOption("save");
        Radd.addOption("return"); 

        Radd.footer = "\t\tUse Up / Down key to move selection and press enter to select\n\t\tPress Escape to go back";


        bool valid = true;
        while (1) {
            
            switch (Radd.prompt()) 
            {
            case -1:
                return;
                break;
            case 0:
                cout << " Cust ID :";
                cin >> temp.custId;
                Radd.setValue(0, to_string(temp.custId));
                break;

            case 1:
                while (true) {

                    cout << "Rental date (YYYY-MM-DD) :";
                    cin.ignore();
                    getline(cin,temp.rentalDate);
                    if (validateDate(temp.rentalDate))
                    {
                        break;
                    }
                    else
                    {
                        cout << "\n\t\t\t\t\tInvalid date format. Please use YYYY-MM-DD.\n";
                    }
                }
                Radd.setValue(1, temp.rentalDate);
                break;
            
            case 2 :
                valid = true;
                temp = temp;
                temp.InsertRental();
                cout << " rental entry for rental " << temp.rentalId << " added successfully!" << endl;
                _getch();
                break;

            case 3:

                return;
            default:
                break;
            }
        }


    }

void ViewAllRental(payment pays, rental ruser , customer cuser, staff suser, reservation reuser, vehicle vehicles)
{
    vector<rental> rentals;
    string dispR = "";

    rental temp = ruser;
    temp.custId = cuser.custId;
    temp.staffId = suser.staffId;
    int rentalId = 0, custId = 0, staffId = 0 ;
    string rentalDate = "", status = "";
    bool asc = true;

    Menu rList;
    rList.header = "Search rental : ";
    rList.addOption("rental date");
    rList.addOption("status");
    rList.addOption("sorting");
    rList.addOption("search");
    rList.addOption("back");

    rList.footer = "\t\tFill in the details, then press Enter after each input.\n\t\tEnter '5' to go back.";


    while (1)
    {
        if (asc)
        {
            rList.setValue(2, "Ascending");
        }
        else
        {
            rList.setValue(2, "Descending");
        }


        if (dispR == "")
        {
            dispR = "\nResult:\n\n";
            stringstream tmpR;
            tmpR << setw(10) << "Rental ID" << "|" << setw(10) << "Cust ID" << "|" << setw(10) << " Staff ID" << "|" << setw(20) << " Rental Date " << "|" << endl;

            for (int i = 0; i < rentals.size(); i++)
            {
                tmpR << setw(10) << rentals[i].rentalId << "|" << setw(10) << rentals[i].custId << "|" << setw(10) << rentals[i].staffId << "|" << setw(20) << rentals[i].rentalDate << "|" << endl;
            }
            dispR += tmpR.str();
        }
        rList.footer = dispR;


        switch (rList.prompt())
        {
        case 1:
            cout << "\nInsert Rental Date : ";

            getline(cin, rentalDate);
            rList.setValue(0, rentalDate);
            break;

        case 2:
            cout << "Insert Status : ";
            getline(cin, status);
            rList.setValue(1, status);
            break;
  
        case 3:
            asc = !asc;
            break;

        case 4:
            rentals = rental::findRental(rentalDate, asc);
            dispR = "";
            break;
        case 5:
            rentReservation(pays, ruser, reuser, vehicles);
        }
    }
}
    
    //vehicle

void vehiclePage()
    {
        ArrowMenu vMenu;
        vMenu.header = "\t\t====================== Vehicle Page ========================\n";
        vMenu.addOption("insert vehicle");
        vMenu.addOption("update vehicle"); 
        vMenu.addOption("delete vehicle");
        vMenu.addOption("display vehicle");
        vMenu.addOption("Back");

        vMenu.footer = " \t\tUse Up / Down key to move selection and press enter to select\n\t\tPress Escape to go back";

        admin auser;
        vehicle vehicles;
        string tmpinput;
        bool valid = true;
        while (1) {
            switch (vMenu.prompt()) {

            case -1:
                return;
                break;
            case 0:
                InsertVehicle (vehicles);
            case 1:
                UpdateVehicle();
            case 2:
                DeleteVehicle(vehicles);
            case 3:
                ViewAllVehicle();
            case 4:
                adhome(auser);
                break;

            default:
                break;
            }
        }
    }
 
vehicle InsertVehicle(vehicle vehicles)
    {
        vehicle newVehicle;
        Menu insertMenu;

        insertMenu.header = "\n\n\t========================= Insert Vehicle Page ============================\n\n";
        insertMenu.addOption("Vehicle Type: ");
        insertMenu.addOption("No Plate: ");
        insertMenu.addOption("Model");
        insertMenu.addOption("Year:");
        insertMenu.addOption("Availibility:");
        insertMenu.addOption("Vehicle Rate:");
        insertMenu.addOption("Save");
        insertMenu.addOption("return");
        insertMenu.footer = "\t\tFill in the details, then press Enter after each input.\n\t\tEnter '8' to go back.";


        bool valid = true;
        while (1) {

            switch (insertMenu.prompt())
            {
            case 1:
                cout << "Vehicle Type :";
                getline (cin, newVehicle.vehicleType);
                insertMenu.setValue(0, newVehicle.vehicleType);
                break;
            case 2:
                cout << "No Plate :";
                getline (cin, newVehicle .noPlate);
                insertMenu.setValue(1, newVehicle.noPlate);
                break;
            case 3:
                cout << "Model :";
                getline (cin, newVehicle.model);
                insertMenu.setValue(2, newVehicle.model);
                break;
            case 4:
                cout << " Year :";
                getline (cin, newVehicle.year);
                insertMenu.setValue(3, newVehicle.year);
                break;
          
            case 5:
                cout << " Vehicle Rate :";
                cin >> newVehicle.vehicleRate;
                insertMenu.setValue(4,to_string( newVehicle.vehicleRate));
                break;

            case 6:
                valid = true;
                newVehicle.InsertVehicle();
                cout << " vehicle entry for car " << " added successfully!" << endl;
                _getch();
                break;

            case 8:
                return vehicles ;
            default:
                break;
            }
        }

    }

void ViewAllVehicle()
    {
        vector<vehicle> vehicles;
        string dispV = "";

        int vehicleId = 0 , vehicleRate = 0;
        string vehicleType = "", model = "" , noPlate = "";
        bool asc = true;

        Menu vList;
        vList.header = "Search vehicle : ";
        vList.addOption("vehicle Type");
        vList.addOption("noPlate");
        vList.addOption("model");
        vList.addOption("sorting");
        vList.addOption("search");
        vList.addOption("back");

        vList.footer = "\t\tFill in the details, then press Enter after each input.\n\t\tEnter '6' to go back.";


        while (1)
        {
            if (asc)
            {
                vList.setValue(3, "Ascending");
            }
            else
            {
                vList.setValue(3, "Descending");
            }


            if (dispV == "")
            {
                dispV = "\nResult:\n\n";
                stringstream tmpV;
                tmpV << setw(4) << "ID" << "|" << setw(15) << " Vehicle Type " << "|" << setw(10) << "No Plate" << "|" << setw(15) << "Model" << "|" << setw(15) << "Vehicle Rate" << "|" << endl;

                for (int i = 0; i < vehicles.size(); i++)
                {
                    tmpV << setw(4) << vehicles[i].vehicleId << "|" << setw(15) << vehicles[i].vehicleType << "|" << setw(10) << vehicles[i].noPlate << "|" << setw(15) << vehicles[i].model << "|" << setw(15) << vehicles[i].vehicleRate << "|" << endl;
                }
                dispV += tmpV.str();
            }
            vList.footer = dispV;


            switch (vList.prompt())
            {
            case 1:
                cout << "\nInsert Vehicle Type : ";
                getline(cin, vehicleType);
                vList.setValue(0, vehicleType);
                break;

            case 2:
                cout << "Insert No Plate : ";
                getline(cin, noPlate);
                vList.setValue(1, noPlate);
                break;
            case 3:
                cout << "Insert Model : ";
                getline(cin, model);
                vList.setValue(2, model);
                break;

            case 4:
                asc = !asc;
                break;

            case 5:
                vehicles = vehicle::findVehicle( vehicleType, noPlate , model , asc);
                dispV = "";
                break;
            case 6:
                return;


            }
        }


    }

void UpdateVehicle()
{

}
 
vehicle DeleteVehicle(vehicle vehicles)
{
    vehicle temp = vehicles;
    Menu veDelete;
    system("cls");
    veDelete.header = "\n\n\t -------------------------------------------------- DELETE VEHICLE MENU ---------------------------------------------- \n\n";
    veDelete.addOption("Vehicle ID : ");
    veDelete.addOption("Back");

    veDelete.footer = "\t\tFill in the details, then press Enter after each input.\n\t\tEnter '2' to go back.";

    char confirm;
    string tmpInput;
    stringstream ss;

    while (1)
    {
        switch (veDelete.prompt())
        {
        case 1:
            cout << "Insert vehicle ID:";
            cin >> temp.vehicleId;  // Use a separate variable for the first name
            veDelete.setValue(0, to_string(temp.vehicleId));

            vehicles.vehicleId == temp.vehicleId;

            vehicles = temp;
            _getch();

            cout << "\n\n\t Are you sure want to delete vehicle ? (y/n)";
            confirm = _getch();
            if (confirm == 'Y' || confirm == 'y')
            {
                vehicles = temp;
                vehicles.remove();
                cout << "\n\n\t Vehicle deleted.";
                _getch();
            }
            else
            {
                cout << "\n\n\t Vehicle saved.";
            }
            system("cls");
            break;
        case 2:
            return vehicles;
            system("cls");
            break;
        default:
            break;
        }
    }
}


// payment
payment rentReservation(payment pays , rental ruser, reservation reuser ,vehicle vehicles)
{
    
    payment temp = pays,pay;
    int paymentId = 0, rentalId = 0, vehicleId = 0, ID, value;
    vehicle vehi;
    reservation reserve;
    string displayString = " ", payment_Date = "";
    temp.rentalId = ruser.rentalId;

    Menu rentMenu;
    rentMenu.header = "Rental Reservation";
    rentMenu.addOption("View All Rental");
    rentMenu.addOption(" Enter Rental ID");
    rentMenu.addOption(" Enter Vehicle ID");
    rentMenu.addOption(" Set Start Date (yyyy-mm-dd)");
    rentMenu.addOption(" Set End Date (yyyy-mm-dd)");
    rentMenu.addOption(" Set No.Day");
    rentMenu.addOption(" Reserve");
    rentMenu.addOption(" Proceed to Payment");
    rentMenu.addOption(" Back");

    rentMenu.footer = "\t\tFill in the details, then press Enter after each input.\n\t\tEnter '9' to go back.";

    bool valid = true;
    char confirm;

    customer cuser;
    staff suser;
    while (1)
    {
        
        switch (rentMenu.prompt())
        {
        case 1:
            ViewAllRental(pays, ruser, cuser, suser, reuser, vehicles);
        case 2:
            cout << "Enter Rental ID: ";
            cin >> reserve.rentalId;
            rentMenu.setValue(1, to_string(reserve.rentalId));
            break;
        case 3:
            cout << "Enter Vehicle ID: ";
            cin >> reserve.vehicleId;
            rentMenu.setValue(2, to_string(reserve.vehicleId));
            break;
        case 4:
            cout << "Set start date (yyyy-mm-dd): ";
            cin >> reserve.startDate;
            rentMenu.setValue(3, reserve.startDate);
            break;
        case 5:
            cout << "Set end date (yyyy-mm-dd): ";
            cin >> reserve.endDate;
            rentMenu.setValue(4, reserve.endDate);
            break;
        case 6:
            cout << "Set No.Day : ";
            cin >> reserve.noPerday;
            rentMenu.setValue(5, to_string(reserve.noPerday));
            break;

        case 7:
            cout << "Proceed reservation? (y/n): ";
            confirm = _getch();
            if (confirm == 'Y' || confirm == 'y') {
                // Validate vehicleId
                if (reserve.vehicleId <= 0) {
                    cout << "Error: Invalid vehicle ID. Please enter a valid positive integer for the vehicle ID." << endl;
                    _getch();
                    break;  // Exit the case to prevent further processing
                }

                // Validate start date
                if (reserve.startDate.empty()) {
                    cout << "Error: Start date cannot be empty. Please enter a valid start date (yyyy-mm-dd)." << endl;
                    _getch();
                    break;  // Exit the case to prevent further processing
                }

                // Check for existing reservation on the specified start date
                if (reservationExists(reserve.vehicleId, reserve.startDate)) {
                    cout << "Error: Vehicle is already booked on the specified start date." << endl;
                    cout << "Reservation not allowed." << endl;
                    _getch();
                    break;  // Exit the case to prevent further processing
                }

                // Proceed with reservation insertion
                reserve.insert();
                cout << "\Reservation successfully saved.";
                _getch();
            }
            else {
                cout << "\Reservation cancelled. ";
                _getch();
            }
            break;

        case 8:

            int value;
            vehi = vehicle::selectVehicle(reserve.vehicleId);

            value = vehi.vehicleRate * reserve.noPerday;

            pay.rentalId = reserve.rentalId;
            pay.value = value;
            
            pay.insert();

            paymentTrans(reserve.rentalId, ruser, reserve, vehicles);
            break;

        case 9:
            sthome(suser);
            break;
        case 10:
            exit(0);
        }
    }
}

void paymentTrans(int rentalId, rental ruser, reservation reuser , vehicle vehicles )
{
    Menu transMenu;
    vehicle vehi;
    transMenu.header = "Payment Transaction ";
    payment pay;
    vector<report> rep;
    
    int value;
    vehi = vehicle::selectVehicle(reuser.vehicleId);

    value = vehi.vehicleRate * reuser.noPerday;

    system("cls");
    // Display reservation details
    cout << "\n\t\t Your reservation details:  " << " \nTotal Payment: " << value << endl;
    cout << rentalId;
    _getch();

      
    // Display calculation details
    cout << "\n\nnoPerday = " << reuser.noPerday << ", vehicleRate = " << vehi.vehicleRate << endl;
    cout << "Total payment = " << value << endl; 

    // Confirm payment with the user
    cout << "\t\t\t\t\t\n\nYour total payment is RM " << value <<
        "\n\t\t\t\t\tDo you want to continue with the payment? (y/n)";

    char confirm;
    confirm = _getch();
    if (confirm == 'Y' || confirm == 'y')
    {
        pay.rentalId = reuser.rentalId;
        pay.value = value;
        // Assuming reserve.insert() should be done here
        cout << "\n\t\t\t\t\tYour payment is successful!";
        cout << "\n\t\t\t\t\tPress Enter to continue...";  // Prompt for Enter key
    }
    else
    {
        cout << "Payment Cancelled.";
    }
    _getch();
    
}

    
void SaleReportMenu(admin auser ) {

   

        string startDate, endDate;

        bool sortByDate = true, ascending = true;

        Menu saleMenu;
        saleMenu.addOption("Press 1 to Enter Start Date");
        saleMenu.addOption("Press 2 to Enter End Date");
        saleMenu.addOption("Press 3 to Choose Sort By Option");
        saleMenu.setValue(2, "Date");
        saleMenu.addOption("Press 4 to Choose Ordering");
        saleMenu.setValue(3, "Ascending");
        saleMenu.addOption("Press 5 to Generate Report");
        saleMenu.addOption("Press 6 to Back to Home");

        vector<sale> result; // vector to store the result

        vector<int>::iterator iterator; //iterator is declare using what we are iterating, in this case it is vector of integer

        while (1)
        {
            stringstream ss;
            // construct our report header
            ss << endl << "\n\t\t\t\t\t--------------- SALES REPORT -------------- \n" << endl
                << "\t\t\t\t\t+---------------------+--------------------+" << endl << "\t\t\t\t\t|" << setw(20) << "Date" << " |";

            ss << setw(20) << "Sale" << "|" << endl << "\t\t\t\t\t|---------------------+--------------------|";

            double totalSale = 0;
            // repeat same structure for content of the report
            for (int i = 0; i < result.size(); i++)
            {
                ss << endl << "\t\t\t\t\t|" << setw(20) << result[i].date.substr(0, 7) << "|";

                ss << setw(20) << result[i].value << "|";
                totalSale += result[i].value;

            }

            ss << endl << "\t\t\t\t\t|" << setw(20) << "Total Sale" << " | ";

            ss << setw(19) << totalSale << "|" << endl << "\t\t\t\t\t+---------------------+--------------------+";

            ss << endl << "\n\t\t\t\t\t-------------- END OF REPORT --------------" << endl;
            saleMenu.header = ss.str();


            switch (saleMenu.prompt())
            {
            case 1:
                cout << "\t\t\t\t\tInsert Start Date (YYYY-MM-DD): ";
                cin >> startDate;
                saleMenu.setValue(0, startDate);
                break;
            case 2:
                cout << "\t\t\t\t\tInsert End Date (YYYY-MM-DD): ";
                cin >> endDate;
                saleMenu.setValue(1, endDate);
                break;
            case 3:   // sort by
                sortByDate = !sortByDate;
                if (sortByDate)
                    saleMenu.setValue(2, "Date");
                else
                    saleMenu.setValue(2, "Price");
                break;
            case 4:
                ascending = !ascending;
                if (ascending)
                    saleMenu.setValue(3, "Ascending");
                else
                    saleMenu.setValue(3, "Descending");
                break;
            case 5:
                result.clear();
                result = sale::salesReport(startDate, endDate, sortByDate, ascending);
                break;
            case 6:
                return;
                break;
            }
        }
    
}

bool validateDate(const std::string& date) {
    // Define a regex pattern for YYYY-MM-DD format
    std::regex dateRegex(R"(\d{4}-\d{2}-\d{2})");

    // Check if the date matches the format
    return std::regex_match(date, dateRegex);
}