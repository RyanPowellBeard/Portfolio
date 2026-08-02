#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>

/*Global Variables*/
std::ofstream saveResults;
//Using mutex instead of atomic. Atomic is more relaxed ordering with better performace
//whereas mutex has a stricter ordering
std::mutex mut; //mutex declaration

//proto functions
void count_up(int *results);
void count_down(int *results);
void open_file(std::string saveFile);
void write_file(int *results, int id);
void close_file(void);

int main(void){
	try {
		//declare a string variable to hold the name of file for saving results
		std::string saveFile = "results.txt";

		//Parameter Variables(Instance Variables)
		//declare id numbner for count up and count down
		int idOne = 1;
		int idTwo = 2;

    	//declare a pointer array with dynamic memory (memory heap)
    	//allocating memory to hold 20 values and null indicator
    	int * upResults = new (std::nothrow) int[21];
		//handle exception by informing user
		if (upResults == nullptr){std::cout << "\nMemory could not be allocated.\n";}

    	int * downResults = new int[21];
		//handle exception by informing user
		if (downResults == nullptr){std::cout << "\nMemory could not be allocated.\n";}


		//Declaring and launching threads
		std::thread countOne(count_up, upResults);
		std::thread countTwo(count_down, downResults);
	
		//joining threads
		countOne.join();
		countTwo.join();

		//function calls
    	open_file(saveFile);
		write_file(upResults, idOne);
		write_file(downResults, idTwo);
		close_file();


    	//Free memory by deleting dynamic pointers
    	delete[] upResults;
    	delete[] downResults;

		return 0;
	}
		catch (std::exception& e) {
			//inform user of excetion
			std::cout << "Exception thrown in main().\n" << e.what();
	}


}

void count_up(int *results){
	try {
		//Access to this function thread is mutually exclusive
		std::lock_guard<std::mutex> guard(mut);
		for (int i = 0; i < 21; i++){
			std::cout << "Up count is: " << i << "\n";
			results[i] = i;

		}


	}
	catch (std::exception& e) {
		//inform user of exception
		std::cout << "Exception thrown in count_up().\n" << e.what();
	}

}

void count_down(int *results){
	try {
		//Access to this function thread is mutually exclusive
		std::lock_guard<std::mutex> guard(mut);
		for (int i = 20; i >= 0; i--){
			std::cout << "Down count is: " << i << "\n";
			results[i] = i;
		}


	}
	catch (std::exception& e) {
		//inform user of exceptio
		std::cout << "Exception thrown in count_down().\n" << e.what();
	}

}

//Function to open file
void open_file(std::string saveFile){
	try {

		//Try and open file
		//using app to append file to preserve previous results
		saveResults.open(saveFile, std::ios_base::app);

		//Check to ensure file opened
		if (saveResults.is_open()){
			//Inform user if file opened successfuly
			std::cout << "File opened successfuly.\n";
		}
		//If file is not open
		else {std::cout << "File is not open.\n";}
	}
	catch (std::exception& e){
		//inoform user of exception
		std::cout << "File did not open correctly.\n" << e.what();
	
	}
}

//Function to save to file
void write_file(int * results, int id){
	try{
		saveResults << "ID " << id << std::endl;

		if (id == 1){
			for (int i = 0; i < 21; i++){ //needs to compare to char array length
				saveResults << results[i] << std::endl;
        	}
		}
		if (id == 2){
			for (int i = 20; i >= 0; i--){ //needs to compare to char array length
				saveResults << results[i] << std::endl;
        	}
		}
	}
	catch (std::exception& e){
        	//Inform user of exception and location, then print what() caused the exception
        	std::cout << "Exception thrown writing to file. \n" << e.what();
    	}	

}

//Function to close file
void close_file(void){
	try {
		saveResults.close();
		//Run a check to ensure file closed
		if (saveResults.is_open()){//need to look at while loop to for force closing
			std::cout << "File did not close.\n";
		}
		else {std::cout << "File closed.\n";}
	}
	catch (std::exception& e){
        //Inform user of exception and location, then print what() caused the exception
        std::cout << "Exception thrown trying to close file. \n" << e.what();
    }
}
