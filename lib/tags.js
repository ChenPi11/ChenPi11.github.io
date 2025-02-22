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

newTag("test");
newTag("HTML")
newTag("CSS")
newTag("JavaScript")
newTag("React")
newTag("Node.js")
newTag("Python")
newTag("Django")
newTag("Flask")
newTag("Java")
newTag("Spring")
newTag("Kotlin")
newTag("Swift")
newTag("iOS")
newTag("Android")
newTag("SQL")
newTag("NoSQL")
newTag("MongoDB")
newTag("PostgreSQL")
newTag("MySQL")
newTag("GraphQL")

function onHashChange() {
    if (window.location.hash !== "") {
        const tag = window.location.hash.substring(1);
        $(".tag").removeClass("active");
        $(`#tag-${tag}`).addClass("active");
    }
}

$(onHashChange);
$(window).on("hashchange", onHashChange);
