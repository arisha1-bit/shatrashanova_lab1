#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <float.h>
#include <unordered_map>
#include <unordered_set>
#include "header.h"
using namespace std;
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
        cout << "Error!!! Input numeric value >= " << min << " and =< " << max<<endl;
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
            out << "\nIndex of pipe: " << p.idp << "\nPipe info: " << "\nName: " << p.name << "\nLenght: " 
                << p.lenght << "\nDiameter : " << p.diameter
                << "\nStatus: " << status_check(p.status) << endl;
            return out;
        }
ostream& operator<< (ostream& out, CS& cs) {
            out << "\nIndex of CS: " << cs.idcs << "\nCS info:\nName: " << cs.name << "\nNumber of workshops: " << cs.workshop
                << "\nNumber of working workshops: " << cs.working_workshop << "\nEffectiveness: "
                << cs.effectiveness << "%" << endl;
            return out;
}
ostream& operator<< (ostream& out, unordered_set <int>& p) {
    out << "Exiting id: ";
    for (auto& i : p) {
        out << i << " ";
    }
    out << endl;
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
    cout << "Status: " << status_check(status) << endl;
    cout << "Enter new status of pipe (0 if in repairing, 1 if works)" << endl;
    status = correctnumber(0,1);
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
    getline(file, name);
    getline(file, name);
    file >> lenght;
    file >> diameter;
    file >> status;
    iddp.insert(idp);
}
void CS::load_cs(ifstream& file) {
    file >> idcs;
    iddcs.insert(idcs);
    getline(file, name);
    getline(file, name); 
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
        option = correctnumber(0, 9);
        switch (option) {
        case 1: {
            iddp.insert(Pipe::max_id);
            Pipe p;
            cin >> p;
            pipe_group.insert({ p.get_id(), p });
            break;
        }
        case 2: {
            iddcs.insert(CS::max_idd);
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
            int id1;
            int x;
            vector <int> idp;
            if (pipe_group.size() != 0) {
                cout << "1.Choose one pipe 2.Choose pipes 3.Delete pipe" << endl;;
                edit = correctnumber(1, 3);
                if (edit == 1) {
                    cout << "1.Choose pipe to edit" << endl;
                    cout << iddp;
                    id1 = correctnumber(0, (int)pipe_group.size());
                    if (iddp.find(id1) != iddp.end()) {
                        pipe_group[id1].edit_Pipe();
                        cout << "Pipe was edited";
                    }
                    else
                        cout << "There is no such pipe";
                }
                if (edit == 2) {
                    vector <int> idp;
                    cout << "Choose pipes by 1.filter 2.id" << endl;
                    x = correctnumber(1, 2);
                    if (x == 1) {
                        search_p(pipe_group, idp);
                        if (idp.size() != 0) {
                            cout << "Enter new status (0 if repairing, 1 if works)" << endl;
                            bool s;
                            s = correctnumber(0, 1);
                            for (auto& i : idp)
                                pipe_group[i].status = s;
                        }

                        else
                            cout << "There is no such pipe";
                    }


                    if (x == 2) {
                        unordered_set <int> ids;
                        cout << iddp;
                        cout << "Enter the number of identifiers of pipe you want to edit" << endl;
                        int n;
                        int y;
                        n = correctnumber(0, (int)pipe_group.size());
                        cout << "Enter idetifiers of pipes" << endl;
                        for (int i = 0; i < n; i++) {
                            y = correctnumber(0, Pipe::max_id - 1);
                            if (pipe_group.find(y) != pipe_group.end()) {
                                if (iddp.find(y) != iddp.end())
                                    ids.insert(y);
                            }
                            else
                            {
                                cout << "There is no such pipe" << endl;;
                                i = i - 1;
                            }
                        }
                        cout << "Enter new status (0 if repairing, 1 if works)" << endl;
                        bool s;
                        s = correctnumber(0, 1);
                        for (auto& i : ids) {
                            for (auto& i : ids)
                                pipe_group[i].status = s;
                        }
                    }
                }
                if (edit == 3) {
                    cout << "1. identifier of one pipe you want to delete 2.delete some pipes" << endl;
                    int d;
                    d = correctnumber(1, 2);
                    if (d == 1) {
                        cout << iddp;
                        cout << "Enter id of pipe you want to delete" << endl;
                        int n;
                        n = correctnumber(0, (int)pipe_group.size());
                        if (iddp.find(n) != iddp.end()) {
                            pipe_group.erase(pipe_group.find(n));
                        }
                    }
                    else {
                        unordered_set <int> id;
                        cout << "1.delete by filter 2.delete by id" << endl;
                        int n;
                        n = correctnumber(1, 2);
                        int x;
                        if (n == 2) {
                            cout << iddp;
                            cout << "Enter the number of pipe you want to edit" << endl;;
                            int y;
                            y = correctnumber(1, (int)pipe_group.size());
                            cout << "Enter idetifiers of pipes" << endl;
                            for (int i = 0; i < y; i++) {
                                cin >> x;
                                if (iddp.find(x) != iddp.end()) {
                                    id.insert(x);
                                    
                                }
                                else
                                {
                                    i = i - 1;
                                    cout << "There is no such pipe" << endl;

                                    
                                }
                            }
                            for (auto& pi : id) {
                                pipe_group.erase(pipe_group.find(pi));

                            }
                        }

                        else {
                            search_p(pipe_group, idp);
                            for (auto& i : idp)
                                pipe_group.erase(pipe_group.find(i));
                            for (auto& i : idp)
                                iddp.erase(i);
                        }
                    }
                }

                    cout << "Pipe was deleted";

                
                
            }
            else
                cout << "There is no pipe to edit" << endl;
            break;
        }
        case 5: {
            vector <int> idcs;
            if (cs_group.size() != 0) {
                cout << "1.Edit one CS 2.Edit CSs 3.Delete CS" << endl;
                int edit;
                edit = correctnumber(1, 3);
                if (edit == 1) {
                    int id;
                    cout << iddcs;
                    cout << "Choose CS to edit" << endl;
                    id = correctnumber(0, (int)cs_group.size());
                    if (iddcs.find(id) != iddcs.end()) {
                        cs_group[id].edit_cs();
                        cout << "CS was edited";
                    }
                }
                if (edit == 2) {
                    unordered_set <int> idw;
                    cout << "Choose  by 1.filter 2.id" << endl;
                    int n;
                    n = correctnumber(1, 2);
                    if (n == 2) {
                        cout << iddcs;
                        cout << "Enter the number of cs you want to edit";
                        int y;
                        y = correctnumber(0, (int)cs_group.size());
                        cout << "Enter idetifiers of CSs" << endl;
                        for (int i = 0; i < y; i++) {
                            if (cs_group.find(i) != cs_group.end())
                                idw.insert(i);

                        }
                        for (auto& id : iddcs) {
                            if (iddcs.find(id) != iddcs.end()) {
                                for (auto& i : idw)
                                    cs_group[i].edit_cs();
                            }
                            else {
                                cout << "There is no such cs";
                                break;
                            }
                        }


                    }
                    else {
                        search_cs(cs_group, idcs);
                        for (auto& i : idcs)
                            cs_group[i].edit_cs();
                    }

                }
                if (edit == 3) {
                    cout << "1. identifier of one CS you want to delete 2.delete some CS" << endl;
                    int d;
                    d = correctnumber(1, 2);
                    if (d == 1) {
                        cout << iddcs;
                        cout << "Enter id of CS you want to delete" << endl;
                        int n;
                        n = correctnumber(0, (int)cs_group.size());
                        if (iddcs.find(n) != iddcs.end()) {
                            cs_group.erase(cs_group.find(n));
                        }
                    }
                    else {
                        unordered_set <int> idd;
                        cout << "1.delete by filter 2.delete by id" << endl;
                        int n;
                        n = correctnumber(1, 2);
                        if (n == 2) {
                            cout << iddcs;
                            cout << "Enter the number of cs you want to edit" << endl;
                            int y;
                            int x;
                            y = correctnumber(1, (int)cs_group.size());
                            cout << "Enter idetifiers of CSs" << endl;
                            for (int i = 0; i < y; i++) {
                                cin >> x;
                                if (cs_group.find(x) != cs_group.end())
                                    idd.insert(x);
                                else
                                {
                                    i = i - 1;
                                    cout << "There is no such CS" << endl;
                                }
                            }
                            for (auto& i : idd)

                                cs_group.erase(cs_group.find(i));



                        }
                        else {
                            search_cs(cs_group, idcs);
                            for (auto& i : idcs)
                                cs_group.erase(cs_group.find(i));
                            for (auto& i : iddcs)
                                iddcs.erase(i);
                        }
                    }
                }
            

                    cout << "CS was deleted";

                
            }
            else
                cout << "There is no CS to edit" << endl;
            break;
        }
        case 6: {
            string x;
            cout << "Enter the name of file " << endl;
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
            cout << "Enter the name of file  " << endl;
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
                    if (Pipe::max_id <= newP.get_id())
                        Pipe::max_id = newP.get_id() + 1;

                }
                for (int i = 0; i < len2; i++) {
                    newCS.load_cs(file);
                    cs_group.insert({ newCS.get_idd(),newCS });
                    if (CS::max_idd <= newCS.get_idd())
                        CS::max_idd = newCS.get_idd() + 1;

                }
            }
            break;
        }
        case 8: {
            vector <int> x;
            if (pipe_group.size() != 0) {
                search_p(pipe_group, x);
                if (x.size() != 0) {
                    for (auto& i : x)
                        cout << pipe_group[i] << endl;
                }
                else
                    cout << "There is no such pipe" << endl;
            }
            else
                cout << "There is no pipe to find" << endl;
            break;
        }
        case 9: {
            vector <int> x;
            if (cs_group.size() != 0) {
                search_cs(cs_group, x);
                if (x.size() != 0) {
                    for (auto& i : x)
                        cout << cs_group[i] << endl;
                }
                else
                    cout << "There is no such CS";
            }
            else
                cout << "There is no CS to find" << endl;
            break;
        }
        case 0: {
            return 0;
        }
        default: cout << "Input correct number (0-7)";
            break;

        }
    }
    return 0;
} 
