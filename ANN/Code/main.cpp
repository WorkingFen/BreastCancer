#include "test.hpp"

int main(int argc, char* argv[])
{
    Load load;
	Test test;

	std::vector<Data*> input;
	
    if(argc > 1){
	    std::string file(argv[1]);
	    input = load.read(file);
    }
    else input = load.read("../Data/wdbc.data");

	std::cout << "Test 1: {4, 1}" << std::endl;
	mlp network1(30, {4, 1});
	for(int i = 0; i < 10; i++){
		test.makeTest(input, network1, load.getSize());
	}
	std::cout << std::endl << "Test 2: {6, 3, 1}" << std::endl;
	mlp network2(30, {6, 3, 1});
	for(int i = 0; i < 10; i++){
		test.makeTest(input, network2, load.getSize());
	}
	
	std::cout << std::endl << "Test 3: {7, 3, 2, 1}" << std::endl;
	mlp network3(30, {7, 3, 2, 1});
	for(int i = 0; i < 10; i++){
		test.makeTest(input, network3, load.getSize());
	}
	
	std::cout << std::endl << "Test 4: {11, 1}" << std::endl;
	mlp network4(30, {11, 1});
	for(int i = 0; i < 10; i++){
		test.makeTest(input, network4, load.getSize());
	}
	
	std::cout << std::endl << "Test 5: {30, 1}" << std::endl;
	mlp network5(30, {30, 1});
	for(int i = 0; i < 10; i++){
		test.makeTest(input, network5, load.getSize());
	}
	
	std::cout << std::endl << "Test 6: {100, 1}" << std::endl;
	mlp network6(30, {100, 1});
	for(int i = 0; i < 10; i++){
		test.makeTest(input, network6, load.getSize());
	}

    return 0;
}
