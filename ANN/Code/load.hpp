#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <vector>
#include "data.hpp"

class Load{
private:
	std::ifstream loading;
	unsigned size = 0;

public:
	std::vector<Data*> read(std::string file){
		std::string line;
		std::vector<std::string> data;
		std::vector<Data*> input;

		this->loading.open(file);
		if(loading.good()){
			int id;
			char diagnosis;
			std::vector<double> features(30);
			while(loading >> line){
				data = split(line, ',');
				id = atoi(data[0].c_str());
				diagnosis = data[1][0];
				for(int i = 0; i < 30; i++)
					features[i] = std::stod(data[i+2]);
				input.push_back(new Data(id, diagnosis, features));
				this->size++;
			}
		}
		else{
		    std::string msg = "An error occurred while loading from file " + file;
		    throw msg;
		}
		this->loading.close();
		return input;
	}

	std::vector<std::string> split(const std::string& s, char delimiter){
		std::vector<std::string> tokens;
		std::string token;
		std::istringstream tokenStream(s);
		while(std::getline(tokenStream, token, delimiter))
			tokens.push_back(token);
		return tokens;
	}
	
	unsigned getSize(){ return this->size; }
};
