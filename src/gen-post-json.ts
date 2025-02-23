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

import { isChenPi11Blog } from "./is-blog.js";
import { loadPosts, Post } from "./post-meta.js";
import { logInfo, logError } from "./log.js";
import { _, initI18n } from "./i18n.js";
import process from "process";
import * as fs from "fs";

interface PostMeta {
    title: string;
    date: string;
    tags: string[];
}

function toPostMetas(posts: Post[]): PostMeta[] {
    const postsJson: PostMeta[] = [];
    posts.forEach((post) => {
        postsJson.push({
            title: post.getTitle(),
            date: post.getDate(),
            tags: post.getTagList(),
        });
    });
    return postsJson;
}

function getTagsMap(posts: Post[]): Map<string, number> {
    const tagMap: Map<string, number> = new Map();
    posts.forEach((post) => {
        post.getTagList().forEach((tag) => {
            if (tagMap.has(tag)) {
                tagMap.set(tag, tagMap.get(tag)! + 1);
            } else {
                tagMap.set(tag, 1);
            }
        })
    });
    return tagMap;
}

function mapToObject(map: Map<string, any>): Record<string, any> {
    const obj: Record<string, any> = {};
    map.forEach((value, key) => {
        obj[key] = value;
    });
    return obj;
};

function getPostsJson(posts: Post[], tagsMap: Map<string, number>): string {
    const postsJson: PostMeta[] = toPostMetas(posts);
    const tags: string[] = Array.from(tagsMap.keys()).sort((a, b) => {
        return tagsMap.get(b)! - tagsMap.get(a)!;
    });
    const sortedTagsMap: Map<string, number> = new Map();
    tags.forEach((tag) => {
        sortedTagsMap.set(tag, tagsMap.get(tag)!);
    });

    return JSON.stringify({
        posts: postsJson,
        tags: mapToObject(sortedTagsMap),
    });
}

function main() {
    initI18n();
    if (!isChenPi11Blog()) {
        logError(_("Not a chenpi11-blog project."));
        process.exit(1);
    }
    if ("--help" in process.argv || "-h" in process.argv) {
        logInfo(_("Usage: gen-post-json <posts-dir> <output-file>"));
        process.exit(0);
    }
    if (process.argv.length != 4) {
        logError(_("Usage: gen-post-json <posts-dir> <output-file>"));
        process.exit(1);
    }

    try {
        const postsDir: string = process.argv[2];
        const outputFile: string = process.argv[3];

        const posts: Post[] = loadPosts(postsDir);
        const tagsMap: Map<string, number> = getTagsMap(posts);

        if (posts.length == 0) {
            throw new Error(_("No posts found."));
        }
        fs.writeFileSync(outputFile, getPostsJson(posts, tagsMap));
    }
    catch (exception: any) {
        logError(exception.message);
        process.exit(1);
    }
}

main();
