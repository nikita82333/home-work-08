#ifndef SEARCHPARAMETERS_H
#define SEARCHPARAMETERS_H

#include <vector>
#include <string>

enum class HashAlgo {
    MurMurHash2,
    CRC32,
    MD5
};

class SearchParameters {
public:
    SearchParameters(int argc, char** argv);

    [[nodiscard]] std::vector<std::string> get_dirs() const;
    [[nodiscard]] std::vector<std::string> get_excluded_dirs() const;
    [[nodiscard]] std::vector<std::string> get_excluded_dirs_full() const;
    [[nodiscard]] int get_max_depth() const;
    [[nodiscard]] unsigned int get_min_file_size() const;
    [[nodiscard]] std::vector<std::string> get_file_regex() const;
    [[nodiscard]] unsigned int get_block_size() const;
    [[nodiscard]] HashAlgo get_hash_algo() const;

private:
    std::vector<std::string> _dirs;
    std::vector<std::string> _excluded_dirs;
    std::vector<std::string> _excluded_dirs_full;
    int _max_depth {0};
    unsigned int _min_file_size {1};
    std::vector<std::string> _file_regex;
    unsigned int _block_size {8};
    HashAlgo _hash_algo {HashAlgo::MurMurHash2};

    static std::size_t replace_all(std::string& inout, std::string_view what, std::string_view with);
    static std::string make_regex(std::string& file_mask);

};


#endif //SEARCHPARAMETERS_H
