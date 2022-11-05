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
    friend ostream& operator<< (ostream& out, unordered_set <int>& p);
    friend ostream& operator<< (ostream& out, Pipe& p);
    void edit_Pipe();
    void save_pipe(ofstream& file);
    void load_pipe(ifstream& file);
    int get_id() { return idp; }

private:
    double lenght = 0, diameter = 0;
    int idp = 0;

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
      double get_unused() { return (((double)workshop - (double)working_workshop) / (double)workshop) * 100; }
      string name = "";


private:
    int  workshop, working_workshop, idcs;
    double effectiveness;
};
int Pipe::max_id = 0;
int CS::max_idd = 0;
unordered_set <int> iddp;
unordered_set <int> iddcs;