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
        if (option == 1) {
            cout << "\nInput lenght ";
            cin >> p.lenght;
            p.lenght= check_cin(p.lenght);
            cout << "\nInput diameter ";
            cin >> p.diameter;
            p.diameter=check_cin(p.diameter);
            cout << "\nChoose status of pipe (1 if repairing, 2 if works) ";
            cin >> p.status;
            p.status=check_status_cin(p.status);
            cout << status_check(p.status) << endl;
        }
        if (option == 2) {
            cout << "\nInput name ";
            cin >> cs.name;
            cout << "\nNumber of workshops ";
            cin >> cs.workshop;
            cs.workshop=check_cin(cs.workshop);
            cout << "\nNumber of working workshops ";
            cin >> cs.working_workshop;
            cs.working_workshop=check_workshop_cin(cs.working_workshop, cs.workshop);
            cs.effectiveness = float(cs.workshop) / float(cs.working_workshop);
            cout << "\nEffectiveness: " << cs.effectiveness << endl;
        }
        if (option == 3) {
            cout << "\nPipe info:\nLenght: " << p.lenght << "\nDiameter: " << p.diameter << "\nStatus: " << status_check(p.status) << endl;;
            cout << "\n\nCS info:\nName: " << cs.name << "\nNumber of workshops: " << cs.workshop << "\nNumber of working workshops: " << cs.working_workshop << "\nEffectiveness: " << cs.effectiveness << "\n\n\n";
        }
        if (option == 4) {
            if (p.status == -1)
                cout << "\nThere is no pipe to edit" << endl;
            else {
                cout << "Input new status of pipe (1 if pipe is repairing, 2 if pipe works" << endl;
                cin >> p.status;
                p.status=check_status_cin(p.status);
                cout << status_check(p.status) << endl;
            }


        }
        if (option == 5) {
            if (cs.working_workshop==-1)
                cout << "\nThere is no CS to edit" << endl;
            else {
                cout << "Input new number of working workshops: " << endl;
                cin >> cs.working_workshop;
                cs.working_workshop=check_workshop_cin(cs.working_workshop, cs.workshop);
                cs.effectiveness = float(cs.workshop) / float(cs.working_workshop);
                cout << "\nEffectiveness: " << cs.effectiveness << endl;
            }
        }
        if (option == 0) {
            return 0;
        }
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