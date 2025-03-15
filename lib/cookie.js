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

/**
 * Get cookie value by name.
 *
 * @param {string} name
 * @returns {string} Cookie value.
 */
export function getCookie(name) {
    let nameEQ = name.trim() + "=";
    let ca = document.cookie.split(";");
    for (let i = 0; i < ca.length; i++) {
        let c = ca[i].trim();
        if (c.indexOf(nameEQ) == 0) {
            return c.substring(nameEQ.length, c.length);
        }
    }
    return null;
}

/**
 * Get default cookie days.
 *
 * @returns {number} Default cookie days.
 */
export function getDefaultCookieDays() {
    if (getCookie("keep-theme-settings") == "true") {
        return 365;
    }
    return 7;
}

/**
 * Set cookie.
 *
 * @param {string} name Cookie name.
 * @param {string} value Cookie value.
 * @param {number} days Days to expire.
 */
export function setCookie(name, value, days) {
    let expires = "";
    let date = new Date();
    if (days) {
        date.setTime(date.getTime() + (days * 24 * 60 * 60 * 1000));
        expires = "; expires=" + date.toUTCString();
    }
    else {
        date.setTime(date.getTime() + (getDefaultCookieDays() * 24 * 60 * 60 * 1000));
        expires = "; expires=" + date.toUTCString();
    }
    document.cookie = name + "=" + (value || "") + expires + "; path=/";
}

/**
 * Update cookie days.
 *
 * @param {string} name Cookie name.
 * @param {number} days Days to expire.
 */
export function updateCookieDays(name, days) {
    let value = getCookie(name);
    setCookie(name, value, days);
}

/**
 * Erase cookie.
 *
 * @param {string} name Cookie name.
 */
export function eraseCookie(name) {
    document.cookie = name + "=; Max-Age=-99999999;";
}

/**
 * List all cookies.
 *
 * @returns {Map<string, string>} Map of cookie name and value.
 */
export function listCookies() {
    let result = [];
    let cookies = document.cookie.split(";");
    for (let i = 0; i < cookies.length; i++) {
        let cookie = cookies[i];
        let eqPos = cookie.indexOf("=");
        let name = eqPos > -1 ? cookie.substring(0, eqPos) : cookie;
        name = name.trim();
        let value = getCookie(name);
        result.push([name, value]);
    }
    result.sort(function (a, b) {
        if (a[0] < b[0]) {
            return -1;
        }
        if (a[0] > b[0]) {
            return 1;
        }
    })
    return new Map(result);
}
