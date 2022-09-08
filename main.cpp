#include "operations.h"
#include <bits/stdc++.h>

string reverse(string s) {
    string ret;

    for (const auto &item: s) {
        ret = item + ret;
    }

    return ret;
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

string formatNumber(string s) {
    if (!include(s, ".")) return s;

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

    ret = reverse(ret);

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
    if (s == "-" || s == "." || s == "0" || s == "1" || s == "2" || s == "3" || s == "4" || s == "5" || s == "6" || s == "7" || s == "8" || s == "9") return "number";
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

bool onlyType(string s, const string& t) {
    if (catalog(s) == t) return true;

    for (const auto &item: s) if (catalog(item) != t) return false;

    if (t == "number") if (include(s, "-")) if (s[0] != '-' || s[s.length()] != '-') return false;

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

            if (me == "number" && c == '-') {
                if (catalog(s[i-1]) == "number") {
                    cout << "break\n";
                    break;
                }
            }

            ret += c;
        } else break;
    }

    if (!fow) ret = reverse(ret);

    return ret;
}

bool compareOp(Operation i1, Operation i2)
{
    return (i1.pri > i2.pri);
}

Operation getPriority(string s) {
    Operation fin;

    fin.exi = false;

    vector<Op*> ops = getOperationss();
    vector<Operation> arr;

    long long IFS = 0;

    for (int i = 0; i < s.length(); ++i) {
        for (const auto &item: ops) {
            bool is = true;

            for (int j = 0; j < item->op.length(); ++j) {
                if (s[i + j] != item->op[j]) { is = false; break; }
            }

            if (is && item->op == "-") if (catalog(s[i-1]) != "number" || i == 0) {
                cout << "continue\n";
                continue;
            }

            if (is) {
                Operation op;

                op.min = i;
                op.max = i+item->op.length()-1;
                op.ope = s.substr(i, item->op.length());
                op.pri = item->pri - IFS;
                op.exi = true;
                op.obj = item;

                int g = generify(s, i, false).length();

                if (s[i-g-1] == '{') op.pri = 1000;
                if (s[i-g-1] == '[') op.pri = 10000;
                if (s[i-g-1] == '(') op.pri = 100000;

                arr.push_back(op);
            }
        }

        if (s[i] == 'I' && s[i+1] == 'F') IFS += 1000000;
        if (s[i] == ';') IFS -= 1000000;
    }

    sort(arr.begin(), arr.end(), compareOp);

    fin = arr[0];

    return fin;
}

parseR parse(string s) {
    while(include(s, " ")) s = replace(s, " ", "");

    string ret, res;
    Operation op = getPriority(s);

    while (op.exi) {
        // vars
        int min = op.min, max = op.max;
        string OP = op.ope, A = generify(s, min, false), B = generify(s, max, true);
        double a = hstod(A), b = hstod(B);

        cout << "A: " << A << ", B: " << b << ";\n";

        // code
        Aditional ad;

        ad.s = s;
        ad.min = min;
        ad.max = max;

        Run r = op.obj->r(a, b, A, B, ad);

        res = r.res;
        bool useA = r.useA;
        bool useB = r.useB;
        int aL = r.aLe == -1 ? A.length() : r.aLe;
        int bL = r.bLe == -1 ? B.length() : r.bLe;

        if (!r.ret.empty()) ret = r.ret;

        // using code
        string S;
        int haveSp = 0;
        char c;
        int norm;

        ret += "\n";

        res = formatNumber(res);

        if (useA) norm = min - aL;
        else norm = min;

        c = s[norm - 1];

        if (c == '(' || c == '[' || c == '{') haveSp = 1;

        ret += s.substr(0, norm) + "~~  ";

        if (useA) ret += s.substr(min-aL, aL) + " ";

        ret += OP;

        S += s.substr(0, norm - haveSp);

        S += res;

        haveSp = 0;
        if (useB) norm = max + 1 + bL;
        else norm = max + 1;

        c = s[max + B.length() + 1];

        if (c == ')' || c == ']' || c == '}') haveSp = 1;

        if (useB) ret += " " + s.substr(max+1, bL);

        ret += " = ((" + res + "))";

        ret += "  ~~" + s.substr(norm, s.length());
        S += s.substr(norm + haveSp, s.length());

        ret += ";";

        s = S;

        if (onlyType(s, "number")) {
            cout << "s: " << S << ";\n";
            ret += "\nRESULTADO FINAL: " + res;
            op.exi = false;
        } else {
            op = getPriority(s);
        }
    }

    parseR pr;

    pr.full = ret;
    pr.res = res;

    return pr;
}

int main() {
    string ex;

    while (true) {
        cout << "\ndigite a conta para o programa resolver, caso nao queira mais digite \"parar\"\nconta:";
        cin >> ex;

        if (ex == "parar") break;

        cout << "\n";
        cout << parse(ex).full;
    }

    //cout << "pow: " << pow(27,1.0/3.0) << ";\n";

    //cout << "gp: " + getPriority("3+33+333+3333").ope + ";\n";

    //cout << "onlyType: " << onlyType("100.313", "number") << ";\n";

    //cout << "replace: " << replace("-100.33", "n", "-") << "\n";

    return 0;
}
