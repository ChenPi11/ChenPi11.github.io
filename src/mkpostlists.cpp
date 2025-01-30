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

#include "config.hpp"

#include "file-util.hpp"
#include "i18n.hpp"
#include "log.hpp"
#include "post.hpp"

#include <cstdlib>
#include <iostream>
#include <string>

namespace
{
void show_help()
{
    std::printf("%s", _("Usage: mkpostlists [-h|--help] [-V|--version] [-v|--verbose]\n"));
    std::printf("\n");
    std::printf("%s", _("Options:\n"));
    std::printf("%s", _("  -h, --help     Display this help and exit.\n"));
    std::printf("%s", _("  -V, --version  Output version information and exit.\n"));
    std::printf("%s", _("  -v, --verbose  Verbosely report processing.\n"));
}
} // namespace

int main(int argc, char *argv[])
{
    logging::init(argc, argv);
    logging::set_level(logging::LogLevel::WARN);
    i18n::i18n_init();

    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];
        if (arg == "-h" || arg == "--help")
        {
            show_help();

            return EXIT_SUCCESS;
        }
        else if (arg == "-V" || arg == "--version")
        {
            std::printf("mkpostlists " PACKAGE_VERSION "\n");
            std::printf("%s", _("Copyright (C) 2025 ChenPi11\n"));
            std::printf("%s", _("License GPLv3+: GNU GPL version 3 or later <https://gnu.org/licenses/gpl.html>\n"));
            std::printf("%s", _("This is free software: you are free to change and redistribute it.\n"));
            std::printf("%s", _("There is NO WARRANTY, to the extent permitted by law.\n"));
            std::printf("%s", _("Written by ChenPi11.\n"));

            return EXIT_SUCCESS;
        }
        else if (arg == "-v" || arg == "--verbose")
        {
            logging::set_level(logging::LogLevel::INFO);
        }
        else
        {
            show_help();

            return EXIT_FAILURE;
        }
    }

    if (!file::is_chenpi11_blog_rootdir())
    {
        logging::error(_("You must run %s in project's root directory!\n"), "mkpostlists");

        return EXIT_FAILURE;
    }

    try
    {
        logging::info(_("Generate post lists ...\n"));

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
        logging::error(_("Errno %d: %s\n"), e.code().value(), e.what());
    }
    catch (const std::runtime_error &e)
    {
        logging::error("%s\n", e.what());
    }
}
