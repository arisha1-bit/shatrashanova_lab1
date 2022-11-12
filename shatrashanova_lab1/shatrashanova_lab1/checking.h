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
template <typename T>
T correctnumber(T min, T max) {
    T x;
    while (((cin >> x).fail()) || (cin.peek() != '\n') || (x < min) || (x > max)) {
        cout << "Error!!! Input numeric value >= " << min << " and =< " << max << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }
    return x;
}
template <typename T>
ostream& operator<< (ostream& out, unordered_map <int, T>& p) {
    out << "Exiting id: ";
    for (auto& [i, obj] : p) {
        out << i << " ";
    }
    out << endl;
    return out;
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
            id.push_back(cs.second.get_id());
    }
    return id;
}
