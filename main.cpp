#include <iostream>
#include <vector>
#include "Headers/neuron.hpp"

using namespace std;

int main()
{
    neuron x(1,3);
    
    for(int i=0;i<x.getNumberOfInputs();i++)
    {
        x.setInput(i,10);
    }
    cout << x.getOutput() << endl;
    return 0;
}