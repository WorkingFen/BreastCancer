#include <iostream>
#include <vector>

class Data{
private:
	int id;
	char diagnosis;
	//double* features;
	std::vector<double> features;

public:
/*
	Data(int id, char diagnosis, double* features){
		this->id = id;
		this->diagnosis = diagnosis;
		this->features = features;
	}
*/
	Data(int id, char diagnosis, std::vector<double> features){
		this->id = id;
		this->diagnosis = diagnosis;
		this->features = features;
	}
	~Data(){};

	int getID(){ return this->id; }

	char getDiagnosis(){ return this->diagnosis; }

	double getFeature(int f){ return this->features[f]; }

	//double* getFeatures(){ return this->features; }	
};
