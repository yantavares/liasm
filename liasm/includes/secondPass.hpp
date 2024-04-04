#ifndef SECOND_PASS_HPP
#define SECOND_PASS_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

int secondPass(int &ACC,
               int &PC,
               std::unordered_map<std::string, int> &memory,
               std::unordered_map<std::string, int> &labels,
               std::unordered_map<int, std::string> &program);

#endif // SECOND_PASS_HPP
