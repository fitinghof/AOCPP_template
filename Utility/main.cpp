#include "Solution.hpp"

int main(int argc, char* argv[]){
    if(argc != 2) return -1;

    Solution solution(argv[1]);
    std::cout << "Part 1: " << solution.partOne() << "\n";
    std::cout << "Part 2: " << solution.partTwo() << "\n";
}