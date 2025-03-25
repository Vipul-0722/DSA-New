#include <bits/stdc++.h>
using namespace std;

// Function to define precedence of operators
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Function to check if a character is an operator
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Function to convert Infix to Postfix
string infixToPostfix(string infix) {
    stack<char> st;
    string postfix;
    
    for (char c : infix) {
        if (isalnum(c)) {
            postfix += c; // If operand, add to postfix
        } else if (c == '(') {
            st.push(c);
        } else if (c == ')') {
            while (!st.empty() && st.top() != '(') {
                postfix += st.top();
                st.pop();
            }
            st.pop(); // Remove '(' from stack
        } else if (isOperator(c)) {
            while (!st.empty() && precedence(st.top()) >= precedence(c)) {
                postfix += st.top();
                st.pop();
            }
            st.push(c);
        }
    }
    
    while (!st.empty()) {
        postfix += st.top();
        st.pop();
    }
    
    return postfix;
}

// Function to convert Infix to Prefix
string infixToPrefix(string infix) {
    reverse(infix.begin(), infix.end()); // Reverse infix expression
    
    for (char &c : infix) {
        if (c == '(') c = ')';
        else if (c == ')') c = '(';
    }
    
    string prefix = infixToPostfix(infix);
    reverse(prefix.begin(), prefix.end()); // Reverse postfix to get prefix
    
    return prefix;
}

// Function to evaluate Postfix expression
int evaluatePostfix(string postfix) {
    stack<int> st;
    
    for (char c : postfix) {
        if (isdigit(c)) {
            st.push(c - '0'); // Convert char to int
        } else {
            int val2 = st.top(); st.pop();
            int val1 = st.top(); st.pop();
            
            switch (c) {
                case '+': st.push(val1 + val2); break;
                case '-': st.push(val1 - val2); break;
                case '*': st.push(val1 * val2); break;
                case '/': st.push(val1 / val2); break;
            }
        }
    }
    
    return st.top();
}

// Function to evaluate Prefix expression
int evaluatePrefix(string prefix) {
    stack<int> st;
    reverse(prefix.begin(), prefix.end());
    
    for (char c : prefix) {
        if (isdigit(c)) {
            st.push(c - '0'); // Convert char to int
        } else {
            int val1 = st.top(); st.pop();
            int val2 = st.top(); st.pop();
            
            switch (c) {
                case '+': st.push(val1 + val2); break;
                case '-': st.push(val1 - val2); break;
                case '*': st.push(val1 * val2); break;
                case '/': st.push(val1 / val2); break;
            }
        }
    }
    
    return st.top();
}

// Driver function
int main() {
    string infix = "(3+5)*2";
    
    string postfix = infixToPostfix(infix);
    string prefix = infixToPrefix(infix);
    
    cout << "Infix Expression: " << infix << endl;
    cout << "Postfix Expression: " << postfix << endl;
    cout << "Prefix Expression: " << prefix << endl;
    
    cout << "Postfix Evaluation: " << evaluatePostfix(postfix) << endl;
    cout << "Prefix Evaluation: " << evaluatePrefix(prefix) << endl;
    
    return 0;
}
