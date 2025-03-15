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

import { showErrorToPage } from "./page-msg.js";

if (!ReadableStream) {
    showErrorToPage("Your browser doesn't support ReadableStream.");
}

/**
 * Async queue implementation.
 */
export class Queue {
    /**
     * Constructor.
     *
     * @constructor
     * @returns {Queue} Queue instance.
     */
    constructor() {
        this.controller = null;
        this.stream = new ReadableStream({
            start: (controller) => {
                this.controller = controller;
            }
        });
    }

    /**
     * Push value to queue.
     *
     * @param {*} value Value to push.
     */
    push(value) {
        this.controller.enqueue(value);
    }

    /**
     * Pop value from queue.
     *
     * @returns {*} Value from queue.
     */
    async pop() {
        const reader = this.stream.getReader();
        const { value } = await reader.read();
        reader.releaseLock();
        return value;
    }

    /**
     * Get queue size.
     *
     * @returns {number} Size of the queue.
     */
    size() {
        return this.controller.desiredSize;
    }
}
