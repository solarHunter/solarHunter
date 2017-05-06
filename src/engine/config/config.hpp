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
        std::map<std::string, std::string> Options;
    };
  }
}

#endif
