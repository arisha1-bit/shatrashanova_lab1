﻿// shatrashanova1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
using namespace std;
struct Pipe
{
    float lenght = 0, diameter = 0;
    int status = -1, change_pipe = 0;

};
struct CS
{
    string name="";
    int  workshop = 0, working_workshop = -1, change_cs = 0;
    float effectiveness = 0;

};
int main()
{
    int option = -1; 
    Pipe p;
    CS cs;

    while (option) {
        cout << "\nChoose option:\n 1.Add pipe 2.Add CS 3.View all objects 4.Edit pipe 5.Edit CS 6.Save 7.Load 0.Exit\n";
        cin >> option;
        if (option == 1) {
            cout << "\nInput lenght ";
            cin >> p.lenght;
            if (!p.lenght) {
                do {
                    cout << "Error!!! Input numeric value" << endl;
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    cin >> p.lenght;
                } while (!p.lenght);
            }
            cout << "\nInput diameter ";
            cin >> p.diameter;
            if (!p.diameter) {
                do {
                    cout << "Error!!! Input numeric value" << endl;
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    cin >> p.diameter;
                } while (!p.diameter);
            }
            cout << "\nChoose status of pipe (1 if repairing, 2 if works) ";
            cin >> p.status;
            if ((p.status>2) || (!p.status) || (p.status<0)) {
                do {
                    cout << "Error!!! Input numeric value (1 or 2)" << endl;
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    cin >> p.status;
                } while ((p.status > 2) || (!p.status) || (p.status<0));
            }
            if (p.status == 1) {
                cout << "\nPipe is repairing\n"<<endl;
            }
            else {
                cout << "\nPipe works\n"<<endl;
            }
        }
        if (option == 2) {
            cout << "\nInput name ";
            cin >> cs.name;
            cout << "\nNumber of workshops ";
            cin >> cs.workshop;
            cout << "\nNumber of working workshops ";
            cin >> cs.working_workshop;
            cout << "\nInput effectiveness ";
            cin >> cs.effectiveness;
        }
        if (option == 3) {
            cout << "\nPipe info:\nLenght: " << p.lenght << "\nDiameter: " << p.diameter;
            if (p.status == 0) {
                cout << "\nStatus: repairing\n\n\n";
            }
            else {
                cout << "\nStatus: works\n\n\n";
            }
            cout << "\n\nCS info:\nName: " << cs.name << "\nNumber of workshops: " << cs.workshop << "\nNumber of working workshops: " << cs.working_workshop << "\nEffectiveness: " << cs.effectiveness << "\n\n\n";
        }
        if (option == 4) {
            if (p.lenght == 0 && p.diameter == 0 && p.status == -1)
                cout << "\nThere is no pipe to edit"<<endl;
            else {
                cout << "\nLenght: " << p.lenght << "\nDiameter: " << p.diameter;
                if (p.status == 1) {
                    cout << "\nStatus: repairing\n\n";
                }
                else {
                    cout << "\nStatus: works\n\n";
                }
                do {
                    cout << "Which  property you want to change? 1.Lenght 2.Diameter 3.Status 4.Done 5.Cancel" << endl;
                
                    cin >> p.change_pipe;
                    if (p.change_pipe == 1) {
                        cout << "\nInput new lenght" << endl;
                        cin >> p.lenght;
                        cout << "\nSuccesfully! new lenght: " << p.lenght << endl;
                    }
                    else if (p.change_pipe == 2) {
                        cout << "\nInput new diameter" << endl;
                        cin >> p.diameter;
                        cout << "\nSuccesfully! new diameter: " << p.diameter << endl;
                    }
                    else if (p.change_pipe == 3) {
                        cout << "\nChoose new status: (0 if repairing, 1 of works)" << endl;
                        cin >> p.status;
                        if (p.status == 1) 
                            cout << "\nSuccesfully! new Status: repairing\n";
                        else 
                            cout << "\nSuccesfully! new Status: works\n";   
                    }
                }
                while (p.change_pipe != 4 && p.change_pipe!=5);
                if (p.change_pipe == 4)
                    cout << "\nPipe was changed" << endl;
                if (p.change_pipe == 5)
                    cout << "\Changing was canceled" << endl;
            }
            
        }
        if (option == 5) {
            if (cs.name == "" && cs.workshop == 0 && cs.working_workshop == -1 && cs.effectiveness==0)
                cout << "\nThere is no CS to edit" << endl;
            else {
                cout << "\nName: " << cs.name << "\nWorkshops: " << cs.workshop << "\nWorking workshops: " << cs.working_workshop << "\nEffectiveness: " << cs.effectiveness << endl;
                do {
                    cout << "Which  property you want to change? 1.Name 2.Workshops 3.Working workshops 4.Effectiveness 5.Done 6.Cancel" << endl;

                    cin >> cs.change_cs;
                    if (cs.change_cs == 1) {
                        cout << "\nInput new name" << endl;
                        cin >> cs.name;
                        cout << "\nSuccesfully! new name: " << cs.name << endl;
                    }
                    else if (cs.change_cs == 2) {
                        cout << "\nInput new number of workshops" << endl;
                        cin >> cs.workshop;
                        cout << "\nSuccesfully! new number of workshops: " << cs.workshop << endl;
                    }
                    else if (cs.change_cs == 3) {
                        cout << "\nInput new number of working workshops" << endl;
                        cin >> cs.working_workshop;
                        cout << "\nSuccesfully! new number of working workshops: " << cs.working_workshop << endl;
                    }
                    else if (cs.change_cs == 4) {
                        cout << "\nInput new effectiveness" << endl;
                        cin >> cs.effectiveness;
                        cout << "\nSuccesfully! new effectiveness: " << cs.effectiveness << endl;
                    }
                } while (cs.change_cs != 5 && cs.change_cs != 6);
                if (cs.change_cs == 5)
                    cout << "\nPipe was changed" << endl;
                if (cs.change_cs == 6)
                    cout << "\Changing was canceled" << endl;
            }

        }
        if (option == 0) {
            return 0;
        }

        system("pause");
    }

    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
