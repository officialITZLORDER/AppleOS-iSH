#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

const char *expr;

void skip_spaces() {
    while (*expr == ' ') expr++;
}

double parse_expression();

double parse_number() {
    skip_spaces();
    return strtod(expr, (char**)&expr);
}

double parse_factor() {
    skip_spaces();

    if (*expr == '(') {
        expr++;
        double result = parse_expression();
        if (*expr == ')') expr++;
        return result;
    }

    return parse_number();
}

double parse_term() {
    double result = parse_factor();

    while (1) {
        skip_spaces();

        if (*expr == '*') {
            expr++;
            result *= parse_factor();
        } else if (*expr == '/') {
            expr++;
            result /= parse_factor();
        } else {
            break;
        }
    }

    return result;
}

double parse_expression() {
    double result = parse_term();

    while (1) {
        skip_spaces();

        if (*expr == '+') {
            expr++;
            result += parse_term();
        } else if (*expr == '-') {
            expr++;
            result -= parse_term();
        } else {
            break;
        }
    }

    return result;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s \"expression\"\n", argv[0]);
        return 1;
    }

    expr = argv[1];
    double result = parse_expression();

    printf("%lf\n", result);
    return 0;
}
