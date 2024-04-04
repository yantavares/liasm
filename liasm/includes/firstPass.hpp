#ifndef FIRST_PASS_HPP
#define FIRST_PASS_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

int firstPass(std::ifstream &file,
              std::unordered_map<std::string, int> &memory,
              std::unordered_map<std::string, int> &labels,
              std::unordered_map<int, std::string> &program);

#endif // FIRST_PASS_HPP
