#include <iostream>
#include <math.h>
#include <sstream>
#include <vector>
#include <vector>

using namespace std;

stringstream convet;

class Operation {
    public:
        int min;
        int max;
        int pri;
        bool exi;
        string ope;
};

class Run : public error_code {
    public:
        string res;
        bool useA = true;
        bool useB = true;
};

bool onlyType(string s, string t);
string parse(string s);
string generify(string s);