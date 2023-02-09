#include "HashCalculator.h"

std::uint32_t HashCalculator::crc32(const std::string& string) {
    boost::crc_32_type result;
    result.process_bytes(string.data(), string.length());
    return result.checksum();
}

std::size_t HashCalculator::murmurhash2(const std::string& string) {
    return std::hash<std::string>{}(string);
}

std::string HashCalculator::md5_string(const std::string& string) {
    boost::uuids::detail::md5 hash;
    boost::uuids::detail::md5::digest_type digest;
    hash.process_bytes(string.data(), string.size());
    hash.get_digest(digest);
    const auto char_digest = reinterpret_cast<const char*>(&digest);
    std::string result;
    boost::algorithm::hex(char_digest, char_digest + sizeof(char_digest), std::back_inserter(result));
    return result;
}

duint64_t HashCalculator::md5_duint64(const std::string& string) {
    boost::uuids::detail::md5 hash;
    boost::uuids::detail::md5::digest_type digest;
    hash.process_bytes(string.data(), string.size());
    hash.get_digest(digest);
    return { (std::uint64_t)(*(std::uint64_t*)&digest[0]),
             (std::uint64_t)(*(std::uint64_t*)&digest[2]) };
}
