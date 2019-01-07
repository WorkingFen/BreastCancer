#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <math.h>
#include <random>
#include "neuron.hpp"

using namespace std;

class mlp{
    vector<int> layerInputs;                                                                                   // wektor przechowujący informację o liczbie wejść do neuronów w każdej z powłok
    vector<vector<neuron>> neurons;
    vector<double> networkOutput;
    vector<double> expectedNetworkOutput;
    vector<double> error;

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
    layer - numer warstwy w której jesteśmy (k)
    errors - wektor błędów z k+1-szej warstwy
    inputNumber - numer wejścia neuronu (liczone od 0)

    zapewne zrobimy macierz errors w klasie i nie będzie ona potrzebna tutaj w parametrach
    ale już taki layer raczej musi być przekazany w parametrze, chociaż mogę się mylić

    */

    double countInnerError(vector<double> errors, int layer, int inputNumber, double input)
    {
        //double y = neurons[layer-1][inputNumber].getOutput(); // wyjście j-tego neuronu warstwy k-1
        //double s = neurons[layer][inputNumber].getSum();        // suma obliczana przez i-ty neuron k-tej warstwy

        double s = neurons[layer-1][inputNumber].getSum();    // suma obliczana przez i-ty neuron k-tej warstwy
        double derivative = exp(s)/ pow(1 + exp(s), 2);

        double sum = 0;                                         // suma error * waga

        vector<double> weightVector;
        for(int i=0;i<layerInputs[layer+1];i++)
        {
            weightVector.push_back(neurons[layer][i].getWeightVector()[inputNumber]);
        }
        
        double weight;
        for(int i = 0; i < neurons[layer].size(); i++)
        {
            weight = weightVector[i];
            sum += weight * errors[i]/neurons[layer][inputNumber].getOutput();
        }

        return derivative * input * sum;
    }

    void propagateBackwards()
    {
        int startingIndex=0;
        int layer=layerInputs.size()-2;

        for(int i=0;i<layerInputs[layer+1];i++)                                                                                                 // propagacja po neuronach warstwy wyjściowej
        {
            for(int j=0;j<layerInputs[layer];j++)
                error.push_back(countOuterError(networkOutput[i],expectedNetworkOutput[i],j));
        }

        for(int z=layer;z>0;z--)                                                                                                               // propagacja po neuronach warstw ukrytych
        {
            for(int i=0;i<layerInputs[z];i++)                                                                                                 
            {
                vector<double> errors;
                for(int x=0;x<layerInputs[z+1];x++)                                                                                            // przygotowanie wektora errors
                {
                    errors.push_back(error[startingIndex+i+(x*layerInputs[z])]);                                                               // layerInputs[z]-offset, i-stride
                }

                for(int j=0;j<layerInputs[z-1];j++)
                {
                    if(z>1)
                        error.push_back(countInnerError(errors,z,j,neurons[z-2][j].getOutput()));
                    else
                        error.push_back(countInnerError(errors,z,j,neurons[z-1][0].getInput(j)));                                              // liczenie błędów dla wejść sieci (wejście nie zależy od numeru neuronu -> dla każdego takie samo)
                }
            }
            startingIndex+=layerInputs[z+1]*layerInputs[z];
        }                                                                                       
    }

    public:
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
        
        vector<double> out (layer.back());
        expectedNetworkOutput=out;
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

    void processDataAndLearn()
    {
        processData();
        propagateBackwards();
        // funkcja wyjścia -> metoda private
        // wsteczna propagacja, zmiana wag -> metoda private
    }

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
