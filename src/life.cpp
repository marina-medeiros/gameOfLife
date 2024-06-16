#include <iostream>
#include <vector>
#include <fstream> 
#include <utility>
#include <set>
#include <sstream>
#include <cstdlib> // for system
#include <thread>   // for sleep_for
#include <chrono>   // for chrono::seconds

#include "life.h"
#include "../lib/canvas.h"
#include "../lib/common.h"


namespace life{
/**
 * @brief Reads the matrix configuration from a file.
 *
 * This function reads the matrix configuration from the specified file,
 * initializes the matrix size, and sets the character representing a live cell.
 *
 * @param path The path to the configuration file.
 */
    void Life::read_matrix_config(std::string path){
        path = "../" + path;
        std::ifstream inputFile(path);

        if (!inputFile.is_open()) { 
            std::cerr << "Error opening the matrix intiation file! " << path << std::endl;
            return;
        }

        std::string line;

        std::getline(inputFile, line);

        size_t spacePos = line.find(' ');

        m_rows = stoi(line.substr(0, spacePos)) + 2;
        m_cols = stoi(line.substr(spacePos + 1)) + 2;

        std::cout << ">>> Grid size read from input file: " << m_cols << " by cols" << m_rows << " rows." << std::endl;

        std::getline(inputFile, line);
        m_liveChar = line[0];

        std::cout << ">>> Character that represents a living cell read from input file: " << m_liveChar << std::endl;

        // Resize the matrix to the appropriate number of rows and columns
        m_currentMatrix.resize(m_rows, std::vector<int>(m_cols, 0));

        std::string rowSubstring;
        for(int ii = 1; ii < m_rows-1; ii++){
            std::getline(inputFile, line);
            int lineSize = static_cast<int>(line.size());
            if(lineSize < m_cols){
                rowSubstring = line;
                rowSubstring.resize(m_cols, '.');
            }else{
                rowSubstring = line.substr(0, m_cols);
            }
            for (int jj = 1; jj < m_cols-1; jj++) {
                if (rowSubstring[jj-1] == m_liveChar) {
                    m_currentMatrix[ii][jj] = 1;
                } else {
                    m_currentMatrix[ii][jj] = 0;
                }
            }
        }

        inputFile.close();
        std::cout << ">>> Finished reading input data file.\n" << std::endl;
    }


/**
 * @brief Sets the conditions for cell birth and survival.
 *
 * This function sets the birth and survival conditions for the simulation
 * based on the given input string.
 *
 * @param input A string representing the birth and survival conditions in the format "B3/S23".
 */
    void Life::set_conditions(const std::string input){
        size_t slashPos = input.find('/');

        std::string bornPart = input.substr(1, slashPos - 1);
        std::string survivesPart = input.substr(slashPos + 2);
        
        for(char c : bornPart){
            m_bornConditions.push_back(c - '0');
        }

        for(char c : survivesPart){
            m_surviveConditions.push_back(c - '0');
        }
    }


/**
 * @brief Extracts the prefix of the configuration file name.
 *
 * This function extracts the prefix (e.g., "cfg1") from the configuration file path.
 *
 * @return The extracted prefix of the configuration file name.
 */
    std::string Life::extractConfigPrefix() {
        // Find the position of the last '/'
        size_t lastSlashPos = m_cfgFile.find_last_of('/');
        if (lastSlashPos == std::string::npos) {
            return "";
        }

        // Find the position of the last '.'
        size_t lastDotPos = m_cfgFile.find_last_of('.');
        if (lastDotPos == std::string::npos) {
            return "";
        }

        // Extract the substring between the last '/' and the last '.'
        return m_cfgFile.substr(lastSlashPos + 1, lastDotPos - lastSlashPos - 1);
    }

/**
 * @brief Finds the dead neighbors of a cell.
 *
 * This function finds the dead neighbors of a cell at the specified row and column.
 *
 * @param row The row index of the cell.
 * @param col The column index of the cell.
 * @return A vector of pairs representing the coordinates of the dead neighbors.
 */
    std::vector<std::pair<int, int>> Life::find_dead_neighbors(int row, int col){
        std::vector<std::pair<int, int>> coords;
        std::vector<std::pair<int, int>> directions = {
            {-1, -1}, {-1, 0}, {-1, 1},
            { 0, -1},         { 0, 1},
            { 1, -1}, { 1, 0}, { 1, 1}
        };

        int count = 0;
        for(const auto& dir : directions){
            if(m_currentMatrix[row + dir.first][col + dir.second] == 0){
                coords.emplace_back((row + dir.first), (col + dir.second));
                count++;
            }
        }

        return coords;
    }

/**
 * @brief Counts the live neighbors of a cell.
 *
 * This function counts the live neighbors of a cell at the specified row and column.
 *
 * @param row The row index of the cell.
 * @param col The column index of the cell.
 * @return The number of live neighbors.
 */
    int Life::count_live_neighbors(int row, int col){
        int count = 0;
        std::vector<std::pair<int, int>> directions = {
            {-1, -1}, {-1, 0}, {-1, 1},
            { 0, -1},         { 0, 1},
            { 1, -1}, { 1, 0}, { 1, 1}
        };

        for(const auto& dir : directions){
            if(m_currentMatrix[row + dir.first][col + dir.second] == 1){
                count++;
            }
        }

        return count;
    }

/**
 * @brief Sets the borders cells. A cell is considered a border cell when it is a dead neighbor of a live cell.
 *
 * This function sets the borders cells by marking the dead neighbors of live cells.
 */
    void Life::set_borders(){
        for(int ii = 1; ii < m_rows -1; ii++){
            for(int jj = 1; jj < m_cols-1; jj++){
                if(m_currentMatrix[ii][jj] == 1){
                    std::vector<std::pair<int, int>> deadNeighbors = find_dead_neighbors(ii, jj);
                    for(const auto& cell : deadNeighbors){
                        m_currentMatrix[cell.first][cell.second] = 2;
                    }
                }
            }
        }
    }

/**
 * @brief Generates a new matrix for the next generation.
 *
 * This function generates a new matrix for the next generation based on the current matrix
 * and the birth and survival conditions.
 *
 * @return The new matrix for the next generation.
 */
    std::vector<std::vector<int>> Life::generate_new_matrix(){
        set_borders();
        std::vector<std::vector<int>> newMatrix = m_currentMatrix;
        for(int ii = 1; ii < m_rows-1; ii++){
            for(int jj = 1; jj < m_cols-1; jj++){
                if(m_currentMatrix[ii][jj] == 1){
                    int aliveNeighbors = count_live_neighbors(ii, jj);
                    bool willSurvive = false;
                    for(const auto& surviveCondition : m_surviveConditions){
                        if(aliveNeighbors == surviveCondition){
                            willSurvive = true;
                        }
                    }
                    if(!willSurvive){
                        newMatrix[ii][jj] = 0;
                    }
                }
                if(m_currentMatrix[ii][jj] == 2){
                    int aliveNeighbors = count_live_neighbors(ii, jj);
                    for(const auto& bornCondition : m_bornConditions){
                        if(aliveNeighbors == bornCondition){
                            newMatrix[ii][jj] = 1;
                            break;
                        }
                    }
                }
            }
        }

        return newMatrix;
    }

/**
 * @brief Counts the number of alive cells in the current matrix.
 *
 * This function counts the number of alive cells (cells with value 1) in the current matrix.
 *
 * @return The number of alive cells.
 */
    int Life::count_alive_cells(){
        int count = 0;
        for (const auto& row : m_currentMatrix) {
            for (int value : row) {
                if(value == 1){
                    count++;
                }
            }
        }

        return count;
    }

/**
 * @brief Generates a string key for the current matrix.
 *
 * This function generates a string key representing the current matrix state,
 * used for detecting repeated patterns.
 *
 * @return A string key representing the current matrix state.
 */
    std::string Life::generate_matrix_key(){
        std::string stringfication;
        std::stringstream oss;
        for(int ii = 1; ii < m_rows-1; ii++){
            for(int jj = 1; jj < m_cols-1; jj++){
                if(m_currentMatrix[ii][jj] == 2){
                    oss << "0";
                }else{
                    oss << m_currentMatrix[ii][jj];
                }
            }
        }

        stringfication = oss.str();
        return stringfication;
    }

/**
 * @brief Checks if the given matrix key is already present.
 *
 * This function checks if the given matrix key is already present in the set of all matrices.
 *
 * @param matrixKey The matrix key to check.
 * @return True if the matrix key is already present, false otherwise.
 */
    bool Life::matrix_is_repeated(std::string matrixKey) {
        auto result = m_allMatrixes.insert(matrixKey);
        
        return !result.second;
    }

/**
 * @brief Prints the current matrix to the console.
 *
 * This function prints the current matrix to the console, displaying the generation count.
 *
 * @param genCount The current generation count.
 */
    void Life::print_matrix(int& genCount){
        std::cout << "Generation " << genCount << ":" << std::endl;
        for(int ii = 1; ii < m_rows-1; ii++){
            std::cout << '[';
            for(int jj = 1; jj < m_cols-1; jj++){
                if(m_currentMatrix[ii][jj] == 2 || m_currentMatrix[ii][jj] == 0){
                    std::cout << ' ';
                }else{
                    std::cout << m_liveChar;
                }
            }
            std::cout << ']' << std::endl;
        }
        std::cout << std::endl;
    }

/**
 * @brief Runs the simulation loop.
 *
 * This function runs the simulation loop, generating new generations and updating the matrix.
 * The loop terminates if a repeated pattern is detected, no live cells are present, or the maximum
 * number of generations is reached.
 */
    void Life::simulation_loop(){
        int genCount = 1;
        while(true){
            if(matrix_is_repeated(generate_matrix_key())){
                return;
            }
            if(count_alive_cells() == 0){
                break;
            }
            if(genCount > m_maxGen){
                break;
            }
            unsigned width = static_cast<unsigned int>(m_cols-2);
            unsigned height = static_cast<unsigned int>(m_rows-2);
            Canvas image(width, height, m_blockSize);
            int frame_duration_ms = 1000 / m_fps;
            std::this_thread::sleep_for(std::chrono::milliseconds(frame_duration_ms));
            if(m_image){
                image.matrix_to_png(m_currentMatrix, m_aliveColor, m_bkgColor, m_imagePath, extractConfigPrefix(), genCount);
                print_matrix(genCount);
            }else{
                print_matrix(genCount);
            }
            genCount++;
            std::vector<std::vector<int>> newMatrix = generate_new_matrix();
            m_currentMatrix = newMatrix;
        }
    }

}