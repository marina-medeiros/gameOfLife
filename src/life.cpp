#include <iostream>
#include <vector>
#include <fstream> 
#include <iostream> 
#include <utility>
#include <set>
#include <sstream>

#include "life.h"
#include "../lib/canvas.h"
#include "../lib/common.h"


namespace life{
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

        std::getline(inputFile, line);
        char live = line[0];

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
            for (int jj = 0; jj < m_cols; jj++) {
                if (rowSubstring[jj] == live) {
                    m_currentMatrix[ii][jj+1] = 1;
                } else {
                    m_currentMatrix[ii][jj+1] = 0;
                }
            }
        }

        inputFile.close();
    }

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

        // Function to extract the 'cfg1' part of the given path
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

    std::vector<std::pair<int, int>> Life::find_dead_neighbors(int x, int y){
        std::vector<std::pair<int, int>> coords;
        std::vector<std::pair<int, int>> directions = {
            {-1, -1}, {-1, 0}, {-1, 1},
            { 0, -1},         { 0, 1},
            { 1, -1}, { 1, 0}, { 1, 1}
        };

        for(const auto& dir : directions){
            if(m_currentMatrix[y + dir.first][x + dir.second] == 0){
                coords.emplace_back((y + dir.first), (x + dir.second));
            }
        }

        return coords;
    }

    int Life::count_live_neighbors(int x, int y){
        int count = 0;
        std::vector<std::pair<int, int>> directions = {
            {-1, -1}, {-1, 0}, {-1, 1},
            { 0, -1},         { 0, 1},
            { 1, -1}, { 1, 0}, { 1, 1}
        };

        for(const auto& dir : directions){
            if(m_currentMatrix[y + dir.first][x + dir.second] == 0){
                count++;
            }
        }

        return count;
    }

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

    bool Life::matrix_is_repeated(std::string matrixKey){
        if(!m_allMatrixes.insert(matrixKey).second){
            return true;
        }else{
            m_allMatrixes.insert(matrixKey);
        }
        return false;
    }

    void Life::print_matrix(int& genCount){
        std::cout << "Generation " << genCount << ":" << std::endl;
        for(int ii = 1; ii < m_rows-1; ii++){
            std::cout << '[';
            for(int jj = 1; jj < m_cols-1; jj++){
                if(m_currentMatrix[ii][jj] == 2){
                    std::cout << ' ';
                }if(m_currentMatrix[ii][jj] == 0){
                    std::cout << '.';
                }if(m_currentMatrix[ii][jj] == 1){
                    std::cout << '*';
                }
                // if(m_currentMatrix[ii][jj] == 2 || m_currentMatrix[ii][jj] == 0){
                //     std::cout << ' ';
                // }else{
                //     std::cout << '*';
                // }
            }
            std::cout << ']' << std::endl;
        }
        std::cout << std::endl;
    }


    void Life::simulation_loop(){
        int genCount = 1;
        while(true){
            if(matrix_is_repeated(generate_matrix_key())){
                break;
            }
            if(count_alive_cells() == 0){
                break;
            }
            if(genCount > m_maxGen){
                break;
            }
            unsigned width = static_cast<unsigned int>(m_cols);
            unsigned height = static_cast<unsigned int>(m_rows);
            Canvas image(width, height, m_blockSize);
            print_matrix(genCount);
            genCount++;
            // if(m_image){ //problema com as cores
            //     image.matrix_to_png(m_currentMatrix, m_aliveColor, m_bkgColor, m_imagePath, extractConfigPrefix());
            // }
            std::vector<std::vector<int>> newMatrix = generate_new_matrix();
            m_currentMatrix = newMatrix;
        }
    }

}