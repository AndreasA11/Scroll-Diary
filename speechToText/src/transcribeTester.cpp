#include <iostream>
#include <fstream>


int main(int argc, char** argv) {
    if(argc < 3) {
        std::cerr << "Usage: <testInput.txt> <testResult.txt> \n";
        exit(1);
    }

    std::string testResultFilePath = argv[2];
    std::ifstream resultStream(testResultFilePath);


    if(!resultStream.is_open()) {
        std::cerr << "Error in opening file: " << testResultFilePath << "\n";
        exit(1);
    }

    std::string inputString;
    std::string resultString;

    bool startComparison = false;

    std::string fullInputString;
    std::string fullResultString;

    while(std::getline(resultStream, resultString)) {
        if(startComparison) {
            //start comparison logic. Maybe put everything into one string?
            if(resultString[0] == '[') {
                continue; //for [INFO] lines
            }
            for(int i = 0; i < resultString.size(); ++i) {
                if(resultString[i] != '\n') {
                    fullResultString += resultString[i];
                }

            }
        }
        
        if(resultString != "Press Ctrl+C to stop" && !startComparison) {
            //do nothing
        } else {
            startComparison = true;
        }

    }

    resultStream.close();

    std::string testInputFilePath = argv[1];
    std::ifstream inputStream(testInputFilePath);

    if(!inputStream.is_open()) {
        std::cerr << "Error in opening file: " << testInputFilePath << "\n";
        exit(1);
    }

    while(std::getline(inputStream, inputString)) {
        for(int i = 0; i < inputString.size(); ++i) {
            if(inputString[i] != '\n') {
                fullInputString += inputString[i];   
            }
        }
    }

    inputStream.close();

    std::cout << "RESULT: " << fullResultString << "\n";
    std::cout << "\n";
    std::cout << "INPUT: " << fullInputString << "\n";

    
    
    
    
    return 0;

    
}