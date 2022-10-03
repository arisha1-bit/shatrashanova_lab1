#include <iostream>
#include <fstream>
#include <string>
using namespace std;
struct Pipe
{
    float lenght = 0, diameter = 0;
    bool status = 0;

};
struct CS
{
    string name = "";
    int  workshop = -1, working_workshop = -1;
    float effectiveness = 0;
};
string status_check(bool x)
{
    if (x == true)
        return ("Pipe works");
    else if (x == false)
        return ("Pipe is repairing");


}
float check_cin(float x)
{
    while ((((cin >> x).fail()) || (cin.peek() != '\n')) || (x <= 0)) {
        cout << "Error!!! Input numeric value > 0" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }
    return x;
}
int check_shop(int x)
{
    while (((cin >> x).fail()) || (cin.peek() != '\n') || (x <= 0)) {
        cout << "Error!!! Input integer numeric value > 0" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }
    return x;
}
bool check_status_cin(bool x)
{
    while (((cin >> x).fail()) || (cin.peek() != '\n')) {
        cout << "Error!!! Input numeric value (0 or 1)" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    } 
    return x;
}
int check_workshop_cin(int x, int y)
{
    while (((cin >> x).fail()) || (cin.peek() != '\n') || (x < 0) || (x > y)) {
        cout << "Error!!! Input integer numeric value not more than workshops" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }
    return x;
}
int check_option(int x)
{
    while (((cin >> x).fail()) || (cin.peek() != '\n')){
        cout <<  "Input correct number (0-7)" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }
    return x;
}
void createPipe(Pipe& p)
{
    cout << "\nInput lenght ";
    p.lenght = check_cin(p.lenght);
    cout << "\nInput diameter ";
    p.diameter = check_cin(p.diameter);
    cout << "\nChoose status of pipe (0 if repairing, 1 if works) ";
    p.status = check_status_cin(p.status);
    cout << status_check(p.status) << endl;
}
void createCS(CS& cs)
{
    cout << "\nInput name ";
    cin.clear();
    cin.ignore(INT_MAX, '\n');
    getline(cin, cs.name);
    cout << "\nNumber of workshops ";
    cs.workshop = check_shop(cs.workshop);
    cout << "\nNumber of working workshops ";
    cs.working_workshop = check_workshop_cin(cs.working_workshop, cs.workshop);
    cs.effectiveness = float(cs.working_workshop) / float(cs.workshop) * 100;
    cout << "\nEffectiveness: " << cs.effectiveness << "%" << endl;
}
void information(CS& cs, Pipe& p) {
    cout << "\nPipe info:\nLenght: " << p.lenght << "\nDiameter: " << p.diameter
        << "\nStatus: " << status_check(p.status) << endl;;
    cout << "\n\nCS info:\nName: " << cs.name << "\nNumber of workshops: " << cs.workshop
        << "\nNumber of working workshops: " << cs.working_workshop << "\nEffectiveness: "
        << cs.effectiveness << "%" << endl;
}
void pipechange(Pipe& p) {
    if (p.lenght == 0)
        cout << "\nThere is no pipe to edit" << endl;
    else {
        cout << "Input new status of pipe (1 if pipe is repairing, 2 if pipe works" << endl;
        p.status = check_status_cin(p.status);
        cout << status_check(p.status) << endl;
    }
}
void cschange(CS& cs) {
    if (cs.working_workshop == -1)
        cout << "\nThere is no CS to edit" << endl;
    else {
        cout << "Input new number of working workshops: " << endl;
        cs.working_workshop = check_workshop_cin(cs.working_workshop, cs.workshop);
        cs.effectiveness = (float(cs.working_workshop) / float(cs.workshop)) * 100;
        cout << "\nEffectiveness: " << cs.effectiveness << "%" << endl;
    }
}
void saving(CS& cs, Pipe& p) {
    ofstream file;
    file.open("saved_information.txt");
    file << p.lenght << endl << p.diameter << endl << p.status << endl << cs.name << endl
        << cs.workshop << endl << cs.working_workshop << endl << cs.effectiveness << "%"
        << endl;
    file.close();
}
void loading(CS& cs, Pipe& p) {
    ifstream file2;
    string line;
    file2.open("saved_information.txt");
    if (file2.is_open()) {
        getline(file2, line);
        p.lenght = stof(line);
        getline(file2, line);
        p.diameter = stof(line);
        getline(file2, line);
        p.status = stoi(line);
        getline(file2, line);
        cs.name = line;
        getline(file2, line);
        cs.workshop = stoi(line);
        getline(file2, line);
        cs.working_workshop = stoi(line);
        getline(file2, line);
        cs.effectiveness = stod(line);
    }
    else
        cout << "You don't have any file";
}
int main()
{
    int option = -1;
    Pipe p;
    CS cs;

    while (option) {
        cout << "\nChoose option:\n 1.Add pipe 2.Add CS 3.View all objects " <<
            "4.Edit pipe 5.Edit CS 6.Save 7.Load 0.Exit\n";
        option = check_option(option);
        switch (option) {
            case 1: {
                createPipe(p);
            break;
        }
            case 2: {
                createCS(cs);
            break;
        }
            case 3: {
                information(cs, p);
            break;
        }
            case 4: {
                pipechange(p);
            break;
        }
            case 5: {
                cschange(cs);
            break;
        }
            case 6: {
                saving(cs, p);
                break;
            }
            case 7: { 
                loading(cs, p);
                break;
            }
            case 0: {
            return 0;
        }
            default: cout << "Input correct number (0-7)";
                break;        }
    }
    return 0;
}