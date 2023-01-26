#include "FileReader.h"

FileReader::FileReader(const std::string &filename, uintmax_t file_size, unsigned int block_size)
        : _file_size(file_size), _block_size(block_size) {
    _file.open(filename, std::ios::binary);
}

FileReader::FileReader(FileReader&& other) noexcept {
    _block_size = other._block_size;
    _file_size = other._file_size;
    _block_count = other._block_count;
    _file = std::move(other._file);
    other._block_count = 0;
    other._file_size = 0;
    other._file = std::ifstream {};
}

FileReader::~FileReader() {
    _file.close();
}

std::string FileReader::read_block() {
    if (_file.is_open()) {
        std::string str(_block_size, '\0');
        if (_block_count < _file_size / _block_size) {
            _file.read(str.data(), _block_size);
            ++_block_count;
        } else if (_block_count == _file_size / _block_size && _file_size % _block_size != 0) {
            _file.read(str.data(), _file_size % _block_size);
            ++_block_count;
        } else {
            str.clear();
        }
        return str;
    }
    return {};
}

