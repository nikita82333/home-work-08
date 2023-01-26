#ifndef FILEREADER_H
#define FILEREADER_H

#include <string>
#include <fstream>

class FileReader {
public:
    FileReader(const std::string& filename, uintmax_t file_size, unsigned int block_size);
    FileReader(FileReader&& reader) noexcept;
    FileReader() = default;
    ~FileReader();
    std::string read_block();

private:
    std::ifstream _file;
    uintmax_t _file_size {};
    unsigned int _block_size {};
    unsigned int _block_count {0};

};


#endif //FILEREADER_H
