#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>

class Solution {
   public:
    virtual long int partOne();
    virtual long int partTwo();
    std::string input;

    Solution(std::string inputPath) {
        std::ifstream file(inputPath);

        if (file) {
            std::ostringstream buffer;
            buffer << file.rdbuf();
            input = buffer.str();
        } else {
            std::cerr << "Error: Could not open file " << inputPath << std::endl;
        }
    }
};