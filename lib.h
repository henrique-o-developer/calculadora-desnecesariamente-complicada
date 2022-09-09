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

class Run {
public:
    string res;
    bool useA = true;
    bool useB = true;
    int aLe = -1;
    int bLe = -1;
    string ret;
    vector<formatter> keys;
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
};

class Aditional {
public:
    string s;
    string ret;
    int min;
    int max;
    vector<formatter> keys;
};

class Op {
public:
    Run (*r)(long double a, long double b, string A, string B, Aditional ad);
    int pri;
    string op;

    Op(Run (*rc)(long double a, long double b, string A, string B, Aditional ad), int pric, string opc) {
        r = rc;
        pri = pric;
        op = std::move(opc);
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
parseR parse(string s, vector<formatter> keys);
bool include(string s, string h);
numberF separate(string num);
long double hstod(string s, vector<formatter> keys);
string formatNumber(string s);