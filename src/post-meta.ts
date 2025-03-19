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

import { logInfo, logVerbose } from "./log.js";
import { _ } from "./i18n.js";
import { sprintf } from "sprintf-js";
import { readFileSync, readdirSync } from "fs";
import upath from "upath";

/**
 * Post meta info.
 *
 * @author ChenPi11
 * @export
 * @class Post
 * @implements {Post}
 */
export class Post {
    private link: string;
    private title: string;
    private date: string;
    private tags: Set<string>;
    private description: string;
    private license: string;

    /**
     * Creates an instance of Post.
     *
     * @param {string} link Link of the post.
     * @param {string} title Title of the post.
     * @param {string} date Date of the post.
     * @param {string[]} tags Tags of the post.
     * @param {string} description Description of the post.
     * @param {string} license License of the post.
     * @memberof Post
     */
    constructor(link: string, title: string, date: string, tags: string[], description: string, license: string) {
        this.link = link;
        this.title = title;
        this.date = date;
        this.tags = new Set(tags);
        this.description = description;
        this.license = license;
    }

    /**
     * Returns the link of the post.
     *
     * @returns {string} Link of the post.
     * @memberof Post
     */
    getLink(): string {
        return this.link;
    }

    /**
     * Returns the tag list of the post.
     *
     * @returns {string[]} Tag list of the post.
     * @memberof Post
     */
    getTagList(): string[] {
        return Array.from(this.tags);
    }

    /**
     * Returns the title of the post.
     *
     * @returns {string} Title of the post.
     * @memberof Post
     */
    getTitle(): string {
        return this.title;
    }

    /**
     * Returns the date of the post.
     *
     * @returns {string} Date of the post.
     * @memberof Post
     */
    getDate(): string {
        return this.date;
    }

    /**
     * Returns the description of the post.
     *
     * @returns {string} Description of the post.
     * @memberof Post
     */
    getDescription(): string {
        return this.description;
    }

    /**
     * Returns the license of the post.
     *
     * @returns {string} License of the post.
     * @memberof Post
     */
    getLicense(): string {
        return this.license;
    }
}

/**
 * Returns a human-readable size string.
 *
 * @param size The size of the file in bytes.
 * @returns 
 */
function getHumanReadableSize(size: number): string {
    const units = ["B", "KB", "MB", "GB", "TB"];
    let i = 0;
    while (size >= 1024 && i < units.length - 1) {
        size /= 1024;
        i++;
    }
    return sprintf("%d %s", size, units[i]);
}

/**
 * Loads a post from a file.
 *
 * @param {string} filePath Path of the file.
 * @returns {Post} Post loaded from the file.
 */
function loadPost(filePath: string): Post {
    const link = `/posts/${upath.basename(filePath, ".info")}.html`;
    const content = readFileSync(filePath, "utf-8");
    const lines = content.split("\n");
    const title = lines[0];
    const date = lines[1];
    const tags = lines[2].split(",");
    const description = lines[3];
    const license = lines[4];
    logVerbose(sprintf(_("Post \"%s\":"), link));
    logVerbose(sprintf(_("\tTitle: %s"), title));
    logVerbose(sprintf(_("\tContent: %d Bytes (%s)"), content.length, getHumanReadableSize(content.length)));
    logVerbose(sprintf(_("\tDate: %s"), date));
    logVerbose(sprintf(_("\tTags: %s"), tags.join(", ")));
    logVerbose(sprintf(_("\tDescription: %s"), description));
    logVerbose(sprintf(_("\tLicense: %s"), license));

    return new Post(link, title, date, tags, description, license);
}

/**
 * Loads all posts from a directory.
 *
 * @param {string} postDir Directory of the posts.
 * @returns {Post[]} Posts loaded from the directory.
 */
export function loadPosts(postDir: string): Post[] {
    const posts: Post[] = [];
    readdirSync(postDir).forEach((file) => {
        const filePath = upath.join(postDir, file);
        if (upath.extname(file) === ".info") {
            posts.push(loadPost(filePath));
            logInfo(sprintf(_("Loaded post: %s"), file));
        }
    })
    return posts;
}
