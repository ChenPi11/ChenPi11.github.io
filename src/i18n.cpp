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

#include "i18n.hpp"

#if HAVE_LIBINTL_H
#include <libintl.h>
#endif // HAVE_LIBINTL_H

#include <cstdio>
#include <clocale>
#include <filesystem>

namespace
{
    bool is_chenpi11_blog_locale_dir(const std::filesystem::path &path)
    {
        return std::filesystem::is_regular_file(path / "zh_CN" / "LC_MESSAGES" / PACKAGE_NAME ".mo");
    }
}

void i18n::i18n_init()
{
    if (std::setlocale(LC_ALL, "") == NULL)
    {
        // Don't use logging::warn(). It will call i18n::gettext().
        std::fprintf(stderr, "WARNING: Cannot set locale.\n");
    }

    const char* locale_dir;

    if (is_chenpi11_blog_locale_dir(".venv/share/locale"))
    {
        locale_dir = ".venv/share/locale";
    }
    else if (is_chenpi11_blog_locale_dir("/usr/local/share/locale"))
    {
        locale_dir = "/usr/local/share/locale";
    }
    else
    {
        locale_dir = "/usr/share/locale";
    }

    bindtextdomain(PACKAGE_NAME, locale_dir);
    bind_textdomain_codeset(PACKAGE_NAME, "UTF-8");
    textdomain(PACKAGE_NAME);

    errno = 0;
}

const char *i18n::gettext(const char *msg)
{
    return ::gettext(msg);
}
