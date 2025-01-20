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
#ifndef _CONFIGURE_HPP_
#define _CONFIGURE_HPP_

#include <string>
#include <vector>

inline void replace(std::string &str, const std::string &from, const std::string &to)
{
    std::size_t pos = 0;
    while ((pos = str.find(from, pos)) != std::string::npos)
    {
        str.replace(pos, from.length(), to);
        pos += to.length();
    }
}

struct configure_t
{
    std::string key;
    std::string value;
};

using configures_t = std::vector<configure_t>;

inline std::string configure(const configures_t &configs, const std::string &src)
{
    std::string res = src;
    for (const struct configure_t &config : configs)
    {
        std::string key = "@" + config.key + "@";
        replace(res, key, config.value);
    }

    return res;
}

#endif
