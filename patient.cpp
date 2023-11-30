using namespace std;
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

#include "global.h"
#include "patient.h"
#include "hospital.h"

patient::patient()
{
    id = -1;
    hospitalized = 0;
    alive = 1;
    cat = "patient";
    category = 2;
}
void patient::fillMap()
{
    fstream f;
    f.open("patients.csv", ios::in);
    string temp;
    //skipping the first row containing column headers;
    getline(f >> ws, temp);
    //analyzing each entry afterwards;
    while (getline(f >> ws, temp))
    {
        patient p;
        stringstream s(temp);
        string str1, str4, str5, str7, str8, str9, str10, str11;
        getline(s, str1, ',');
        getline(s, p.firstName, ',');
        getline(s, p.lastName, ',');
        getline(s, str4, ',');
        getline(s, str5, ',');
        getline(s, p.phoneNumber, ',');
        getline(s, str7, ',');
        getline(s, str8, ',');
        getline(s, str9, ',');
        getline(s, str10, ',');
        getline(s, str11, ',');
        int num1 = strToNum(str1);
        if (num1 > 0)
        {
            p.id = num1;
        }
        p.gender = str4[0];
        int num5 = strToNum(str5);
        if (num5 >= 0)
        {
            p.age = num5;
        }
        p.add.strToAdd(str7);
        int num8 = strToNum(str8);
        if (num8 >= 0)
        {
            p.height = num8;
        }
        int num9 = strToNum(str9);
        if (num9 >= 0)
        {
            p.weight = num9;
        }
        p.hospitalized = (str10 == "Y");
        p.alive = (str11 == "Y");
        hospital::patientsList[num1] = p;
    }
    f.close();
    return;
}

void patient::saveMap()
{
    fstream f;
    f.open("temp.csv", ios::out);
    f << "patientId,firstName,lastName,gender,age,mobNumber,address,height,weight,wasHospitalized?,stillAlive(ifHospitalized)?\n";
    for (auto i : hospital::patientsList)
        f << i.second.id << "," << i.second.firstName << "," << i.second.lastName << "," << i.second.gender
        << "," << i.second.age << "," << i.second.phoneNumber << "," << i.second.add.addToStr()
        << "," << i.second.height << "," << i.second.weight << ","
        << (i.second.hospitalized ? 'Y' : 'N') << "," << (i.second.alive ? 'Y' : 'N') << endl;
    f.close();
    remove("patients.csv");
    rename("temp.csv", "patients.csv");
    return;
}

void patient::addPerson()
{
    person::addPerson();
    cout << "\nEnter the height of the patient (in cms):\n";
    cin >> height;
    cout << "\nEnter the weight of the patient (in pounds):\n";
    cin >> weight;
    char response;
    cout << "\nIs the patient being hospitalized? (Y = Yes || N = No)\n";
    cin >> response;
    if (response != 'Y' && response != 'N')
    {
        cout << "Invalid Response!" << endl;
        cout << "Return the pre-Menu!" << endl;
        return;
    }
    //hospitalized = (response == 'Y');
    if (response == 'Y')
    {
        hospitalized = true;
    }
    if (response == 'N')
    {
        hospitalized = false;
    }
    if (hospital::patientsList.rbegin() != hospital::patientsList.rend())
        id = ((hospital::patientsList.rbegin())->first) + 1;
    else
        id = 1;
    hospital::patientsList[id] = *this;

    //creating a fstream object to read/write from/to files;
    fstream f;
    //creating a record in patientsHistory.csv;
    f.open("./data/patientsHistory.csv", ios::app);
    f << firstName << "," << lastName << "," << gender << "," << age
        << "," << phoneNumber << "," << add.addToStr() << "," << height << ","
        << weight << "," << ((hospitalized) ? "Y" : "N")
        << ","
        << "Y"
        << ","
        << "N"
        << "\n";
    f.close();

    cout << "\n"
        << firstName << " " << lastName << " registered successfully!\n";
    cout << "Their ID is: " << id << "\n";

    return;
}
void patient::printDetails()
{
    if (id == -1)
        return;
    person::printDetails();
    cout << "Height (cms)    : " << height << endl;
    cout << "Weight (pounds) : " << weight << endl;
    cout << "Was Hospitalized?";
    if (hospitalized)
        cout << 'Y' << endl;
    else
        cout << 'N' << endl;
    cout << "Alive?          : ";
    if (alive)
        cout << 'Y' << endl;
    else
        cout << 'N' << endl;
    return;
}
void patient::printDetailsFromHistory(string extraDetails)
{
    return;
}
void patient::getDetails(int rec)
{
    int response = 0;
    cout << "\nOPTIONS:\n[1]: Filter by ID\n\n";
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
        if (hospital::patientsList.find(reqId) != hospital::patientsList.end())
            *this = hospital::patientsList[reqId];
        else
            cout << "\nNo matching record found!\n";
    }
    return;
}
void patient::getDetailsFromHistory()
{
    return;
}
void patient::hospitalize()
{
    cout << "\nSearch for the patient.\n";
    getDetails();
    if (id == -1)
        return;
    hospital::patientsList[id].hospitalized = 1;
    string s, temp, corrected;
    stringstream str;
    fstream f, fout;
    str << firstName << "," << lastName
        << "," << gender << "," << age << "," << phoneNumber << "," << add.addToStr()
        << "," << height << "," << weight << ",";
    if (hospitalized)
        str << "Y";
    else
        str << "N";
    str << ",";
    if (alive)
        str << "Y" ;
    else
        str << "N" ;
    str << ",N"
        << "\n";
    getline(str >> ws, s);
    str << firstName << "," << lastName
        << "," << gender << "," << age << "," << phoneNumber << "," << add.addToStr()
        << "," << height << "," << weight << ","
        << "Y,";
    if (alive)
        str << "Y,N" << endl;
    else
        str << "N,N" << endl;
    getline(str >> ws, corrected);
    f.open("patientsHistory.csv", ios::in);
    fout.open("temp.csv", ios::out);
    while (getline(f, temp))
    {
        if (temp == s)
            fout << corrected << "\n";
        else
            fout << temp << "\n";
    }
    f.close();
    fout.close();
    s.erase();
    temp.erase();
    remove("patientsHistory.csv");
    rename("temp.csv", "patientsHistory.csv");
    cout << firstName << " " << lastName << " hospitalized successfully!\n";
    return;
}
void patient::reportADeath()
{
    cout << "\nSearch for the patient.\n";
    getDetails();
    if (id == -1)
        return;
    hospital::patientsList[id].alive = 0;
    if (!hospital::patientsList[id].hospitalized)
        hospital::patientsList.erase(id);
    string s, temp, corrected;
    stringstream str;
    fstream f, fout;
    str << firstName << "," << lastName
        << "," << gender << "," << age << "," << phoneNumber << "," << add.addToStr()
        << "," << height << "," << weight << ",";
    if (hospitalized)
        str << "Y";
    else
        str << "N";
    str << ",";
    if (alive)
        str << "Y";
    else
        str << "N";
    str << ",N"
        << "\n";
    getline(str, s);
    f.open("patientsHistory.csv", ios::in);
    fout.open("temp.csv", ios::out);
    while (getline(f, temp))
    {
        if (temp == s)
        {
            fout << firstName << "," << lastName
                << "," << gender << "," << age << "," << phoneNumber << "," << add.addToStr()
                << "," << height << "," << weight << "," << ((hospitalized) ? "Y,N,N\n" : "N,N,N\n");
        }
        else
            fout << temp << "\n";
    }
    f.close();
    fout.close();
    s.erase();
    temp.erase();
    remove("patientsHistory.csv");
    rename("temp.csv", "patientsHistory.csv");
    cout << firstName << " " << lastName << " reported dead, we hope their soul rests in peace, amen!\n";
    return;
}
void patient::removePerson()
{
    cout << "\nSearch for the patient you want to discharge.\n";
    getDetails();
    if (id == -1)
        return;
    if (!hospitalized)
    {
        cout << "\nPatient wasn't hospitalized, can't be discharged!\n\n";
        return;
    }
    hospital::patientsList.erase(id);
    string s, temp;
    stringstream str;
    fstream f, fout;
    str << firstName << "," << lastName
        << "," << gender << "," << age << "," << phoneNumber << "," << add.addToStr()
        << "," << height << "," << weight << ",";
    if (hospitalized)
        str << "Y";
    else
        str << "N";
    str << ",";
    if (alive)
        str << "Y";
    else
        str << "N";
    str << ",N"
        << "\n";
    getline(str, s);
    f.open("patientsHistory.csv", ios::in);
    fout.open("temp.csv", ios::out);
    while (getline(f, temp))
    {
        if (temp == s)
        {
            fout << firstName << "," << lastName
                << "," << gender << "," << age << "," << phoneNumber << "," << add.addToStr()
                << "," << height << "," << weight << "," << ((hospitalized) ? "Y" : "N")
                << ","
                << ((alive) ? "Y" : "N")
                << ",Y"
                << "\n";
        }
        else
            fout << temp << "\n";
    }
    f.close();
    fout.close();
    s.erase();
    temp.erase();
    remove("patientsHistory.csv");
    rename("temp.csv", "patientsHistory.csv");
    cout << firstName << " " << lastName << " discharged!\n";
    return;
}
