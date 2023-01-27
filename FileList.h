#ifndef FILELIST_H
#define FILELIST_H

#include <map>
#include <vector>
#include <string>

#include <boost/filesystem.hpp>
#include <boost/regex.hpp>

#include "SearchParameters.h"

namespace fs = boost::filesystem;
using file_list_type = std::map<uintmax_t, std::vector<std::size_t>>;

/// <summary>
/// Class FileList - creates the first list of files to search for duplicates.
/// </summary>
/// <param name="params">A link to a class SearchParameters containing the parameters required for the search.</param>
class FileList {
public:
    explicit FileList(const SearchParameters& params);

    file_list_type get_file_list();
    std::vector<std::string> get_file_names();

private:
    void build_file_list();
    bool is_match_filename(const std::string& filename);
    bool is_excluded_dir(const fs::path& path);

    std::size_t _file_id {0};
    std::vector<std::string> _file_names;
    file_list_type _file_list;
    const SearchParameters& _params;
    std::vector<boost::regex> _regex_list;
};


#endif //FILELIST_H
