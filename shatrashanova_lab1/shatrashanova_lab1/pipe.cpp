#include "pipe.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <float.h>
#include <unordered_map>
#include <unordered_set>
#include "checking.h"
#include "graph.h"
using namespace std;
System s;
string status_check(bool x)
{
    if (x == true)
        return ("Pipe works");
    else
        return ("Pipe is repairing");
}
int Pipe::max_id = 0;
istream& operator>> (istream& in, Pipe& p)
{
    cout << "\n Index of pipe: " << p.idp;
    cout << "\nInput name ";
    s.pipe.insert(p.idp);
    cin.clear();
    cin.ignore(INT_MAX, '\n');
    getline(cin, p.name);
    cout << "\nInput lenght ";
    p.lenght = correctnumber(0.0, DBL_MAX);
    cout << "\nInput diameter ";
    p.diameter = correctnumber(0.0, DBL_MAX);
    cout << "\nChoose status of pipe (0 if repairing, 1 if works) ";
    p.status = correctnumber(0,1);
    cout << status_check(p.status) << endl;
    return in;
}
ostream& operator<< (ostream& out, Pipe& p) {
            out << "\nIndex of pipe: " << p.idp << "\nPipe info: " << "\nName: " << p.name << "\nLenght: " 
                << p.lenght << "\nDiameter : " << p.diameter
                << "\nStatus: " << status_check(p.status) << endl;
            return out;
        }
void Pipe::edit_Pipe() {
    cout << "Status: " << status_check(status) << endl;
    cout << "Enter new status of pipe (0 if in repairing, 1 if works)" << endl;
    status = correctnumber(0,1);
    cout << status_check(status) << endl;;
}
 void Pipe::save_pipe(ofstream& file) {
    file << idp << endl << name << endl << lenght << endl << diameter << endl << status << endl;
}
 void Pipe::load_pipe(ifstream& file) {
    file >> idp;
    getline(file, name);
    getline(file, name);
    file >> lenght;
    file >> diameter;
    file >> status;
}
 bool check_p_name(Pipe& p, string name) {
     return (p.name.find(name) != string::npos);
 }
 bool check_p_status(Pipe& p, bool status) {
     return (p.status == status);
 }

