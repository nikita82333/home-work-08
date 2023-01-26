#ifndef HASHCALCULATOR_H
#define HASHCALCULATOR_H

#include <string>

#include <boost/crc.hpp>
#include <boost/uuid/detail/md5.hpp>
#include <boost/algorithm/hex.hpp>

#define BOOST_UUID_COMPAT_PRE_1_71_MD5

using duint64_t = std::pair<std::uint64_t, std::uint64_t>;

class HashCalculator {
public:
    HashCalculator() = default;

    static std::uint32_t crc32(const std::string& string);
    static std::size_t murmurhash2(const std::string& string);
    static std::string md5_string(const std::string& string);
    static duint64_t md5_duint64(const std::string& string);

};


#endif //HASHCALCULATOR_H
