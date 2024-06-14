#ifndef LIFE_H  // Correcting the include guard
#define LIFE_H

#include <set>
#include <vector>
#include <string>

namespace life {
    class Life {
        private:
            std::set<std::string> m_allMatrixes;
            std::vector<std::vector<int>> m_currentMatrix = {
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0},
                {0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0},
                {0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
            };
            //std::vector<std::vector<int>> m_newMatrix;

            int m_rows = 8;
            int m_cols = 8;
            std::vector<int> m_surviveConditions = {2, 3};
            std::vector<int> m_bornConditions = {3};
            int m_maxGen = 50; 

        public:
            std::set<std::string> get_m_allMatrixes(){return m_allMatrixes;}
            std::vector<std::vector<int>> get_m_currentMatrix(){return m_currentMatrix;}
            //std::vector<std::vector<int>> get_m_newMatrix(){return m_newMatrix;}

            void read_matrix_config(std::string path);
            void set_conditions(std::string input);
            std::vector<std::pair<int, int>> find_dead_neighbors(int x, int y);
            int count_live_neighbors(int x, int y);
            void set_borders();
            std::vector<std::vector<int>> generate_new_matrix();
            int count_alive_cells();
            std::string generate_matrix_key();
            bool matrix_is_repeated(std::string matrixKey);
            void simulation_loop();
            void print_matrix();
    };
}

#endif // LIFE_H