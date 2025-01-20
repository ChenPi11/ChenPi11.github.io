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

#include <log.h>
#include <markdown-it.h>
#include <post.h>

#include <sys/stat.h>

static int directory_exists(const char *path)
{
    struct stat info;

    if (stat(path, &info) != 0)
    {
        return 0;
    }
    else if (info.st_mode & S_IFDIR)
    {
        return 1;
    }
    return 0;
}

int main(int argc, char *argv[])
{
    log_init(argc, argv);
    if (argc != 3)
    {
        die("Usage: %s <template file> <source file>\n", argv[0]);
    }

    if (!directory_exists(POST_OUTPUT_DIR))
    {
        die("You must run %s in project's root directory!\n", argv[0]);
    }

    const char *template_file = argv[1];
    const char *source_file = argv[2];

    markdown_it_init();
    post_init(template_file);

    struct post_t p = load_post(source_file);
    save_post(p);
}
