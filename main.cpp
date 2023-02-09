#include <iostream>

#include "DuplicateSearch.h"

int _CRT_glob = 0;//to ignore '*' in command line

int main(int argc, char** argv) {

    if (argc < 3) {
        std::cout << "Using: bayan -d <dirs> [-ex <dirs>] [-l level] [-ms min_file_size]" << std::endl
                    << "             [-fm <file_masks>] [-s block_size] [-h hash_algorithm]" << std::endl
                    << "  -d  <dirs>         - list of directories to search" << std::endl
                    << "  -ex <dirs>         - list of directories excluded from the search" << std::endl
                    << "  -l  level          - depth level (0 - only current directory (default))" << std::endl
                    << "  -ms min_file_size  - minimum file size in bytes (1 byte - default value)" << std::endl
                    << "  -fm <file_masks>   - list of file masks to search" << std::endl
                    << "  -s  block_size     - size of the block used to read files in bytes (8 bytes - default value)"
                    << std::endl
                    << "  -h  hash_algorithm - hashing algorithm: murmurhash2 (default), crc32, md5" << std::endl;
        return -1;
    }

    DuplicateSearch engine(argc, argv);

    for (const auto& file_group : engine.search()) {
        for (const auto& file : file_group) {
            std::cout << file << std::endl;
        }
        std::cout << std::endl;
    }

    return 0;
}

