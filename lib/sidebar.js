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

import { getTheme, setTheme } from "./theme-loader.js";

const navToggle = $("#nav-toggle");
const navClose = $("#nav-close");
const settingsToggle = $("#settings-toggle");
const homeToggle = $("#home-toggle");
const sidebar = $("#sidebar");
const container = $(".container");

navToggle.on("click", function () {
    sidebar.css("left", "0px");
    container.addClass("active");
});

navClose.on("click", function () {
    sidebar.css("left", "-250px");
    container.removeClass("active");
});

settingsToggle.on("click", function () {
    window.location.href = "/settings.html";
});

homeToggle.on("click", function () {
    window.location.href = "/index.html"; 
})

function onThemeButtonClick() {
    if (getTheme() == "light") {
        setTheme("dark");
    }
    else {
        setTheme("light");
    }
}

export function syncThemeButton() {
    const themeButtonDiv = $("#theme-button");
    themeButtonDiv.empty();
    const themeButton = document.createElement("theme-button");
    themeButton.setAttribute("value", getTheme());
    themeButton.setAttribute("size", "2");
    themeButton.addEventListener("click", onThemeButtonClick);
    themeButtonDiv.append(themeButton);
}

syncThemeButton();
