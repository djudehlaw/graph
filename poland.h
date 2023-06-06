#ifndef POLAND_H
#define POLAND_H

#endif // POLAND_H

#include <string>
#include <cmath>

#include <string>
#include <cmath>

using namespace std;

struct Stack {
    double number;
    char znak;
    Stack* next;
};

void push(Stack*& top, double a, char b) {
    Stack* p = new(Stack);
    p->number = a;
    p->znak = b;
    p ->
    next = top;
    top = p;
}

Stack pop(Stack*& top) {
    Stack temp = *top;
    top = (*top).next;
    return temp;
}

Stack* top1 = nullptr, * top2 = nullptr;
int pr = 0;

int check(char ch) {
    int prior;
    if (ch == '+' || ch == '-') {
        prior = 1;
    }
    if (ch == '/' || ch == '*') {
        prior = 2;
    }
    if (ch == 'q' || ch == '^') {
        prior = 3;
    }
    if (ch == 't' || ch == 'c' || ch == 's' || ch == 'l') {
        prior = 4;
    }
    if (ch == '(') {
        prior = 0;
    }
    return prior;
}
int apply(char znak) {

    const double EPS = 0.000001;
    double a, b, c;
    b = pop(top1).number;

    if (znak == '+') {
        a = pop(top1).number;
        c = a + b;
    }
    if (znak == '-') {
        a = pop(top1).number;
        c = a - b;
    }
    if (znak == '/') {
        a = pop(top1).number;
        if (abs(b) < EPS) {
            pr = -1;
            return -1;
        } else {
            c = a / b;
        }
    }
    if (znak == '*') {
        a = pop(top1).number;
        c = a * b;
    }
    if (znak == '^') {
        a = pop(top1).number;
        c = pow(a, b);
    }
    if (znak == 'c') {
        c = cos(b);
    }
    if (znak == 't') {
        if (b == 90) {
            pr = -1;
            return -1;
        } else {
            c = tan(b);
        }
    }
    if (znak == 'l') {
        if (b < EPS) {
            pr = -1;
            return -1;
        } else {
            c = log(b);
        }
    }
    if (znak == 'q') {
        if (b < 0 - EPS) {
            pr = -1;
            return -1;
        } else {
            c = sqrt(b);
        }
    }
    if (znak == 's') {
        c = sin(b);
    }
    push(top1, c, '@');
    return 0;
}

void replace_All(string &s, string s1, string s2) {
    size_t ind = s.find(s1);
    while (ind != std::string::npos) {
        s.replace(ind, s1.size(), s2);
        ind = s.find(s1, ind + s2.size());
    }
    return;
}

int error(string s) {
    int temp = 0;
    for (int i = 0; i < s.length() - 1; i++) {
        if (s[i] == '(' && s[i + 1] == ')') {
            return -1;
        }
    }
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '(') {
            temp++;
        }
        if (s[i] == ')') {
            temp--;
        }
        if (temp < 0) {
            return -1;
        }
    }
    if (temp != 0) {
        return -1;
    }
    for (int i = 0; i < s.length()-1; i++) {
        if (s[i] == '+' && s[i + 1] == '+' ||
            s[i] == '+' && s[i + 1] == '-' ||
            s[i] == '+' && s[i + 1] == '*' ||
            s[i] == '+' && s[i + 1] == '/' ||
            s[i] == '-' && s[i + 1] == '+' ||
            s[i] == '-' && s[i + 1] == '-' ||
            s[i] == '-' && s[i + 1] == '*' ||
            s[i] == '-' && s[i + 1] == '/' ||
            s[i] == '*' && s[i + 1] == '+' ||
            s[i] == '*' && s[i + 1] == '-' ||
            s[i] == '*' && s[i + 1] == '*' ||
            s[i] == '*' && s[i + 1] == '/' ||
            s[i] == '/' && s[i + 1] == '-' ||
            s[i] == '/' && s[i + 1] == '+' ||
            s[i] == '/' && s[i + 1] == '*' ||
            s[i] == '/' && s[i + 1] == '/' ||
            s[i] == '^' && s[i + 1] == '+' ||
            s[i] == '^' && s[i + 1] == '-' ||
            s[i] == '^' && s[i + 1] == '/' ||
            s[i] == '^' && s[i + 1] == '*' ||
            s[i] == '^' && s[i + 1] == '^' ||
            s[i] == '+' && s[i + 1] == '^' ||
            s[i] == '-' && s[i + 1] == '^' ||
            s[i] == '/' && s[i + 1] == '^' ||
            s[i] == '*' && s[i + 1] == '^') {
            return -1;
        }
    }
    if (s[0] == '*' || s[0] == '/' || s[0] == '+') {
        return -1;
    }
    for (int i = 0; i < s.length() - 2; i++) {
        if (s[i] == 'l' && s[i + 1] == '0' && s[i + 2] == '-') {
            return -1;
        }
        if (s[i] == 'q' && s[i + 1] == '0' && s[i + 2] == '-') {
            return -1;
        }
    }
    if (s[s.length()-1] == '+' || s[s.length()-1] == '*' || s[s.length()-1] == '/' || s[s.length()-1] == '-') {
        return -1;
    }
    for (int i = 0; i < s.length()-1; i++) {
        if (s[i] == '(' && s[i + 1] == '+' ||
            s[i] == '(' && s[i + 1] == '*' ||
            s[i] == '(' && s[i + 1] == '/' ||
            s[i] == '-' && s[i + 1] == ')') {
            return -1;
        }
    }
    return 0;
}


int calc(string s, double &ans) {
    string  ss;
    pr = 0;
    if (s[0] == '-') {
        s = '0' + s;
    }
    for (int i = 0; i < s.length()-1; i++) {
        if (s[i] == '(' && s[i + 1] == '-') {
            ss = ss + s[i] + '0';
        } else {
            ss += s[i];
        }
    }
    s = ss+s[s.length()-1];


    replace_All(s, "sin", "s");
    replace_All(s, "cos", "c");
    replace_All(s, "tg", "t");
    replace_All(s, "ln", "l");
    replace_All(s, "sqrt", "q");

    if (error(s) == -1) {
        return -1;
    }

     for (int i = 0; i < s.length(); i++) {

        if (s[i] >= '0' && s[i] <= '9' ) {
            int dot = 1;
            double temp = 0;
            while (i < s.length() && s[i] >= '0' && s[i] <= '9') {
                temp = temp * 10 + (s[i] - '0');
                i++;
            }
            if(s[i] == '.'){
                i++;
                while (i < s.length() && s[i] >= '0' && s[i] <= '9') {
                    temp = temp * 10 + (s[i] - '0');
                    dot*=10;
                    i++;
                }
                temp = temp/dot;
            }
            i--;
            push(top1, temp, '@');
        }
        if (s[i] == '(') {
            push(top2, 0.0, s[i]);
        }
        if (s[i] == ')') {
            while ((*top2).znak != '(') {
                apply(pop(top2).znak);
            }
            pop(top2);
        }
        if (s[i] == '/' || s[i] == '*' || s[i] == '+' || s[i] == '-' || s[i] == '^' ||
            s[i] == 's' || s[i] == 'c' || s[i] == 'l' || s[i] == 't' || s[i] == 'q') {
            while (top2 != nullptr && check(s[i]) <= check((*top2).znak)) {
                pr = apply(pop(top2).znak);
                if (pr == -1) {
                    return -1;
                }
            }
            push(top2, 0.0, s[i]);
        }
    }

    while (top2 != nullptr) {
        pr = apply(pop(top2).znak);
        if (pr == -1) {
            return -1;
        }
    }
    ans = pop(top1).number;
    return 0;
}
