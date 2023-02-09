#include <iostream>

#include "FileList.h"

FileList::FileList(const SearchParameters& params) : _params(params) {
    for (const auto& regex : _params.get_file_regex()) {
        _regex_list.emplace_back(regex);
    }
    build_file_list();
}

void FileList::build_file_list() {
    for (const auto& dir : _params.get_dirs()) {
        try {
            fs::path path(dir);
            for (fs::recursive_directory_iterator it(path, fs::directory_options::skip_permission_denied);
                 it != fs::recursive_directory_iterator(); it++) {
                if (fs::is_regular_file(it->path())) {
                    if (file_size(it->path()) >= _params.get_min_file_size() &&
                            is_match_filename(it->path().filename().string())) {
                        if (_file_list.count(file_size(it->path())) == 1) {
                            _file_list[file_size(it->path())].emplace_back(_file_id);
                        } else {
                            _file_list.emplace(file_size(it->path()), std::vector<std::size_t>{_file_id});
                        }
                        _file_names.push_back(it->path().string());
                        ++_file_id;
                    }
                } else if (fs::is_directory(it->path())) {
                    if (it.depth() >= _params.get_max_depth() || is_excluded_dir(it->path())) {
                        it.disable_recursion_pending();
                    }
                }
            }
        } catch (const std::exception& exception) {
            std::cerr << "Incorrect search directory: " << dir << std::endl;
        }
    }
}

bool FileList::is_match_filename(const std::string& filename) {
    if (_regex_list.empty()) {
        return true;
    }
    boost::smatch result;
    for (const auto& regex : _regex_list) {
        if (boost::regex_match(filename, result, regex)) {
            return true;
        }
    }
    return false;
}

bool FileList::is_excluded_dir(const fs::path& path) {
    for (const auto& ex_dir : _params.get_excluded_dirs()) {
        if (ex_dir == path.filename().string()) {
            return true;
        }
    }
    for (const auto& ex_dir_full : _params.get_excluded_dirs_full()) {
        if (fs::equivalent(path, fs::path(ex_dir_full))) {
            return true;
        }
    }
    return false;
}

file_list_type FileList::get_file_list() {
    return _file_list;
}

std::vector<std::string> FileList::get_file_names() {
    return _file_names;
}
