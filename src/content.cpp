/**
 * @file content.cpp
 * @brief String utils implementation.
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

#include "content.hpp"

#include <string>
#include <vector>

std::vector<std::string> content::split(const std::string &str, const char delim)
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

bool content::endswith(const std::string &str, const std::string &suffix)
{
    return str.size() >= suffix.size() && str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}
