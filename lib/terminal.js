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

import { getPreferredTermTheme } from './term-themes.js';

class TerminalApplet extends HTMLElement {
    static observedAttributes = ["title", "columns", "rows", "src"];

    constructor() {
        super();
    }

    connectedCallback() {
        const $this = $(this);
        this.title = $this.attr("title") || "未命名终端";
        this.src = $this.attr("src");
        if (!this.src) {
            console.error("Terminal applet's src is not defined.");
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
            fontFamily: "Meslo, monospace",
            fontSize: 14,
            scrollback: 9999999,
        });
        this.loadAddons();
        this.terminal.open(this.terminalElement.get(0));
        this.terminal.resize(this.columns, this.rows);
        this.postLoadAddons();

        // Initialize collapsible state.
        this.collapsed = false;

        // Click event.
        const self = this;
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

        window.addEventListener("DOMContentLoaded", function () {
            const terminalElement = self.terminalElement
            terminalElement.css("maxHeight", `${terminalElement.prop("scrollHeight")}px`);
        });

        // Execute applet.
        this.executeApplet();
    }

    loadAddons() {
    }

    postLoadAddons() {
    }

    executeApplet() {
        const $this = $(this);
        this.applet_element = $(`<script src="${this.src}"></script>`);
        $this.append(this.applet_element);
    }

}

// Define the custom element
customElements.define("terminal-applet", TerminalApplet);
