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

#include <markdown-it.h>

#include <content.h>
#include <log.h>

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

    return -1;
}

#define CHECKCMD(exec) exec " --version > /dev/null 2>&1"

void markdown_it_init(void)
{
    info("Checking for markdown-it ... ");
    if (command_exec(CHECKCMD("npx markdown-it")) == 0)
    {
        markdown_it_command = "npx markdown-it";
    }
    else if (command_exec(CHECKCMD("markdown-it")) == 0)
    {
        markdown_it_command = "markdown-it";
    }
    else if (command_exec(CHECKCMD(".venv/bin/markdown-it")) == 0)
    {
        markdown_it_command = ".venv/bin/markdown-it";
    }
    else if (command_exec(CHECKCMD("venv/bin/markdown-it")) == 0)
    {
        markdown_it_command = "venv/bin/markdown-it";
    }
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
    info("%s\n", markdown_it_command);
    return;

NOTFOUND:
    info("not found\n");
    die("Can't find markdown-it. Did you forget to run setup?\n"
        "You can also set the MARKDOWN_IT environment variable.\n");
}

struct content_t markdown_it_tohtml(const char *filepath)
{
    struct content_t content;
    int ret;
    char tmpfile[256];
    char command[BUFSIZ];

    if (markdown_it_command == NULL)
    {
        die("markdown-it is not initialized.\n");
    }

    memset(tmpfile, 0, 256);
    memset(command, 0, BUFSIZ);

    snprintf(tmpfile, 256, "%s.tmp", get_proc_name());
    snprintf(command, BUFSIZ, "%s %s > %s", markdown_it_command, filepath, tmpfile);

    info("Executing: %s\n", command);
    ret = command_exec(command);
    if (ret != 0)
    {
        die("markdown-it failed with exit code %d\n", ret);
    }

    content = read_file(tmpfile);
    if (unlink(tmpfile) != 0)
    {
        warn("unlink %s failed\n", tmpfile);
    }

    return content;
}
