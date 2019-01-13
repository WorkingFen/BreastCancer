#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <math.h>
#include <random>
#include "neuron.hpp"

using namespace std;

class mlp{
    vector<int> layerInputs;                                     // wektor przechowujący informację o liczbie wejść do neuronów w każdej z warstw; elementy wektora o indeksach od 1 wzwyż można też traktować jako liczbę neuronów w danej warstwie sieci
    vector<vector<neuron>> neurons;                              // wektor wektorów reprezentujący neurony i ich ułożenie w sieci
    vector<double> networkOutput;                                // wektor przechowujący wyjścia sieci
    vector<double> expectedNetworkOutput;                        // wektor przechowujący oczekiwane wyjścia sieci (proces uczenia)
    vector<double> error;                                        // wektor kolumnowy przechowujący dq/d(theta)
    vector<double> columnWeightVector;                           // wektor kolumnowy przechowujący wagi wejść neuronów wchodzących w skład sieci


    /*
    outputValue - wartość na wyjściu sieci (wyjście może być wektorem, więc może istnieć konieczność wywołania tej metody dla każdego elementu wektora wyjść sieci)
    expectedOutputValue - oczekiwana wartość wyjścia
    inputNumber - numer wejścia neuronu (liczone od 0)
    */
    double countOuterError(double outputValue, double expectedOutputValue, int inputNumber)
    {
        int layer=layerInputs.size()-2;

        return (outputValue-expectedOutputValue)*neurons[layer-1][inputNumber].getOutput();
    }

    /*
    errors - wektor błędów z k+1-szej warstwy
    layer - numer warstwy w której jesteśmy (k)
    neuronNumber - numer neuronu z pierwszej warstwy
    input - wartość na danym wejściu neuronu, dla którego liczymy błędy

    zapewne zrobimy macierz errors w klasie i nie będzie ona potrzebna tutaj w parametrach
    ale już taki layer raczej musi być przekazany w parametrze, chociaż mogę się mylić

    */
    double countInnerError(vector<double> errors, int layer, int neuronNumber, double input)
    {
        double s = neurons[layer-1][neuronNumber].getSum();                                                                                      // suma obliczana przez i-ty neuron k-tej warstwy
        double derivative = exp(s)/ pow(1 + exp(s), 2);

        double sum = 0;                                                                                                                         // suma error * waga
        vector<double> weightVector;
        for(int i=0;i<layerInputs[layer+1];i++)
        {
            weightVector.push_back(neurons[layer][i].getWeightVector()[neuronNumber]);
        }
        
        double weight;
        for(int i = 0; i < neurons[layer].size(); i++)
        {
            weight = weightVector[i];
            sum += weight * errors[i]/neurons[layer][i].getOutput();
        }
 
        return derivative * input * sum;
    }

    /*
    errors - wektor błędów z k+1-szej warstwy
    neuronNumber - numer neuronu z pierwszej warstwy
    input - wartość na danym wejściu neuronu, dla którego liczymy błędy

    zapewne zrobimy macierz errors w klasie i nie będzie ona potrzebna tutaj w parametrach
    ale już taki layer raczej musi być przekazany w parametrze, chociaż mogę się mylić

    */
    double countInputError(vector<double> errors, int neuronNumber, double input)
    {
        double s = neurons[0][neuronNumber].getSum();                                                                                      // suma obliczana przez i-ty neuron k-tej warstwy
        double derivative = exp(s)/ pow(1 + exp(s), 2);

        double sum = 0;                                                                                                                         // suma error * waga
        vector<double> weightVector;
        for(int i=0;i<layerInputs[2];i++)
        {
            weightVector.push_back(neurons[1][i].getWeightVector()[neuronNumber]);
        }
        
        double weight;
        for(int i = 0; i < neurons[1].size(); i++)
        {
            weight = weightVector[i];
            sum += weight * errors[i]/neurons[1][i].getOutput();
        }

        return derivative * input * sum;
    }

    /*
    Metoda wykonująca propagację wsteczną. Wypełnia przy tym wektory kolumnowe wag i dq/d(theta).
    */
    void propagateBackwards()
    {
        int startingIndex=0;
        int layer=layerInputs.size()-2;

        for(int i=0;i<layerInputs[layer+1];i++)                                                                                              // propagacja po neuronach warstwy wyjściowej
        {
            vector<double> weight = neurons[layer][i].getWeightVector();                                                                    // tworzenie wektora kolumnowego wag                                                                     
            columnWeightVector.insert(end(columnWeightVector), begin(weight), --end(weight)); // --end() bo chyba nie chcę wagi wejścia o wartości 1

            for(int j=0;j<layerInputs[layer];j++)

                error.push_back(countOuterError(networkOutput[i],expectedNetworkOutput[i],j));
        }

        for(int z=layer;z>0;z--)                                                                                                               // propagacja po neuronach warstw ukrytych
        {
            for(int i=0;i<layerInputs[z];i++)                                                                                                 
            {
                vector<double> weight = neurons[z-1][i].getWeightVector();                                                                    // tworzenie wektora kolumnowego wag                                                                     
                columnWeightVector.insert(end(columnWeightVector), begin(weight), --end(weight)); // --end() bo chyba nie chcę wagi wejścia o wartości 1

                vector<double> errors;

                for(int x=0;x<layerInputs[z+1];x++)                                                                                            // przygotowanie wektora errors
                {
                    errors.push_back(error[startingIndex+i+(x*layerInputs[z])]);                                                               // x*layerInputs[z]->stride, startingIndex+i->offset
                }

                for(int j=0;j<layerInputs[z-1];j++)
                {
                    // dlaczego z-2 a nie z-1 :/
                    if(z>1)
                        error.push_back(countInnerError(errors,z,i,neurons[z-2][j].getOutput()));
                    else
                        error.push_back(countInputError(errors,i,neurons[z-1][0].getInput(j)));                                              // liczenie błędów dla wejść sieci (wejście nie zależy od numeru neuronu -> dla każdego takie samo)
                    
                }
            }
            startingIndex+=layerInputs[z+1]*layerInputs[z];
        }                                                                                       
    }

    /*
    Metoda przeprowadzająca sochastyczny najszybszy spadek
    */
    void sochasticDescent(double beta)
    {
        for(int i = 0; i < error.size(); ++i)
        {
            columnWeightVector[i] = columnWeightVector[i] - (beta * error[i] * 0.5);
        }

        return;
    }

    /*
    Metoda sprawdzająca dokładność przybliżenia wyjścia sieci neuronowej do zadanej oczekiwanej wartości.
    */
    bool precisionReached(double epsilon)
    {
        for(int i=0;i<networkOutput.size();i++)
        {
            //cout << abs(networkOutput[i]-expectedNetworkOutput[i]) / expectedNetworkOutput[i] << endl;
            if(abs(networkOutput[i]-expectedNetworkOutput[i]) / expectedNetworkOutput[i] > epsilon)
                return false;
        }
        return true;
    }

    public:

    /*
    Kozak debuggery
    */
    void print_weights()
    {
        cout<<"PRINT_WEIGHTS()"<<endl;
        int layer=layerInputs.size()-1;
        int j = 0;
        for(int z=layer;z>0;z--)              
        {
            for(int i=0;i<layerInputs[z];i++)                                                                                                 
            {
                cout<<"warstwa : "<<z<<" / neuron: "<<i<<" / wejscia: "<<neurons[z-1][i].getNumberOfInputs()<<" / wagi: ";
                vector<double> wagi = neurons[z-1][i].getWeightVector();
                j = 0;
                
                for (vector<double>::const_iterator w = wagi.begin(); w != --wagi.end(); ++w)
                    {
                        cout << *w<<" ";
                        
                        j++;
                    }
                cout<<endl;
            }
        }        
    }
    void print_weights_column_vector()
    {
        cout<<"PRINT_WEIGHTS_COLUMN_VECTOR()"<<endl;

        for(vector<double>::const_iterator i = columnWeightVector.begin(); i != columnWeightVector.end(); ++i)
        {
            cout<<*i<<" ";
        }
        cout<<endl;
    }

    void print_errors()
    {
        cout<<"PRINT_ERRORS()"<<endl;
        for(vector<double>::const_iterator i = error.begin(); i != error.end(); ++i)
        {
            cout<<*i<<" ";
        }
        cout<<endl;     
    }


    /*
    numberOfParameters - informacja o liczbie parametrów wejściowych
    layer - wektor przechwoujący informację o liczbie neuronów w każdej z powłok
    */
    mlp(int numberOfParameters, vector<int> layer)
    {
        layerInputs.push_back(numberOfParameters);
        layerInputs.insert(end(layerInputs), begin(layer), end(layer));
        int j=0;

        neurons.resize(layer.size());
        for(vector<int>::iterator it = layer.begin(); it != layer.end()-1; ++it)                               // stworzenie neuronów warstw ukrytych
        {
            for(int i=0;i<(*it);i++)                                                                           // resize tutaj nie zadziała, ponieważ zapełni wektor identycznymi neuronami (konstruktor zostanie wywołany raz dla każdej warstwy)
                neurons[j].push_back(neuron(1,layerInputs[j]));
            j++;
        }

        for(int i=0;i<layer.back();i++)
            neurons[j].push_back(neuron(0,layerInputs[j]));                                                   // stworzenie neuronów (liniowych) warstwy wyjściowej
        
        //vector<double> out (layer.back());
        //expectedNetworkOutput=out;
        expectedNetworkOutput.resize(layer.back());                                                          // domyślnie na wyjściu sieci jest wektor zer
        networkOutput.resize(layer.back());
    }

    ~mlp(){};

    /*
    Metoda pozwalająca na ustawienie wartości w wektorze wejść.
    */
    void setInput(int inputNumber, double value)
    {
        for(int i=0;i<layerInputs[1];i++)
            neurons[0][i].setInput(inputNumber, value);
    }

    void setExpectedOutput(int outputNumber, double value)
    {
        expectedNetworkOutput[outputNumber]=value;
    }

    /*
    Metoda symulująca przepływ danych przez perceptron.
    */
    void processData()
    {
        double output;
        int end=layerInputs.size();
        vector<double> outputVector;
        for(int i=1;i<end;i++)                                                                              // "przejście" przez sieć
        {
            for(int j=0;j<layerInputs[i];j++)
            {
                output=neurons[i-1][j].getNewOutput();
                if(i!=(end-1))
                {
                    for(int z=0;z<layerInputs[i+1];z++)                                                    // przekazanie wyjścia danego neuronu do neuronów następnej warstwy
                        neurons[i][z].setInput(j, output);
                }
                else
                    outputVector.push_back(output);
            }
        }
        networkOutput.assign(outputVector.begin(), outputVector.end());
    }

    /*
    Metoda symulująca przepływ danych przez perceptron i naukę (przykład po przykładzie).
    */
    void processDataAndLearn()
    {
        //print_weights();cout<<endl;
        double i=10;

        while(!precisionReached(0.01) && i<50)
        {
            //print_weights();cout<<endl;
            processData();
            propagateBackwards();
            sochasticDescent(1/i);

            int weightIndex=0;
            for(int z=layerInputs.size()-1;z>0;z--)                                                                                         // ustawienie wag
            {
                for(int i=0;i<layerInputs[z];i++)
                {
                    for(int j=0;j<layerInputs[z-1];j++)
                    {
                        neurons[z-1][i].setWeight(j,columnWeightVector[weightIndex]);
                        weightIndex++;
                    }
                }
            }

            error.clear();                                                                                                                  // wyczyszczenie buforów
            columnWeightVector.clear();

            //if(fmod(i,3)==0)
             //   i+=2;

            i+=0.5;
        }
        
        //print_weights();cout<<endl;
    }

    /*
    Zwraca wektor wyjść danej sieci neuronowej.
    */
    vector<double> getOutputVector()
    {
        return networkOutput;
    }

    friend ostream &operator<<( ostream &output, const mlp &network )
    {
        for(double i: network.networkOutput)
            output << i << " ";
    }         
};
