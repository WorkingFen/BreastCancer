#include <iostream>

class Data{
private:
	int id;
	char diagnosis;
	double* features;

public:
	Data(int id, char diagnosis, double* features){
		this->id = id;
		this->diagnosis = diagnosis;
		this->features = features;
	}

	~Data(){};

	int getID(){ return this->id; }

	char getDiagnosis(){ return this->diagnosis; }

	double getFeature(int f){ return this->features[f]; }

	double* getFeatures(){ return this->features; }	
};
