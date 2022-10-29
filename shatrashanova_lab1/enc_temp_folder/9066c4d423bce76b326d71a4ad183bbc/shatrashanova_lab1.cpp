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
    string name = "";
    bool status = 0;
    Pipe() {
        idp=max_id++;
    }
    friend istream& operator>> (istream& in, Pipe& p);
    friend ostream& operator<< (ostream& out, Pipe& p);
    void edit_Pipe();
    void save_pipe(ofstream& file);
    void load_pipe(ifstream& file);
    int get_id() { return idp;}

private:
    double lenght=0, diameter=0;
    int idp=0;

};
class CS
{
public: static int max_idd;
      CS() {
          idcs = max_idd++;
      }
      friend istream& operator>> (istream& in, CS& p);
      friend ostream& operator<< (ostream& out, CS& cs);
      void save_cs(ofstream& file);
      void edit_cs();
      void load_cs(ifstream& file);
      int get_idd() { return idcs; }
      double get_unused() { return ((workshop - working_workshop) / workshop) * 100; }
      string name = "";


private:
    int  workshop, working_workshop, idcs;
    double effectiveness;
};
int Pipe::max_id = 0;
int CS::max_idd = 0;
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
    while (((cin>>x).fail()) || (cin.peek() != '\n') || (x < min) || (x > max)) {
        cout << "Error!!! Input numeric value > " << min << " and < " << max<<endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }
    return x;
}
template <typename T>
using filter_p = bool (*) (Pipe& p, T par);
template <typename T>
using filter_cs = bool(*) (CS& cs, T par);
template <typename T>
vector <int> search_p_by_parametr(unordered_map <int, Pipe>& pipe_group, filter_p<T> f, T par) {
    vector <int> id;
    for (auto& pipe : pipe_group) {
        if (f(pipe.second, par))
            id.push_back(pipe.second.get_id());
    }
    return id;
}
template <typename T>
vector <int> search_cs_by_parametr(unordered_map <int, CS>& cs_group, filter_cs<T> f, T par) {
    vector <int> id;
    for (auto& cs : cs_group) {
        if (f(cs.second, par))
            id.push_back(cs.second.get_idd());
    }
    return id;
}
bool check_p_name(Pipe& p, string name) {
    return (p.name.find(name) != string::npos);
}
bool check_p_status(Pipe& p, bool status) {
    return (p.status == status);
}
bool check_cs_name(CS& cs, string name) {
    return (cs.name.find(name) != string::npos);
}
bool check_unworking(CS& cs, double p) {
    return (cs.get_unused() >= p);
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
    cout << "\nIndex of cs: " << cs.idcs;
    cout << "\nInput name ";
    cin.clear();
    cin.ignore(INT_MAX, '\n');
    getline(cin, cs.name);
    cout << "\nNumber of workshops ";
    cs.workshop = correctnumber(0,INT_MAX);
    cout << "\nNumber of working workshops ";
    cs.working_workshop = correctnumber(0,cs.workshop);
    cout << "\nEnter the effectiveness ";
    cs.effectiveness = correctnumber(0, 100);
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
void search_p(unordered_map <int, Pipe>& pipe_group, vector<int>& id) {
    int x;
    cout << "Search pipe by 1.name 2.status" << endl;
    x = correctnumber(1, 2);
    if (x == 1) {
        string name;
        cout << "Enter the name of pipe: " << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        getline(cin, name);
        id = search_p_by_parametr(pipe_group, check_p_name, name);
    }
    else {
        bool k;
        cout << "Enter status of pipe (0 if repairing, 1 if in work): " << endl;
        k = correctnumber(0, 1);
        id = search_p_by_parametr(pipe_group, check_p_status, k);
    }
}
void search_cs(unordered_map <int, CS>& cs_group, vector<int>& id) {
    int x;
    cout << "Search CS by 1.name 2.percentage of unused shops" << endl;
    x = correctnumber(1, 2);
    if (x == 1) {
        string name;
        cout << "Enter the name of CS: " << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        getline(cin, name);
        id = search_cs_by_parametr(cs_group, check_cs_name, name);

    }
    else {
        double k;
        cout << "Enter the percentage of unused shops" << endl;
        k = correctnumber(0, 100);
        id = search_cs_by_parametr(cs_group, check_unworking, k);
    }

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
    cout << "Working workshop: " << working_workshop << endl;
    cout << "Enter new number of working workshops" << endl;
    working_workshop = correctnumber(0, workshop);
}
void Pipe::edit_Pipe() {
    cout << status_check(status) << endl;
    cout << "Choose new status of pipe (0 if in repairing, 1 if in work)" << endl;
    status = correctnumber(0, 1);
    cout << status_check(status);
}
void Pipe::save_pipe(ofstream& file) {
    file << idp << endl << name << endl << lenght << endl << diameter << endl << status << endl;
}
void CS::save_cs(ofstream& file) {
    file << idcs << endl << name << endl
        << workshop << endl << working_workshop << endl << effectiveness << endl;
}
void Pipe::load_pipe(ifstream& file) {
    file >> idp;
    file >> name;
    file >> lenght;
    file >> diameter;
    file >> status;
}
void CS::load_cs(ifstream& file) {
    file >> idcs;
    file >> name;
    file >> workshop;
    file >> working_workshop;
    file >> effectiveness;
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
                int edit;
                int id;
                if (pipe_group.size() != 0) {
                    cout << "1.Choose one pipe 2.Choose pipes 3.Delete pipe";
                    edit = correctnumber(1, 2);
                    if (edit == 1) {
                        cout << "\n1.Choose pipe to edit" << endl;
                        id = correctnumber(0, (int)pipe_group.size());
                        pipe_group[id].edit_Pipe();
                    }
                }
                else
                    cout << "There is no pipe to edit" << endl;
            break;
        }
            case 5: {
                cout << "1.Edit CS 2.Delete CS" << endl;
                int edit;
                edit = correctnumber(1, 2);
                if (edit == 1) {
                    if (cs_group.size() != 0) {
                        int id;
                        cout << "/nChoose CS to edit" << endl;
                        id = correctnumber(1, (int)cs_group.size());
                        cs_group[id].edit_cs();
                    }
                    else
                        cout << "There is no CS to edit" << endl;
                }
                else
                {

                }
            break;
        }
            case 6: {
                string x;
                cout << "Enter the name of file without .txt: " << endl;
                cin >> x;
                ofstream file;
                file.open(x + ".txt");
                if (!file) 
                    cout << "Error" << endl;
                else {
                    file << pipe_group.size() << " " << cs_group.size() << endl;
                    for (auto pipe : pipe_group)
                        pipe.second.save_pipe(file);
                    for (auto cs : cs_group)
                        cs.second.save_cs(file);
                }
                break;
            }
            case 7: { 
                string x;
                int len1, len2;
                Pipe newP;
                CS newCS;
                cout << "Enter the name of file without .txt: " << endl;
                cin >> x;
                ifstream file;
                file.open(x + ".txt");
                if (!file)
                    cout << "There is no such file";
                else {
                    Pipe::max_id = 0;
                    CS::max_idd = 0;
                    pipe_group.clear();
                    cs_group.clear();
                    file >> len1 >> len2;
                    for (int i = 0; i < len1; i++) {
                        newP.load_pipe(file);
                        pipe_group.insert({ newP.get_id(),newP });
                        if (Pipe::max_id < newP.get_id()) {
                            Pipe::max_id = newP.get_id();
                        }
                    }
                    for (int i = 0; i < len2; i++) {
                        newCS.load_cs(file);
                        cs_group.insert({ newCS.get_idd(),newCS });
                        if (CS::max_idd < newCS.get_idd());
                        CS::max_idd = newCS.get_idd();

                    }
                }
                break;
            }
            case 8: {
                vector <int> x;
                search_p(pipe_group, x);
                for (auto& i : x)
                    cout << pipe_group[i] << endl;

                break;
            }
            case 9: {
                vector <int> x;
                search_cs(cs_group, x);
                for (auto& i : x)
                    cout << cs_group[i] << endl;
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
