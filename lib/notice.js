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
 * Notice element.
 *
 * @class
 * @extends HTMLElement
 */
export class BaseNotice extends HTMLElement {
    /**
     * Attributes to observe.
     *
     * @type {string[]}
     */
    static observedAttributes = [];

    /**
     * Create a BaseNotice.
     *
     * @constructor
     */
    constructor() {
        super();
    }

    /**
     * Set the message, level and icon of the notice.
     *
     * @param {string} message - The message to display.
     * @param {string} level - The level of the notice.
     * @param {string} icon - The icon to display.
     */
    setMessage(message, level, icon) {
        this.message = message;
        this.level = level;
        this.icon = icon;
    }

    /**
     * Called when <notice> is connected to the DOM.
     */
    connectedCallback() {
        const $this = $(this);
        $this.text("");
        $this.addClass("notice");
        $this.addClass("notice-" + this.level);
        $this.append($(`<span class="notice-icon">${this.icon}</span>`));
        $this.append($(`<span class="notice-message">${this.message}</span>`));
    }
}

/**
 * InfoNotice element.
 *
 * @class
 * @extends BaseNotice
 */
export class InfoNotice extends BaseNotice {
    /**
     * Create an InfoNotice.
     *
     * @constructor
     */
    constructor() {
        super();
    }

    /**
     * Called when <info-notice> is connected to the DOM.
     */
    connectedCallback() {
        const info = $(this).text();
        this.setMessage(info, "info", "&#60020;");
        super.connectedCallback();
    }
}

/**
 * WarningNotice element.
 *
 * @class
 * @extends BaseNotice
 */
export class WarningNotice extends BaseNotice {
    /**
     * Create a WarningNotice.
     *
     * @constructor
     */
    constructor() {
        super();
    }

    /**
     * Called when <warning-notice> is connected to the DOM.
     */
    connectedCallback() {
        const info = $(this).text();
        this.setMessage(info, "warning", "&#60012;");
        super.connectedCallback();
    }
}

/**
 * ErrorNotice element.
 *
 * @class
 * @extends BaseNotice
 */
export class ErrorNotice extends BaseNotice {
    /**
     * Create an ErrorNotice.
     *
     * @constructor
     */
    constructor() {
        super();
    }

    /**
     * Called when <error-notice> is connected to the DOM.
     */
    connectedCallback() {
        const info = $(this).text();
        this.setMessage(info, "error", "&#60039;");
        super.connectedCallback();
    }
}

customElements.define("info-notice", InfoNotice);
customElements.define("warning-notice", WarningNotice);
customElements.define("error-notice", ErrorNotice);
