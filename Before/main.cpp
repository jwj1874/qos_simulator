#include <iostream>
#include "Simulator.h"
using namespace std;
int main(){
    cout << "===Communication Scheduling Simullation Start===\n";

    Simulator simulator;
    simulator.run();
    cout << "===Simullation Exit===\n";
    return 0;
}