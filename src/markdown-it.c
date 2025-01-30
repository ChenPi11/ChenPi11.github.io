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

#include "markdown-it.h"

#include "content.h"
#include "defines.h"
#include "file-util.h"
#include "i18n.h"
#include "log.h"

#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

const char *markdown_it_command;

int command_exec(const char *cmd)
{
    int status = system(cmd);

    if (status == -1)
    {
        perror("system");
    }
    else if (WIFEXITED(status))
    {
        return WEXITSTATUS(status);
    }

    return RET_ERROR;
}

#define CHECKCMD(exec) exec " --version > /dev/null 2>&1"

#define CHECK_CASE(cmd)                                                                                                \
    else if (command_exec(CHECKCMD(cmd)) == 0)                                                                         \
    {                                                                                                                  \
        markdown_it_command = cmd;                                                                                     \
    }

void markdown_it_init(void)
{
    info(_("Checking for markdown-it ... "));
    if (0)
    {
    }
    CHECK_CASE("npx markdown-it")
    CHECK_CASE("markdown-it")
    CHECK_CASE(".venv/bin/markdown-it")
    CHECK_CASE("venv/bin/markdown-it")
    else
    {
        char *markdown_it_env = getenv("MARKDOWN_IT");
        if (markdown_it_env == NULL)
        {
            markdown_it_env = getenv("MARKDOWNIT");
        }
        if (markdown_it_env == NULL)
        {
            goto NOTFOUND;
        }
        markdown_it_command = markdown_it_env;
    }

    fprintf(stderr, "%s\n", markdown_it_command);

    return;

NOTFOUND:
    fprintf(stderr, _("not found\n"));
    error(_("Can't find markdown-it. Did you forget to run setup?\n"
          "You can also set the MARKDOWN_IT environment variable.\n"));
}

struct content_t markdown_it_tohtml(const char *filepath)
{
    struct content_t content = null_content;
    int ret = 0;
    char tmpfile[PATH_MAX];
    char command[PATH_MAX];

    init_struct(tmpfile);
    init_struct(command);

    if (markdown_it_command == NULL)
    {
        die(_("markdown-it is not initialized.\n"));
    }

    if (snprintf(tmpfile, PATH_MAX, "%s.tmp", get_proc_name()) < 0)
    {
        die(_("snprintf() failed.\n"));
    }
    if (snprintf(command, PATH_MAX, "%s %s > %s", markdown_it_command, filepath, tmpfile) < 0)
    {
        die(_("snprintf() failed.\n"));
    }

    info(_("Executing: %s\n"), command);
    ret = command_exec(command);
    if (ret != 0)
    {
        die(_("markdown-it failed with exit code %d.\n"), ret);
    }

    content = read_file(tmpfile);
    if (is_null_content(content))
    {
        goto ERROR;
    }

    if (remove_file(tmpfile) != RET_SUCCESS)
    {
        warn(_("Remove %s failed.\n"), tmpfile);
    }

    return content;

ERROR:
    return null_content;
}
