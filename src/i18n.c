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

#include "i18n.h"

#include "content.h"
#include "file-util.h"

#include <errno.h>
#if ENABLE_NLS
#include "gettext.h"
#endif // ENABLE_NLS
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

static int is_chenpi11_blog_locale_dir(const char *dir)
{
    char pathbuf[PATH_MAX];

    init_struct(pathbuf);

    if (snprintf(pathbuf, PATH_MAX, "%s/zh_CN/LC_MESSAGES/" PACKAGE_NAME ".mo", dir) < 0)
    {
        fprintf(stderr, "ERROR: snprintf() failed.\n");

        return FALSE;
    }

    return is_file(pathbuf);
}

void i18n_init()
{
    const char *locale_dir = NULL;

    if (setlocale(LC_ALL, "") == NULL)
    {
        // Don't use warn(). It will call gettext().
        fprintf(stderr, "WARNING: Cannot set locale.\n");
    }

#if ENABLE_NLS
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
#endif // ENABLE_NLS

    errno = 0;
}
