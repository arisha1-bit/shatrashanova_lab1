#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <float.h>
#include <unordered_map>

using namespace std;
class Pipe
{
public:
    static int max_id;

    Pipe() {
        idp=max_id++;
    }
    friend istream& operator>> (istream& in, Pipe& p);
    friend ostream& operator<< (ostream& out, Pipe& p);
    int get_id() { return idp;}

private:
    float lenght, diameter;
    bool status;
    int idp;
    string name = "";

};
class CS
{
public: static int max_idd;
       CS() {
           idcs = max_idd++;
       }
       friend istream& operator>> (istream& in, CS& p);
       friend ostream& operator<< (ostream& out, CS& cs);
       int get_idd() { return idcs; }

private:
    string name;
    int  workshop, working_workshop, idcs;
    float effectiveness;
};
string status_check(bool x)
{
    if (x == true)
        return ("Pipe works");
    else if (x == false)
        return ("Pipe is repairing");
}
template <typename T>
T correctnumber(T min, T max) {
    T x;
    cin >> x;
    while (cin.fail() || (cin.peek() != '\n') || (x < min) || (x > max)) {
        cout << "Error!!! Input numeric value > " << min << "and < " << max<<endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }
    return x;
}
istream& operator>> (istream& in, Pipe& p)
{
    cout << "\n Index of pipe: " << p.idp;
    cout << "\nInput name ";
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
istream& operator>> (istream& in, CS& cs)
{
    idcs++;
    cs.idcs = idcs;
    cout << "\nIndex of cs: " << cs.idcs;
    cout << "\nInput name ";
    cin.clear();
    cin.ignore(INT_MAX, '\n');
    getline(cin, cs.name);
    cout << "\nNumber of workshops ";
    cs.workshop = correctnumber(0,INT_MAX);
    cout << "\nNumber of working workshops ";
    cs.working_workshop = correctnumber(0,cs.workshop);
    cs.effectiveness = correctnumber(0, 100);
    cout << "\nEffectiveness: " << cs.effectiveness << endl;
    return in;
}
ostream& operator<< (ostream& out, Pipe& p) {
            out << "\nIndex of pipe: " << p.idp << "\nPipe info: " << "\nName: " << p.name << "\nLenght: " << p.lenght << "\nDiameter : " << p.diameter
                << "\nStatus: " << status_check(p.status) << endl;
            return out;
        }
ostream& operator<< (ostream& out, CS& cs) {
            out << "\nIndex of CS: " << cs.idcs << "\nCS info:\nName: " << cs.name << "\nNumber of workshops: " << cs.workshop
                << "\nNumber of working workshops: " << cs.working_workshop << "\nEffectiveness: "
                << cs.effectiveness << "%" << endl;
            return out;
}
void information(unordered_map<int, Pipe>& pipe_group, unordered_map<int,CS>& cs_group) {
    for (auto& pipe : pipe_group) {
        cout << pipe.second << endl;
    }
    for (auto& cs : cs_group) {
        cout << cs.second << endl;
    }
}
void CS::edit_cs() {
    cout << "Workshops: " << workshop << endl;
    cout << "Choose new status of pipe (0 if in repairing, 1 if in work)" << endl;
    status = correctnumber(0, 1);
    cout << status_check(status);
}
void Pipe::edit_Pipe() {
    cout << status_check(status) << endl;
    cout << "Choose new status of pipe (0 if in repairing, 1 if in work)" << endl;
    status = correctnumber(0, 1);
    cout << status_check(status);
}
void Pipe::save_pipe(ofstream& file) {
    file << lenght << endl << diameter << endl << status << endl;
}
void CS::save_cs(ofstream& file) {
    file << cs.name << endl
        << cs.workshop << endl << cs.working_workshop << endl << cs.effectiveness << endl;
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
    int id = correctnumber(g);
    return g[id-1];

}
CS& select_cs(vector <CS>& g) {
    cout << "Enter index of CS ";
    int id = correctnumber(g);
    return g[id - 1];

}
int main()
{
    int option = -1;
    unordered_map<int, Pipe> pipe_group;
    unordered_map<int, CS> cs_group;


    while (option) {
        cout << "\nChoose option:\n 1.Add pipe 2.Add CS 3.View all objects " <<
            "4.Edit pipe 5.Edit CS 6.Save 7.Load 8.Search pipe 9.Search CS 0.Exit\n";
        option = correctnumber(0,9);
        switch (option) {
            case 1: {
            Pipe p;
            cin >> p;
            pipe_group.insert({ p.get_id(), p });
            break;
        }
            case 2: {
                CS cs;
                cin >> cs;
                cs_group.insert({ cs.get_idd(), cs });
            break;
        }
            case 3: {
                information(pipe_group, cs_group); 
            break;
        }
            case 4: {
                //int edit;
                //cout << "\n1.Choose pipe to edit 2.Choose all" << endl;;
                //edit = correctnumber(1,2);
                //if (edit == 1)
                  //  pipechange_choose(select_pipe(pipe_group));
               // else
                   // pipechange(pipe_group);
            break;
        }
            case 5: {
                if (cs_group.size() != 0) {
                    int id;
                    id = correctnumber(1, (int)cs_group.size());
                    cout << "/n1.Choose CS to edit" << endl;
                    cs_group[id].
                }
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
            case 8: {
                search_pipe(pipe_group);
                break;
            }
            case 9: {
                search_cs(cs_group);
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

using check = bool(*)(int);
vector <check> = {}