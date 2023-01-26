#ifndef DUPLICATESEARCH_H
#define DUPLICATESEARCH_H

#include <vector>
#include <string>

#include "FileList.h"
#include "FileReader.h"
#include "HashCalculator.h"

using result_type = std::vector<std::vector<std::string>>;
using hash_type = std::pair<std::uint64_t, std::uint64_t>;

class DuplicateSearch {
public:
    explicit DuplicateSearch(int argc, char** argv);

    result_type search();

private:
    template<typename T>
    void recursive_search(T& files);
    hash_type get_hash(const std::string& string);

    std::map<std::size_t, FileReader> _readers;
    hash_type _empty_hash;
    result_type _duplicates;
    HashAlgo _hash_algo;
    unsigned int _block_size;
    file_list_type _file_list;
    std::vector<std::string> _file_names;

};

template<typename T>
void DuplicateSearch::recursive_search(T& files) {
    using next_file_list_type = std::map<hash_type, std::vector<std::size_t>>;
    next_file_list_type next_list;
    for (const auto& file_id : files) {
        hash_type hash = get_hash(_readers[file_id].read_block());
        if (next_list.count(hash) == 1) {
            next_list[hash].push_back(file_id);
        } else {
            next_list.emplace(hash, std::vector<std::size_t>{file_id});
        }
    }
    if constexpr (!std::is_const_v<T>) {
        files.clear();//free memory
    }
    for (auto& [hash, next_files] : next_list) {
        if (next_files.size() > 1) {
            if (hash != _empty_hash) {
                recursive_search(next_files);
            } else {
                _duplicates.emplace_back();
                for (const auto& file_id : next_files) {
                    _duplicates.back().push_back(_file_names[file_id]);
                }
            }
        } else {
            _readers.erase(next_files[0]);//close file
        }
    }
}


#endif //DUPLICATESEARCH_H
