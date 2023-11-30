using namespace std;
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

#include "global.h"
#include "ambulance.h"
#include "hospital.h"

ambulance::ambulance()
{
    id = -1;
    add.strToAdd("`````");
    D.id = -1;
}
void ambulance::fillMap()
{
    fstream f;
    f.open("ambulances.csv", ios::in);
    string temp;
    //skipping the first row containing column headers;
    getline(f >> ws, temp);
    //analyzing each entry afterwards;
    while (getline(f >> ws, temp))
    {
        ambulance a;
        //creating a string stream object to read from string 'temp';
        stringstream s(temp);
        string str1, str5, str6, str7;
        //reading from the string stream object 's';
        getline(s, str1, ',');
        getline(s, a.model, ',');
        getline(s, a.manufacturer, ',');
        getline(s, a.vrn, ',');
        getline(s, str5, ',');
        getline(s, str6, ',');
        getline(s, str7, ',');
        int num1 = strToNum(str1);
        if (num1 > 0)
        {
            a.id = num1;
        }
        if (str5 == "Y")
        {
            a.idle = true;
        }
        else
        {
            a.idle = false;
        }
        if (!a.idle)
        {
            a.add.strToAdd(str6);
            a.D = hospital::driversList[strToNum(str7)];
        }
        hospital::ambulancesList[num1] = a;
    }
    f.close();
    return;
}
void ambulance::saveMap()
{
    fstream f;
    f.open("temp.csv", ios::out);
    // `le first line conataining column headers:
    f << "ambulanceId,model,manufacturer,vrn,idle?,headedTowards(ifNotIdle),driverID(ifNotIdle)\n";
    for (auto i : hospital::ambulancesList)
    {
        f << i.second.id << "," << i.second.model << "," << i.second.manufacturer << "," << i.second.vrn
            << "," << (i.second.idle ? ("Y,NA,NA\n") : ("N," + i.second.add.addToStr() + ","));
        if (!(i.second.idle))
        {
            f << i.second.D.id << endl;
        }
    }
    f.close();
    remove("ambulances.csv");
    rename("temp.csv", "ambulances.csv");
    return;
}
void ambulance::addAmbulance()
{
    if (hospital::ambulancesList.size() == hospital::ambulancesLimit)
    {
        cout << "\n\nAmbulances limit reached, can't add more!\n\n";
        return;
    }
    //getting the basic details of the ambulance from the user side;
    cout << "\nEnter Model of the ambulance:\n";
    getline(cin >> ws, model);
    cout << "\nEnter Manufacturer Name of the ambulance:\n";
    getline(cin >> ws, manufacturer);
    cout << "\nEnter Vehicle Registration Number of the ambulance:\n";
    getline(cin >> ws, vrn);
    if (hospital::ambulancesList.rbegin() != hospital::ambulancesList.rend())
        id = ((hospital::ambulancesList.rbegin())->first) + 1;
    else
        id = 1;
    hospital::ambulancesList[id] = *this;

    //creating a fstream object to read/write from/to files;
    fstream f;
    //creating a record in ambulancesHistory.csv;
    f.open("ambulancesHistory.csv", ios::app);
    f << model << "," << manufacturer << "," << vrn << ",Y" << endl;
    f.close();

    cout << "\n"
        << model << " by " << manufacturer << " added successfully!\n";
    cout << "Its ID is: " << id << "\n";
}
void ambulance::printDetails()
{
    if (id == -1)
        return;
    cout << "Details:\n";
    cout << "ID              : " << id << "\n";
    cout << "Manufacturer    : " << manufacturer << "\n";
    cout << "Model           : " << model << "\n";
    cout << "Reg Number      : " << vrn << "\n";
    cout << "Idle?           : ";
    if (idle == true)
    {
        cout << "Y" << endl;
    }
    else
    {
        cout << "N" << endl;
    }
    if (!idle)
    {
        cout << "Going to Address: ";
        add.print();
        cout << "Driver ID       : " << D.id << "\n";
    }
    return;
}
void ambulance::printDetailsFromHistory(string extraDetails)
{
    return;
}
void ambulance::getDetails(int rec)
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
        if (hospital::ambulancesList.find(reqId) != hospital::ambulancesList.end())
            *this = hospital::ambulancesList[reqId];
        else
            cout << "\nNo matching record found!\n";
    }
    return;
}
void ambulance::getDetailsFromHistory()
{
    return;
}
void ambulance::send()
{
    bool gotOne = 0;
    for (auto i : hospital::ambulancesList)
    {
        if (i.second.idle)
        {
            *this = i.second;
            gotOne = 1;
            break;
        }
    }
    if (!gotOne)
    {
        cout << "No, idle ambulance found!"
            << "\n";
        return;
    }

    gotOne = 0;
    for (auto i : hospital::driversList)
    {
        if (i.second.idle)
        {
            D = i.second;
            gotOne = 1;
            break;
        }
    }
    if (!gotOne)
    {
        cout << "No, idle driver found!"
            << "\n";
        return;
    }

    idle = 0;

    cout << "Enter destination address:\n";
    add.takeInput();

    //updating status of ambulance;
    hospital::ambulancesList[id] = *this;

    //updating status of driver;
    hospital::driversList[D.id].idle = 0;

    cout << model << " by " << manufacturer << " sent with driver " << D.firstName << " " << D.lastName << " (ID = " << D.id << ") successfully!\n";
    return;
}
void ambulance::reportArrival()
{
    getDetails();

    //updating status of driver;
    //note that if we first update the status of ambulance we will lose the identity of it's driver;
    //and then there will be no way to update the status of the driver;
    hospital::driversList[D.id].idle = 1;

    //updating status of ambulance;
    hospital::ambulancesList[id].idle = 1;
    hospital::ambulancesList[id].add.strToAdd("`````");
    driver d;
    hospital::ambulancesList[id].D = d;

    cout << "\nStatus updated successfully!\n\n";
    return;
}
void ambulance::removeAmbulance()
{
    cout << "\nSearch for the ambulance you want to remove.\n";
    getDetails();
    if (id == -1)
        return;
    if (!idle)
    {
        cout << "\nSorry, the ambulance you selected to remove is NOT currently idle.\nOnly idlers can be removed.\n\n";
        return;
    }
    hospital::doctorsList.erase(id);

    string s, temp;
    stringstream str;
    fstream f, fout;
    str << model << "," << manufacturer << "," << vrn << ",Y\n";
    getline(str, s);
    f.open("ambulancesHistory.csv", ios::in);
    fout.open("temp.csv", ios::out);
    while (getline(f, temp))
    {
        if (temp == s)
        {
            fout << model << "," << manufacturer << "," << vrn << ",N"
                << "\n";
        }
        else
            fout << temp << "\n";
    }
    f.close();
    fout.close();
    s.erase();
    temp.erase();
    remove("ambulancesHistory.csv");
    rename("temp.csv", "ambulancesHistory.csv");
    cout << model << " by " << manufacturer << " (VRN = " << vrn << ") removed successfully!\n";
    return;
}