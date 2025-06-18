#include <iostream>
#include <stack>
#include <sstream>
#include <cctype>
#include <map>
#include <stdexcept>

using namespace std;

// Function to define operator precedence
int precedence(char op)
{
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

// Function to perform arithmetic operations
double applyOp(double a, double b, char op)
{
    switch (op)
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        if (b == 0)
            throw runtime_error("Division by zero!");
        return a / b;
    }
    throw runtime_error("Invalid operator");
}

// Function to evaluate the expression
double evaluate(const string &tokens)
{
    stack<double> values;
    stack<char> ops;
    int i = 0;

    while (i < tokens.length())
    {
        if (isspace(tokens[i]))
        {
            i++;
            continue;
        }

        // If number, extract full number
        if (isdigit(tokens[i]) || tokens[i] == '.')
        {
            string val;
            while (i < tokens.length() && (isdigit(tokens[i]) || tokens[i] == '.'))
                val += tokens[i++];
            values.push(stod(val));
        }
        // Opening parenthesis
        else if (tokens[i] == '(')
        {
            ops.push(tokens[i]);
            i++;
        }
        // Closing parenthesis
        else if (tokens[i] == ')')
        {
            while (!ops.empty() && ops.top() != '(')
            {
                double b = values.top();
                values.pop();
                double a = values.top();
                values.pop();
                char op = ops.top();
                ops.pop();
                values.push(applyOp(a, b, op));
            }
            if (!ops.empty())
                ops.pop(); // pop '('
            i++;
        }
        // Operator
        else
        {
            while (!ops.empty() && precedence(ops.top()) >= precedence(tokens[i]))
            {
                double b = values.top();
                values.pop();
                double a = values.top();
                values.pop();
                char op = ops.top();
                ops.pop();
                values.push(applyOp(a, b, op));
            }
            ops.push(tokens[i]);
            i++;
        }
    }

    // Final calculation
    while (!ops.empty())
    {
        double b = values.top();
        values.pop();
        double a = values.top();
        values.pop();
        char op = ops.top();
        ops.pop();
        values.push(applyOp(a, b, op));
    }

    return values.top();
}

int main()
{
    string expression;
    cout << "Enter a mathematical expression (e.g., 3 + 4 * (2 - 1)): ";
    getline(cin, expression);

    try
    {
        double result = evaluate(expression);
        cout << "Result: " << result << endl;
    }
    catch (const exception &e)
    {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}
