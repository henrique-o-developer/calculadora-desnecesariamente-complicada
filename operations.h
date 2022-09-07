#include "lib.h"

class mais: public Op {
    public:
        Run run(double a, double b, string A, string B) {
            Run r;

            r.res = to_string(a+b);

            return r;
        };

        int getPri() {
            return 1;
        };

        string getOp() {
            return "+";
        };
};

class menos: public Op {
    public:
        Run run(double a, double b, string A, string B) {
            Run r;

            r.res = to_string(a-b);

            return r;
        };

        int getPri() {
            return 1;
        };

        string getOp() {
            return "-";
        };
};

class dividido: public Op {
    public:
        Run run(double a, double b, string A, string B) {
            Run r;

            r.res = to_string(a/b);

            return r;
        };

        int getPri() {
            return 2;
        };

        string getOp() {
            return "/";
        };
};

class vezes: public Op {
    public:
        Run run(double a, double b, string A, string B) {
            Run r;

            r.res = to_string(a*b);

            return r;
        };

        int getPri() {
            return 2;
        };

        string getOp() {
            return "*";
        };
};

class elevado: public Op {
    public:
        Run run(double a, double b, string A, string B) {
            Run r;

            r.res = to_string(pow(a, b));

            return r;
        };

        int getPri() {
            return 3;
        };

        string getOp() {
            return "^";
        };
};

class raiz_quadrada: public Op {
    public:
        Run run(double a, double b, string A, string B) {
            Run r;

            double sq;

            if (onlyType(A, "number") && !A.empty()) sq = a;
            else {
                sq = 2;

                r.useA = false;
            }

            r.res = to_string(pow(b, 1/sq));

            return r;
        };

        int getPri() {
            return 3;
        };

        string getOp() {
            return "sqrt";
        };
};

class cosseno: public Op {
    public:
        Run run(double a, double b, string A, string B) {
            Run r;

            r.res = to_string(cos(b));

            r.useA = false;

            return r;
        };

        int getPri() {
            return 4;
        };

        string getOp() {
            return "cos";
        };
};

class tangente: public Op {
    public:
        Run run(double a, double b, string A, string B) {
            Run r;

            r.res = to_string(tan(b));

            r.useA = false;

            return r;
        };

        int getPri() {
            return 4;
        };

        string getOp() {
            return "tan";
        };
};

vector<Op*> getOperationss() {
    vector<Op*> ops;

    ops.push_back(new mais());
    ops.push_back(new menos());
    ops.push_back(new vezes());
    ops.push_back(new dividido());
    ops.push_back(new elevado());
    ops.push_back(new raiz_quadrada());
    ops.push_back(new cosseno());
    ops.push_back(new tangente());

    return ops;
}
