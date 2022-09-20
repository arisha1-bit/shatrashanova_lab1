#include <iostream>
#include <fstream>
using namespace std;
struct Pipe
{
    float lenght = 0, diameter = 0;
    int status = -1, change_pipe = 0;

};
struct CS
{
    string name = "";
    int  workshop = -1, working_workshop = -1, change_cs = 0;
    float effectiveness = 0;
};
string status_check(int x)
{
    if (x == 2)
        return ("Pipe works");
    else if (x == 1)
        return ("Pipe is repairing");
    else
        return ("Unknown");


}
float check_cin(float x)
{
    while ((!x) || (x <= 0)) {
        cout << "Error!!! Input numeric value > 0" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cin >> x;
    }
    return x;
}
int check_status_cin(int x)
{
    while ((x > 2) || (!x) || (x < 0)) {
        cout << "Error!!! Input numeric value (1 or 2)" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cin >> x;
    } 
    return x;
}
int check_workshop_cin(int x, int y)
{
    while ((x > y) || (!x) || (x <= 0)) {
        cout << "Error!!! Input numeric value > 0 and not more than workshops" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cin >> x;
    }
    return x;
}
int main()
{
    int option = -1;
    Pipe p;
    CS cs;
    while (option) {
        cout << "\nChoose option:\n 1.Add pipe 2.Add CS 3.View all objects " <<
            "4.Edit pipe 5.Edit CS 6.Save 7.Load 0.Exit\n";
        cin >> option;
        switch (option) {
            case 1: {
            cout << "\nInput lenght ";
            cin >> p.lenght;
            p.lenght = check_cin(p.lenght);
            cout << "\nInput diameter ";
            cin >> p.diameter;
            p.diameter = check_cin(p.diameter);
            cout << "\nChoose status of pipe (1 if repairing, 2 if works) ";
            cin >> p.status;
            p.status = check_status_cin(p.status);
            cout << status_check(p.status) << endl;
            break;
        }
            case 2: {
            cout << "\nInput name ";
            cin >> cs.name;
            cout << "\nNumber of workshops ";
            cin >> cs.workshop;
            cs.workshop = check_cin(cs.workshop);
            cout << "\nNumber of working workshops ";
            cin >> cs.working_workshop;
            cs.working_workshop = check_workshop_cin(cs.working_workshop, cs.workshop);
            cs.effectiveness = float(cs.workshop) / float(cs.working_workshop);
            cout << "\nEffectiveness: " << cs.effectiveness << endl;
            break;
        }
            case 3: {
            cout << "\nPipe info:\nLenght: " << p.lenght << "\nDiameter: " << p.diameter 
                << "\nStatus: " << status_check(p.status) << endl;;
            cout << "\n\nCS info:\nName: " << cs.name << "\nNumber of workshops: " << cs.workshop
                << "\nNumber of working workshops: " << cs.working_workshop << "\nEffectiveness: "
                << cs.effectiveness << "\n\n\n";
            break;
        }
            case 4: {
            if (p.status == -1)
                cout << "\nThere is no pipe to edit" << endl;
            else {
                cout << "Input new status of pipe (1 if pipe is repairing, 2 if pipe works" << endl;
                cin >> p.status;
                p.status = check_status_cin(p.status);
                cout << status_check(p.status) << endl;
            }
            break;
        }
            case 5: {
            if (cs.working_workshop == -1)
                cout << "\nThere is no CS to edit" << endl;
            else {
                cout << "Input new number of working workshops: " << endl;
                cin >> cs.working_workshop;
                cs.working_workshop = check_workshop_cin(cs.working_workshop, cs.workshop);
                cs.effectiveness = float(cs.workshop) / float(cs.working_workshop);
                cout << "\nEffectiveness: " << cs.effectiveness << endl;
            }
            break;
        }
            case 6: {
                ofstream file;
                file.open("saved_information.txt");
                file << "\nPipe info:\nLenght: " << p.lenght << "\nDiameter: " << p.diameter 
                    << "\nStatus: " << status_check(p.status) << "\n\nCS info:\nName: " << cs.name
                    << "\nNumber of workshops: " << cs.workshop << "\nNumber of working workshops: " 
                    << cs.working_workshop << "\nEffectiveness: " << cs.effectiveness << "\n\n\n";
                file.close();
                break;
            }
            case 7: break;
            case 0: {
            return 0;
        }
        }
    }
    return 0;
}