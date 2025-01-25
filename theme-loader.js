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
const prismCSSPath = "/prism/${theme}/prism.css";
const prismJSPath = "/prism/${theme}/prism.js";

// Add meta tag.
const metaColorScheme = document.createElement("meta");
metaColorScheme.name = "color-scheme";
metaColorScheme.content = theme;
document.head.appendChild(metaColorScheme);

// Add the CSS file to the head.
const gmcCSSLink = document.createElement("link");
gmcCSSLink.rel = "stylesheet";
gmcCSSLink.href = gmcCSSURL.replace("${theme}", theme);
document.head.appendChild(gmcCSSLink);

// Add the CSS file to the head.
const prismCSSLink = document.createElement("link");
prismCSSLink.rel = "stylesheet";
prismCSSLink.href = prismCSSPath.replace("${theme}", theme);
document.head.appendChild(prismCSSLink);

// Add the JavaScript file to the head.
const prismJSScript = document.createElement("script");
prismJSScript.src = prismJSPath.replace("${theme}", theme);
document.head.appendChild(prismJSScript);

// Callback function for setTheme
let themeChangeCallbacks = [];

function setTheme(new_theme) {
    console.log(`Setting theme to '${new_theme}' ...`);
    theme = new_theme;
    metaColorScheme.content = theme;
    gmcCSSLink.href = gmcCSSURL.replace("${theme}", theme);
    prismCSSLink.href = prismCSSPath.replace("${theme}", theme);
    prismJSScript.src = prismJSPath.replace("${theme}", theme);
    // Call the callback functions
    themeChangeCallbacks.forEach(callback => callback(theme));
};

function addThemeChangeCallback(callback) {
    themeChangeCallbacks.push(callback);
}
