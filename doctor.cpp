using namespace std;
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

#include "global.h"
#include "doctor.h"
#include "hospital.h"

doctor::doctor()
{
    id = -1;
    type = "";
    appointmentsBooked = 0;
    cat = "doctor";
    category = 1;
}
void doctor::fillMap()
{
    fstream f;
    f.open("doctors.csv", ios::in);
    string temp;
    //skipping the first row containing column headers;
    getline(f >> ws, temp);
    //analyzing each entry afterwards;
    while (getline(f >> ws, temp))
    {
        doctor d;
        //creating a string stream object to read from string 'temp';
        stringstream s(temp);
        string str1, str4, str5, str7, str9;
        //reading from the string stream object 's';
        getline(s, str1, ',');
        getline(s, d.firstName, ',');
        getline(s, d.lastName, ',');
        getline(s, str4, ',');
        getline(s, str5, ',');
        getline(s, d.phoneNumber, ',');
        getline(s, str7, ',');
        getline(s, d.type, ',');
        getline(s, str9, ',');
        int num1 = strToNum(str1);
        if (num1 > 0)
        {
            d.id = num1;
        }
        d.gender = str4[0];
        int num5 = strToNum(str5);
        if (num5 > 0)
        {
            d.age = num5;
        }
        d.add.strToAdd(str7);
        int num9 = strToNum(str9);
        if (num9 > 0)
        {
            d.appointmentsBooked = num9;
        }
        hospital::doctorsList[d.id] = d;
    }
    f.close();
    return;
}
void doctor::saveMap()
{
    fstream f;
    f.open("temp.csv", ios::out);
    // `le first line conataining column headers:
    f << "doctorId,firstName,lastName,gender,age,mobNumber,address,type,appointmentsBooked\n";
    for (auto i : hospital::doctorsList)
        f << i.second.id << "," << i.second.firstName << "," << i.second.lastName << "," << i.second.gender
        << "," << i.second.age << "," << i.second.phoneNumber << "," << i.second.add.addToStr()
        << "," << i.second.type << "," << i.second.appointmentsBooked << endl;
    f.close();
    remove("doctors.csv");
    rename("temp.csv", "doctors.csv");
    return;
}
void doctor::addPerson()
{
    if (hospital::doctorsList.size() == hospital::doctorsLimit)
    {
        cout << "\n\nDoctors limit reached, can't add more!\n\n";
        return;
    }
    person::addPerson(18, 65);
    if ((age < 18) || (age > 65))
        return;
    cout << "\nEnter the type of the doctor: \n";
    getline(cin >> ws, type);
    if (hospital::doctorsList.rbegin() != hospital::doctorsList.rend())
        id = ((hospital::doctorsList.rbegin())->first) + 1;
    else
        id = 1;
    hospital::doctorsList[id] = *this;

    //creating a fstream object to read/write from/to files;
    fstream f;
    //creating a record in doctorsHistory.csv;
    f.open("doctorsHistory.csv", ios::app);
    f << firstName << "," << lastName << "," << gender << "," << age << "," << phoneNumber << "," << add.addToStr() << "," << type << ",N,NA" << endl;
    f.close();

    cout << "\n"
        << firstName << " " << lastName << " registered successfully!\n";
    cout << "Their ID is: " << id << "\n";

    return;
}
void doctor::printDetails()
{
    if (id == -1)
        return;
    person::printDetails();
    cout << "Type            : " << type << "\n";
    cout << "Appointments    : " << appointmentsBooked << "/8 (appointments booked today)\n";
    return;
}
void doctor::printDetailsFromHistory(string extraDetails)
{
    return;
}
void doctor::getDetails(int rec)
{
    int response = 0;
    cout << "\nOPTIONS:\n[1]: Filter by ID\n";
    cin >> response;
    if (response != 1)
    {
        cout << "Wrong Response!" << endl;
        cout << "Return the pre-Menu!" << endl;
        return;
    }
    //1: Filter by ID;
    if (response == 1)
    {
        int reqId;
        cout << "\nEnter ID:\n";
        cin >> reqId;
        if (hospital::doctorsList.find(reqId) != hospital::doctorsList.end())
            *this = hospital::doctorsList[reqId];
        else
            cout << "\nNo matching record found!\n";
    }
    return;
}
void doctor::getDetailsFromHistory()
{
    return;
}
void doctor::removePerson()
{
    cout << "\nSearch for the doctor you want to remove.\n";
    getDetails();
    if (id == -1)
        return;
    if (appointmentsBooked > 0)
    {
        cout << "\nSelected doctor has appointments booked for today, can't be removed.\n\n";
        return;
    }
    hospital::doctorsList.erase(id);

    string s, temp;
    stringstream str;
    fstream f, fout;
    string reason;
    cout << "\nReason?\n";
    getline(cin >> ws, reason);
    str << firstName << "," << lastName << "," << gender << "," << age
        << "," << phoneNumber << "," << add.addToStr() << "," << type << ",N,NA\n";
    getline(str, s);
    f.open("doctorsHistory.csv", ios::in);
    fout.open("temp.csv", ios::out);
    while (getline(f, temp))
    {
        if (temp == s)
        {
            fout << firstName << "," << lastName << "," << gender << "," << age
                << "," << phoneNumber << "," << add.addToStr() << "," << type << ",Y," << reason << "\n";
        }
        else
            fout << temp << "\n";
    }
    f.close();
    fout.close();
    s.erase();
    temp.erase();
    remove("doctorsHistory.csv");
    rename("temp.csv", "doctorsHistory.csv");
    cout << firstName << " " << lastName << " removed successfully!\n";
    return;
}
