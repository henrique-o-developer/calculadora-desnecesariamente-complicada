#include <iostream>
#include <math.h>
#include <sstream>
#include <utility>
#include <vector>
#include <vector>

using namespace std;

class Run : public error_code {
public:
    string res;
    bool useA = true;
    bool useB = true;
    int aLe = -1;
    int bLe = -1;
    string ret;
};

class parseR {
public:
    string full;
    string res;
};

class Aditional {
public:
    string s;
    string ret;
    int min;
    int max;
};

class Op {
public:
    Run (*r)(double a, double b, string A, string B, Aditional ad);
    int pri;
    string op;

    Op(Run (*rc)(double a, double b, string A, string B, Aditional ad), int pric, string opc) {
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
parseR parse(string s);
string generify(string s);
bool include(string s, string h);