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

function getPreferredColorScheme() {
    // Check if the browser supports the prefers-color-scheme media query.
    if (window.matchMedia) {
        // Check if the preferred color scheme is dark.
        if (window.matchMedia('(prefers-color-scheme: dark)').matches) {
            return 'dark';
        }
        // Check if the preferred color scheme is light.
        if (window.matchMedia('(prefers-color-scheme: light)').matches) {
            return 'light';
        }
    }
    // Default to light if no preference is found.
    return 'light';
}

const urlParams = new URLSearchParams(window.location.search);

// dark or light
var theme = urlParams.get('theme');
if (theme != 'dark' && theme != 'light') {
    theme = getPreferredColorScheme()
}

// Add meta tag.
const meta = document.createElement('meta');
meta.name = 'color-scheme';
meta.content = theme;
document.head.appendChild(meta);

// Add github-markdown-css, it must be added before Prism.js.
const gmcCSSURL = `https://cdnjs.cloudflare.com/ajax/libs/github-markdown-css/5.8.1/github-markdown-${theme}.min.css`

// Add the CSS file to the head.
const gmcCSSLink = document.createElement('link');
gmcCSSLink.rel = 'stylesheet';
gmcCSSLink.href = gmcCSSURL;
document.head.appendChild(gmcCSSLink);

// Add Prism.js.
const prismCSSPath = `/prism/${theme}/prism.css`;
const prismJSPath = `/prism/${theme}/prism.js`;

// Add the CSS file to the head.
const prismCSSLink = document.createElement('link');
prismCSSLink.rel = 'stylesheet';
prismCSSLink.href = prismCSSPath;
document.head.appendChild(prismCSSLink);

// Add the JavaScript file to the head.
const prismJSScript = document.createElement('script');
prismJSScript.src = prismJSPath;
document.head.appendChild(prismJSScript);
