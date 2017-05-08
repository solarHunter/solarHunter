#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

#include "config.hpp"

Engine::Configuration::CConfiguration::CConfiguration() {
  this -> Load(this -> options_path, this -> Options);
}

int Engine::Configuration::CConfiguration::Load(const char *path, std::map<std::string, std::string> &list) {
  std::ifstream is(path);
  if (!is) return 1;

  std::string line, del = "=";
  size_t idx;
  while (getline(is, line)) {
    idx = line.find(del);
    list[line.substr(0, idx)] = line.substr(idx + 1, line.size());
  }
  is.close();
  return 0;
}

int Engine::Configuration::CConfiguration::Save(const char *path, std::map<std::string, std::string> &list) {
  std::ofstream os(path);
  if (!os) return 1;

  for(std::map<std::string, std::string>::iterator iter = list.begin(); iter != list.end(); ++iter) {
    os << iter -> first << "=" << iter -> second << std::endl;
  }
  os.close();
  return 0;
}

Engine::Configuration::CConfiguration::~CConfiguration() {
}
