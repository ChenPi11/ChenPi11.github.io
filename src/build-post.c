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

#include "file-util.h"
#include "i18n.h"
#include "log.h"
#include "markdown-it.h"
#include "post.h"

#include <stdlib.h>

int main(int argc, char *argv[])
{
    const char *template_file = NULL;
    const char *source_file = NULL;
    struct post_t post = null_post;

    log_init(argc, argv);
    i18n_init();

    if (argc != 3)
    {
        die(_("Usage: %s <template file> <source file>\n"), argv[0]);
    }

    if (!is_chenpi11_blog_rootdir())
    {
        die(_("You must run %s in project's root directory!\n"), argv[0]);
    }

    template_file = argv[1];
    source_file = argv[2];

    markdown_it_init();
    post_init(template_file);

    post = load_post(source_file);
    if (is_null_post(post))
    {
        die(_("Cannot load post: %s\n"), source_file);
    }

    if (save_post(post) != RET_SUCCESS)
    {
        die(_("Cannot save post: %s\n"), source_file);
    }

    free_post(&post);

    return EXIT_SUCCESS;

ERROR:
    free_post(&post);
    return EXIT_FAILURE;
}
