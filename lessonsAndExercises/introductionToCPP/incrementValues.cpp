/*
Exercise 1: Increment Values

Rewrite the function below in C++ using references instead of pointers. Also, show how it is called:

C:
void incrementa(int* x, int* y) {
    (*x)++;
    (*y) += 2;
}

// Call: incrementa(&a, &b);
*/

void incrementValues(int& x, int& y);

#include <iostream>
using namespace std;

int main() {
    int x = 0, y = 0;

    cout << "x: " << x << ", y: " << y << endl;
    
    incrementValues(x, y);
    
    cout << "x: " << x << ", y: " << y << endl;

    return 0;
}

void incrementValues(int& x, int& y) {
    x++;
    y += 2;
}