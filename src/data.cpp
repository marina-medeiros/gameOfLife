#include <array>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <fstream> 
#include <iostream> 
#include <cstdlib> // for system
#include <sstream>
#include "data.h"

std::string trim(const std::string &str) {
    size_t first = str.find_first_not_of(' ');
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

std::unordered_map<std::string, std::string> Data::read_ini(std::string iniFile) {
    std::ifstream inputFile(iniFile);
    std::unordered_map<std::string, std::string> answers;

    if (!inputFile.is_open()) { 
        std::cerr << "Error opening the file!" << std::endl;
        return answers;
    }

    std::string line;

    while (std::getline(inputFile, line)) {
        // Ignorar linhas de comentário
        if (line.empty() || line[0] == ';' || line[0] == '#') {
            continue;
        }
        size_t equalPosition = line.find('=');
        if (equalPosition != std::string::npos) {
            std::string key = trim(line.substr(0, equalPosition));
            std::string value = trim(line.substr(equalPosition + 1));

            // Remove comments
            size_t comment_pos = value.find(';');
            if (comment_pos != std::string::npos) {
                value = trim(value.substr(0, comment_pos));
            }

            answers.insert({key, value});
        }
    }
    inputFile.close();
    return answers;
}