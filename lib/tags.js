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

"use strict";

import { getTheme, addThemeChangeCallback } from "/lib/theme-loader.js";

/**
 * Update the theme of the page.
 *
 * @param {string} theme 
 */
function updateTheme(theme) {
    let title_icon = "&#58114;";
    if (theme === "dark") {
        title_icon = "&#58238;";
    }
    $(".tags-title").html(`${title_icon} 标签云 ${title_icon}`);
}

addThemeChangeCallback(updateTheme);

$(function () {
    updateTheme(getTheme());
});

/**
 * Create a new tag.
 *
 * @param {string} tagname
 */
function newTag(tagname) {
    let hue = Math.floor(Math.random() * 360);
    if (hue >= 15 && hue <= 135) {
        hue += 200;
    }
    const color = `hsl(${hue}, 100%, 50%)`;
    const tag = $(`
        <a class="tag" style="background-color: ${color}"
           href="#${tagname}" id="tag-${tagname}">
            ${tagname}
        </a>`);
    $(".tags").append(tag);
}

/**
 * Create a new post.
 *
 * @param {string} link The link to the post.
 * @param {string} title The title of the post.
 * @param {string} date The date of the post.
 * @param {string} desc The description of the post.
 */
function newPost(link, title, date, desc) {
    const post = $(`
                <div class="post">
                    <a href="${link}" class="postlink" target="_blank">
                        <h2>${title}</h2>
                        <p>Posted on <em>${date}</em></p>
                        <p>${desc}</p>
                    </a>
                </div>`);
    $("#posts").append(post);
}

/**
 * The metadata list of the posts.
 *
 * @type {object[]}
 */
var posts = [];

/**
 * The metadata of the posts.
 *
 * @type {object}
 */
var meta = null;

/**
 * Fetch the metadata of the posts.
 *
 * @returns {Promise<object>} The metadata of the posts.
 */
async function fetchPostsMeta() {
    const response = await fetch("/posts-meta.json");
    const posts = await response.json();

    return posts;
}

/**
 * Initialize the tags and posts.
 *
 * @returns {Promise<void>} Resolved when the tags and posts are initialized.
 */
async function initTagsAndPosts() {
    try {
        meta = await fetchPostsMeta();
        const tags = meta.tags;
        posts = meta.posts;
        for (const tag of Object.keys(tags)) {
            newTag(tag);
        }
    }
    catch (exception) {
        console.error(exception);
        $("#posts-hint").text("解析元数据失败");
        $("#posts").html(`<p>${exception.stack}`)
    }
}

/**
 * The promise of the tags and posts.
 *
 * @type {Promise<void>}
 */
var tagsPromise = initTagsAndPosts();

/**
 * Handle the hash change event.
 *
 * @returns {Promise<void>} Resolved when the hash change event is handled.
 */
async function onHashChange() {
    if (window.location.hash !== "") {
        await tagsPromise;
        const tag = decodeURIComponent(window.location.hash.substring(1));
        $(".tag").removeClass("active");
        $(`#tag-${tag}`).addClass("active");

        console.log(`Querying for tag: ${JSON.stringify(tag)} ...`);
        try {
            if (meta === null) {
                // We have awaited the promise, but it failed.
                // Let's wait for the promise output the exception.
                return;
            }
            $("#posts").empty();
            for (const post of posts) {
                if (post.tags.includes(tag)) {
                    newPost(post.link, post.title, post.date, post.desc);
                }
            }
            const postCount = meta.tags[tag];
            if (postCount === undefined || postCount == null || postCount === 0) {
                $("#posts-hint").text("没有找到相关文章");
                return;
            }
            $("#posts-hint").text(`共 ${postCount} 篇文章`);
        }
        catch (exception) {
            console.error(exception);
            $("#posts-hint").text("加载文章失败");
            $("#posts").html(`<p>${exception.stack}`)
        }
    }
}

$(onHashChange);
$(window).on("hashchange", onHashChange);
