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

#pragma once
#ifndef _POST_INFO_HPP_
#define _POST_INFO_HPP_

#include "configure.hpp"
#include "log.h"

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

#include <iostream>

#define POST_DIR_NAME "posts"
#define POST_TEMPLATE_NAME "post-template.html.in"
#define TAG_TEMPLATE_NAME "tag-template.html.in"

inline const std::filesystem::path POST_DIR = std::filesystem::path(POST_DIR_NAME);
inline const std::filesystem::path POST_TEMPLATE = std::filesystem::path(POST_TEMPLATE_NAME);
inline const std::filesystem::path TAG_TEMPLATE = std::filesystem::path(TAG_TEMPLATE_NAME);

inline std::string readfile(const std::filesystem::path &filepath)
{
    std::ifstream file(filepath);
    if (!file)
    {
        ::die("Cannot open file: %s", filepath.c_str());
    }
    std::size_t size = std::filesystem::file_size(filepath);
    std::string data(size, '\0');
    file.read(data.data(), size);
    file.close();
    return data;
}

inline void writefile(const std::filesystem::path &filepath, const std::string &data)
{
    std::ofstream file(filepath);
    if (!file)
    {
        ::die("Cannot open file: %s", filepath.c_str());
    }
    file << data;
    file.close();
}

inline bool endswith(const std::string &str, const std::string &suffix)
{
    return str.size() >= suffix.size() && str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

inline std::vector<std::string> split(const std::string &str, const char delim)
{
    std::vector<std::string> res;
    std::size_t start = 0;
    std::size_t end = 0;
    while ((end = str.find(delim, start)) != std::string::npos)
    {
        res.push_back(str.substr(start, end - start));
        start = end + 1;
    }
    res.push_back(str.substr(start));
    return res;
}

class PostInfo
{
  private:
    std::string m_title;
    std::string m_date;
    std::string m_filename;
    std::vector<std::string> m_tags;

  public:
    PostInfo() = delete;

    PostInfo(const std::filesystem::path &metafile)
    {
        if (!std::filesystem::is_regular_file(metafile))
        {
            ::die("No such file: %s", metafile.c_str());
        }
        m_filename = metafile.stem().string() + ".html";
        std::ifstream infile(metafile);
        std::string line;
        // title
        // date
        // tags
        std::getline(infile, line);
        m_title = line;
        std::getline(infile, line);
        m_date = line;
        std::getline(infile, line);
        infile.close();
        m_tags = split(line, ',');
    }

    std::string get_title() const
    {
        return m_title;
    }

    std::string get_date() const
    {
        return m_date;
    }

    std::vector<std::string> get_tags() const
    {
        return m_tags;
    }

    std::string generate_tags() const
    {
        std::string res;
        std::string template_data = readfile(TAG_TEMPLATE);
        for (auto &tag : m_tags)
        {
            configures_t configs = {{"NAME", tag}};
            res += configure(configs, template_data) + "\n";
        }
        return res;
    }

    std::string generate() const
    {
        std::string template_data = readfile(POST_TEMPLATE);
        configures_t configs = {
            {"FILENAME", m_filename},  {"TITLE", m_title}, {"DATE", m_date}, {"DESCRIPTION", "TODO"}, // TODO
            {"TAGS", generate_tags()},
        };
        return configure(configs, template_data);
    }
};

inline std::vector<PostInfo> load_posts()
{
    std::vector<PostInfo> res;

    std::filesystem::path postdir = POST_DIR;
    if (!std::filesystem::is_directory(postdir))
    {
        ::die("No such directory: %s", postdir.c_str());
    }

    for (const auto &entry : std::filesystem::directory_iterator(postdir))
    {
        std::string filename = entry.path().string();
        if (endswith(filename, ".info"))
        {
            res.emplace_back(filename);
        }
    }

    return res;
}

#endif
