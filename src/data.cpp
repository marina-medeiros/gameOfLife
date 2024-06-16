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

/**
 * @brief Trims leading and trailing spaces from a given string.
 *
 * This function removes all leading and trailing spaces from the input string
 * and returns the result.
 *
 * @param str The input string to be trimmed.
 * @return A new string with leading and trailing spaces removed.
 */
std::string trim(const std::string &str) {
    size_t first = str.find_first_not_of(' ');
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

/**
 * @brief Reads and processes an INI file to extract key-value pairs.
 *
 * This member function of the Data class opens the specified INI file,
 * processes its contents to extract key-value pairs, and stores them in
 * a member variable `variablesAndValues`.
 *
 * @param iniFile The path to the INI file to be read.
 */
void Data::read_ini(std::string iniFile) {
    std::cout << ">>> Trying to open input file [" << iniFile << "]...";
    std::ifstream inputFile(iniFile);
    std::unordered_map<std::string, std::string> answers;

    if (!inputFile.is_open()) { 
        std::cerr << ">>> Error opening initiation file!" << std::endl;
        exit(1);
    }
    std::cout << " done!" << std::endl;
    std::cout << ">>> Processing data, please wait..." << std::endl;

    std::string line;

    while (std::getline(inputFile, line)) {
        // Ignorar linhas de comentário
        if (line.empty() || line[0] == ';' || line[0] == '#') {
            continue;
        }
        size_t equalPosition = line.find('=');
        if (equalPosition != std::string::npos) {
            std::string variable = trim(line.substr(0, equalPosition));
            std::string value = trim(line.substr(equalPosition + 1));

            // Remove comments
            size_t comment_pos = value.find(';');
            if (comment_pos != std::string::npos) {
                value = trim(value.substr(0, comment_pos));
            }

            answers.insert({variable, value});
        }
    }
    inputFile.close();
    variablesAndValues = answers;
}