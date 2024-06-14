/**
 * @file life_game.cpp
 *
 * @description
 * This program simulates the Conway's Game of Life.
 * It reads a initial game configuration from a input file and
 * keeps updating it, if the user so whishes.
 *
 * @author	Selan R dos Santos, <selan.rds@gmail.com>
 * @date	2015, updated 2015-04-03, updated 2024-05-31
 *
 * @remark On 2015-09-19 changed the way stability is verified.
 * In the previous version we just looked back one configuration and compare it
 * with the current configuration.
 * Now, the stability may span more than one configuration. Because of that we
 * need to keep track of all configurations and check whether the current
 * configuration has already been generated.
 * If this is the case, the game has reached stability and must stop.
 */

#include <cstdlib>  // EXIT_SUCCESS

int main(int argc, char* argv[]) {
    
    /*
    valida os args
    lê o arquivão
        passar informações pras classes life e canvas
    cria um objeto da classe Life
    chama as funções:
        void read_matrix_config(std::string path); // set rows e cols
        void set_conditions(std::string input); // set conditions e genCount
    simulation loop 
    !!!adicionar parte do canvas ao simulation loop
    
    */
    return EXIT_SUCCESS; 
}
