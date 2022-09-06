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

string parse(string s);