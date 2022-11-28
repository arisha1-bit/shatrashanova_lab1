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
#include "graph.h"
using namespace std;
int main()
{
    System network;
    int option = -1;
    while (option) {
        cout << "\nChoose option:\n 1.Add pipe 2.Add CS 3.View all objects " <<
            "4.Edit pipe 5.Edit CS 6.Save 7.Load 8.Search pipe 9.Search CS 0.Exit 10.Create a gas transportation system\n";
        option = correctnumber(0, 10);
        switch (option) {
        case 1: {
            Pipe p;
            cin >> p;
            network.pipe_group.insert({ p.get_id(), p });
            network.pipe.insert(p.get_id());
            break;
        }
        case 2: {
            CS cs;
            cin >> cs;
            network.cs_group.insert({ cs.get_id(), cs });
            network.c_s.insert(cs.get_id());
            break;
        }
        case 3: {
            network.information();
            break;
        }
        case 4: {
            network.edit();
            break;
        }
        case 5: {
            network.editcs();
                break;
            }
        case 6: {
            network.save();
            break;
        }
        case 7: {
            network.load();
            break;
        }
        case 8: {
            if (network.pipe_group.size() != 0) {
                auto x = network.search_p();
                if (x.size() != 0) {
                    for (auto& i : x)
                        cout << network.pipe_group[i] << endl;
                }
                else
                    cout << "There is no such pipe" << endl;
            }
            else
                cout << "There is no pipe to find" << endl;
            break;
        }
        case 9: {
            
            if (network.cs_group.size() != 0) {
                auto x=network.search_cs();
                if (x.size() != 0) {
                    for (auto& i : x)
                        cout << network.cs_group[i] << endl;
                }
                else
                    cout << "There is no such CS";
            }
            else
                cout << "There is no CS to find" << endl;
            break;
        }
        case 10: {
            cout << "1.Connect 2.Disconnect" << endl;
                int choise = correctnumber(1, 2);
                if (choise == 1){
                    if ((network.c_s.size() < 2) or (network.pipe.size() < 1))
                        cout << "Not enough objects to create system" << endl;
                    else 
                        cin >> network;
                    }
                else {
                    if (network.graphs.size() != 0) {
                        cout << "Input the entering CS" << endl;
                        int x = correctnumber(0, CS::max_idd);
                        cout << "Input the exiting CS" << endl;
                        int y = correctnumber(0, CS::max_idd);
                            while (x == y) {
                                cout << "You can't disconnect same CS" << endl;
                                y = correctnumber(0, CS::max_idd);
                            }
                            auto i = network.graphs.cbegin();
                            while (i != network.graphs.cend()) {
                                if (((*i).second.id_entrance == x) and ((*i).second.id_exit == y)) {
                                    network.graphs.erase(i);
                                    break;
                                }
                                i++;
                            }
                    }
                        
                    else
                        cout << "There is no any system" << endl;
                    
                } 
            for (auto& [i, j] : network.graphs)
                cout <<i<<") " << j.id_entrance << " " << j.id_exit << " " << j.id_pipe << endl;
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
