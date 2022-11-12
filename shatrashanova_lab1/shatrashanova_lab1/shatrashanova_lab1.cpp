#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <float.h>
#include <unordered_map>
#include <unordered_set>
#include "cs.h"
#include "pipe.h"
#include "checking.h"
using namespace std;
void information(unordered_map<int, Pipe>& pipe_group, unordered_map<int, CS>& cs_group) {
    for (auto& pipe : pipe_group) {
        cout << pipe.second << endl;
    }
    for (auto& cs : cs_group) {
        cout << cs.second << endl;
    }
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
vector<int> search_p(unordered_map <int, Pipe>& pipe_group) {
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
        ids = search_p_by_parametr(pipe_group, check_p_name, name);
    }
    else {
        bool k;
        cout << "Enter status of pipe (0 if repairing, 1 if in work): " << endl;
        k = correctnumber(0, 1);
        ids = search_p_by_parametr(pipe_group, check_p_status, k);
    }
    return ids;
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
void edit(unordered_map<int,Pipe>& pipe_group) 
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
                auto idp = search_p(pipe_group);
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
                    //for (int i = 0; i < y; i++)
                    while (ids.size()<n)
                    {
                        int x = correctnumber(0, Pipe::max_id-1);
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
                    vector <int> idp  = search_p(pipe_group);
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
void editcs(unordered_map<int, CS>& cs_group) {
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
                search_cs(cs_group, idcs);
                if (idcs.size() != 0) {
                    for (auto& i : idcs)
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
                    search_cs(cs_group, idcs);
                    if (idcs.size() != 0) {
                        for (auto& i : idcs) {
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
            Pipe p;
            cin >> p;
            pipe_group.insert({ p.get_id(), p });
            break;
        }
        case 2: {
            CS cs;
            cin >> cs;
            cs_group.insert({ cs.get_id(), cs });
            break;
        }
        case 3: {
            information(pipe_group, cs_group);
            break;
        }
        case 4: {
            edit(pipe_group);
            break;
        }
        case 5: {
            editcs(cs_group);
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
                    cs_group.insert({ newCS.get_id(),newCS });
                    if (CS::max_idd <= newCS.get_id())
                        CS::max_idd = newCS.get_id() + 1;

                }
            }
            break;
        }
        case 8: {
            if (pipe_group.size() != 0) {
                auto x = search_p(pipe_group);
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
