#include <iostream>
using namespace std;


char* expr;

int calc();

void del_spaces(char* str) {
    int i = 0, j = 0;
    while (str[i] != '\0') {
        if (str[i] != ' ') {
            str[j++] = str[i];
        }
        i++;
    }
    str[j] = '\0';
}


char get_first() {
    return *expr;
}


char get_plus() {
    return *expr++;
}


// Конвертирует строку в число ("100 -> 100)
int stoi() {
    int result = get_plus() - '0';
    while (get_first() >= '0' && get_first() <= '9') {
        result = 10 * result + get_plus() - '0';
    }
    return result;
}


int paranth() {
    if (get_first() >= '0' && get_first() <= '9') {
        return stoi();
    }

    else if (get_first() == '(') {
        get_plus();
        int result = calc();
        get_plus();
        return result;
    }

    else if (get_first() == '-') {
        get_plus();
        return -paranth();
    }
}


int mul_div() {
    int result = paranth();
    while (get_first() == '*' || get_first() == '/')
        if (get_plus() == '*')
            result *= paranth();
        else
            result /= paranth();
    return result;
}


int calc() {
    int result = mul_div();
    while (get_first() == '+' || get_first() == '-')
        if (get_plus() == '+')
            result += mul_div();
        else
            result -= mul_div();
    return result;
}


int main() {
    setlocale(LC_ALL, "");

    cout << "Введите ваше выражение >";
    expr = new char[100];
    int i = 0;
    char symbol;
    while (cin.get(symbol) && symbol != '\n') {
        expr[i] = symbol;
        i++;
    }
    expr[i] = '\0';

    del_spaces(expr);
    cout << "Ваш Результат = "   << calc();
}