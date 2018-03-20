#ifndef VERSION_HPP_CMAKE
#define VERSION_HPP_CMAKE

#define PROJECT_VERSION "@PROJECT_VERSION@"
#define PROJECT_VERSION_MAJOR "@PROJECT_VERSION_MAJOR@"
#define PROJECT_VERSION_MINOR "@PROJECT_VERSION_MINOR@"
#define PROJECT_VERSION_PATCH "@PROJECT_VERSION_PATCH@"

#include <string>

namespace mlb {
namespace server {

struct Version {
const std::string version = PROJECT_VERSION;
const std::string major = PROJECT_VERSION_MAJOR;
const std::string minor = PROJECT_VERSION_MINOR;
const std::string release = PROJECT_VERSION_PATCH;
}; 
} // namespace server
} // namespace mlb

#endif
