#include <iostream>
#include <math.h>
#include <sstream>
#include <utility>
#include <vector>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

class formatter {
public:
    string l;
    long double v;
};

class funct {
public:
    string n;
    string c;
};

class Run {
public:
    string res;
    bool useA = true;
    bool useB = true;
    int aLe = -1;
    int bLe = -1;
    string ret;
    vector<formatter> keys;
    vector<funct> func;
};

class numberF {
public:
    string n;
    string l;
};

class parseR {
public:
    string full;
    string res;
    vector<formatter> keys;
    vector<funct> func;
};

class Aditional {
public:
    string s;
    string ret;
    int min;
    int max;
    string A;
    string B;
    vector<formatter> keys;
    vector<funct> func;
};

class Op {
public:
    Run (*r)(vector<long double> a, vector<long double> b, vector<string> A, vector<string> B, Aditional ad);
    int pri;
    string op;
    string rev;

    Op(Run (*rc)(vector<long double> a, vector<long double> b, vector<string> A, vector<string> B, Aditional ad), int pric, string opc, string reverse) {
        r = rc;
        pri = pric;
        op = std::move(opc);
        rev = reverse;
    }
};

class Operation {
public:
    int min;
    int max;
    long long pri;
    bool exi;
    Op* obj;
    string ope;
};

bool onlyType(string s, const string& t);
parseR parse(string s, vector<formatter> keys, vector<funct> func);
bool include(string s, string h);
numberF separate(string num);
vector<long double> hstod(string s, vector<formatter> keys);
string formatNumber(string s);
string generify(string s, int ii, bool fow);
vector<string> split(string s, string d);