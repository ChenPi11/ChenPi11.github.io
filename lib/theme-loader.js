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

// Check if the browser supports the prefers-color-scheme media query.
function getPreferredColorScheme() {
    const colorScheme = getCookie("color-scheme");
    if (colorScheme) {
        return colorScheme;
    }
    if (window.matchMedia) {
        if (window.matchMedia("(prefers-color-scheme: dark)").matches) {
            return "dark";
        }
        if (window.matchMedia("(prefers-color-scheme: light)").matches) {
            return "light";
        }
    }
    // Default to light if no preference is found.
    return "light";
}

const urlParams = new URLSearchParams(window.location.search);

let theme = urlParams.get("theme");
if (theme != "dark" && theme != "light") {
    theme = getPreferredColorScheme();
}

function getTheme() {
    return theme;
}

const gmcCSSURL = "https://cdnjs.cloudflare.com/ajax/libs/github-markdown-css/5.8.1/github-markdown-${theme}.min.css";
const prismCSSPath = "/lib/prism-${theme}.css";
const prismJSPath = "/lib/prism-${theme}.js";

$("body").attr("data-theme", theme);

// Add the CSS file to the head.
const metaColorScheme = $(`<meta name="color-scheme" content="${theme}">`);
$("head").append(metaColorScheme);
const gmcCSSLink = $(`<link rel="stylesheet" href="${gmcCSSURL.replace("${theme}", theme)}">`)
$("head").append(gmcCSSLink);

// Add the CSS file to the head.
const prismCSSLink = $(`<link rel="stylesheet" href="${prismCSSPath.replace("${theme}", theme)}">`)
$("head").append(prismCSSLink);

// Add the JavaScript file to the head.
const prismJSScript = $(`<script src="${prismJSPath.replace("${theme}", theme)}"></script>`)
$("head").append(prismJSScript);

// Callback function for setTheme.
let themeChangeCallbacks = [];

function setTheme(new_theme) {
    theme = new_theme;
    metaColorScheme.attr("content", theme);
    gmcCSSLink.attr("href", gmcCSSURL.replace("${theme}", theme))
    prismCSSLink.attr("href", prismCSSPath.replace("${theme}", theme));
    prismJSScript.attr("src", prismJSPath.replace("${theme}", theme));

    // Call the callback functions.
    themeChangeCallbacks.forEach(callback => callback(theme));
    $("body").attr("data-theme", theme);

    setCookie("color-scheme", theme, 7);
};

function addThemeChangeCallback(callback) {
    themeChangeCallbacks.push(callback);
}
