#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;

struct Casilla {
   
    string shape;
    bool visited;
    bool up;
    bool right;
    bool down;
    bool left;
};