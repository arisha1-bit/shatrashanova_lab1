#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <float.h>
#include <unordered_map>
#include <unordered_set>
#include "pipe.h"
#include "cs.h"
using namespace std;
class System
{
public:
	unordered_map <int, Pipe> pipe_group;
	unordered_map <int, CS> cs_group;
	unordered_set<int> pipe;
	unordered_set<int> c_s;
	void information();
	void save();
	void load();
	void editcs();
	vector<int> search_cs();
	void edit();
	vector<int> search_p();
	struct Graph {
		static int max_idg;
		int id;
		Graph() {
			id = max_idg++;
		}
		int id_entrance;
		int id_exit;
		int id_pipe;
	};
	friend istream& operator>> (istream& in, System& s);
	friend ostream& operator<<(ostream& out, unordered_set<int> s);
	unordered_map <int,Graph> graphs;
	int check_pipe(int x);
};
