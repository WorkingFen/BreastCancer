#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <math.h>
#include "neuron.hpp"

using namespace std;

class mlp{
    vector<int> layerInputs;                                                                                   // wektor przechowujący informację o liczbie wejść do neuronów w każdej z powłok
    vector<vector<neuron>> neurons;
    vector<double> networkOutput;

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
