/**
 * @file file-util.cpp
 * @brief File utils implementation.
 * @author ChenPi11
 * @copyright Copyright (C) 2025 ChenPi11
 */
/*
 * Copyright (C) 2025 ChenPi11
 * This file is part of the chenpi11-blog.
 *
 * chenpi11-blog is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published
 * by the Free Software Foundation, either version 3 of the License,
 * or (at your option) any later version.
 *
 * chenpi11-blog is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with chenpi11-blog.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "file-util.hpp"

#include "i18n.hpp"
#include "log.hpp"

#include <filesystem>
#include <fstream>
#include <string>
#include <system_error>

std::string file::readfile(const std::filesystem::path &filepath)
{
    std::ifstream file(filepath);
    if (!file)
    {
        std::string filepath_str = filepath.string();
        logging::error(_("Cannot open file: %s\n"), filepath_str.c_str());
        throw std::system_error(errno, std::generic_category());
    }

    std::size_t size = std::filesystem::file_size(filepath);
    std::string data(size, '\0');
    file.read(data.data(), size);
    file.close();

    return data;
}

void file::writefile(const std::filesystem::path &filepath, const std::string &data)
{
    std::ofstream file(filepath);
    if (!file)
    {
        std::string filepath_str = filepath.string();
        logging::error(_("Cannot open file: %s\n"), filepath_str.c_str());
        throw std::system_error(errno, std::generic_category());
    }
    file << data;
    file.close();
}
