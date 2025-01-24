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

#include "log.hpp"
#include "post.hpp"

#include <cstdlib>
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
    logging::init(argc, argv);

    try
    {
        logging::info("Generate post lists ...\n");

        std::string all_posts;

        for (const auto &post : post::load_posts())
        {
            all_posts += post.generate() + "\n";
        }

        std::cout << all_posts << std::endl;

        return EXIT_SUCCESS;
    }
    catch (const std::system_error &e)
    {
        logging::error("Errno %d: %s\n", e.code().value(), e.what());
    }
    catch (const std::runtime_error &e)
    {
        logging::error("%s\n", e.what());
    }
}
