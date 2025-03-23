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

#include "post.h"

#include "configure.h"
#include "content.h"
#include "defines.h"
#include "file-util.h"
#include "i18n.h"
#include "log.h"
#include "markdown-it.h"
#include "process.h"

#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static const char *post_template_file = NULL;

struct tags_node_t
{
    struct content_t tag;
    struct tags_node_t *next;
};

static struct tags_t parse_tags(const struct content_t line)
{
    struct tags_t result = null_tags;
    char *token = NULL;
    struct tags_node_t *pnode_start = NULL;
    struct tags_node_t *pnode = NULL;
    struct content_t tmp_line = null_content;
    size_t num = 0;

    pnode_start = pnode = (struct tags_node_t *)alloca(sizeof(struct tags_node_t));
    if (pnode == NULL)
    {
        die(_("Cannot allocate memory.\n"));
    }
    pnode->next = NULL;

    tmp_line = copy_content(line);
    if (is_null_content(tmp_line))
    {
        return null_tags;
    }

    token = strtok(tmp_line.content, TAGS_SEP);
    while (token != NULL)
    {
        pnode->tag = alloca_content(strlen(token) + 1);
        if (is_null_content(pnode->tag))
        {
            return null_tags;
        }
        memcpy(pnode->tag.content, token, pnode->tag.len);
        pnode->tag.content[strlen(token)] = '\0';
        pnode->next = (struct tags_node_t *)alloca(sizeof(struct tags_node_t));
        if (pnode->next == NULL)
        {
            die(_("Cannot allocate memory.\n"));
        }
        pnode->next->next = NULL;

        pnode = pnode->next;
        token = strtok(NULL, TAGS_SEP);
        num++;
    }

    struct content_t *resbuf = (struct content_t *)malloc(sizeof(struct content_t) * num);
    if (resbuf == NULL)
    {
        die(_("Cannot allocate memory.\n"));
    }

    memset(resbuf, 0, sizeof(struct content_t) * num);

    size_t i = 0;
    for (pnode = pnode_start; pnode->next != NULL; pnode = pnode->next, i++)
    {
        resbuf[i] = copy_content(pnode->tag);
    }

    result.first = resbuf;
    result.num = num;

ERROR:
    free_content(&tmp_line);

    return result;
}

static int check_duplicate_tags(struct tags_t tags)
{
    for (size_t i = 0; i < tags.num; i++)
    {
        for (size_t j = i + 1; j < tags.num; j++)
        {
            if (strcmp(tags.first[i].content, tags.first[j].content) == 0)
            {
                die(_("Duplicate tag: \"%s\".\n"), tags.first[i].content);
            }
        }
    }

    return FALSE;

ERROR:
    return TRUE;
}

void post_init(const char *template_file)
{
    if (template_file == NULL)
    {
        die(_("Post template file is NULL.\n"));
    }
    info(_("Using %s as post template.\n"), template_file);
    post_template_file = template_file;

    return;

ERROR:
    exit(EXIT_FAILURE);
}

struct post_t load_post(const char *filepath)
{
    struct post_t post = null_post;
    const char *basename = NULL;
    char *dot_pos = NULL;
    FILE *file = NULL;
    struct content_t line = null_content;

    /* Filename. */
    basename = file_basename(filepath);
    post.filename = alloc_content(strlen(basename));
    if (is_null_content(post.filename))
    {
        return null_post;
    }
    memcpy(post.filename.content, basename, post.filename.len);
    post.filename.content[post.filename.len] = '\0';

    dot_pos = strchr(post.filename.content, '.');
    if (dot_pos != NULL)
    {
        *dot_pos = '\0';
    }

    file = fopen(filepath, "r");
    if (file == NULL)
    {
        die(_("Cannot open file: %s\n"), filepath);
    }

    /* Title. */
    line = read_line(file, filepath);
    if (!startswith(line, CONTENT(TITLE_START)))
    {
        warn(_("First line must start with \"%s\".\n"), TITLE_START);
        die(_("First line of %s is not a title.\n"), filepath);
    }
    if (!endswith(line, CONTENT(TITLE_END)))
    {
        warn(_("First line must end with \"%s\".\n"), TITLE_END);
        die(_("First line of %s is not a title.\n"), filepath);
    }
    if (line.len <= strlen(TITLE_START) + strlen(TITLE_END))
    {
        fclose(file);
        free_content(&line);
        free_post(&post);
        warn(_("First line must contain a title.\n"));
        die(_("First line of %s is not a title.\n"), filepath);
    }
    post.title = alloc_content(line.len - strlen(TITLE_START) - strlen(TITLE_END));
    if (is_null_content(post.title))
    {
        goto ERROR;
    }
    memcpy(post.title.content, line.content + strlen(TITLE_START), post.title.len);
    post.title.content[post.title.len] = '\0';
    if (strip(&post.title) != RET_SUCCESS)
    {
        die(_("Cannot strip title.\n"));
    }
    free_content(&line);

    /* Date. */
    line = read_line(file, filepath);
    if (!startswith(line, CONTENT(DATE_START)))
    {
        warn(_("Second line must start with \"%s\".\n"), DATE_START);
        die(_("Second line of %s is not a date.\n"), filepath);
    }
    if (!endswith(line, CONTENT(DATE_END)))
    {
        warn(_("Second line must end with \"%s\".\n"), DATE_END);
        die(_("Second line of %s is not a date.\n"), filepath);
    }
    if (line.len <= strlen(DATE_END) + strlen(DATE_START))
    {
        fclose(file);
        free_content(&line);
        free_post(&post);
        warn(_("Second line must contain a date.\n"));
        die(_("Second line of %s is not a date.\n"), filepath);
    }
    post.date = alloc_content(line.len - strlen(DATE_END) - strlen(DATE_START));
    if (is_null_content(post.date))
    {
        goto ERROR;
    }
    memcpy(post.date.content, line.content + strlen(DATE_START), post.date.len);
    post.date.content[post.date.len] = '\0';
    if (strip(&post.date) != RET_SUCCESS)
    {
        die(_("Cannot strip date.\n"));
    }
    free_content(&line);

    /* Tags. */
    line = read_line(file, filepath);
    if (!startswith(line, CONTENT(TAG_START)))
    {
        warn(_("Third line must start with \"%s\".\n"), TAG_START);
        die(_("Third line of %s is not a tag.\n"), filepath);
    }
    if (!endswith(line, CONTENT(TAG_END)))
    {
        warn(_("Third line must end with \"%s\".\n"), TAG_END);
        die(_("Third line of %s is not a tag.\n"), filepath);
    }
    if (line.len <= strlen(TAG_END) + strlen(TAG_START))
    {
        warn(_("Third line must contain a tag.\n"));
        die(_("Third line of %s is not a tag.\n"), filepath);
    }

    line.content[line.len - strlen(TAG_END)] = '\0';
    line.content += strlen(TAG_START);
    post.tags = parse_tags(line);
    line.content -= strlen(TAG_START); /* Restore the content so that free_content() can free it. */
    if (check_duplicate_tags(post.tags))
    {
        goto ERROR;
    }
    free_content(&line); // TODO: Invalid free() / delete / delete[] / realloc()

    /* Description. */
    line = read_line(file, filepath);
    if (!startswith(line, CONTENT(DESC_START)))
    {
        warn(_("Fourth line must start with \"%s\".\n"), DESC_START);
        die(_("Fourth line of %s is not a description.\n"), filepath);
    }
    if (!endswith(line, CONTENT(DESC_END)))
    {
        warn(_("Fourth line must end with \"%s\".\n"), DESC_END);
        die(_("Fourth line of %s is not a description.\n"), filepath);
    }
    if (line.len <= strlen(DESC_END) + strlen(DESC_START))
    {
        warn(_("Fourth line must contain a description.\n"));
        die(_("Fourth line of %s is not a description.\n"), filepath);
    }
    post.description = alloc_content(line.len - strlen(DESC_END) - strlen(DESC_START));
    if (is_null_content(post.description))
    {
        goto ERROR;
    }
    memcpy(post.description.content, line.content + strlen(DESC_START), post.description.len);
    post.description.content[post.description.len] = '\0';
    if (strip(&post.description) != RET_SUCCESS)
    {
        die(_("Cannot strip description.\n"));
    }
    free_content(&line);

    /* License. */
    line = read_line(file, filepath);
    if (!startswith(line, CONTENT(LICENSE_START)))
    {
        warn(_("Fifth line must start with \"%s\".\n"), LICENSE_START);
        die(_("Fifth line of %s is not a license.\n"), filepath);
    }
    if (!endswith(line, CONTENT(LICENSE_END)))
    {
        warn(_("Fifth line must end with \"%s\".\n"), LICENSE_END);
        die(_("Fifth line of %s is not a license.\n"), filepath);
    }
    if (line.len <= strlen(LICENSE_END) + strlen(LICENSE_START))
    {
        warn(_("Fifth line must contain a license.\n"));
        die(_("Fifth line of %s is not a license.\n"), filepath);
    }
    post.license = alloc_content(line.len - strlen(LICENSE_END) - strlen(LICENSE_START));
    if (is_null_content(post.license))
    {
        goto ERROR;
    }
    memcpy(post.license.content, line.content + strlen(LICENSE_START), post.license.len);
    post.license.content[post.license.len] = '\0';
    if (strip(&post.license) != RET_SUCCESS)
    {
        die(_("Cannot strip license.\n"));
    }
    free_content(&line);

    /* Content. */
    post.content = read_file(filepath);
    if (is_null_content(post.content))
    {
        goto ERROR;
    }

    free_content(&line);
    close_file(file);

    return post;

ERROR:
    free_content(&line);
    free_post(&post);
    close_file(file);

    return null_post;
}

int save_post_meta(struct post_t post, const char *postinfo_filename)
{
    FILE *postinfo = NULL;

    info(_("Generating %s ...\n"), postinfo_filename);

    postinfo = fopen(postinfo_filename, "w");
    if (postinfo == NULL)
    {
        die(_("Cannot open file: %s\n"), postinfo_filename);
    }

    if (fprintf(postinfo, "%s\n", post.title.content) < 0)
    {
        die(_("Cannot write to file: %s\n"), postinfo_filename);
    }
    if (fprintf(postinfo, "%s\n", post.date.content) < 0)
    {
        die(_("Cannot write to file: %s\n"), postinfo_filename);
    }

    for (size_t i = 0; i < post.tags.num; i++)
    {
        if (fprintf(postinfo, "%s%s", post.tags.first[i].content, i == post.tags.num - 1 ? "\n" : ",") < 0)
        {
            die(_("Cannot write to file: %s\n"), postinfo_filename);
        }
    }

    if (fprintf(postinfo, "%s\n", post.description.content) < 0)
    {
        die(_("Cannot write to file: %s\n"), postinfo_filename);
    }

    if (fprintf(postinfo, "%s\n", post.license.content) < 0)
    {
        die(_("Cannot write to file: %s\n"), postinfo_filename);
    }

    if (fprintf(postinfo, "%s\n", post.last_modified.content) < 0)
    {
        die(_("Cannot write to file: %s\n"), postinfo_filename);
    }

    fclose(postinfo);

    return RET_SUCCESS;
ERROR:
    fclose(postinfo);

    return RET_ERROR;
}

struct content_t get_post_info(const char *filepath, const char *tmp_filename)
{
    struct content_t postinfo = null_content;
    char cmd[BUFSIZ];

    init_struct(cmd);

    if (snprintf(cmd, BUFSIZ, "./scripts/mkpostinfo.awk \"%s\" > \"%s\"", filepath, tmp_filename) < 0)
    {
        die(_("Cannot generate command.\n"));
    }

    info(_("Executing: %s\n"), cmd);

    if (command_exec(cmd))
    {
        die(_("Cannot execute command: %s\n"), cmd);
    }

    postinfo = read_file(tmp_filename);
    if (is_null_content(postinfo))
    {
        die(_("Cannot read file: %s\n"), tmp_filename);
    }

ERROR:
    return postinfo;
}

int save_post(struct post_t post)
{
    char out_filename[BUFSIZ];
    char tmp_filename[BUFSIZ];
    char postinfo_filename[BUFSIZ];
    FILE *tmpfile = NULL;
    struct content_t html_postinfo = null_content;
    struct content_t html_snippet = null_content;

    init_struct(out_filename);
    init_struct(tmp_filename);

    if (snprintf(out_filename, BUFSIZ, POST_OUTPUT_DIR "%s.html", post.filename.content) < 0)
    {
        die(_("Cannot generate filename.\n"));
    }
    if (snprintf(postinfo_filename, BUFSIZ, POST_OUTPUT_DIR "%s.info", post.filename.content) < 0)
    {
        die(_("Cannot generate filename.\n"));
    }
    if (snprintf(tmp_filename, BUFSIZ, POST_OUTPUT_DIR "%s.html.tmp", post.filename.content) < 0)
    {
        die(_("Cannot generate filename.\n"));
    }

    info(_("Generating %s ...\n"), out_filename);

    if (copy_file(post_template_file, out_filename) != RET_SUCCESS)
    {
        die(_("Cannot copy file: %s\n"), post_template_file);
    }

    /* Create tmpfile to save HTML. */
    tmpfile = fopen(tmp_filename, "wb");
    if (tmpfile == NULL)
    {
        die(_("Cannot open file: %s\n"), tmp_filename);
    }
    if (fwrite(post.content.content, sizeof(char), post.content.len, tmpfile) != post.content.len)
    {
        die(_("Cannot write to file: %s\n"), tmp_filename);
    }
    close_file(tmpfile);

    /* Save post meta. */
    if (save_post_meta(post, postinfo_filename) != RET_SUCCESS)
    {
        die(_("Cannot save post meta.\n"));
    }

    /* Generate HTML. */
    html_snippet = markdown_it_tohtml(tmp_filename);
    if (is_null_content(html_snippet))
    {
        die(_("Cannot convert markdown to html.\n"));
    }

    /* Generate post info. */
    html_postinfo = get_post_info(postinfo_filename, tmp_filename);
    if (is_null_content(html_postinfo))
    {
        goto ERROR;
    }

    /* Configure. */
    struct configure_t configures_[] = {PAIR("CONTENT", html_snippet.content), PAIR("SUBTITLE", post.title.content),
                                        PAIR("POSTINFO", html_postinfo.content),
                                        PAIR("FILENAME", post.filename.content)};

    if (configure(create_configures(configures_), out_filename) != RET_SUCCESS)
    {
        die(_("Cannot configure file: %s\n"), out_filename);
    }

    if (remove_file(tmp_filename) != RET_SUCCESS)
    {
        die(_("Cannot remove file: %s\n"), tmp_filename);
    }

    free_content(&html_postinfo);
    free_content(&html_snippet);

    return RET_SUCCESS;
ERROR:

    free_content(&html_postinfo);
    free_content(&html_snippet);
    close_file(tmpfile);

    return RET_ERROR;
}

void free_tags(struct tags_t *tags)
{
    if (tags == NULL)
    {
        return;
    }

    for (size_t i = 0; i < tags->num; i++)
    {
        free_content(&tags->first[i]);
    }

    free(tags->first);
}

void free_post(struct post_t *post)
{
    if (post == NULL)
    {
        return;
    }

    free_content(&post->filename);
    free_content(&post->title);
    free_content(&post->date);
    free_content(&post->description);
    free_content(&post->license);
    free_content(&post->content);
    free_content(&post->last_modified);
    free_tags(&post->tags);
}
