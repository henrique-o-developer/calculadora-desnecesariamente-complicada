#include "operations.h"

string reverse(string s) {
    string ret;

    for (const auto &item: s) {
        ret = item + ret;
    }

    return ret;
}

string formatNumber(string s) {
    s = reverse(s);
    string ret;
    bool direct = true;

    for (const auto &item: s) {
        if (item == '0') {
            if (!direct) {
                ret += item;
            }
        } else {
            if (item == '.' && direct) {
                direct = false;
                continue;
            }

            direct = false;

            ret += item;
        }
    }

    return reverse(ret);
}

bool include(string s, string h) {
    bool ret = false;

    for (int i = 0; i < s.length(); i++) {
        bool e = true;

        for (int j = 0; j < h.length(); j++) {
            if (s[i + j] != h[j]) e = false;
        }

        if (e) {
            ret = true;
        }
    }

    return ret;
}

string replace(string s, string r, string R) {
    string ret = "";

    for (int i = 0; i < s.length(); i++) {
        bool e = true;

        for (int j = 0; j < r.length(); j++) {
            if (s[i + j] != r[j]) e = false;
        }

        if (e) {
            ret += R;
            i += r.length()-1;
        }
        else ret += s[i];
    }

    return ret;
}

string catalog(string s) {
    if (s == "n" || s == "." || s == "0" || s == "1" || s == "2" || s == "3" || s == "4" || s == "5" || s == "6" || s == "7" || s == "8" || s == "9") return "number";
    if (s == " ") return "null";

    return s;
}

string catalog(char c) {
    stringstream ss;
    string s;

    ss << c;
    ss >> s;

    return catalog(s);
}

bool onlyType(string s, string t) {
    if (catalog(s) == t) return true;

    for (const auto &item: s) if (catalog(item) != t) return false;

    return true;
}

double hstod(string s) {
    s = replace(s, " ", "");
    s = replace(s, "n", "-");

    if (!onlyType(s, "number")) return 0;
    if (s.empty()) return 0;

    return stod(s);
}

string generify(string s, int ii, bool fow) {
    string ret;
    string me = "null";

    for (int i = ii;;) {
        if (fow) {
            i++;
            if (i > s.length()) break;
        } else {
            i--;
            if(i < 0) break;
        }

        char c = s[i];

        if (me == catalog(c) || me == "null") {
            if (me == "null") me = catalog(c);

            ret += c;
        } else break;
    }

    if (!fow) ret = reverse(ret);

    return ret;
}

Operation getPriority(string s) {
    Operation fin;

    fin.exi = false;

    vector<Op*> ops = getOperationss();
    vector<Operation> arr;

    for (int i = 0; i < s.length(); ++i) {
        for (const auto &item: ops) {
            bool is = true;

            for (int j = 0; j < item->getOp().length(); ++j) {
                if (s[i + j] != item->getOp()[j]) { is = false; break; }
            }

            if (is) {
                Operation op;

                op.min = i;
                op.max = i+item->getOp().length()-1;
                op.ope = s.substr(i, item->getOp().length());
                op.pri = item->getPri();
                op.exi = true;
                op.obj = item;

                int g = generify(s, i, false).length();

                if (s[i-g-1] == '{') op.pri = 1000;
                if (s[i-g-1] == '[') op.pri = 10000;
                if (s[i-g-1] == '(') op.pri = 100000;

                arr.push_back(op);
            }
        }
    }

    unsigned int max_p = 0;
    bool stop = false;

    for (const auto &item: arr) if (item.pri > max_p) max_p = item.pri;

    for (int i = max_p+1; i >= 0; i--) {
        for (const auto &item: arr) {
            if (i == item.pri && !stop) {
                fin = item;

                stop = true;
            }
        }
    }

    return fin;
}

string parse(string s) {
    while(include(s, " ")) s = replace(s, " ", "");
    while(include(s, ";")) s = replace(s, ";", "");

    string ret = "conta: " + s + ";\n", res;
    Operation op = getPriority(s);

    while (op.exi) {
        int min = op.min, max = op.max;
        string OP = op.ope, A = generify(s, min, false), B = generify(s, max, true);
        double a = hstod(A), b = hstod(B);
        bool useA, useB;

        Run r = op.obj->run(a, b, A, B);

        res = r.res;
        useA = r.useA;
        useB = r.useB;

        string S;
        int haveSp = 0;
        char c;
        int norm;

        ret += "\n";

        res = replace(res, "-", "n");
        res = formatNumber(res);

        if (useA) norm = min - A.length();
        else norm = min;

        c = s[norm - 1];

        if (c == '(' || c == '[' || c == '{') haveSp = 1;

        ret += s.substr(0, norm) + "~~  ";

        if (useA) ret += A + " ";

        ret += OP;

        S += s.substr(0, norm - haveSp);

        S += res;

        haveSp = 0;
        if (useB) norm = max + 1 + B.length();
        else norm = max + 1;

        c = s[max + B.length() + 1];

        if (c == ')' || c == ']' || c == '}') haveSp = 1;

        if (useB) ret += " " + B;

        ret += " = ((" + res + "))";

        ret += "  ~~" + s.substr(norm, s.length());
        S += s.substr(norm + haveSp, s.length());

        ret += ";";

        s = S;

        cout << "s: " << s << ";\n";


        if (onlyType(s, "number")) {
            ret += "\nRESULTADO FINAL: " + res;
            op.exi = false;
        } else {
            op = getPriority(s);
        }
    }

    return ret;
}

int main() {
    cout << parse("2 sqrt { 5 ^ 2 }");

    //cout << "pow: " << pow(27,1.0/3.0) << ";\n";

    //cout << "gp: " + getPriority("3+33+333+3333").ope + ";\n";

    //cout << "onlyType: " << onlyType("100.313", "number") << ";\n";

    //cout << "replace: " << replace("-100.33", "n", "-") << "\n";

    return 0;
}
