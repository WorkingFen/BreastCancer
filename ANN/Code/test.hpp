#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <string>
#include <cstdlib>
#include "mlp.hpp"
#include "load.hpp"

using namespace std;

class Test{
private:
	
	void scale(mlp *network, std::vector<Data*> input, unsigned index){
		/////////////////////////// Skalowanie danych wejściowych //////////////////////////
        
        network->setInput(0, (input[index]->getFeature(0))/100);
		network->setInput(1, (input[index]->getFeature(1))/100);
        network->setInput(2, (input[index]->getFeature(2))/100);
        network->setInput(3, (input[index]->getFeature(3))/100);
		network->setInput(4, (input[index]->getFeature(4))*10);
		network->setInput(5, (input[index]->getFeature(5))*10);
		network->setInput(6, (input[index]->getFeature(6))*100);
		network->setInput(7, (input[index]->getFeature(7))*100);
        network->setInput(8, (input[index]->getFeature(8))*10);
        network->setInput(9, (input[index]->getFeature(9))*100);
		network->setInput(10, (input[index]->getFeature(10))*10);
		network->setInput(11, (input[index]->getFeature(11)));
		network->setInput(12, (input[index]->getFeature(12))/10);
        network->setInput(13, (input[index]->getFeature(13))/100);
        network->setInput(14, (input[index]->getFeature(14))*100);
		network->setInput(15, (input[index]->getFeature(15))*100);
		network->setInput(16, (input[index]->getFeature(16))*100);
		network->setInput(17, (input[index]->getFeature(17))*100);
		network->setInput(18, (input[index]->getFeature(18))*100);
        network->setInput(19, (input[index]->getFeature(19))*1000);
        network->setInput(20, (input[index]->getFeature(20))/100);
        network->setInput(21, (input[index]->getFeature(21))/100);
        network->setInput(22, (input[index]->getFeature(22))/1000);
        network->setInput(23, (input[index]->getFeature(23))/1000);
		network->setInput(24, (input[index]->getFeature(24))*10);
		network->setInput(25, (input[index]->getFeature(25))*10);
		network->setInput(26, (input[index]->getFeature(26))*10);
		network->setInput(27, (input[index]->getFeature(27))*100);
		network->setInput(28, (input[index]->getFeature(28))*10);
		network->setInput(29, (input[index]->getFeature(29))*10);
        
        ////////////////////////////////////////////////////////////////////////////////////
	}
	
public:

	void makeTest(std::vector<Data*> input, unsigned inputAmount, std::vector<int> layers, unsigned noInstances, unsigned challangesNo){
		mlp network(inputAmount, layers);

		default_random_engine rand_num{static_cast<long unsigned int>(chrono::high_resolution_clock::now().time_since_epoch().count())};
		uniform_real_distribution<> dis(0,noInstances-1);

		int properlyClassified=0;

		for(int i=0;i<challangesNo;i++)                              // uczenie sieci neuronowej na 2000 wybieranych losowo przykładach
		{
			int chosenExample=dis(rand_num);

			scale(&network, input, chosenExample);
			
			if(input[chosenExample]->getDiagnosis()=='M')
				network.setExpectedOutput(0, 1);
			else
				network.setExpectedOutput(0, 0);

			network.processDataAndLearn();  
		}

		for(int i=0;i<noInstances;i++)                              // sprawdzanie jakości nauki
		{
			scale(&network, input, i);
			
			network.processData();

			if((input[i]->getDiagnosis()=='M' && network.getOutputVector()[0]>=0.5) || (input[i]->getDiagnosis()=='B' && network.getOutputVector()[0]<0.5))
				properlyClassified+=1;
		}

		cout << "Properly classified: " << properlyClassified << " in "<< noInstances;
		cout <<" examples. That is " << ((double)properlyClassified/noInstances)*100 << " percent." << endl;
	}
	
	void makeTest(std::vector<Data*> input, mlp network, unsigned noInstances){
		unsigned challangesNo = floor((noInstances*3)/4);
		unsigned verificationNo = noInstances - challangesNo;
		
		std::vector<Data*> verifyingInput;
		std::vector<unsigned> verifyingNumbers;
		
		default_random_engine rand_num{static_cast<long unsigned int>(chrono::high_resolution_clock::now().time_since_epoch().count())};
		uniform_real_distribution<> dis(0,noInstances-1);
		
		for(int i=0;i<verificationNo;){			
			int example = dis(rand_num);
			
			bool repeat = false;

			for(int j=0;j<verifyingNumbers.size();j++){
				if(verifyingNumbers[j]==example){
					repeat = true;
					break;
				}				
			}
			if(!repeat){
				verifyingInput.push_back(input[example]);
				verifyingNumbers.push_back(example);
				i++;
			}
		}
		
		std::sort(verifyingNumbers.begin(), verifyingNumbers.end(), std::greater<int>());
		
		for(int i=0;i<verificationNo;i++)
			input.erase(input.begin()+verifyingNumbers[i]);

		int properlyClassified=0;

		for(int i=0;i<challangesNo;i++)                           // uczenie sieci neuronowej na 75% przykładów
		{
			scale(&network, input, i);
			
			if(input[i]->getDiagnosis()=='M')
				network.setExpectedOutput(0, 1);
			else
				network.setExpectedOutput(0, 0);

			network.processDataAndLearn();  
		}
		
		unsigned mDis = 0;
		unsigned bDis = 0;

		int truePositive=0;
		int trueNegative=0;
		int falsePositive=0;
		int falseNegative=0;

		for(int i=0;i<verificationNo;i++)                // sprawdzanie jakości nauki na pozostałych przykładach
		{
			scale(&network, verifyingInput, i);
			
			network.processData();
			
			if(verifyingInput[i]->getDiagnosis()=='M') mDis++;
			else bDis++;

			if((verifyingInput[i]->getDiagnosis()=='M' && network.getOutputVector()[0]>=0.5) || (verifyingInput[i]->getDiagnosis()=='B' && network.getOutputVector()[0]<0.5))
				properlyClassified+=1;

			if(verifyingInput[i]->getDiagnosis()=='M' && network.getOutputVector()[0]>=0.5)
				truePositive++;
			else if(verifyingInput[i]->getDiagnosis()=='M')
				falseNegative++;
			else if(verifyingInput[i]->getDiagnosis()=='B' && network.getOutputVector()[0]<0.5)
				trueNegative++;
			else
				falsePositive++;
		}
		
		cout << "Distribution M:B -> " << mDis << ":" << bDis << "\t";
		cout << "Properly classified: " << properlyClassified << " in "<< verificationNo;
		cout <<" examples. That is " << ((double)properlyClassified/verificationNo)*100 << " percent." << endl;
		cout << "TRUE POSITIVE: " << truePositive << " FALSE POSITIVE: " << falsePositive << " TRUE NEGATIVE: " << trueNegative << " FALSE NEGATIVE: " << falseNegative << endl;
	}



/* funkcja sprawdzająca czy struktura sieci została poprawnie przypisana */
int testStructure(int inputsN, std::vector<int> neurons){
	mlp network(inputsN,neurons);

	int networkInputs = network.getNumberOfNetworkInputs();
	std::vector<int> n = network.getNumberOfNeurons();

	if (inputsN != networkInputs){ 		// sprawdzenie liczby wejść
		return -1;
	}
	if (neurons.size() != n.size()) return -2;   // sprawdzenie liczby warstw

	auto it = neurons.begin();
	auto it2 = n.begin();
	for(it; it != neurons.end(); ++it){ 	// sprawdzenie liczby neuronów w każdej warstwie

		if(*it != *it2) return -3;	

		++it2;
	}

	return 1;
}

/* funkcja sprawdzająca, czy wejścia 1. warstwy zostają poprawnie przypisane do sieci */
int testInputs(int inputsN, std::vector<int> neuronsN, std::vector<double> inputs){
	mlp network(inputsN, neuronsN);

	int i = 0;
	for(auto it = inputs.begin(); it != inputs.end(); ++it){
		network.setInput(i, *it);
		++i;
	} 

	std::vector<std::vector<neuron>> neurons = network.getNeurons();

	auto layer = neurons.begin();
	for(auto n = (*layer).begin(); n != (*layer).end(); ++n){     // dla każdego neuronu w 1. warswie

		if(inputs.size() != (*n).getNumberOfInputs()) return -2;

		for(int j = 0; j < inputs.size(); j++){					   // dla każdego wejścia neuronu
			if((*n).getInput(j) != inputs[j]){
				return -1;
			}
		}
	}
	return 1;
}

/*  funkcja sprawdzająca, czy wyjście neuronu jest prawidłowo obliczane */
int testNeuronF(){
	neuron n(1, 3);

	n.setInput(0,1.5);
	n.setInput(1,0.5);
	n.setInput(2,0.3);

	n.setWeight(0,0.1);
	n.setWeight(1,0.2);
	n.setWeight(2,0.13);
	n.setWeight(3,0.13);

	double out = n.getNewOutput();
	if(out < 0.61 && out > 0.6 ) return 1;
	return -1;
}


	
};
	
	