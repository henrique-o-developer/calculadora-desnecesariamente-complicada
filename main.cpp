#include "operations.h"

string reverse(string s) {
    string ret;

    for (const auto &item: s) {
        ret = item + ret;
    }

    return ret;
}

bool includeOnly(string s, string h) {
    bool ret = true;

    for (int i = 0; i < s.length(); i++) {
        bool ae = false;

        for (int j = 0; j < h.length(); j++) {
            if (s[i] == h[j]) ae = true;
        }

        if (!ae) ret = false;
    }

    return ret;
}

bool includeAny(string s, string h) {
    for (int i = 0; i < s.length(); i++) {
        for (int j = 0; j < h.length(); j++) {
            if (s[i] == h[j]) return true;
        }
    }

    return false;
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
    if (includeOnly(s, "0123456789.-abcdefghijklmnopqrstuvwxyz,")) return "number";
    if (s == " ") return "null";

    return s;
}

numberF separate(string num) {
    numberF ret;

    for (const auto &item: num) {
        stringstream ss;
        string s;

        ss << item;
        ss >> s;

        if (includeOnly(s, "abcdefghijklmnopqrstuvwxyz")) {
            ret.l += s;
        } else ret.n += s;
    }

    return ret;
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

    for (const auto &item: s) {
        if (catalog(item) != t) return false;
    }


    if (t == "number") if (include(s, "-")) if (s[0] != '-') return false;

    return true;
}

vector<string> split(string s, string d) {
    vector<string> ret;
    int min = 0;

    for (int i = 0; i < s.length(); i++) {
        bool e = true;

        for (int j = 0; j < d.length(); j++) {
            if (s[i + j] != d[j]) e = false;
        }

        if (e) {
            ret.push_back(s.substr(min, i-min));
            min = i+1;
        }
    }

    ret.push_back(s.substr(min, s.length()));

    return ret;
}

vector<long double> hstod(string s, vector<formatter> keys) {
    s = replace(s, " ", "");
    vector<long double> ret;

    for (const auto &item: split(s, ",")) {
        string f = separate(item).l;
        string n = separate(item).n;
        n = n.empty() ? "1" : n;

        long double multiply = 1;

        for (const auto &item: keys) {
            if (f == item.l) multiply = item.v;
        }

        if (!onlyType(s, "number")) {
            ret.push_back(0);
            continue;
        }

        if (s.empty()) {
            ret.push_back(0);
            continue;
        }

        ret.push_back(stold(n) * multiply);
    }

    return ret;
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

    vector<Op*> ops = getOperations();
    vector<Operation> arr;

    long long IFS = 0;

    for (int i = 0; i < s.length(); ++i) {
        bool conf = false;

        for (const auto &item: ops) {
            if (conf) continue;

            bool is = true;

            for (int j = 0; j < item->op.length(); ++j) {
                if (s[i + j] != item->op[j]) { is = false; break; }
            }

            if (is && item->op == "-") if (catalog(s[i-1]) != "number" || i == 0) {
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
                conf = true;

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

parseR parse(string s, vector<formatter> keys, vector<funct> func) {
    while(include(s, " ")) s = replace(s, " ", "");

    string ret, res;
    Operation op = getPriority(s);

    while (op.exi) {
        // vars
        int min = op.min, max = op.max;
        string OP = op.ope, A = generify(s, min, false), B = generify(s, max, true);
        vector<long double> a = hstod(A, keys), b = hstod(B, keys);

        // code
        Aditional ad;

        ad.s = s;
        ad.min = min;
        ad.max = max;
        ad.keys = keys;
        ad.func = func;
        ad.A = A;
        ad.B = B;

        Run r = op.obj->r(a, b, split(A, ","), split(B, ","), ad);

        res = r.res;
        bool useA = r.useA;
        bool useB = r.useB;
        int aL = r.aLe == -1 ? A.length() : r.aLe;
        int bL = r.bLe == -1 ? B.length() : r.bLe;

        if (!r.ret.empty()) ret = r.ret;
        if (r.keys.size() != 0) keys = r.keys;
        if (r.func.size() != 0) func = r.func;

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
            ret += "\nRESULTADO FINAL: " + res;
            op.exi = false;
        } else {
            op = getPriority(s);
        }
    }

    parseR pr;

    pr.full = ret;
    pr.res = res;
    pr.keys = keys;
    pr.func = func;

    return pr;
}

int main() {
    string ex;
    vector<formatter> dkeys;
    vector<funct> dfunct;

    while (true) {
        cout << "\ndigite a conta para o programa resolver, caso nao queira mais digite \"parar\" ou \"help\" para ver os comandos\nconta:";

        getline(cin, ex);

        if (ex == "parar") break;
        if (ex == "help") {
            for (const auto &item: getOperations()) {
                cout << "op: " << item->op << ", prioridade de execucao: " << item->pri << ";\n";
            }

            cout << "total de comandos: " << getOperations().size() << ";\n";

            continue;
        }

        parseR p = parse(ex, dkeys, dfunct);

        dkeys = p.keys;
        dfunct = p.func;

        cout << "\n";
        cout << p.full;
    }

    //cout << "fn: " << formatNumber(to_string((long double) 12)) << ";\n";

    //cout << "pow: " << pow(27,1.0/3.0) << ";\n";

    //separate("22.33578bac");

    //cout << "gp: " + getPriority("3+33+333+3333").ope + ";\n";

    //cout << "onlyType: " << onlyType("100.313", "number") << ";\n";

    //cout << "replace: " << replace("-100.33", "n", "-") << "\n";

    return 0;
}
