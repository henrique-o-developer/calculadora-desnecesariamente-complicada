#include "lib.h"

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

vector<string> getOperations() {
    vector<string> ret = {"+", "-", "*", "/", "!", "?", "^", "sqrt"};

    return ret;
}

int getOperationPriority(const string& s) {
    if (s == "+" || s == "-") return 1;
    if (s == "*" || s == "/") return 2;
    if (s == "sqrt" || s == "^") return 3;
    if (s == "!" || s == "?") return 4;

    return 0;
}

Operation getPriority(string s) {
    Operation fin;

    fin.exi = false;

    vector<string> ops = getOperations();
    vector<Operation> arr;

    for (int i = 0; i < s.length(); ++i) {
        for (const auto &item: ops) {
            bool is = true;

            for (int j = 0; j < item.length(); ++j) {
                if (s[i + j] != item[j]) { is = false; break; }
            }

            if (is) {
                Operation op;

                op.min = i;
                op.max = i+item.length()-1;
                op.ope = s.substr(i, item.length());
                op.pri = getOperationPriority(op.ope);
                op.exi = true;

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
    s = replace(s, " ", "");

    string ret, res;
    Operation op = getPriority(s);

    while (op.exi) {
        int min = op.min, max = op.max;
        string OP = op.ope, A = generify(s, min, false), B = generify(s, max, true);
        double a = hstod(A), b = hstod(B);
        bool useA = true, useB = true;

        if (OP == "+") res = to_string(a+b);

        if (OP == "-") res = to_string(a-b);

        if (OP == "*") res = to_string(a*b);

        if (OP == "/") res = to_string(a/b);

        if (OP == "!") {
            useB = false;

            double con = 1;

            for (double j = a; j > 0; j--) {
                con *= j;
            }

            res = to_string(con);
        }

        if (OP == "?") {
            useB = false;

            double con = 0;

            for (double j = a; j > 0; j-=1) {
                con += j;
            }

            res = to_string(con);
        }

        if (OP == "sqrt") {
            double sq;

            if (onlyType(A, "number") && !A.empty()) {
                sq = a;

                useA = true;
            } else {
                sq = 2;

                useA = false;
            }

            res = to_string(pow(b,1.0/sq));
        }

        if (OP == "^") res = to_string(pow(a, b));

        string S;

        res = replace(res, "-", "n");
        res = formatNumber(res);

        ret += "\n";

        res = replace(res, "-", "n");

        if (useA) {
            ret += A + " ";

            S = s.substr(0, min - A.length());
        } else {
            S = s.substr(0, min);
        }

        ret += OP;
        S += res;

        if (useB) {
            ret += " " + B;

            S += s.substr(max + 1 + B.length(), s.length());
        } else S += s.substr(max + 1, s.length());

        ret += " = " + res;

        s = S;

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
    cout << "parse: " + parse("1/3") + ";\n";

    //cout << "pow: " << pow(27,1.0/3.0) << ";\n";

    //cout << "gp: " + getPriority("3+33+333+3333").ope + ";\n";

    //cout << "onlyType: " << onlyType("100.313", "number") << ";\n";

    //cout << "replace: " << replace("-100.33", "n", "-") << "\n";

    return 0;
}