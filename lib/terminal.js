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

const theme_neon = {
    "foreground": "#F8F8F8",
    "background": "#171717",
    "cursor": "#F8F8F8",
    "black": "#171717",
    "brightBlack": "#878787",
    "red": "#D81765",
    "brightRed": "#FF0000",
    "green": "#97D01A",
    "brightGreen": "#76B639",
    "yellow": "#FFA800",
    "brightYellow": "#E1A126",
    "blue": "#16B1FB",
    "brightBlue": "#289CD5",
    "magenta": "#FF2491",
    "brightMagenta": "#FF2491",
    "cyan": "#0FDCB6",
    "brightCyan": "#0A9B81",
    "white": "#EBEBEB",
    "brightWhite": "#F8F8F8"
}

class TerminalApplet extends HTMLElement {
    static observedAttributes = ["title", "columns", "rows", "src"];

    constructor() {
        super();
    }

    connectedCallback() {
        this.title = this.getAttribute("title") || "Terminal";
        this.src = this.getAttribute("src");
        if (this.src == null) {
            console.error("Terminal applet's src is not defined.");
        }

        this.setAttribute("class", "terminal-applet");
        // Create header.
        this.header = document.createElement("div");
        this.header.setAttribute("class", "terminal-applet-header");
        this.appendChild(this.header);
        // Create button.
        this.button = document.createElement("button");
        this.button.setAttribute("class", "terminal-applet-toggle-button");
        this.button.setAttribute("type", "button");
        this.button.textContent = "-";
        this.header.appendChild(this.button);
        // Create title element.
        this.titleElement = document.createElement("div");
        this.titleElement.setAttribute("class", "terminal-applet-title");
        this.titleElement.textContent = this.title;
        this.header.appendChild(this.titleElement);
        // Create terminal element.
        this.terminalElement = document.createElement("div");
        this.terminalElement.setAttribute("class", "terminal-applet-terminal");
        this.appendChild(this.terminalElement);

        // Set columns and rows.
        this.columns = this.getAttribute("columns") || "80";
        this.rows = this.getAttribute("rows") || "25";
        this.columns = parseInt(this.columns);
        this.rows = parseInt(this.rows);

        // Create terminal.
        this.terminal = new Terminal({
            theme: theme_neon,
            fontFamily: "Meslo, monospace",
            fontSize: 14,
            scrollback: 9999999,
        });
        this.loadAddons();
        this.terminal.open(this.terminalElement);
        this.terminal.resize(this.columns, this.rows);
        this.postLoadAddons();

        // Initialize collapsible state.
        this.collapsed = false;

        // Click event.
        const this_ref = this;
        function toggleContent() {
            let terminalElement = this_ref.terminalElement
            let button = this_ref.button

            if (this_ref.collapsed) {
                terminalElement.style.maxHeight = terminalElement.scrollHeight + 'px';
                button.textContent = '-';
                this_ref.collapsed = false;
            } else {
                terminalElement.style.maxHeight = '0px';
                button.textContent = '+';
                this_ref.collapsed = true;
            }
        }

        this.header.addEventListener("click", toggleContent);

        window.addEventListener("load", function () {
            const terminalElement = this_ref.terminalElement
            terminalElement.style.maxHeight = `${terminalElement.scrollHeight}px`;
        });

        // Execute applet.
        this.executeApplet();
    }

    loadAddons() {
    }

    postLoadAddons() {
    }

    executeApplet() {
        this.applet_element = document.createElement("script");
        this.applet_element.type = "text/javascript";
        this.applet_element.src = this.src;
        this.appendChild(this.applet_element);
    }

}

// Define the custom element
customElements.define("terminal-applet", TerminalApplet);
