#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <float.h>
#include <unordered_map>
#include <unordered_set>
using namespace std;
class Pipe
{

    public:
        static int max_id;
        string name = "";
        bool status = 0;
        Pipe() {
            idp = max_id++;
        }
        friend istream& operator>> (istream& in, Pipe& p);
        friend ostream& operator<< (ostream& out, Pipe& p);
        void edit_Pipe();
        void save_pipe(ofstream& file);
        void load_pipe(ifstream& file);
        int get_id() { return idp; }

    private:
        double lenght = 0, diameter = 0;
        int idp = 0;

    };


