#include <iostream>
#include <vector>
#include "Headers/mlp.hpp"

using namespace std;

int main()
{
    mlp x(3, {3, 2, 1});

    x.setInput(0,3);
    x.setInput(1,3);
    x.setInput(2,3);

    cout << x.processData() << endl;

    return 0;
}