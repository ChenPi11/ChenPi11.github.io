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

import { IOBuffer } from "./io.js";
import { playBell } from "./bell.js";
import {
    getPreferredTermTheme, registerTerminal,
    getPreferredTermFontFamily, getPreferredTermFontSize,
} from './term-themes.js';

function getOutputableData(output) {
    // Replace \n with \r\n.
    let output_ = output.replaceAll("\n", "\r\n");
    // Replace \x7f with \b.
    output_ = output_.replaceAll("\x7f", "\b \b");
    // Bell when \x07 is received.
    if (output_.includes("\x07")) {
        playBell();
    }
    return output_;
}

function standardizedOutput(output) {
    // Replace \r with \n.
    let output_ = output.replaceAll("\r", "\n");
    // Bell when \x07 is received.
    if (output_.includes("\x07")) {
        playBell();
    }
    return output_;
}

export class TerminalApplet extends HTMLElement {
    static observedAttributes = ["title", "columns", "rows", "src", "readonly"];

    /**
     * Create a terminal applet.
     * @constructor
     */
    constructor() {
        super();
        this.stdin = new IOBuffer();
    }

    /**
     * Internal function to handle input data.
     * @param {string} data The input data.
     */
    onData(data) {
        if (data === "\x1b[3~") {
            // TODO: Support delete.
            return;
        }
        let str = standardizedOutput(data);
        this.terminal.write(getOutputableData(str).replaceAll("\x1b", "\udb84\udeb7"));
        this.stdin.write(str);
    }

    /**
     * Called when <terminal-applet>'s attributes are changed.
     * @param {string} name The attribute name.
     * @param {string} _oldValue The old value.
     * @param {string} newValue The new value.
     */
    attributeChangedCallback(name, _oldValue, newValue) {
        if (name === "title" && newValue && this.titleElement) {
            this.title = newValue;
            this.titleElement.text(this.title);
        }
        if (name === "columns" && newValue && this.terminal) {
            this.columns = parseInt(newValue);
            this.terminal.resize(this.columns, this.rows);
        }
        if (name === "rows" && newValue && this.terminal) {
            this.rows = parseInt(newValue);
            this.terminal.resize(this.columns, this.rows);
        }
    }

    /**
     * Called when <terminal-applet> is connected to the DOM.
     */
    connectedCallback() {
        const $this = $(this);
        this.title = $this.attr("title") || "未命名终端";
        this.src = $this.attr("src");
        this.readonly = $this.attr("readonly") || true;
        if (!this.src) {
            throw new Error("Terminal applet's src is not defined.");
        }

        $this.addClass("terminal-applet");
        // Create header.
        this.header = $(`<div class="terminal-applet-header"></div>`);
        $this.append(this.header);
        // Create button.
        this.button = $(`<button class="terminal-applet-toggle-button" type="button">-</button>`);
        this.header.append(this.button);
        // Create title element.
        this.titleElement = $(`<div class="terminal-applet-title"></div>`);
        this.titleElement.text(this.title);
        this.header.append(this.titleElement);
        // Create terminal element.
        this.terminalElement = $(`<div class="terminal-applet-terminal"></div>`);
        $this.append(this.terminalElement);

        // Set columns and rows.
        this.columns = this.getAttribute("columns") || "80";
        this.rows = this.getAttribute("rows") || "25";
        this.columns = parseInt(this.columns);
        this.rows = parseInt(this.rows);

        // Create terminal.
        this.terminal = new Terminal({
            theme: getPreferredTermTheme(),
            fontFamily: getPreferredTermFontFamily(),
            scrollback: 9999999,
        });
        registerTerminal(this.terminal);
        this.loadAddons();
        this.terminal.open(this.terminalElement.get(0));
        this.terminal.resize(this.columns, this.rows);
        if (!this.readonly)
        {
            this.terminal.onData(this.onData.bind(this));
        }

        // Initialize collapsible state.
        this.collapsed = false;

        // Click event.
        const self = this;
        $(function () {
            // Set terminal font size later, or a bug for char 'W' will be occur.
            self.terminal.options.fontSize = getPreferredTermFontSize();
        })
        function toggleContent() {
            const terminalElement = self.terminalElement
            const button = self.button

            if (self.collapsed) {
                terminalElement.css("maxHeight", `${terminalElement.prop("scrollHeight")}px`);
                button.text("-");
                self.collapsed = false;
            } else {
                terminalElement.css("maxHeight", "0px");
                button.text("+");
                self.collapsed = true;
            }
        }
        this.header.on("click", toggleContent);

        $(function () {
            const terminalElement = self.terminalElement;
            terminalElement.css("maxHeight", `${terminalElement.prop("scrollHeight")}px`);
        });

        this.executeApplet();
        this.postLoadAddons();
    }

    /**
     * Called when we are loading addons.
     */
    loadAddons() {
        this.fitAddon = new FitAddon.FitAddon();
        this.terminal.loadAddon(this.fitAddon);
    }

    /**
     * Called when we are loaded addons.
     */
    postLoadAddons() {
        function fit() {
            this.fitAddon.fit();
        }
        fit = fit.bind(this);
        $(window).on("resize", fit);
    }

    /**
     * Execute applet.
     */
    executeApplet() {
        const $this = $(this);
        this.applet_element = $(`<script src="${this.src}" type="module"></script>`);
        $this.append(this.applet_element);
    }

}

// Define the custom element.
customElements.define("terminal-applet", TerminalApplet);

/**
 * Terminal handles.
 * 
 * @typedef {Object} TerminalHandles
 * @property {HTMLElement} element Terminal element.
 * @property {Terminal} terminal Terminal instance.
 * @property {IOBuffer} stdin Input buffer.
 */
export class TerminalHandles {
    constructor(element, terminal, stdin) {
        this.element = element;
        this.terminal = terminal;
        this.stdin = stdin;
    }
}

/**
 * Get terminal instance.
 * 
 * @param {string} id Terminal element's id.
 * @returns {TerminalHandles} Terminal instance.
 */
export function getTerminal(id) {
    const terminalDOMElement = $(`#${id}`).get(0);
    return new TerminalHandles(terminalDOMElement, terminalDOMElement.terminal, terminalDOMElement.stdin);
}

/**
 * Write raw data to terminal. Replace '\n' to '\r\n'.
 * 
 * @param {Terminal} term Terminal instance.
 * @param {string} str String to print.
 */
export function fwrite(term, str) {
    term.write(getOutputableData(str));
}

/**
 * Write raw data to terminal with new line.
 * 
 * @param {Terminal} term Terminal instance.
 * @param {string} str String to print.
 */
export function fwriteln(term, str) {
    term.writeln(str);
}

/**
 * Print formatted string to terminal.
 * 
 * @param {Terminal} term Terminal instance.
 * @param {string} format Format string.
 * @param  {...any} args Arguments.
 */
export function fprintf(term, format, ...args) {
    const output = vsprintf(format, args);
    fwrite(term, output);
}

/**
 * Print formatted string to terminal with new line.
 * 
 * @param {Terminal} term Terminal instance.
 * @param {string} format Format string.
 * @param  {...any} args Arguments.
 */
export function fprintfln(term, format, ...args) {
    const output = vsprintf(format, args);
    fwriteln(term, output);
}

/**
 * Print formatted string to terminal with new line.
 *
 * @param {Terminal} term Terminal instance.
 * @param {string} format Format string.
 * @param {Array} args Arguments.
 */
export function vfprintf(term, format, args) {
    const output = vsprintf(format, args);
    fwrite(term, output);
}

/**
 * Read data from terminal at most `size` bytes.
 * 
 * @param {IOBuffer} file Input buffer.
 * @returns {Promise<string>} Input string.
 */
export async function fread(file, size) {
    return await file.read(size);
}

/**
 * Read data from terminal until '\n' is received.
 * 
 * @param {IOBuffer} file Input buffer.
 * @returns {Promise<string>} Input string.
 */
export async function freadln(file) {
    return await file.readLine();
}

/**
 * Print prompt and readline.
 * 
 * @param {Terminal} stdout Terminal instance.
 * @param {IOBuffer} stdin Input buffer.
 * @param {string} prompt Prompt string.
 */
export async function input(stdout, stdin, prompt) {
    fprintf(stdout, prompt);
    return await freadln(stdin);
}
