# Introduction

The Conway's Game of Life program is a C++ implementation of the classic cellular automaton devised by mathematician John Conway. In this program, players can simulate the evolution of cells on a grid, where each cell can either be alive or dead based on a set of simple rules. This implementation includes features such as customizable grid size, initial configuration of live cells, and the ability to specify the rules for cell birth and survival. Additionally, the program can generate PNG images of the grid at each generation, allowing users to visualize the evolution of the cells. The code is organized into classes that manage the grid, handle the simulation logic, and facilitate the creation of image files. 

# Author(s)

- Nome: Bianca Maciel Medeiros e Marina Medeiros Araujo Leite
- Email: *<bianca.medeiros.701@ufrn.edu.br e marinamaleite@gmail.com>*
- Turma: DIM0176

# Grading

Preencha os itens que você implementou, indicando qual a nota esperada para cada item.

| Item                                                                                      | Valor máximo | Valor esperado |
| ----------------------------------------------------------------------------------------- | :----------: | :------------: |
| Coleta corretamente os parâmetro via arquivo de configuração INI                          |      10      |       10       |
| Lê uma configuração a partir de um arquivo ascii e inicializa um objeto Life              |      5       |       5        |
| Exibe corretamente uma configuração na saída padrão                                       |      10      |       10       |
| Exibe corretamente uma configuração na imagem gravada                                     |      10      |       10       |
| Aplica corretamente as regras de evolução descritas na Seção 1                            |      10      |       10       |
| Executa corretamente a evolução da configuração                                           |      10      |       10       |
| Detecta corretamente estabilidade da simulação, com a indicação da frequência             |      15      |       15       |
| Detecta corretamente extinção da simulação                                                |      5       |       5        |
| Gera corretamente os arquivos de imagens                                                  |      10      |       10       |
| Permite o cancelamento de uma partida em andamento                                        |      5       |       5        |
| Programa apresenta pelo menos uma classe                                                  |      5       |       5        |
| Trata corretamente erros de entrada do usuário                                            |      10      |       10       |

# Compiling and Runnig

To compile and run the game, follow these steps:

1. Ensure you have CMake installed on your system.
2. Clone the repository to your local machine.
3. Navigate to the project directory in your terminal.
4. Go into the source file: `cd source`
4. Create a build directory: `mkdir build && cd build`.
5. Generate the build files with CMake: `cmake ..`.
6. Compile the project: `cmake --build .`.
7. Run the compiled executable: `./glife`. followed by the path of the config file (e.g. './glife ../config/glife.ini').
