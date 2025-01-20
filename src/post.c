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

#include <post.h>

#include <configure.h>
#include <copyfile.h>
#include <log.h>
#include <markdown-it.h>

#include <malloc.h>
#include <string.h>
#include <unistd.h>

static const char *post_template_file = NULL;

static const char *file_basename(const char *path)
{
    const char *slash = strrchr(path, '/');
    if (slash)
    {
        return slash + 1;
    }
    return path;
}

static struct content_t read_line(const char *path, FILE *file)
{
    struct content_t content;
    char *line = NULL;
    size_t len = 0;
    ssize_t read = 0;

    memset(&content, 0, sizeof(struct content_t));

    read = getline(&line, &len, file);
    if (read == -1)
    {
        if (feof(file))
        {
            free(line);
            die("EOF reached\n");
        }
        else
        {
            free(line);
            die("Cannot read file (getline): %s\n", path);
        }
    }
    content.len = read - 1;
    content.content = line;

    return content;
}

static struct tags_t parse_tags(struct content_t line)
{
    struct tags_t tags;
    struct content_t *ptags = NULL;
    size_t num = 0;

    char *token = strtok(line.content, TAGS_SEP);
    while (token != NULL)
    {
        struct content_t tag;
        tag.len = strlen(token);
        tag.content = malloc(tag.len + 1);
        if (tag.content == NULL)
        {
            die("Cannot allocate memory.\n");
        }
        memcpy(tag.content, token, tag.len);
        tag.content[tag.len] = '\0';
        num++;

        ptags = realloc(ptags, num * sizeof(struct content_t));
        if (ptags == NULL)
        {
            die("Cannot allocate memory.\n");
        }
        memcpy(ptags + num - 1, &tag, sizeof(struct content_t));
        token = strtok(NULL, TAGS_SEP);
    }

    tags.num = num;
    tags.first = ptags;

    return tags;
}

static void check_duplicate_tags(struct tags_t tags)
{
    for (size_t i = 0; i < tags.num; i++)
    {
        for (size_t j = i + 1; j < tags.num; j++)
        {
            if (strcmp(tags.first[i].content, tags.first[j].content) == 0)
            {
                warn("Duplicate tag: \"%s\"\n", tags.first[i].content);
                free_tags(&tags);
                die("Duplicate tag.\n");
            }
        }
    }
}

void post_init(const char *template_file)
{
    if (template_file == NULL)
    {
        die("Post template file is not specified.\n");
    }
    info("Using %s as post template\n", template_file);
    post_template_file = template_file;
}

struct post_t load_post(const char *filepath)
{
    struct post_t post;
    memset(&post, 0, sizeof(struct post_t));

    // Filename.
    const char *basename = file_basename(filepath);
    post.filename.len = strlen(basename);
    post.filename.content = malloc(post.filename.len + 1);
    if (post.filename.content == NULL)
    {
        die("Cannot allocate memory.\n");
    }
    memcpy(post.filename.content, basename, post.filename.len);
    post.filename.content[post.filename.len] = '\0';
    char *dot_pos = strchr(post.filename.content, '.');
    if (dot_pos != NULL)
    {
        *dot_pos = '\0';
    }

    FILE *file = fopen(filepath, "r");
    if (file == NULL)
    {
        free_post(&post);
        die("Cannot open file: %s\n", filepath);
    }

    // Title.
    struct content_t line = read_line(filepath, file);
    if (line.len < 2 || strncmp(line.content, TITLE_START, strlen(TITLE_START)) != 0)
    {
        fclose(file);
        free_content(&line);
        free_post(&post);
        warn("First line must start with \"# \"\n");
        die("First line of %s is not a title\n", filepath);
    }
    post.title.len = line.len - 2;
    post.title.content = malloc(post.title.len + 1);
    if (post.title.content == NULL)
    {
        fclose(file);
        free_content(&line);
        free_post(&post);
        die("Cannot allocate memory.\n");
    }
    memcpy(post.title.content, line.content + 2, post.title.len);
    post.title.content[post.title.len] = '\0';
    free_content(&line);

    // Date.
    line = read_line(filepath, file);
    if (strncmp(line.content, DATE_START, strlen(DATE_START)) != 0)
    {
        fclose(file);
        free_content(&line);
        free_post(&post);
        warn("Second line must start with \"" DATE_START "\"\n");
        die("Second line of %s is not a date\n", filepath);
    }
    if (strncmp(line.content + line.len - strlen(DATE_END), DATE_END, strlen(DATE_END)) != 0)
    {
        fclose(file);
        free_content(&line);
        free_post(&post);
        warn("Second line must end with \"" DATE_END "\"\n");
        die("Second line of %s is not a date.\n", filepath);
    }
    if (line.len <= strlen(DATE_END) + strlen(DATE_START))
    {
        fclose(file);
        free_content(&line);
        free_post(&post);
        warn("Second line must contain a date.\n");
        die("Second line of %s is not a date.\n", filepath);
    }
    post.date.len = line.len - strlen(DATE_END) - strlen(DATE_START);
    post.date.content = malloc(post.date.len + 1);
    if (post.date.content == NULL)
    {
        fclose(file);
        free_content(&line);
        free_post(&post);
        die("Cannot allocate memory.\n");
    }
    memcpy(post.date.content, line.content + strlen(DATE_START), post.date.len);
    post.date.content[post.date.len] = '\0';
    free_content(&line);

    // Tags.
    line = read_line(filepath, file);
    if (strncmp(line.content, TAG_START, strlen(TAG_START)) != 0)
    {
        fclose(file);
        free_content(&line);
        free_post(&post);
        warn("Third line must start with \"" TAG_START "\"\n");
        die("Third line of %s is not a tag\n", filepath);
    }
    if (strncmp(line.content + line.len - strlen(TAG_END), TAG_END, strlen(TAG_END)) != 0)
    {
        fclose(file);
        free_content(&line);
        free_post(&post);
        warn("Third line must end with \"" TAG_END "\"\n");
        die("Third line of %s is not a tag.\n", filepath);
    }
    if (line.len <= strlen(TAG_END) + strlen(TAG_START))
    {
        fclose(file);
        free_content(&line);
        free_post(&post);
        warn("Third line must contain a tag.\n");
        die("Third line of %s is not a tag.\n", filepath);
    }

    line.content[line.len - strlen(TAG_END)] = '\0';
    line.content += strlen(TAG_START);
    post.tags = parse_tags(line);
    check_duplicate_tags(post.tags);

    post.content = read_file(filepath);

    return post;
}

void save_post(struct post_t post)
{
    char out_filename[BUFSIZ];
    memset(out_filename, 0, BUFSIZ);
    snprintf(out_filename, BUFSIZ, POST_OUTPUT_DIR "%s.html", post.filename.content);

    char postinfo_filename[BUFSIZ];
    memset(postinfo_filename, 0, BUFSIZ);
    snprintf(postinfo_filename, BUFSIZ, POST_OUTPUT_DIR "%s.info", post.filename.content);

    info("Generating %s ...\n", out_filename);

    copy_file(post_template_file, out_filename);

    char tmp_filename[BUFSIZ];
    memset(tmp_filename, 0, BUFSIZ);
    snprintf(tmp_filename, BUFSIZ, POST_OUTPUT_DIR "%s.html.tmp", post.filename.content);
    FILE *tmpfile = fopen(tmp_filename, "w");
    if (tmpfile == NULL)
    {
        die("Cannot open file: %s\n", tmp_filename);
    }
    fwrite(post.content.content, 1, post.content.len, tmpfile);
    fclose(tmpfile);

    struct content_t html_snippet = markdown_it_tohtml(tmp_filename);

    unlink(tmp_filename);

    struct configure_t config_content = {"CONTENT", html_snippet.content};
    struct configure_t config_subtitle = {"SUBTITLE", post.title.content};
    struct configures_t configures;
    configures.first = malloc(sizeof(struct configure_t) * 2);
    configures.num = 2;
    configures.first[0] = config_content;
    configures.first[1] = config_subtitle;
    configure(configures, out_filename);

    FILE *postinfo = fopen(postinfo_filename, "w");
    if (postinfo == NULL)
    {
        free_content(&html_snippet);
        free_configures(&configures);
        die("Cannot open file: %s\n", postinfo_filename);
    }
    fprintf(postinfo, "%s\n", post.title.content);
    fprintf(postinfo, "%s\n", post.date.content);
    for (size_t i = 0; i < post.tags.num; i++)
    {
        fprintf(postinfo, "%s%s", post.tags.first[i].content, i == post.tags.num - 1 ? "\n" : ",");
    }
    fclose(postinfo);

    free_content(&html_snippet);
    free_configures(&configures);
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
    free_tags(&post->tags);
}
