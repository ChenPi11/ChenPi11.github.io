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

#include "post.hpp"

#include "configure.hpp"
#include "content.hpp"
#include "file-util.hpp"
#include "i18n.hpp"

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

namespace
{

const std::filesystem::path POST_DIR = std::filesystem::path(POST_DIR_NAME);
const std::filesystem::path POST_TEMPLATE = std::filesystem::path(POST_TEMPLATE_NAME);
const std::filesystem::path TAG_TEMPLATE = std::filesystem::path(TAG_TEMPLATE_NAME);

} // namespace

post::PostInfo::PostInfo(const std::filesystem::path &metafile)
{
    if (!std::filesystem::is_regular_file(metafile))
    {
        throw std::runtime_error(_("No such file: ") + metafile.string());
    }
    m_filename = metafile.stem().string();
    std::ifstream infile(metafile);
    std::string line;
    if (std::getline(infile, line).fail())
    {
        throw std::runtime_error(_("Read file failed: ") + metafile.string());
    }
    m_title = line;
    if (std::getline(infile, line).fail())
    {
        throw std::runtime_error(_("Read file failed: ") + metafile.string());
    }
    m_date = line;
    if (std::getline(infile, line).fail())
    {
        throw std::runtime_error(_("Read file failed: ") + metafile.string());
    }
    m_tags = content::split(line, ',');
    if (std::getline(infile, line).fail())
    {
        throw std::runtime_error(_("Read file failed: ") + metafile.string());
    }
    m_description = line;

    infile.close();
}

std::string post::PostInfo::generate_tags() const
{
    std::string res;
    std::string template_data = file::readfile(TAG_TEMPLATE);
    for (auto &tag : m_tags)
    {
        configure::configures_t configs = {{"NAME", tag}};
        res += configure::configure(configs, template_data) + "\n";
    }
    return res;
}

std::string post::PostInfo::generate() const
{
    std::string template_data = file::readfile(POST_TEMPLATE);
    configure::configures_t configs = {
        {"FILENAME", m_filename},       {"TITLE", m_title},        {"DATE", m_date},
        {"DESCRIPTION", m_description}, {"TAGS", generate_tags()},
    };
    return configure::configure(configs, template_data);
}

std::vector<post::PostInfo> post::load_posts()
{
    std::vector<post::PostInfo> res;

    std::filesystem::path postdir = POST_DIR;
    if (!std::filesystem::is_directory(postdir))
    {
        throw std::runtime_error("No such directory: " + postdir.string());
    }

    for (const auto &entry : std::filesystem::directory_iterator(postdir))
    {
        std::string filename = entry.path().string();
        if (content::endswith(filename, ".info"))
        {
            res.emplace_back(filename);
        }
    }

    return res;
}
