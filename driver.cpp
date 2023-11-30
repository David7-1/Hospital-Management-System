using namespace std;
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

#include "global.h"
#include "driver.h"
#include "hospital.h"

driver::driver()
{
    id = -1;
    licenseNumber = "";
    idle = 1;
    cat = "driver";
    category = 4;
}
void driver::fillMap()
{
    fstream f;
    f.open("drivers.csv", ios::in);
    string temp;
    getline(f >> ws, temp);
    while (getline(f >> ws, temp))
    {
        driver d;
        stringstream s(temp);
        string str1, str4, str5, str7, str9;
        getline(s, str1, ',');
        getline(s, d.firstName, ',');
        getline(s, d.lastName, ',');
        getline(s, str4, ',');
        getline(s, str5, ',');
        getline(s, d.phoneNumber, ',');
        getline(s, str7, ',');
        getline(s, d.licenseNumber, ',');
        getline(s, str9, ',');
        int num1 = strToNum(str1);
        if (num1 > 0)
        {
            d.id = num1;
        }
        d.gender = str4[0];
        int num5 = strToNum(str5);
        if (num5 >= 0)
        {
            d.age = num5;
        }
        d.add.strToAdd(str7);
        if (str9 == "Y")
        {
            d.idle = true;
        }
        else
        {
            d.idle = false;
        }
        hospital::driversList[num1] = d;
    }
    f.close();
    return;
}
void driver::saveMap()
{
    fstream f;
    f.open("temp.csv", ios::out);
    f << "driverId,firstName,lastName,gender,age,mobNumber,address,licenseNumber,idle?\n";
    for (auto i : hospital::driversList)
        f << i.second.id << "," << i.second.firstName << "," << i.second.lastName << "," << i.second.gender
        << "," << i.second.age << "," << i.second.phoneNumber << "," << i.second.add.addToStr()
        << "," << i.second.licenseNumber << "," << (i.second.idle ? 'Y' : 'N') << endl;
    f.close();
    remove("drivers.csv");
    rename("temp.csv", "drivers.csv");
    return;
}
void driver::addPerson()
{
    if (hospital::driversList.size() == hospital::driversLimit)
    {
        cout << "\n\nDrivers limit reached, can't add more!\n\n";
        return;
    }
    person::addPerson(18, 65);
    if ((age < 18) || (age > 65))
        return;
    cout << "\nEnter the license number of the driver: \n";
    getline(cin >> ws, licenseNumber);
    if (hospital::driversList.rbegin() != hospital::driversList.rend())
        id = ((hospital::driversList.rbegin())->first) + 1;
    else
        id = 1;
    hospital::driversList[id] = *this;

    fstream f;
    f.open("driversHistory.csv", ios::app);
    f << firstName << "," << lastName << "," << gender << "," << age << "," << phoneNumber << "," << add.addToStr() << "," << licenseNumber << ",N,NA" << endl;
    f.close();
    cout << "\n"
        << firstName << " " << lastName << " registered successfully!\n";
    cout << "Their ID is: " << id << "\n";

    return;
}
void driver::printDetails()
{
    if (id == -1)
        return;
    person::printDetails();
    cout << "License Number  : " << licenseNumber << "\n";
    cout << "Idle?           : ";
    if (idle == true)
    {
        cout << "Y" << endl;
    }
    else
    {
        cout << "N" << endl;
    }
    return;
}
void driver::printDetailsFromHistory(string extraDetails)
{
    return;
}
void driver::getDetails(int rec)
{
    int opt = 0;
    cout << "\nOPTIONS:\n[1]: Filter by ID\n\n";
    cin >> opt;
    if (opt != 1)
    {
        cout << "Wrong Response!" << endl;
        cout << "Return the pre-menu!" << endl;
        return;
    }
    //1: Filter by ID;
    if (opt == 1)
    {
        int reqId;
        cout << "\nEnter ID:\n";
        cin >> reqId;
        if (hospital::driversList.find(reqId) != hospital::driversList.end())
            *this = hospital::driversList[reqId];
        else
            cout << "\nNo matching record found!\n";
    }
    return;
}
void driver::getDetailsFromHistory()
{
    return;
}
void driver::removePerson()
{
    cout << "\nSearch for the driver you want to remove.\n";
    getDetails();
    if (id == -1)
        return;
    if (!idle)
    {
        cout << "\nSorry, the driver you selected to remove is NOT currently idle.\nOnly idlers can be removed.\n\n";
        return;
    }
    hospital::driversList.erase(id);

    string s, temp;
    stringstream str;
    fstream f, fout;
    string reason;
    cout << "\nReason?\n";
    getline(cin >> ws, reason);
    str << firstName << "," << lastName << "," << gender << "," << age
        << "," << phoneNumber << "," << add.addToStr() << "," << licenseNumber << ",N,NA\n";
    getline(str, s);
    f.open("driversHistory.csv", ios::in);
    fout.open("temp.csv", ios::out);
    while (getline(f, temp))
    {
        if (temp == s)
        {
            fout << firstName << "," << lastName << "," << gender << "," << age
                << "," << phoneNumber << "," << add.addToStr() << "," << licenseNumber << ",Y," << reason << "\n";
        }
        else
            fout << temp << "\n";
    }
    f.close();
    fout.close();
    s.erase();
    temp.erase();
    remove("driversHistory.csv");
    rename("temp.csv", "driversHistory.csv");
    cout << firstName << " " << lastName << " removed successfully!\n";
    return;
}