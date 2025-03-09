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

import {
    listTermThemes,
    getTermTheme,
    getPreferredTermTheme,
    getPreferredTermThemeName,
    setPreferredTermTheme,
    registerTerminal
} from '/lib/term-themes.js';
import { getTheme, addThemeChangeCallback } from '/lib/theme-loader.js';
import { listCookies, setCookie, getCookie, updateCookieDays, eraseCookie } from '/lib/cookie.js';

for (const [name, _] of listTermThemes()) {
    const option = $(`<label>
                        <input type="radio" name="theme" value="${name}">
                        ${name}
                        </label>`);
    $("#theme-option").append(option);
}

function updateTermThemeSetting() {
    $(`input[value="${getPreferredTermThemeName()}"]`).prop("checked", true);
    if (getTheme() == "dark") {
        $("#theme-preview-tag").html("暗色主题下终端的主题");
    }
    else {
        $("#theme-preview-tag").html("亮色主题下终端的主题");
    }
}

let onThemeChanged = function () { }; // For updateCookieList below.

$(`input[name="theme"]`).on("change", function () {
    setPreferredTermTheme($(this).val());
    const theme = $(`input[name="theme"]:checked`).val();
    term.options.theme = getTermTheme(theme);
    onThemeChanged();
});

const term = new Terminal({
    fontFamily: "Meslo, monospace",
    theme: getPreferredTermTheme(),
    fontSize: 14,
    scrollback: 9999999,
});
registerTerminal(term);
term.resize(30, 12);
term.open($("#term-preview").get(0));
term.writeln("\x1b[0m前景色\x1b[0m");
term.writeln("\x1b[30m黑色\x1b[0m\t\x1b[1;30m亮黑色\x1b[0m\t\x1b[40m黑色背景\x1b[0m");
term.writeln("\x1b[31m红色\x1b[0m\t\x1b[1;31m亮红色\x1b[0m\t\x1b[41m红色背景\x1b[0m");
term.writeln("\x1b[32m绿色\x1b[0m\t\x1b[1;32m亮绿色\x1b[0m\t\x1b[42m绿色背景\x1b[0m");
term.writeln("\x1b[33m黄色\x1b[0m\t\x1b[1;33m亮黄色\x1b[0m\t\x1b[43m黄色背景\x1b[0m");
term.writeln("\x1b[34m蓝色\x1b[0m\t\x1b[1;34m亮蓝色\x1b[0m\t\x1b[44m蓝色背景\x1b[0m");
term.writeln("\x1b[35m紫色\x1b[0m\t\x1b[1;35m亮紫色\x1b[0m\t\x1b[45m紫色背景\x1b[0m");
term.writeln("\x1b[36m青色\x1b[0m\t\x1b[1;36m亮青色\x1b[0m\t\x1b[46m青色背景\x1b[0m");
term.writeln("\x1b[37m白色\x1b[0m\t\x1b[1;37m亮白色\x1b[0m\t\x1b[47m白色背景\x1b[0m");
term.writeln("\uf31a \uf31b \uf31c \uf31d \uf31e \uf31f");
term.writeln("Hello World")

$(".keep-theme-settings").on("click", function () {
    const toggleButton = $("#keep-theme-button");
    toggleButton.toggleClass("active");
    let keepThemeSettings = toggleButton.hasClass("active");
    if (keepThemeSettings) {
        setCookie("keep-theme-settings", "true", 365);
    }
    else {
        setCookie("keep-theme-settings", "false");
        eraseCookie("keep-theme-settings");
    }

    const needKeeps = ["color-scheme", "term-theme", "term-theme-dark"]
    for (const needKeep of needKeeps) {
        updateCookieDays(needKeep, keepThemeSettings ? 365 : 7)
    }
});

$(function () {
    const keepThemeSettings = getCookie("keep-theme-settings") == "true";
    if (keepThemeSettings) {
        $(".keep-theme-settings").addClass("active");
    }
})

function updateCookieList() {
    const cookieList = $("#cookie-list");
    cookieList.empty();
    cookieList.append("<h2>Cookies</h2>");
    for (const [key, value] of listCookies()) {
        const listItem = $(`<div class="list-item">
                                <div class="item-content">
                                    <span class="item-name">${key}</span>
                                    <span class="item-value">${value}</span>
                                </div>
                            </div>`);
        cookieList.append(listItem);
    }
}

$(updateTermThemeSetting);
$(updateCookieList);
onThemeChanged = updateCookieList;
addThemeChangeCallback(updateCookieList);
addThemeChangeCallback(updateTermThemeSetting);
