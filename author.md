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
| Lê nome do jogador                                                                        |      5       |       5        |
| Exibe e gerencia menu de opções                                                           |      10      |       10       |
| Exibe e gerencia escolha de categoria das palavras                                        |      10      |       10       |
| Exibe regras do jogo quando solicitado                                                    |      5       |       5        |
| Exibe tabela de pontuação                                                                 |      5       |       5        |
| Contabiliza e acumula os pontos de várias partidas                                        |      10      |       10       |
| Escolhe uma palavra aletória (sem repetir) a partir das lista de palavras lida do arquivo |      10      |       10       |
| Controla o número de erros para um jogador perder uma partida                             |      5       |       5        |
| Exibe partes do boneco na forca conforme os erros se acumulam                             |      5       |       5        |
| Exibe os erros/acertos da palavra secreta em uma partida                                  |      10      |       10       |
| Exibe palavra secreta completa, quando uma partida é perdida                              |      5       |       5        |
| Exibe a lista de chutes errados                                                           |      5       |       5        |
| Permite o cancelamento de uma partida em andamento                                        |      5       |       5        |
| Apresenta as telas no formato organizacional sugerido                                     |      5       |       5        |
| Projeto contém pelo menos 2 classes                                                       |      5       |       5        |
| Programa gerencia erros corretamente                                                      |      5       |       5        |
| Lê palavras e categorias do arquivo de palavras `words.csv`                               |      10      |       10       |
| Lê informações do pontuação `score.hgm`                                                   |      10      |       10       |
| Funcionamento geral correto do program                                                    |      10      |       10       |

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
