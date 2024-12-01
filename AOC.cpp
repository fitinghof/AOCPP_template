#include <chrono>
#include <iostream>
#include <filesystem>
#include <fstream>

const std::string compiler = "g++ ";
const std::string FLAGS = "-std=c++20 -g -I./Utility ";
const std::string exeName = "Solution.exe ";


const std::filesystem::path mainFile =
    std::filesystem::path("Utility") /
    std::filesystem::path("main.cpp");

const std::filesystem::path solutions = "Solutions";

const std::string part1Name = "part1.cpp";
const std::string part2Name = "part2.cpp";
const std::string hppName = "Solution.hpp";
const std::string inputName = "input.txt";

const std::filesystem::path templateFolder = "templates";
const std::filesystem::path templatePart1 = templateFolder / "part1_template.txt";
const std::filesystem::path templatePart2 = templateFolder / "part2_template.txt";
const std::filesystem::path templatehpp = templateFolder / "templatehpp.txt";

struct currentAOC {
    std::chrono::year year;
    std::chrono::day day;
};

void setup(currentAOC currentAOC);

int main(int argc, char* argv[]){
    auto time = std::chrono::zoned_time(std::chrono::current_zone(), std::chrono::system_clock::now()).get_local_time();

    auto dur = time.time_since_epoch();
    auto ymd = std::chrono::year_month_day(std::chrono::time_point_cast<std::chrono::days>(time));

    std::cout << time << "\n";
    std::cout << ymd << "\n";

    currentAOC currentAOC{ymd.year(), ymd.day()};

    switch (argc) {
        case 1:
            break;
        case 2:
            currentAOC.day = std::chrono::day(std::stol(argv[1]));
            break;
        case 3:
            currentAOC.year = std::chrono::year(std::stol(argv[1]));
            currentAOC.day = std::chrono::day(std::stol(argv[2]));
            break;
        default:
            return -1;
    }

    setup(currentAOC);

    const std::filesystem::path yearPath = solutions / std::to_string((int)currentAOC.year);
    const std::filesystem::path dayPath = yearPath / ("day" + std::to_string((unsigned int)currentAOC.day));
    std::string cppFiles = mainFile.string() + " ";

    for (std::filesystem::path file : std::filesystem::directory_iterator(dayPath)){
        if(file.string().ends_with(".cpp")){
            cppFiles += file.string() + " ";
        }
    }
    std::filesystem::path outPath = dayPath / exeName;

    std::string buildCommand = compiler + FLAGS + cppFiles + "-o " + outPath.string();
    system(buildCommand.c_str());

    std::string runCommand = outPath.string() + (dayPath / inputName).string();
    system(runCommand.c_str());
}

void setup(currentAOC currentAOC){

    // paths
    const std::filesystem::path yearPath = solutions / std::to_string((int)currentAOC.year);
    const std::filesystem::path dayPath = yearPath / ("day" + std::to_string((unsigned int)currentAOC.day));

    if(!std::filesystem::exists(dayPath) ||
        !std::filesystem::is_directory(dayPath)) {
        if(!std::filesystem::create_directories(dayPath)){
            std::cerr << "Failed to create day dir\n";
            return exit(-1);
        }
    }

    if(!std::filesystem::exists(dayPath / part1Name)) {
        std::filesystem::copy_file(templatePart1, dayPath / part1Name, std::filesystem::copy_options::skip_existing);
    }
    if(!std::filesystem::exists(dayPath / part2Name)) {
        std::filesystem::copy_file(templatePart2, dayPath / part2Name, std::filesystem::copy_options::skip_existing);
    }
    if(!std::filesystem::exists(dayPath / inputName)) {
        std::ofstream(dayPath / inputName);
    }
}