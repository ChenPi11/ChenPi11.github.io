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

import { Queue } from "./queue.js";

/**
 * An async FIFO IO buffer for terminal applet.
 */
export class IOBuffer {
    /**
     * Constructor.
     * @constructor
     * @returns {IOBuffer} IOBuffer instance.
     */
    constructor() {
        this.buffer = new Queue();
    }

    /**
     * Write data to buffer.
     * @param {string} data Data to write.
     */
    write(data) {
        for (let i = 0; i < data.length; i++) {
            this.buffer.push(data[i]);
        }
    }

    /**
     * Get a char from buffer.
     * @returns {Promise<string>} A char from buffer.
     */
    async getChar() {
        return await this.buffer.pop();
    }

    /**
     * Read data from buffer at most `size` bytes.
     * @param {number} size Size to read.
     * @returns {Promise<string>} Data from buffer.
     */
    async read(size) {
        let result = "";
        for (let i = 0; i < size; i++) {
            result += await this.getChar();
            if (this.buffer.size() === 0) {
                break;
            }
        }
        return result;
    }

    /**
     * Read all data from buffer.
     * @returns {Promise<string>} All data from buffer.
     */
    async readAll() {
        let result = "";
        while (this.buffer.size() > 0) {
            result += await this.getChar();
        }
        return result;
    }

    /**
     * Read a line from buffer.
     * @returns {Promise<string>} A line from buffer.
     */
    async readLine() {
        let result = [];
        while (true) {
            const c = await this.getChar();
            if (c === "\x7f") {
                result.pop();
                continue;
            }
            // XTerm.js uses CR to indicate a newline.
            if (c === "\r" || c === "\n") {
                break;
            } else {
                result.push(c);
            }
        }
        return result.join("");
    }
}
