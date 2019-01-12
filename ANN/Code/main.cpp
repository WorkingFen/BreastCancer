#include <iostream>
#include <vector>
#include "mlp.hpp"
#include "load.hpp"

using namespace std;

int main(int argc, char* argv[])
{
    Load load;
    std::vector<Data*> input;

    if(argc > 1){
	    std::string file(argv[1]);
	    input = load.read(file);
    }
    else input = load.read("../Data/wdbc.data");

    mlp first(30, {2, 1});

    for(int i = 0; i < 30; i++) first.setInput(i, 3);

    first.processData();
    cout << endl << endl << first;
    first.setExpectedOutput(0, 77);
    first.processDataAndLearn();
    cout << endl << endl << first;
    cout << endl;    

    mlp x(3, {2, 1});

    x.setInput(0,3);
    x.setInput(1,3);
    x.setInput(2,3);
    x.processData();
    cout <<endl<<endl<< x;
    x.setExpectedOutput(0,1);
    x.processDataAndLearn();
    cout <<endl<<endl<< x;
    cout << endl;

    /*for(auto a : input){
	    cout << a->getID() << " " << a->getDiagnosis() << " " << a->getFeature(0) << endl;
    }*/

    return 0;
}
