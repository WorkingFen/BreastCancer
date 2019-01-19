#include <iostream>
#include <vector>
#include <chrono>
#include <random>
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


    mlp first(30, {5, 1});

    default_random_engine rand_num{static_cast<long unsigned int>(chrono::high_resolution_clock::now().time_since_epoch().count())};
    uniform_real_distribution<> dis(0,284);                                                                                                 // jest 285 instancji problemu

    int properlyClassified=0;

    for(int i=0;i<2000;i++)                                                                                                                 // uczenie sieci neuronowej na 2000 wybieranych losowo przykładach
    {
        int chosenExample=dis(rand_num);
        
        /*
        for(int j = 0; j < 30; j++) 
        {
            first.setInput(j, input[chosenExample]->getFeature(j));
        }
        */

        //////////// Skalowanie danych wejściowych ////////////
        
        /*for(int j = 0; j < 2; j++)                                                          
        {
            first.setInput(j, (input[chosenExample]->getFeature(j))/10);
        }*/
        first.setInput(0, (input[chosenExample]->getFeature(0))/100);
	first.setInput(1, (input[chosenExample]->getFeature(1))/100);
        first.setInput(2, (input[chosenExample]->getFeature(2))/100);
        first.setInput(3, (input[chosenExample]->getFeature(3))/100);
        /*for(int j = 4; j < 9; j++)                                                          
        {
            first.setInput(j, (input[chosenExample]->getFeature(j))*10);
        }*/
	first.setInput(4, (input[chosenExample]->getFeature(4))*10);
	first.setInput(5, (input[chosenExample]->getFeature(5))*10);
	first.setInput(6, (input[chosenExample]->getFeature(6))*100);
	first.setInput(7, (input[chosenExample]->getFeature(7))*100);
        first.setInput(8, (input[chosenExample]->getFeature(8))*10);
        first.setInput(9, (input[chosenExample]->getFeature(9))*100);
        /*for(int j = 10; j < 13; j++)                                                          
        {
            first.setInput(j, input[chosenExample]->getFeature(j));
        }*/
	first.setInput(10, (input[chosenExample]->getFeature(10))*10);
	first.setInput(11, (input[chosenExample]->getFeature(11)));
	first.setInput(12, (input[chosenExample]->getFeature(12))/10);
        first.setInput(13, (input[chosenExample]->getFeature(13))/100);
        first.setInput(14, (input[chosenExample]->getFeature(14))*100);
        /*for(int j = 15; j < 19; j++)                                                          
        {
            first.setInput(j, (input[chosenExample]->getFeature(j))*100);
        }*/
	first.setInput(15, (input[chosenExample]->getFeature(15))*100);
	first.setInput(16, (input[chosenExample]->getFeature(16))*100);
	first.setInput(17, (input[chosenExample]->getFeature(17))*100);
	first.setInput(18, (input[chosenExample]->getFeature(18))*100);
        first.setInput(19, (input[chosenExample]->getFeature(19))*1000);
        first.setInput(20, (input[chosenExample]->getFeature(20))/100);
        first.setInput(21, (input[chosenExample]->getFeature(21))/100);
        first.setInput(22, (input[chosenExample]->getFeature(22))/1000);
        first.setInput(23, (input[chosenExample]->getFeature(23))/1000);
        /*for(int j = 24; j < 30; j++)                                                          
        {
            first.setInput(j, (input[chosenExample]->getFeature(j))*10);
        }*/
	first.setInput(24, (input[chosenExample]->getFeature(24))*10);
	first.setInput(25, (input[chosenExample]->getFeature(25))*10);
	first.setInput(26, (input[chosenExample]->getFeature(26))*10);
	first.setInput(27, (input[chosenExample]->getFeature(27))*100);
	first.setInput(28, (input[chosenExample]->getFeature(28))*10);
	first.setInput(29, (input[chosenExample]->getFeature(29))*10);
        
        ////////////////////////////////////////////////////////////////////////////////////

        if(input[chosenExample]->getDiagnosis()=='M')
            first.setExpectedOutput(0, 1);
        else
            first.setExpectedOutput(0, 0);

        first.processDataAndLearn();  
        //cout << input[chosenExample]->getDiagnosis() << " ";
        //cout << first;
        //cout << endl; 
        //cout << i << endl;
    }

    for(int i=0;i<284;i++)                                                                                                                              // sprawdzanie jakości nauki
    {
        //////////// Skalowanie danych wejściowych ////////////
        /*for(int j = 0; j < 2; j++)                                                          
        {
            first.setInput(j, (input[i]->getFeature(j))/10);
        }*/
	first.setInput(0, (input[i]->getFeature(0))/100);
	first.setInput(1, (input[i]->getFeature(1))/100);
        first.setInput(2, (input[i]->getFeature(2))/100);
        first.setInput(3, (input[i]->getFeature(3))/100);
        /*for(int j = 4; j < 9; j++)                                                          
        {
            first.setInput(j, (input[i]->getFeature(j))*10);
        }*/
	first.setInput(4, (input[i]->getFeature(4))*10);
	first.setInput(5, (input[i]->getFeature(5))*10);
	first.setInput(6, (input[i]->getFeature(6))*100);
	first.setInput(7, (input[i]->getFeature(7))*100);
	first.setInput(8, (input[i]->getFeature(8))*10);
        first.setInput(9, (input[i]->getFeature(9))*100);
        /*for(int j = 10; j < 13; j++)                                                          
        {
            first.setInput(j, input[i]->getFeature(j));
        }*/
	first.setInput(10, (input[i]->getFeature(10))*10);
	first.setInput(11, (input[i]->getFeature(11)));
	first.setInput(12, (input[i]->getFeature(12))/10);
        first.setInput(13, (input[i]->getFeature(13))/100);
        first.setInput(14, (input[i]->getFeature(14))*100);
        /*for(int j = 15; j < 19; j++)                                                          
        {
            first.setInput(j, (input[i]->getFeature(j))*100);
        }*/
	first.setInput(15, (input[i]->getFeature(15))*100);
	first.setInput(16, (input[i]->getFeature(16))*100);
	first.setInput(17, (input[i]->getFeature(17))*100);
	first.setInput(18, (input[i]->getFeature(18))*100);
        first.setInput(19, (input[i]->getFeature(19))*1000);
        first.setInput(20, (input[i]->getFeature(20))/100);
        first.setInput(21, (input[i]->getFeature(21))/100);
        first.setInput(22, (input[i]->getFeature(22))/1000);
        first.setInput(23, (input[i]->getFeature(23))/1000);
        /*for(int j = 24; j < 30; j++)                                                          
        {
            first.setInput(j, (input[i]->getFeature(j))*10);
        }*/
	first.setInput(24, (input[i]->getFeature(24))*10);
	first.setInput(25, (input[i]->getFeature(25))*10);
	first.setInput(26, (input[i]->getFeature(26))*10);
	first.setInput(27, (input[i]->getFeature(27))*100);
	first.setInput(28, (input[i]->getFeature(28))*10);
	first.setInput(29, (input[i]->getFeature(29))*10);
        ////////////////////////////////////////////////////////////////////////////////////
        first.processData();
        cout << input[i]->getDiagnosis() << " ";
        cout << first.getOutputVector()[0];
        cout << endl;

        if((input[i]->getDiagnosis()=='M' && first.getOutputVector()[0]>=0.5) || (input[i]->getDiagnosis()=='B' && first.getOutputVector()[0]<0.5))
            properlyClassified+=1;
    }

    cout << "Properly classified: " << properlyClassified << " in 285 examples. That is " << ((double)properlyClassified/285)*100 << " percent." << endl;
    /*
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
    */

    /*for(auto a : input){
	    cout << a->getID() << " " << a->getDiagnosis() << " " << a->getFeature(0) << endl;
    }*/

    return 0;
}
