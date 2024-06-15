#ifndef LIFE_H  // Correcting the include guard
#define LIFE_H

#include <set>
#include <vector>
#include <string>
#include <stdexcept>
#include <sstream>
#include <iostream>

#include "data.h"
#include "../lib/canvas.h"
#include "../lib/common.h"

namespace life {
    class Life {
        private:
            std::set<std::string> m_allMatrixes;
            std::vector<std::vector<int>> m_currentMatrix;
            //std::vector<std::vector<int>> m_newMatrix;

            int m_rows = 8;
            int m_cols = 8;
            std::vector<int> m_surviveConditions = {2, 3};
            std::vector<int> m_bornConditions = {3};
            int m_maxGen = 50;
            std::string m_cfgFile;
            std::string m_gameRules; // sets conditions
            bool m_image;
            std::string m_aliveColor;
            int m_blockSize = 10;
            std::string m_bkgColor;
            std::string m_imagePath;
            int m_fps;

        public:
            Life(const Data& data) {
                // Initialize member variables using the Data object
                const auto& config = data.get_variablesAndValues();

                if (config.find("input_cfg") != config.end()) {
                    m_cfgFile = config.at("input_cfg");
                    if(m_cfgFile.length() >=2 && m_cfgFile.front() == '"'  && m_cfgFile.back() == '"'){
                        m_cfgFile = m_cfgFile.substr(1, m_cfgFile.length() - 2);
                    }
                    read_matrix_config(m_cfgFile);
                    std::cout << m_cfgFile << std::endl;
                }
                if (config.find("generate_image") != config.end()) {
                    m_image = config.at("generate_image") == "true";
                    std::cout << m_image << std::endl;
                }
                if (config.find("max_gen") != config.end()) {
                    m_maxGen = std::stoi(config.at("max_gen"));
                    std::cout << m_maxGen << std::endl;
                }
                if (config.find("alive") != config.end()) {
                    m_aliveColor = config.at("alive");
                    std::cout << m_aliveColor << std::endl;
                }
                if (config.find("bkg") != config.end()) {
                    m_bkgColor = config.at("bkg");
                    std::cout << m_bkgColor << std::endl;
                }
                if (config.find("block_size") != config.end()) {
                    m_blockSize =  std::stoi(config.at("block_size"));
                    std::cout << m_blockSize << std::endl;
                }
                if (config.find("path") != config.end()) {
                    m_imagePath = config.at("path");
                    if(m_imagePath.length() >=2 && m_imagePath.front() == '"'  && m_imagePath.back() == '"'){
                        m_imagePath = m_imagePath.substr(1, m_imagePath.length() - 2);
                    }
                    std::cout << m_imagePath << std::endl;
                }
                if (config.find("fps") != config.end()) {
                    m_fps = std::stoi(config.at("fps"));
                    std::cout << m_fps << std::endl;
                }
                if (config.find("game_rules") != config.end()) {
                    m_gameRules = config.at("game_rules");
                    set_conditions(m_gameRules);
                    std::cout << m_gameRules << std::endl;
                    for(const auto& bornCondition : m_bornConditions){
                        std::cout << bornCondition << " ";
                    }
                    std::cout << std::endl;
                    for(const auto& surv : m_surviveConditions){
                        std::cout << surv << " ";
                    }
                    std::cout << std::endl;
                }

                m_currentMatrix.resize(m_rows, std::vector<int>(m_cols, 0));
            }

            std::set<std::string> get_m_allMatrixes(){return m_allMatrixes;}
            std::vector<std::vector<int>> get_m_currentMatrix(){return m_currentMatrix;}
            int get_rows() {return m_rows;}
            int get_cols() {return m_cols;}
            void read_matrix_config(std::string path);
            std::string extractConfigPrefix();
            void set_conditions(std::string input);
            std::vector<std::pair<int, int>> find_dead_neighbors(int x, int y);
            int count_live_neighbors(int x, int y);
            void set_borders();
            std::vector<std::vector<int>> generate_new_matrix();
            int count_alive_cells();
            std::string generate_matrix_key();
            bool matrix_is_repeated(std::string matrixKey);
            void simulation_loop();
            void print_matrix(int& genCount);
    };
}

#endif // LIFE_H