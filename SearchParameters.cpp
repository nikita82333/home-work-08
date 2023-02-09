#include "SearchParameters.h"

//-d <dirs> [-ex <dirs>] [-l level(=0)] [-ms min_file_size(=1byte)] [-fm <file_masks>] [-s block_size(=8bytes)]
//[-h {murmurhash2(=default), crc32, md5}]

SearchParameters::SearchParameters(int argc, char** argv) {
    std::string last_key;
    for (int i = 1; i < argc; ++i) {
        if (argv[i][0] == '-') {
            last_key = std::string(argv[i]);
        } else {
            if (last_key == "-d") {
                _dirs.emplace_back(argv[i]);
            } else if (last_key == "-ex") {
                std::string ex_dir(argv[i]);
                std::size_t pos1 = ex_dir.find('/');
                std::size_t pos2 = ex_dir.find('\\');
                if (pos1 != std::string::npos || pos2 != std::string::npos) {
                    _excluded_dirs_full.push_back(ex_dir);
                } else {
                    _excluded_dirs.push_back(ex_dir);
                }
            } else if (last_key == "-l") {
                try {
                    _max_depth = std::stoi(argv[i]);
                } catch (const std::exception& exception) {}
            } else if (last_key == "-ms") {
                try {
                    _min_file_size = std::stoi(argv[i]);
                } catch (const std::exception& exception) {}
            } else if (last_key == "-fm") {
                std::string file_mask(argv[i]);
                _file_regex.push_back(make_regex(file_mask));
            } else if (last_key == "-s") {
                try {
                    _block_size = std::stoi(argv[i]);
                } catch (const std::exception& exception) {}
            } else if (last_key == "-h") {
                std::string hash(argv[i]);
                if (hash == "crc32") {
                    _hash_algo = HashAlgo::CRC32;
                } else if (hash == "md5") {
                    _hash_algo = HashAlgo::MD5;
                }
            }
        }
    }
}

std::size_t SearchParameters::replace_all(std::string &inout, std::string_view what, std::string_view with) {
    std::size_t count{};
    for (std::string::size_type pos{};
         std::string::npos != (pos = inout.find(what.data(), pos, what.length()));
         pos += with.length(), ++count) {
        inout.replace(pos, what.length(), with.data(), with.length());
    }
    return count;
}

std::string SearchParameters::make_regex(std::string &file_mask) {
    replace_all(file_mask, ".", "\\.");
    replace_all(file_mask, "*", ".*");
    replace_all(file_mask, "?", ".{1}");
    return file_mask;
}

std::vector<std::string> SearchParameters::get_dirs() const {
    return _dirs;
}

std::vector<std::string> SearchParameters::get_excluded_dirs() const {
    return _excluded_dirs;
}

std::vector<std::string> SearchParameters::get_excluded_dirs_full() const {
    return _excluded_dirs_full;
}

int SearchParameters::get_max_depth() const {
    return _max_depth;
}

unsigned int SearchParameters::get_min_file_size() const {
    return _min_file_size;
}

std::vector<std::string> SearchParameters::get_file_regex() const {
    return _file_regex;
}

unsigned int SearchParameters::get_block_size() const {
    return _block_size;
}

HashAlgo SearchParameters::get_hash_algo() const {
    return _hash_algo;
}
