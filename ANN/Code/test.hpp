#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <string>
#include <cstdlib>

using namespace std;

class Test{
private:
	
	void scale(mlp network, std::vector<Data*> input, unsigned index){
		/////////////////////////// Skalowanie danych wejściowych //////////////////////////
        
        network.setInput(0, (input[index]->getFeature(0))/100);
		network.setInput(1, (input[index]->getFeature(1))/100);
        network.setInput(2, (input[index]->getFeature(2))/100);
        network.setInput(3, (input[index]->getFeature(3))/100);
		network.setInput(4, (input[index]->getFeature(4))*10);
		network.setInput(5, (input[index]->getFeature(5))*10);
		network.setInput(6, (input[index]->getFeature(6))*100);
		network.setInput(7, (input[index]->getFeature(7))*100);
        network.setInput(8, (input[index]->getFeature(8))*10);
        network.setInput(9, (input[index]->getFeature(9))*100);
		network.setInput(10, (input[index]->getFeature(10))*10);
		network.setInput(11, (input[index]->getFeature(11)));
		network.setInput(12, (input[index]->getFeature(12))/10);
        network.setInput(13, (input[index]->getFeature(13))/100);
        network.setInput(14, (input[index]->getFeature(14))*100);
		network.setInput(15, (input[index]->getFeature(15))*100);
		network.setInput(16, (input[index]->getFeature(16))*100);
		network.setInput(17, (input[index]->getFeature(17))*100);
		network.setInput(18, (input[index]->getFeature(18))*100);
        network.setInput(19, (input[index]->getFeature(19))*1000);
        network.setInput(20, (input[index]->getFeature(20))/100);
        network.setInput(21, (input[index]->getFeature(21))/100);
        network.setInput(22, (input[index]->getFeature(22))/1000);
        network.setInput(23, (input[index]->getFeature(23))/1000);
		network.setInput(24, (input[index]->getFeature(24))*10);
		network.setInput(25, (input[index]->getFeature(25))*10);
		network.setInput(26, (input[index]->getFeature(26))*10);
		network.setInput(27, (input[index]->getFeature(27))*100);
		network.setInput(28, (input[index]->getFeature(28))*10);
		network.setInput(29, (input[index]->getFeature(29))*10);
        
        ////////////////////////////////////////////////////////////////////////////////////
	}
	
public:

	void makeTest(unsigned inputAmount, vector<int> layers, unsigned noInstances, unsigned challangesNo){
		std::vector<Data*> input;
		mlp network(inputAmount, layers);

		default_random_engine rand_num{static_cast<long unsigned int>(chrono::high_resolution_clock::now().time_since_epoch().count())};
		uniform_real_distribution<> dis(0,noInstances-1);

		int properlyClassified=0;

		for(int i=0;i<challangesNo;i++)                           // uczenie sieci neuronowej na 2000 wybieranych losowo przykładach
		{
			int chosenExample=dis(rand_num);

			scale(network, input, chosenExample);
			
			if(input[chosenExample]->getDiagnosis()=='M')
				network.setExpectedOutput(0, 1);
			else
				network.setExpectedOutput(0, 0);

			network.processDataAndLearn();  
		}

		for(int i=0;i<noInstances;i++)                                                                                                                              // sprawdzanie jakości nauki
		{
			scale(network, input, i);
			
			network.processData();
			cout << input[i]->getDiagnosis() << " ";
			cout << network.getOutputVector()[0];
			cout << endl;

			if((input[i]->getDiagnosis()=='M' && network.getOutputVector()[0]>=0.5) || (input[i]->getDiagnosis()=='B' && network.getOutputVector()[0]<0.5))
				properlyClassified+=1;
		}

		cout << "Properly classified: " << properlyClassified << " in "<< noInstances <<" examples. That is " << ((double)properlyClassified/noInstances)*100 << " percent." << endl;
	}
	
}
	
	