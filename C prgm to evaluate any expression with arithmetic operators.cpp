#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

// Function to return precedence of operators
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

// Function to perform arithmetic operations
double applyOp(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        case '^': return pow(a, b);
    }
    return 0;
}

// Function to evaluate the expression
double evaluate(const char* tokens) {
    int i;
    // Stack for numbers
    double values[100];
    int valuesIndex = -1;

    // Stack for operators
    char ops[100];
    int opsIndex = -1;

    for (i = 0; i < strlen(tokens); i++) {
        // Current token is a whitespace, skip it
        if (tokens[i] == ' ')
            continue;

        // Current token is a number, push it to stack for numbers
        else if (isdigit(tokens[i])) {
            double val = 0;
            // There may be more than one digit in the number
            while (i < strlen(tokens) && (isdigit(tokens[i]) || tokens[i] == '.')) {
                if (tokens[i] == '.') {
                    i++;
                    double decimal = 1;
                    while (i < strlen(tokens) && isdigit(tokens[i])) {
                        decimal /= 10;
                        val += (tokens[i] - '0') * decimal;
                        i++;
                    }
                } else {
                    val = (val * 10) + (tokens[i] - '0');
                    i++;
                }
            }
            i--;
            values[++valuesIndex] = val;
        }

        // Current token is an opening brace, push it to 'ops'
        else if (tokens[i] == '(') {
            ops[++opsIndex] = tokens[i];
        }

        // Closing brace encountered, solve entire brace
        else if (tokens[i] == ')') {
            while (opsIndex != -1 && ops[opsIndex] != '(') {
                double val2 = values[valuesIndex--];
                double val1 = values[valuesIndex--];
                char op = ops[opsIndex--];
                values[++valuesIndex] = applyOp(val1, val2, op);
            }
            if (opsIndex != -1)
                opsIndex--; // pop opening brace
        }

        // Current token is an operator
        else {
            while (opsIndex != -1 && precedence(ops[opsIndex]) >= precedence(tokens[i])) {
                double val2 = values[valuesIndex--];
                double val1 = values[valuesIndex--];
                char op = ops[opsIndex--];
                values[++valuesIndex] = applyOp(val1, val2, op);
            }
            ops[++opsIndex] = tokens[i];
        }
    }

    // Entire expression has been parsed at this point, apply remaining ops to remaining values
    while (opsIndex != -1) {
        double val2 = values[valuesIndex--];
        double val1 = values[valuesIndex--];
        char op = ops[opsIndex--];
        values[++valuesIndex] = applyOp(val1, val2, op);
    }

    // Top of 'values' contains the result, return it
    return values[valuesIndex];
}

int main() {
    char expression[100];
    printf("Enter an expression: ");
    fgets(expression, 100, stdin);
    // Remove trailing newline character
    expression[strcspn(expression, "\n")] = 0;
    printf("Result: %.2f\n", evaluate(expression));
    return 0;
}

