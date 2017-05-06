#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

#include "config.hpp"

Engine::Configuration::CConfiguration::CConfiguration() {
  std::ifstream is("./solarhunter.conf");

  std::string line, del = "=";
  size_t idx;
  while (getline(is, line)) {
    idx = line.find(del);
    this -> Options[line.substr(0, idx)] = line.substr(idx + 1, line.size());
  }
  is.close();
}

Engine::Configuration::CConfiguration::~CConfiguration() {
}
