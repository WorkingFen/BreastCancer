#include <iostream>
#include <vector>
#include "mlp.hpp"

using namespace std;

int main()
{
    mlp x(3, {2, 1});

    x.setInput(0,3);
    x.setInput(1,3);
    x.setInput(2,3);
    x.processDataAndLearn();
    cout <<endl<<endl<< x;
    cout << endl;

    return 0;
}
