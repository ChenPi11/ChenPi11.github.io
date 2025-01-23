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

const navToggle = document.getElementById("nav-toggle");
const navClose = document.getElementById("nav-close");
const sidebar = document.getElementById("sidebar");
const container = document.querySelector(".container");

navToggle.addEventListener("click", function () {
    sidebar.style.left = "0px";
    container.classList.add("active");
});

navClose.addEventListener("click", function () {
    sidebar.style.left = "-250px";
    container.classList.remove("active");
});

const themeButtonDiv = document.getElementById("theme-button");
const themeButton = document.createElement("theme-button");
themeButton.setAttribute("value", getTheme());
themeButton.setAttribute("size", "2");
themeButton.addEventListener("click", function () {
    if (getTheme() == "light") {
        setTheme("dark");
    }
    else {
        setTheme("light");
    }
});
themeButtonDiv.appendChild(themeButton);
