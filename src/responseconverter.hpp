#ifndef RESPONSECONVERTER_HPP_I8L9MGF3
#define RESPONSECONVERTER_HPP_I8L9MGF3

#include <string>

#include "database_types.hpp"

namespace mlb {
namespace data {
struct ResponseConverter {
    std::string serialize(const Players& players);
};
}  // namespace data
}  // namespace mlb

#endif /* end of include guard: RESPONSECONVERTER_HPP_I8L9MGF3 */
