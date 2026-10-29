#include <stdio.h>

int globalCount;
float scaleFactor;

void calculate() {
    int localResult;
    float scaleFactor; // global var
}

int main() {
    int localResult; //separate function scope
    int i;
    {
        int i; // nested variable
        char blockVar;
    }
    int localResult; //error redefinition
    return 0;
}
