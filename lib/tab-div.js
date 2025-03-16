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
 * Tab div page.
 *
 * @class
 * @extends HTMLElement
 */
export class TabDivPage extends HTMLElement {
    /**
     * Attributes to observe.
     *
     * @type {string[]}
     */
    static observedAttributes = ["name"];

    /**
     * Create a tab div page.
     *
     * @constructor
     */
    constructor() {
        super();
    }

    /**
     * Called when <tab-div-page> is connected to the DOM.
     */
    connectedCallback() {
        const $this = $(this);
        this.name = $this.attr("name");
        if (!this.name) {
            throw new Error("Tab div page's name is not defined.");
        }
        this.setVisible(false);
        $this.addClass("tab-div-page");
    }

    /**
     * Set the page visible or not.
     *
     * @param {boolean} visible Whether the page is visible.
     */
    setVisible(visible) {
        if (visible) {
            $(this).animate({
                opacity: 1,
                duration: 200
            })
            $(this).css("display", "block");
        } else {
            $(this).animate({
                opacity: 0,
                duration: 200
            })
            $(this).css("display", "none");
        }
    }
}

/**
 * Tab div.
 *
 * @class
 * @extends HTMLElement
 */
export class TabDiv extends HTMLElement {
    /**
     * Attributes to observe.
     *
     * @type {string[]}
     */
    static observedAttributes = ["tab_prefix", "default"];

    /**
     * Create a tabs container.
     *
     * @constructor
     */
    constructor() {
        super();
    }

    /**
     * Called when <tab-div> is connected to the DOM.
     */
    connectedCallback() {
        const $this = $(this);
        this.tab_prefix = $this.attr("prefix");
        this.default = $this.attr("default");
        if (!this.tab_prefix) {
            throw new Error("Tab div's prefix is not defined.");
        }
        if (!this.default) {
            throw new Error("Tab div's default is not defined.");
        }

        this.default = this.tab_prefix + this.default;

        $this.addClass("tab-div");

        // Create header and container.
        this.header = $(`<div class="nav-tabs"></div>`);
        $this.prepend(this.header);
        this.container = $(`<div class="tab-div-container"></div>`);
        $this.append(this.container);

        // Get children.
        this.tabs = [];
        const children = $this.children("tab-div-page");
        for (let i = 0; i < children.length; i++) {
            this.addTabPage($(children[i]));
        }

        // Select default tab.
        const header_buttons = this.header.children();
        for (let i = 0; i < header_buttons.length; i++) {
            if ($(header_buttons[i]).text() == this.default) {
                $(header_buttons[i]).addClass("active");
            }
        }
        this.selectTabPage(this.default);
    }

    /**
     * Register a tab page.
     *
     * @param {TabDivPage} tabPageElement Tab page element.
     */
    addTabPage(tabPageElement) {
        // Move the tab page to the container.
        this.container.append(tabPageElement);
        this.tabs.push(tabPageElement);

        const tabButton = $(`<button class="nav-tab" type="button">${tabPageElement.get(0).name}</button>`);
        tabButton.on("click", (function () {
            this.selectTabPage(tabPageElement.get(0).name);

            const children = this.header.children();
            for (let i = 0; i < children.length; i++) {
                $(children[i]).removeClass("active");
            }
            tabButton.addClass("active");
        }).bind(this))
        this.header.append(tabButton);
    }

    /**
     * Select a tab page.
     *
     * @param {string} name Tab page name.
     */
    selectTabPage(name) {
        let visibleIsSet = false;
        for (let i = 0; i < this.tabs.length; i++) {
            const tab = this.tabs[i].get(0)
            if (tab.name === name) {
                tab.setVisible(true);
                visibleIsSet = true;
            } else {
                tab.setVisible(false);
            }
        }
        if (!visibleIsSet) {
            throw new Error(`Cannot find tab page "${name}".`);
        }
    }
}

customElements.define("tab-div-page", TabDivPage);
customElements.define("tab-div", TabDiv);
