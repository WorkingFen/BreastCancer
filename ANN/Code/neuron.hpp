#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <thread>
#include <random>
#include <math.h>

using namespace std;

class neuron{
    vector<double> input;                                           // wektor wejść
    vector<double> weight;                                          // wektor wag
    double output, sumValue;
    int type, numberOfInputs;                                       // type==0 to neuron liniowy; type==1 to neuron sigmoidalny

    /*
    Sumator
    */
    double sum()
    {
        double x=0;
        for(int i=0;i<numberOfInputs;i++)
             x+=input[i]*weight[i];

        sumValue=x;
        return x;
    }

    /*
    Funkcja aktywacyjna
    */
    double applyFunction()
    {
        if(type==0)
            return sum();
        else
        {
            double z=sum();
            return exp(z)/(1+exp(z));
        }
    }

    public:
    neuron()
    {
        output=0;
        sumValue=0;
        type=0;
        numberOfInputs=1;
        input.resize(1, 1.0);

        if(type==1)                                                               // ustawianie wag dla neuronu z warstwy ukrytej
        {
            default_random_engine rand_num{static_cast<long unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count())};
            uniform_real_distribution<float> dis(-0.18, 0.18);                    // ∼U (−1/√dim(we),1/√dim(we)) - około (-0,18;0,18)
            weight.resize(1, dis(rand_num));   
        }
        else                                                                     // ustawianie wag dla neuronu z warstwy wyjściowej (w przybliżeniu 0)
            weight.resize(1, 0.0000001);
                                                   
    }

    neuron(int type, int numberOfInputs)
    {
        output=0;
        sumValue=0;
        this->type=type;
        this->numberOfInputs=numberOfInputs+1;
        input.resize(this->numberOfInputs, 0.0);
        input[numberOfInputs]=1;
        weight.resize(this->numberOfInputs);

        if(type==1)                                                               // ustawianie wag dla neuronu z warstwy ukrytej
        {
            default_random_engine rand_num{static_cast<long unsigned int>(chrono::high_resolution_clock::now().time_since_epoch().count())};
            this_thread::sleep_for (chrono::milliseconds(1));                     // potrzebne krótkie oczekiwanie, aby seed był inny przy tworzeniu wielu neuronów w krótkim odstępie czasowym
            uniform_real_distribution<float> dis(-0.18, 0.18);                    // ∼U (−1/√dim(we),1/√dim(we)) - około (-0,18;0,18)

            for(int i=0;i<this->numberOfInputs;i++)
                weight[i]=dis(rand_num);
        }
        else                                                                     // ustawianie wag dla neuronu z warstwy wyjściowej (w przybliżeniu 0)
        {
            for(int i=0;i<this->numberOfInputs;i++)
                weight[i]=0.0000001;
        }
        
    }

    ~neuron(){};

    /*
    Zwraca liczbę "edytowalnych" wejść -> ostatnie wejście ma wartość 1.
    */
    int getNumberOfInputs()
    {
        return numberOfInputs-1;
    }

     /*
    Ustawia wartość na danym wejściu neuronu.
    */
    void setInput(int inputNumber, double value)
    {
        input[inputNumber]=value;
    }

     /*
    Ustawia wagę na danym wejściu neuronu.
    */
    void setWeight(int inputNumber, double value)
    {
        weight[inputNumber]=value;
    }

    
    /*
    Zwraca referencję do wektora wag.
    */
    vector<double> getWeightVector()
    {
        return weight;
    } 

    /*
    Wyjście neuronu po przetworzeniu wejść w sumatorze i po zastosowaniu funkcji aktywacyjnej.
    */
    double getNewOutput()
    {
        output=applyFunction();
        return output;
    }

    /*
    Zwraca wartość znajdującą się na danym wejściu neuronu.
    */
    double getInput(int inputNumber)
    {
        return input[inputNumber];
    }

    /*
    Zwraca wartość znajdującą się na wyjściu neuronu (bez dokonywania żadnych dodatkowych operacji).
    */
    double getOutput()
    {
        return output;
    }

    /*
    Zwraca sumę ważoną wejść danego neuronu.
    */
    double getSum()
    {
        return sumValue;
    }
};
