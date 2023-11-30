#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ios> 
#include <limits> 
using namespace std;

#include "global.h"
#include "hospital.h"
#include "address.h"
#include "person.h"
#include "appointment.h"
#include "patient.h"
#include "doctor.h"
#include "nurse.h"
#include "driver.h"
#include "ambulance.h"

void appointmentsMenu();
void patientsMenu();
void doctorsMenu();
void nursesMenu();
void driversMenu();
void ambulancesMenu();

void appointmentsMenu()
{
	int active = 1;
	while (active == 1)
	{
        int choice = 0;
        cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "\nSelect an option:\n\n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "./HOME/APPOINTMENTS\n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "[01] : Book an appointment\n";
        cout << "[02] : Get appointment details\n";
        cout << "[03] : Show all appointments\n\n";
        cout << "[-1] : Back\n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
            case 1:
            {
                appointment a;
                a.book();
                break;
            }
            case 2:
            {
                appointment a;
                a.getDetails();
                a.printDetails();
                break;
            }
            case 3:
            {
                hospital::printAppointments();
                break;
            }
            case -1:
            {
                active = 0;
                break;
            }
        }
        if (choice != 1 and choice != 2 and choice != 3 and choice != -1)
        {
            cout << "Wrong Choice!" << endl;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clearing cin buffer;

        cout << endl;
        cout << "\nPress ENTER to continue...\n";
        cout << endl;

        getchar();
	}
}

void patientsMenu()
{
    bool exit = false;
    while (!exit)
    {
        int purpose = 0;
        cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "\nSelect an option:\n\n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "./HOME/PATIENTS\n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "[01] : Register a new patient\n";
        cout << "[02] : Get patient details\n";
        cout << "[03] : Hospitalize a registered patient\n";
        cout << "[04] : Report a patient's death\n";
        cout << "[05] : Discharge a patient or their body\n";
        cout << "[06] : Get details of all registered patients\n\n";
        cout << "[-1] : Back\n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
        cout << "Enter your choice: ";
        cin >> purpose;
        switch (purpose)
        {
            case 1:
            {
                patient p;
                p.addPerson();
                break;
            }
            case 2:
            {
                patient p;
                p.getDetails(1);
                p.printDetails();
                break;
            }
            case 3:
            {
                patient p;
                p.hospitalize();
                break;
            }
            case 4:
            {
                patient p;
                p.reportADeath();
                break;
            }
            case 5:
            {
                patient p;
                p.removePerson();
                break;
            }
            case 6:
            {
                hospital::printPatients();
                break;
            }
            case -1:
            {
                exit = true;
                break;
            }
            default:
            {
                cout << "Invalid choice!\n";
                break;
            }
        }
        
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clearing cin buffer;
        cout << endl;
        cout << "\nPress ENTER to continue...\n";
        cout << endl;
        getchar();
    }
    return;
}

void doctorsMenu()
{
    bool exit = false;
    while (!exit)
    {
        int purpose = 0;
        cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "\nSelect an option:\n\n";

        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "./HOME/DOCTORS\n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "[01] : Register a new doctor\n";
        cout << "[02] : Get doctor details\n";
        cout << "[03] : Remove a doctor\n";
        cout << "[04] : Get details of all registered doctors\n\n";
        cout << "[-1] : Back\n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
        cout << "Enter your choice: ";
        cin >> purpose;
        switch (purpose)
        {
            case 1:
            {
                doctor d;
                d.addPerson();
                break;
            }
            case 2:
            {
                doctor d;
                d.getDetails(1);
                d.printDetails();
                break;
            }
            case 3:
            {
                doctor d;
                d.removePerson();
                break;
            }
            case 4:
            {
                hospital::printDoctors();
                break;
            }
            case -1:
            {
                exit = true;
                break;
            }
            default:
            {
                cout << "Invalid choice!\n";
                break;
            }
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clearing cin buffer;

        cout << endl;
        cout << "\nPress ENTER to continue...\n";
        cout << endl;

        getchar();
    }
    return;
}

void nursesMenu()
{
    bool exit = false;
    while (!exit)
    {
        int purpose = 0;
        cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "\nSelect an option:\n\n";

        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "./HOME/NURSES\n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "[01] : Register a new nurse\n";
        cout << "[02] : Get nurse details\n";
        cout << "[03] : Remove a nurse\n";
        cout << "[04] : Get details of all registered nurses\n\n";
        cout << "[-1] : Back\n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
        cout << "Enter your choice: ";
        cin >> purpose;
        switch (purpose)
        {
            case 1 :
            {
                nurse n;
                n.addPerson();
                break;
            }
            case 2:
            {
                nurse n;
                n.getDetails(1);
                n.printDetails();
                break;
            }
            case 3:
            {
                nurse n;
                n.removePerson();
                break;
            }
            case 4:
            {
                hospital::printNurses();
                break;
            }
            case -1:
            {
                exit = true;
                break;
            }
            default:
            {
                cout << "Invalid choice!\n";
                break;
            }
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clearing cin buffer;

        cout << endl;
        cout << "\nPress ENTER to continue...\n";
        cout << endl;

        getchar();
    }
    return;
}

void driversMenu()
{
    bool exit = false;
    while (!exit)
    {
        int purpose = 0;
        cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "\nSelect an option:\n\n";

        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "./HOME/DRIVERS\n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "[01] : Register a new driver\n";
        cout << "[02] : Get driver details\n";
        cout << "[03] : Remove a driver\n";
        cout << "[04] : Get details of all registered drivers\n\n";
        cout << "[-1] : Back\n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
        cout << "Enter your choice: ";
        cin >> purpose;
        switch (purpose)
        {
            case 1:
            {
                driver d;
                d.addPerson();
                break;
            }
            case 2:
            {
                driver d;
                d.getDetails(1);
                d.printDetails();
                break;
            }
            case 3:
            {
                driver d;
                d.removePerson();
                break;
            }
            case 4:
            {
                hospital::printDrivers();
                break;
            }
            case -1:
            {
                exit = true;
                break;
            }
            default:
            {
                cout << "Invalid choice!\n";
                break;
            }
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clearing cin buffer;

        cout << endl;
        cout << "\nPress ENTER to continue...\n";
        cout << endl;

        getchar();
    }
    return;
}

void ambulancesMenu()
{
    bool exit = false;
    while (!exit)
    {
        int purpose = 0;
        cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "\nSelect an option:\n\n";

        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "./HOME/AMBULANCES\n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "[01] : Add an ambulance\n";
        cout << "[02] : Send an ambulance\n";
        cout << "[03] : Get ambulance details\n";
        cout << "[04] : Report ambulance arrival\n";
        cout << "[05] : Remove an ambulance\n";
        cout << "[06] : Get details of all registered ambulances\n\n";
        cout << "[-1] : Back\n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
        cout << "Enter your choice: ";
        cin >> purpose;
        switch (purpose)
        {
            case 1:
            {
                ambulance a;
                a.addAmbulance();
                break;
            }
            case 2:
            {
                ambulance a;
                a.send();
                break;
            }
            case 3:
            {
                ambulance a;
                a.getDetails(1);
                a.printDetails();
                break;
            }
            case 4:
            {
                ambulance a;
                a.reportArrival();
                break;
            }
            case 5:
            {
                ambulance a;
                a.removeAmbulance();
                break;
            }
            case 6:
            {
                hospital::printAmbulances();
                break;
            }
            case -1:
            {
                exit = true;
                break;
            }
            default:
            {
                cout << "Invalid choice!\n";
                break;
            }
        }
       
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clearing cin buffer;

        cout << endl;
        cout << "\nPress ENTER to continue...\n";
        cout << endl;

        getchar();
    }
    return;
}

int getDate(string s)
{
    int dd, mm, yyyy;
    if (s != "")
        cout << "\n\n\nLast usage date (DD-MM-YYYY) : " << s.substr(6, 2) + "-" + s.substr(4, 2) + "-" + s.substr(0, 4) + "\n";
    cout << "\nPlease Enter Today's Date (DD-MM-YYYY) :\n\nEnter Day: ";
    cin >> dd;
    while (dd < 1 || dd > 31)
    {
        cout << "Invalid Day! Please enter a valid day: ";
        cin >> dd;
    }
    cout << "Enter Month: ";
    cin >> mm;
    while (mm < 1 || mm > 12)
    {
        cout << "Invalid Month! Please enter a valid month: ";
        cin >> mm;
    }
    cout << "Enter Year (YYYY): ";
    cin >> yyyy;
    yyyymmdd = yyyy * 10000 + mm * 100 + dd;
    return yyyymmdd;
}

int main()
{
    fstream f;
    f.open("appointments.csv", ios::in);
    string temp, s, header;
    getline(f, header);
    getline(f, temp);
    f.close();
    stringstream str(temp);
    getline(str, s, ',');
    getline(str, s, ',');
    int now = getDate(s);
    if (stoi(((s == "") ? ("0") : (s))) < now)
    {
        f.open("temp.csv", ios::out);
        f << header << "\n";
        f.close();
        remove("appointments.csv");
        rename("temp.csv", "appointments.csv");
        fstream fout("temp.csv", ios::out);
        f.open("doctors.csv", ios::in);
        getline(f, temp);
        fout << temp << endl;
        while (getline(f, temp))
        {
            if (temp.size())
                temp[temp.size() - 1] = '0';
            fout << temp << endl;
        }
        f.close();
        fout.close();
        remove("doctors.csv");
        rename("temp.csv", "doctors.csv");
    }
    else if (stoi(s) > now && s != "")
    {
        cout << "\nEntered date detected wrong!\nToday's date can't be older than the last usage date, which is : "
            << s.substr(6, 2) + "-" + s.substr(4, 2) + "-" + s.substr(0, 4) + "\n";
        return 0;
    }
    {
        doctor d1;
        patient p;
        nurse n;
        driver d2;
        ambulance a1;
        appointment a2;
        d1.fillMap();
        p.fillMap();
        n.fillMap();
        d2.fillMap();
        a1.fillMap();
        a2.fillMap();
    }
    while (1)
    {
        int category = 0;
        cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "\nSelect a category:\n\n";

        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "./HOME\n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "[01] : APPOINTMENTS\n";
        cout << "[02] : PATIENTS\n";
        cout << "[03] : DOCTORS\n";
        cout << "[04] : NURSES\n";
        cout << "[05] : DRIVERS\n";
        cout << "[06] : AMBULANCES\n\n";
        cout << "[-1] : EXIT\n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
        cout << "Enter your choice: ";
        cin >> category;
        cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "\n";
        switch (category)
        {
            case 1:
            {
                appointmentsMenu();
                break;
            }
            case 2:
            {
                patientsMenu();
                break;
            }
            case 3:
            {
                doctorsMenu();
                break;
            }
            case 4:
            {
                nursesMenu();
                break;
            }
            case 5:
            {
                driversMenu();
                break;
            }
            case 6:
            {
                ambulancesMenu();
                break;
            }
            case -1:
            {
                cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
                cout << "\nShutting Down System...\n";
                cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
                break;
            }
            default:
            {
                cout << "\nInvalid Choice!\n";
                break;
            }
        }
        
        cout << endl;
    }
    // saving data inside maps by overwriting it on the files
    {
        doctor d1;
        patient p;
        nurse n;
        driver d2;
        ambulance a1;
        appointment a2;
        d1.saveMap();
        p.saveMap();
        n.saveMap();
        d2.saveMap();
        a1.saveMap();
        a2.saveMap();
    }

    return 0;
}