"use strict";

window.addEventListener("load", (function () {
    let termElement = document.getElementById("80x25");
    const term = termElement.terminal;
    for (let i = 0; i < 25; i++) {
        term.writeln("00000000000000000000000000000000000000000000000000000000000000000000000000000000");
    }
}));
