#include "DuplicateSearch.h"

DuplicateSearch::DuplicateSearch(int argc, char** argv) {
    SearchParameters params(argc, argv);
    _hash_algo = params.get_hash_algo();
    _block_size = params.get_block_size();
    FileList file_list(params);
    _file_list = file_list.get_file_list();
    _file_names = file_list.get_file_names();
    _empty_hash = get_hash("");
}

result_type DuplicateSearch::search() {
    for (auto& [file_size, files] : _file_list) {
        if (files.size() > 1) {
            for (const auto& file_id : files) {
                FileReader reader(_file_names[file_id], file_size, _block_size);
                _readers.emplace(file_id, std::move(reader));
            }
            recursive_search(files);
        }
    }
    return _duplicates;
}

hash_type DuplicateSearch::get_hash(const std::string& string) {
    hash_type hash {};
    switch (_hash_algo) {
        case HashAlgo::MurMurHash2:
            hash.first = HashCalculator::murmurhash2(string);
            break;
        case HashAlgo::CRC32:
            hash.first = HashCalculator::crc32(string);
            break;
        case HashAlgo::MD5:
            hash = HashCalculator::md5_duint64(string);
            break;
    }
    return hash;
}

