using namespace std;
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

#include "global.h"
#include "appointment.h"
#include "hospital.h"

appointment::appointment()
{
    id = -1;
    D.id = -1;
    P.id = -1;
}
appointment::~appointment()
{
    id = -1;
    D.id = -1;
    P.id = -1;
    return;
}
void appointment::fillMap()
{
    fstream f;
    f.open("appointments.csv", ios::in);
    string temp;
    getline(f >> ws, temp);
    while (getline(f >> ws, temp))
    {
        appointment a;
        stringstream s(temp);
        string str1;
        getline(s, str1, ',');
        string str2;
        getline(s, str2, ',');
        string str3;
        getline(s, str3, ',');
        string str4;
        getline(s, str4, ',');
        string str5;
        getline(s, str5, ',');
        int num1 = strToNum(str1);
        if (num1 > 0)
        {
            a.id = num1;
        }
        int num3 = strToNum(str3);
        if (num3 > 0)
        {
            a.D = hospital::doctorsList[num3];
        }
        int num4 = strToNum(str4);
        if (num4 > 0)
        {
            a.P = hospital::patientsList[num4];
        }
        int num5 = strToNum(str5);
        if (num5 > 0)
        {
            a.hour = num5;
        }
        hospital::appointmentsList[num1] = a;
    }
    f.close();
    return;
}

void appointment::saveMap()
{
    fstream f;
    f.open("temp.csv", ios::out);
    // `le first line conataining column headers:
    f << "appointmentId,date(YYYYMMDD),doctorId,patientId,startTime(in 24-hr format)\n";
    for (auto i : hospital::appointmentsList)
        f << i.second.id << "," << yyyymmdd << "," << i.second.D.id << "," << i.second.P.id<< "," << i.second.hour << endl;
    f.close();
    remove("appointments.csv");
    rename("temp.csv", "appointments.csv");
    return;
}

void appointment::printDetails()
{
    if (id == -1)
        return;
    else
    {
        cout << "\n\n\nAppointment Details:\nID                 : " << id << endl
            << "Patient's Name     : " + P.firstName + " " + P.lastName + "(ID = " << P.id << ")" << endl
            << "Doctor's Name      : " + D.firstName + " " + D.lastName + "(ID = " << D.id << ")" << endl
            << "Time (24 Hr format): " << hour << ":00 Hrs to " << endl;
        return;
    }
}

void appointment::book()
{
    if (hospital::appointmentsList.size() >= 8 * hospital::doctorsList.size())
    {
        cout << "\n\nSorry, no doctor is available for appointment today!\n\n";
        return;
    }
    cout << endl;
    cout << endl;
    cout << endl;
    cout << "The paitent has already registered?" << endl;
    char response;
    cin >> response;
    if (response != 'Y' && response != 'N')
    {
        cout << "Invalid Response!" << endl;
        cout << "Return to pre-menu!" << endl;
        return;
    }
    if (response == 'Y')
    {
        cout << "Search for the required patients:" << endl;
        response = 'Y';
        while (response == 'Y')
        {
            P.getDetails();
            response = 'S';
            if (P.id == -1)
            {
                cout << "Try again!" << endl;
                cin >> response;
                if (response != 'Y' && response != 'N')
                {
                    cout << "Invalid Response!" << endl;
                    cout << "Return to pre-menu!" << endl;
                    return;
                }
            }
        }
    }
    if (response == 'N')
    {
        cout << "The patient has not been registered!" << endl;
        P.addPerson();
    }
    cout << endl;
    cout << endl;
    cout << "Looking for the suitable doctor!" << endl;
    response = 'Y';
    while (response == 'Y')
    {
        P.getDetails();
        response = 'S';
        if (P.id == -1)
        {
            cout << "Wrong Response! Try Again!" << endl;
            cin >> response;
            if (response != 'Y' && response != 'N')
            {
                cout << "Invalid Response!" << endl;
                cout << "Return to pre-menu!" << endl;
                return;
            }
        }
    }
    if (response == 'N')
    {
        return;
    }
    if (hospital::appointmentsList.rbegin() != hospital::appointmentsList.rend())
        id = ((hospital::appointmentsList.rbegin())->first) + 1;
    else
        id = 1;
    hour = 5 + D.appointmentsBooked;
    hospital::appointmentsList[id] = *this;

    hospital::doctorsList[D.id].appointmentsBooked++;
    cout << "\nAppointment of patient " + P.firstName + " " + P.lastName + " with doctor "
        << D.firstName << " " << D.lastName << " booked successfully!" << endl;
    printDetails();
    return;
}

void appointment::getDetails()
{
    cout << "\nEnter appointment ID:\n";
    cin >> id;
    if (hospital::appointmentsList.find(id) != hospital::appointmentsList.end())
    {
        
    }
    else
    {
        cout << "\nInvalid appointment ID!" << endl;
        id = -1;
        return;
    }
    if (id <= 0)
    {
        cout << "\nInvalid appointment ID!" << endl;
        id = -1;
        return;
    }
    *this = hospital::appointmentsList[id];
    return;
}
