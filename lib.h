#include <iostream>
#include <math.h>
#include <sstream>
#include <vector>
#include <vector>

using namespace std;

stringstream convet;

class Run : public error_code {
    public:
        string res;
        bool useA = true;
        bool useB = true;
};

class Op {
    public:
        virtual Run run(double a, double b, string A, string B) { return *new Run; };
        virtual int getPri() { return 0; };
        virtual string getOp() { return ""; };
};

class Operation {
    public:
        int min;
        int max;
        int pri;
        bool exi;
        Op* obj;
        string ope;
};

bool onlyType(string s, string t);
string parse(string s);
string generify(string s);