#include "graph.h"
#include "pipe.h"
#include "cs.h"
#include "checking.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <float.h>
#include <unordered_map>
#include <unordered_set>
using namespace std;

int System::Graph::max_idg = 0;
bool check_p_name(Pipe p, string name) {
    return (p.name.find(name) != string::npos);
}
bool check_p_status(Pipe p, bool status) {
    return (p.status == status);
}
bool check_cs_name(CS cs, string name) {
    return (cs.name.find(name) != string::npos);
}
bool check_unworking(CS cs, double p) {
    return (cs.get_unused() >= p);
}
vector<int> System::search_cs() {
    int x;
    vector <int> id;
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
        id = search_cs_by_parametr(cs_group,check_unworking, k);
    }
    return id;
}
vector<int> System::search_p() {
    vector<int> ids;
    int x;
    cout << "Search pipe by 1.name 2.status" << endl;
    x = correctnumber(1, 2);
    if (x == 1) {
        string name;
        cout << "Enter the name of pipe: " << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        getline(cin, name);
        ids = search_p_by_parametr(pipe_group,check_p_name, name);
    }
    else {
        bool k;
        cout << "Enter status of pipe (0 if repairing, 1 if in work): " << endl;
        k = correctnumber(0, 1);
        ids = search_p_by_parametr(pipe_group,check_p_status, k);
    }
    return ids;
}
void System::information() {
    for (auto& pipe : pipe_group) {
        cout << pipe.second << endl;
    }
    for (auto& cs : cs_group) {
        cout << cs.second << endl;
    }
}
void System::save() {
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
}
void System::load() {
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
            pipe.insert(newP.get_id());
            if (Pipe::max_id <= newP.get_id())
                Pipe::max_id = newP.get_id() + 1;

        }
        for (int i = 0; i < len2; i++) {
            newCS.load_cs(file);
            cs_group.insert({ newCS.get_id(),newCS });
            c_s.insert(newCS.get_id());
            if (CS::max_idd <= newCS.get_id())
                CS::max_idd = newCS.get_id() + 1;

        }
    }
}
void System::editcs() {
    vector <int> idcs;
    if (cs_group.size() != 0) {
        cout << "1.Edit one CS 2.Edit CSs 3.Delete CS" << endl;
        int edit;
        int x;
        edit = correctnumber(1, 3);
        if (edit == 1) {
            int id;
            cout << cs_group;
            cout << "Choose CS to edit" << endl;
            id = correctnumber(0, (int)cs_group.size());
            if (cs_group.find(id) != cs_group.end()) {
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
                cout << cs_group;
                cout << "Enter the number of cs you want to edit" << endl;
                int y;
                y = correctnumber(1, (int)cs_group.size());
                cout << "Enter idetifiers of CSs" << endl;
                for (int i = 0; idw.size() < y; i++) {
                    cin >> x;
                    if (cs_group.find(x) != cs_group.end())
                        idw.insert(x);
                    else {

                        cout << "There is no such cs" << endl;
                    }
                }
                for (auto& id : idw)

                    cs_group[id].edit_cs();
            }

            else {
                auto idp = search_cs();
                if (idp.size() != 0) {
                    for (auto& i : idp)
                        cs_group[i].edit_cs();
                }

                else {
                    cout << "There is no such CS";

                }

            }
        }
        if (edit == 3) {
            cout << "1. identifier of one CS you want to delete 2.delete some CS" << endl;
            int d;
            d = correctnumber(1, 2);
            if (d == 1) {
                cout << cs_group;
                cout << "Enter id of CS you want to delete" << endl;
                int n;
                n = correctnumber(0, CS::max_idd - 1);
                while (cs_group.find(n) == cs_group.end()) {
                    cout << "There is no such cs" << endl;
                    n = correctnumber(0, CS::max_idd - 1);
                }
                cs_group.erase(cs_group.find(n));

            }
            else {
                unordered_set <int> idd;
                cout << "1.delete by filter 2.delete by id" << endl;
                int n;
                n = correctnumber(1, 2);
                if (n == 2) {
                    cout << cs_group;
                    cout << "Enter the number of cs you want to edit" << endl;
                    int y;
                    int x;
                    y = correctnumber(1, (int)cs_group.size());
                    cout << "Enter idetifiers of CSs" << endl;
                    for (int i = 0; i < y; i++) {
                        x = correctnumber(0, CS::max_idd);
                        if (cs_group.find(x) != cs_group.end())
                            idd.insert(x);
                        else
                        {
                            i = i - 1;
                            cout << "There is no such CS" << endl;
                        }
                    }
                    for (auto& i : idd) {
                        cs_group.erase(cs_group.find(i));
                    }
                }
                else {
                    auto idp = search_cs();
                    if (idp.size() != 0) {
                        for (auto& i : idp) {
                            cs_group.erase(cs_group.find(i));
                        }
                    }
                    else {
                        cout << "There is no such cs" << endl;


                    }
                }

            }
        }
    }
    else
        cout << "There is no CS to edit" << endl;
}
void System::edit()
{
    if (pipe_group.size() != 0) {
        cout << "1.Choose one pipe 2.Choose pipes 3.Delete pipe" << endl;;
        int edit = correctnumber(1, 3);
        if (edit == 1) {
            cout << "1.Choose pipe to edit" << endl;
            cout << pipe_group;
            int id = correctnumber(0, (int)pipe_group.size());
            if (pipe_group.find(id) != pipe_group.end()) {
                pipe_group[id].edit_Pipe();
                cout << "Pipe was edited" << endl;
            }
            else
                cout << "There is no such pipe";
        }
        if (edit == 2) {
            cout << "Choose pipes by 1.filter 2.id" << endl;
            int x = correctnumber(1, 2);
            if (x == 1) {
                auto idp = search_p();
                if (idp.size() != 0) {
                    cout << "Enter new status (0 if repairing, 1 if works)" << endl;
                    bool s;
                    s = correctnumber(0, 1);
                    for (auto& i : idp)
                        pipe_group[i].status = s;
                }

                else {
                    cout << "There is no such pipe";

                }
            }


            if (x == 2) {
                unordered_set <int> ids;
                cout << pipe_group;
                cout << "Enter the number of identifiers of pipe you want to edit" << endl;
                int n;
                int id;
                n = correctnumber(1, (int)pipe_group.size());
                cout << "Enter idetifiers of pipes" << endl;
                for (int i = 0; ids.size() < n; i++) {
                    id = correctnumber(0, Pipe::max_id - 1);
                    if (pipe_group.find(id) != pipe_group.end()) {
                        if (pipe_group.find(id) != pipe_group.end())
                            ids.insert(id);
                    }
                    else
                    {
                        cout << "There is no such pipe" << endl;;
                    }
                }
                cout << "Enter new status (0 if repairing, 1 if works)" << endl;
                bool s;
                s = correctnumber(0, 1);
                for (auto& i : ids) {
                    pipe_group[i].status = s;
                }
            }
        }
        if (edit == 3) {
            cout << "1. identifier of one pipe you want to delete 2.delete some pipes" << endl;
            int d;
            d = correctnumber(1, 2);
            if (d == 1) {
                cout << pipe_group;
                cout << "Enter id of pipe you want to delete" << endl;
                int n;
                n = correctnumber(0, Pipe::max_id - 1);
                while (pipe_group.find(n) == pipe_group.end()) {
                    cout << "There is no such pipe" << endl;
                    n = correctnumber(0, Pipe::max_id - 1);
                }
                pipe_group.erase(pipe_group.find(n));
            }

            else {
                unordered_set <int> ids;
                cout << "1.delete by filter 2.delete by id" << endl;
                int action = correctnumber(1, 2);
                if (action == 2) {
                    cout << pipe_group;
                    cout << "Enter the number of pipe you want to edit" << endl;;
                    int n = correctnumber(1, (int)pipe_group.size());
                    cout << "Enter idetifiers of pipes" << endl;

                    while (ids.size() < n)
                    {
                        int x = correctnumber(0, Pipe::max_id - 1);
                        if (pipe_group.find(x) != pipe_group.end())
                            ids.insert(x);
                        else
                            cout << "There is no such pipe" << endl;
                    }

                    for (auto& id : ids) {
                        pipe_group.erase(pipe_group.find(id));
                    }

                }

                else {
                    auto idp = search_p();
                    if (idp.size() != 0) {
                        for (auto& i : idp) {
                            pipe_group.erase(pipe_group.find(i));
                        }
                        cout << "Pipe was deleted";
                    }
                    else {
                        cout << "There is no such pipe";

                    }

                }
            }

        }
    }



    else
        cout << "There is no pipe to edit" << endl;
}
ostream& operator<<(ostream& out, unordered_set<int> s) {
    cout << "Free objects: ";
    for (auto& i : s)
        cout<< i << " ";
    cout << endl;
    return out;
}
istream& operator>> (istream& in, System& s) {
    System::Graph gr;
    cout << s.c_s;
    cout << "Choose CS (id) on entrance" << endl;
    gr.id_entrance = correctnumber(0, INT_MAX);
    while (s.cs_group.find(gr.id_entrance) == s.cs_group.end()) {
        cout << "There is no such CS, try again" << endl;
        gr.id_entrance = correctnumber(0, INT_MAX);
    }
    cout << s.c_s;
    cout << "Choose CS(id) on exit" << endl;
    gr.id_exit = correctnumber(0, INT_MAX);
    while (s.cs_group.find(gr.id_exit) == s.cs_group.end()) {
        cout << "There is no such CS, try again" << endl;
        gr.id_exit = correctnumber(0, INT_MAX);
    }
    cout << s.pipe;
    cout << "Choose Pipe(id) to connect" << endl;
    gr.id_pipe = correctnumber(0, INT_MAX);
    while (s.pipe_group.find(gr.id_pipe) == s.pipe_group.end()) {
        cout << "There is no such pipe, try again" << endl;
        gr.id_pipe = correctnumber(0, INT_MAX);
    }
    for (auto& i : s.pipe) {
        s.pipe.erase(s.pipe.find(gr.id_pipe));
        break;
    }
    s.graphs.insert({gr.id,gr });
    return in;

}