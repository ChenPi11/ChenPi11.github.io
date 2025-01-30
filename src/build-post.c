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

#include "config.h"

#include "file-util.h"
#include "i18n.h"
#include "log.h"
#include "markdown-it.h"
#include "post.h"

#include <stdlib.h>

static void show_help()
{
    printf("%s", _("Usage: build-post [-h|--help] [-V|--version] [-v|--verbose] <template file> <source file>\n"));
    printf("\n");
    printf("%s", _("Options:\n"));
    printf("%s", _("  -h, --help     Display this help and exit.\n"));
    printf("%s", _("  -V, --version  Output version information and exit.\n"));
    printf("%s", _("  -v, --verbose  Verbosely report processing.\n"));
}

int main(int argc, char *argv[])
{
    int verbose = 0;
    const char *template_file = NULL;
    const char *source_file = NULL;
    struct post_t post = null_post;

    log_init(argc, argv);
    i18n_init();

    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0)
        {
            show_help();

            return EXIT_SUCCESS;
        }
        if (strcmp(argv[i], "-V") == 0 || strcmp(argv[i], "--version") == 0)
        {
            printf("build-post " PACKAGE_VERSION "\n");
            printf("%s", _("Copyright (C) 2025 ChenPi11\n"));
            printf("%s", _("License GPLv3+: GNU GPL version 3 or later <https://gnu.org/licenses/gpl.html>\n"));
            printf("%s", _("This is free software: you are free to change and redistribute it.\n"));
            printf("%s", _("There is NO WARRANTY, to the extent permitted by law.\n"));
            printf("%s", _("Written by ChenPi11.\n"));

            return EXIT_SUCCESS;
        }
        else if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--verbose") == 0)
        {
            verbose = 1;
            continue;
        }
        if (template_file == NULL)
        {
            template_file = argv[i];
        }
        else
        {
            source_file = argv[i];
        }
    }

    set_log_level(verbose ? LOG_INFO : LOG_WARN);

    if (template_file == NULL || source_file == NULL)
    {
        show_help();

        return EXIT_FAILURE;
    }

    if (!is_chenpi11_blog_rootdir())
    {
        die(_("You must run %s in project's root directory!\n"), "build-post");
    }

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
