#include "databaseimpl.hpp"

namespace fakeData {
const mlb::data::ArticleHeader artHeader0{
    10,
    "AKADEMIA BASKETU 2016/2017",
    R"(Jeśli jeszcze do kogoś nie dotarliśmy z koszykarskim przesłaniem, to nasze wspaniałe trenerki od miesiąca pracują już z dziećmi w ramach AKADEMII BASKETU. Zajęć z Pauliną Gajdosz i Martą Malczewską naprawdę nie trzeba zbytn [...])",
    "2016-10-02 21:04",
    1,
    "M SZ",
    mlb::data::Picture{
        "http://miastobasketu.com/gfx/zdjeciaglowne/AKADEMIABANER800.jpg"}};
}

namespace mlb {
namespace data {

DatabaseImpl::DatabaseImpl(bool useFakeData) : _fake(useFakeData) {}

ArticleHeaders DatabaseImpl::articleHeaders() const {
    return ArticleHeaders{{fakeData::artHeader0}};
}
} // namespace data
} // namespace mlb
