#include <iostream>
#include <fstream>
#include <string>
#include <vector>;
using namespace std;
int idp = 0;
int idcs = 0;
struct Pipe
{
    float lenght = 0, diameter = 0;
    bool status = 0;
    int idp = 0;

};
struct CS
{
    string name = "";
    int  workshop = -1, working_workshop = -1, idcs = 0;
    float effectiveness = 0;
};
string status_check(bool x)
{
    if (x == true)
        return ("Pipe works");
    else if (x == false)
        return ("Pipe is repairing");


}
int editioncheck() {
    int x;
    while (((cin >> x).fail()) || (cin.peek() != '\n') || (x < 1)||(x>2)) {
        cout << "Error!!! Input integer numeric value (1 or 2) " << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }
    return x;
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
    idp++;
    p.idp = idp;
    cout << "\n Index of pipe: " << p.idp;
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
    idcs++;
    cs.idcs = idcs;
    cout << "\nIndex of cs: " << cs.idcs;
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
int check_id_of_pipe(vector <Pipe>& g) {
    int x;
    while (((cin >> x).fail()) || (cin.peek() != '\n') || (x > g.size()) || (x<0)) {
        cout << "Error!!! Input integer numeric index of existing pipe > 0" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }
    return x;
}
int check_id_of_cs(vector <CS>& g) {
    int x;
    while (((cin >> x).fail()) || (cin.peek() != '\n') || (x > g.size()) || (x < 0)) {
        cout << "Error!!! Input integer numeric index of existing CS > 0" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }
    return x;
}
void information(vector <Pipe>& gp, vector <CS>& gcs) {
    if (gp.size() != 0) {
        for (int i = 0; i < gp.size(); i++) {
            cout << "\nIndex of pipe: " << gp[i].idp << "\nPipe info:\nLenght: " << gp[i].lenght << "\nDiameter: " << gp[i].diameter
                << "\nStatus: " << status_check(gp[i].status) << endl;
        }
    }
    if (gcs.size() != 0) {
        for (int i = 0; i < gp.size(); i++) {
            cout << "\nIndex of CS: " << gcs[i].idcs << "\nCS info:\nName: " << gcs[i].name << "\nNumber of workshops: " << gcs[i].workshop
                << "\nNumber of working workshops: " << gcs[i].working_workshop << "\nEffectiveness: "
                << gcs[i].effectiveness << "%" << endl;
        }
    }
}
void pipechange_choose(Pipe& p) {
    if (idp == 0)
        cout << "There is no pipe to change";
    else {
        cout << "Input new status of pipe (1 if pipe is repairing, 2 if pipe works" << endl;
        p.status = check_status_cin(p.status);
        cout << status_check(p.status) << endl;
    }
    }
void pipechange(vector <Pipe>& g) {
    bool x = 0;
    if (idp == 0)
        cout << "There is no pipe to change";
    else {
        cout << "Input new status of pipes (0 if pipe is repairing, 1 if pipe works)" << endl;
        x = check_status_cin(x);
        for (int i = 0; i < g.size(); i++) {
            g[i].status = x;
        }
        cout << status_check(x) << endl;
    }
}
void cschange_choose(CS& cs) {
    if (idcs == 0)
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
Pipe& select_pipe(vector <Pipe>& g) {
    cout << "Enter index of pipe ";
    int id = check_id_of_pipe(g);
    return g[id-1];

}
CS& select_cs(vector <CS>& g) {
    cout << "Enter index of CS ";
    int id = check_id_of_cs(g);
    return g[id - 1];

}
int main()
{
    int option = -1;
    vector <Pipe> pipe_group;
    vector <CS> cs_group;

    while (option) {
        cout << "\nChoose option:\n 1.Add pipe 2.Add CS 3.View all objects " <<
            "4.Edit pipe 5.Edit CS 6.Save 7.Load 8.Search pipe 9.Search CS 0.Exit\n";
        option = check_option(option);
        switch (option) {
        case 1: {
            Pipe p;
            createPipe(p);
            pipe_group.push_back(p); 
            break;
        }
            case 2: {
                CS cs;
                createCS(cs);
                cs_group.push_back(cs); 
            break;
        }
            case 3: {
                information(pipe_group, cs_group); 
            break;
        }
            case 4: {
                int edit;
                cout << "/n1.Choose pipe to edit 2.Choose all" << endl;;
                edit = editioncheck();
                if (edit == 1)
                    pipechange_choose(select_pipe(pipe_group));
                else
                    pipechange(pipe_group);
            break;
        }
            case 5: {
                int edit;
                cout << "/n1.Choose CS to edit" << endl;
                cschange_choose(select_cs(cs_group));
            break;
        }
            case 6: {
                //saving(cs, p);
                break;
            }
            case 7: { 
               // loading(cs, p);
                break;
            }
            case 8:
            {
                break;
            }
            case 9:
            {
                break;
            }
            case 0: {
            return 0;
        }
            default: cout << "Input correct number (0-7)";
                break;       }
    }
    return 0;
}