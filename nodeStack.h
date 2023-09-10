
#include <iostream>

class Stack;

using namespace std;

class nodeStack
{
private:
    float data;
    nodeStack* next;

    friend Stack;
    friend ostream& operator<<(ostream&, Stack&);
};
