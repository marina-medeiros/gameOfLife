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
#include <iostream>
#include <string> 
#include <dirent.h>
#include <iostream>
#include <dirent.h>
#include <cstdlib> 
#include <string>
#include <fstream>

#include "data.h"
#include "life.h"
#include "../lib/canvas.h"
#include "../lib/common.h"

/*!
* Checks if a directory exists.
*
* @param target The path of the directory to check.
*
* @return True if the directory exists, false otherwise.
*/

bool file_exists(const std::string &str) {
    std::ifstream fs{str};
    return fs.is_open();
}


std::string validate_input(int argc, char* argv[]){
    if(argc!=2){
        std::cout<< "Invalid number of arguments, try again" <<std::endl;
        exit(1);
    }
    if(file_exists(argv[1])){
        return argv[1];
    }else{
        std::cout<< "Directory doesn't exist, try again" <<std::endl;
        exit(1);
    }

    return "config/glife.ini";
}

void displayWelcome(int lines, int cols) {
    std::cout << "****************************************************************" << std::endl;
    std::cout << "Welcome to Conway’s game of Life." << std::endl;
    std::cout << "Running a simulation on a grid of size " << lines-2 << " by " << cols-2 << " in which" << std::endl;
    std::cout << "each cell can either be occupied by an organism or not." << std::endl;
    std::cout << "The occupied cells change from generation to generation" << std::endl;
    std::cout << "according to the number of neighboring cells which are alive." << std::endl;
    std::cout << "****************************************************************" << std::endl;
}

int main(int argc, char* argv[]) {
    Data data(validate_input(argc,argv));
    life::Life lifeManager(data);
    displayWelcome(lifeManager.get_rows(), lifeManager.get_cols());
    lifeManager.simulation_loop();
    return EXIT_SUCCESS; 
}
