#include "lib.h"

Run mais(double a, double b, string A, string B, Aditional ad) {
    Run r;

    r.res = to_string(a+b);

    return r;
};

Run menos(double a, double b, string A, string B, Aditional ad) {
    Run r;

    r.res = to_string(a-b);

    return r;
};

Run dividido(double a, double b, string A, string B, Aditional ad) {
    Run r;

    r.res = to_string(a/b);

    return r;
};

Run vezes(double a, double b, string A, string B, Aditional ad) {
    Run r;

    r.res = to_string(a*b);

    return r;
};

Run elevado(double a, double b, string A, string B, Aditional ad) {
    Run r;

    r.res = to_string(pow(a, b));

    return r;
};

Run raiz_quadrada(double a, double b, string A, string B, Aditional ad) {
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

Run cosseno(double a, double b, string A, string B, Aditional ad) {
    Run r;

    r.res = to_string(cos(b));

    r.useA = false;

    return r;
};

Run tangente(double a, double b, string A, string B, Aditional ad) {
    Run r;

    r.res = to_string(tan(b));

    r.useA = false;

    return r;
};

Run igual(double a, double b, string A, string B, Aditional ad) {
    Run ret;

    if (a == b || A == B) {
        ret.res = "1";
    } else ret.res = "-1";

    return ret;
}

Run maiorQue(double a, double b, string A, string B, Aditional ad) {
    Run ret;

    if (a > b) {
        ret.res = "1";
    } else ret.res = "-1";

    return ret;
}

Run menorQue(double a, double b, string A, string B, Aditional ad) {
    Run ret {};

    if (a < b) {
        ret.res = "1";
    } else ret.res = "-1";

    return ret;
}

Run diferente(double a, double b, string A, string B, Aditional ad) {
    Run ret {};

    if (a != b || A != B) {
        ret.res = "1";
    } else ret.res = "-1";

    return ret;
}

Run inverte(double a, double b, string A, string B, Aditional ad) {
    Run ret {};

    ret.useA = false;

    ret.res = to_string(b *= -1);

    return ret;
}

Run modulo(double a, double b, string A, string B, Aditional ad) {
    Run ret {};

    ret.useA = false;

    if (b >= 0) ret.res = to_string(b);
    else ret.res = to_string(b *= -1);

    return ret;
}

Run PI(double a, double b, string A, string B, Aditional ad) {
    Run ret {};

    ret.useA = false;
    ret.useB = false;

    ret.res = "3.141592";

    return ret;
}

Run E(double a, double b, string A, string B, Aditional ad) {
    Run ret;

    if (a >= 0 && b >= 0) ret.res = "1";
    else ret.res = "-1";

    return ret;
}

Run OU(double a, double b, string A, string B, Aditional ad) {
    Run ret;

    if (a >= 0 || b >= 0) ret.res = "1";
    else ret.res = "-1";

    return ret;
}

Run IF(double a, double b, string A, string B, Aditional ad) {
    Run ret {};

    string code = ad.s.substr(ad.max+1, ad.s.length());

    int ifs = 1;
    int fin = 0;

    for (int i = 0; i < code.length(); ++i) {
        char item = code[i];

        if (item == ';') {
            ifs--;
            fin = i;
        }

        if (ifs == 0) break;

        if (item == 'I' && code[i+1] == 'F') {
            ifs++;
        }
    }

    code = code.substr(0, fin);

    ret.bLe = code.length()+1;

    if (a >= 0) {
        parseR pr = parse(code);

        ret.ret = ad.ret;

        ret.ret += "\n~~  START OF IF STATEMENT  ~~";

        ret.ret += pr.full;

        ret.ret += "\n~~  END OF IF STATEMENT  ~~";

        ret.res = pr.res;
    } else ret.res = to_string(0);

    return ret;
}

vector<Op*> getOperationss() {
    vector<Op*> ops;

    ops.push_back(new Op(IF, 0, "IF"));
    ops.push_back(new Op(inverte, 0, "!"));
    ops.push_back(new Op(mais, 1, "+"));
    ops.push_back(new Op(menos, 1, "-"));
    ops.push_back(new Op(vezes, 2, "*"));
    ops.push_back(new Op(dividido, 2, "/"));
    ops.push_back(new Op(elevado, 3, "^"));
    ops.push_back(new Op(raiz_quadrada, 3, "sqrt"));
    ops.push_back(new Op(cosseno, 4, "cos"));
    ops.push_back(new Op(tangente, 4, "tan"));
    ops.push_back(new Op(modulo, 4, "mdl"));
    ops.push_back(new Op(igual, 50, "=="));
    ops.push_back(new Op(maiorQue, 50, ">"));
    ops.push_back(new Op(menorQue, 50, "<"));
    ops.push_back(new Op(diferente, 50, "!="));
    ops.push_back(new Op(E, 50, "&&"));
    ops.push_back(new Op(OU, 50, "||"));
    ops.push_back(new Op(PI, 100, "(pi)"));

    return ops;
}
