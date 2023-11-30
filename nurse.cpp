using namespace std;
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

#include "global.h"
#include "nurse.h"
#include "hospital.h"

nurse::nurse()
{
    id = -1;
    type = "";
    cat = "nurse";
    category = 3;
}
void nurse::fillMap()
{
    fstream f;
    f.open("nurses.csv", ios::in);
    string temp;
    //skipping the first row containing column headers;
    getline(f >> ws, temp);
    //analyzing each entry afterwards;
    while (getline(f >> ws, temp))
    {
        nurse n;
        //creating a string stream object to read from string 'temp';
        stringstream s(temp);
        string str1, str4, str5, str7;
        //reading from the string stream object 's';
        getline(s, str1, ',');
        getline(s, n.firstName, ',');
        getline(s, n.lastName, ',');
        getline(s, str4, ',');
        getline(s, str5, ',');
        getline(s, n.phoneNumber, ',');
        getline(s, str7, ',');
        getline(s, n.type, ',');
        int num1 = strToNum(str1);
        if (num1 > 0)
        {
            n.id = num1;
        }
        n.gender = str4[0];
        int num5 = strToNum(str5);
        if (num5 > 0)
        {
            n.age = num5;
        }
        n.add.strToAdd(str7);
        hospital::nursesList[num1] = n;
    }
    f.close();
    return;
}
void nurse::saveMap()
{
    fstream f;
    f.open("temp.csv", ios::out);
    // `le first line conataining column headers:
    f << "nurseId,firstName,lastName,gender,age,mobNumber,address,type\n";
    for (auto i : hospital::nursesList)
        f << i.second.id << "," << i.second.firstName << "," << i.second.lastName << "," << i.second.gender
        << "," << i.second.age << "," << i.second.phoneNumber << "," << i.second.add.addToStr()
        << "," << i.second.type << endl;
    f.close();
    remove("nurses.csv");
    rename("temp.csv", "nurses.csv");
    return;
}
void nurse::addPerson()
{
    if (hospital::nursesList.size() == hospital::nursesLimit)
    {
        cout << "\n\nNurses limit reached, can't add more!\n\n";
        return;
    }
    //18 and 65 are the age limits for registration of a new nurse;
    person::addPerson(18, 65);
    if ((age < 18) || (age > 65))
        return;
    cout << "\nEnter the type of the nurse: \n";
    getline(cin >> ws, type);
    if (hospital::nursesList.rbegin() != hospital::nursesList.rend())
        id = ((hospital::nursesList.rbegin())->first) + 1;
    else
        id = 1;
    hospital::nursesList[id] = *this;

    //creating a fstream object to read/write from/to files;
    fstream f;
    //creating a record in nursesHistory.csv;
    f.open("nursesHistory.csv", ios::app);
    f << firstName << "," << lastName << "," << gender << "," << age << "," << phoneNumber << "," << add.addToStr() << "," << type << ",N,NA" << endl;
    f.close();

    cout << "\n"
        << firstName << " " << lastName << " registered successfully!\n";
    cout << "Their ID is: " << id << "\n";

    return;
}
void nurse::printDetails()
{
    if (id == -1)
        return;
    person::printDetails();
    cout << "Type            : " << type << "\n";
    return;
}
void nurse::printDetailsFromHistory(string extraDetails)
{
    return;
}
void nurse::getDetails(int rec)
{
    int opt = 0;
    cout << "\nOPTIONS:\n[1]: Filter by ID\n";
    cin >> opt;
    if (opt != 1)
    {
        cout << "Wrong Response!" << endl;
        cout << "Return the pre-Menu!" << endl;
        return;
    }
    //1: Filter by ID;
    if (opt == 1)
    {
        int reqId;
        cout << "\nEnter ID:\n";
        cin >> reqId;
        if (hospital::nursesList.find(reqId) != hospital::nursesList.end())
            *this = hospital::nursesList[reqId];
        else
            cout << "\nNo matching record found!\n";
    }
    return;
}
void nurse::getDetailsFromHistory()
{
    return;
}
void nurse::removePerson()
{
    cout << "\nSearch for the nurse you want to remove.\n";
    getDetails();
    if (id == -1)
        return;
    hospital::nursesList.erase(id);

    string s, temp;
    stringstream str;
    fstream f, fout;
    string reason;
    cout << "\nReason?\n";
    getline(cin >> ws, reason);
    str << firstName << "," << lastName << "," << gender << "," << age
        << "," << phoneNumber << "," << add.addToStr() << "," << type << ",N,NA\n";
    getline(str, s);
    f.open("nursesHistory.csv", ios::in);
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
    remove("nursesHistory.csv");
    rename("temp.csv", "nursesHistory.csv");
    cout << firstName << " " << lastName << " removed successfully!\n";
    return;
}