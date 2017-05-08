#ifndef H_ENGINE_CONFIGURATION
#define H_ENGINE_CONFIGURATION

#include <map>
#include <string>

namespace Engine {
  namespace Configuration {
    class CConfiguration {
      public:
        CConfiguration();
        ~CConfiguration();

        const char *options_path = "./solarhunter.conf";

        int Load(const char *path, std::map<std::string, std::string> &list);
        int Save(const char *path, std::map<std::string, std::string> &list);
        std::map<std::string, std::string> Options;
    };
  }
}

#endif
