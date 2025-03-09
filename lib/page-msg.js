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

const THEME_ERROR = new Object({
    color: "#721c24",
    background: "#f8d7da",
    border: "#ff6347",
});

const THEME_WARNING = new Object({
    color: "#856404",
    background: "#fff3cd",
    border: "#f8d97c",
})

function showMessageToPage(message, theme) {
    const messageElement = $(`
    <div class="page-msg-container">
        <span class="page-msg-icon">&#61553;</span>
        <span class="page-msg-text">${message}</span>
    </div>
    `);
    messageElement.css("color", theme.color);
    messageElement.css("background", theme.background);
    messageElement.css("border", `5px solid ${theme.border}`);
    $("body").prepend(messageElement);
}

/**
 * Show error message to page.
 * @param {*} message 
 */
export function showErrorToPage(message) {
    showMessageToPage(message, THEME_ERROR);
}

/**
 * Show warning message to page.
 * @param {*} message
 */
export function showWarningToPage(message) {
    showMessageToPage(message, THEME_WARNING);
}
