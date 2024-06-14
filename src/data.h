#ifndef _DATA_H_
#define _DATA_H_

#include <array>
#include <set>
#include <string> // std::string
#include <unordered_map>
#include <map>


class Data{
private:
    std::unordered_map<std::string, std::string> variablesAndValues;
    // std::string cfgFile;
    // std::string gameRules;
    // bool image;
    // int maxGen;
    // std::string aliveColor;
    // std::string bkgColor;
    // std::string imagePath;
    // int fps;
public:
    Data() = default;
    void read_ini(std::string iniFile);
};

#endif