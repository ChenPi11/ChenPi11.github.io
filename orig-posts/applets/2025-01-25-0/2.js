"use strict";

window.addEventListener("load", (function () {
    let termElement = document.getElementById("colors");
    const term = termElement.terminal;
    term.writeln("\x1b[30C\x1b[30m\x1b[40m   \x1b[31m\x1b[41m   \x1b[32m\x1b[42m   \x1b[33m\x1b[43m   \x1b[34m\x1b[44m   \x1b[35m\x1b[45m   \x1b[36m\x1b[46m   \x1b[37m\x1b[47m   \x1b[m");
    term.writeln("\x1b[30C\x1b[38;5;8m\x1b[48;5;8m   \x1b[38;5;9m\x1b[48;5;9m   \x1b[38;5;10m\x1b[48;5;10m   \x1b[38;5;11m\x1b[48;5;11m   \x1b[38;5;12m\x1b[48;5;12m   \x1b[38;5;13m\x1b[48;5;13m   \x1b[38;5;14m\x1b[48;5;14m   \x1b[38;5;15m\x1b[48;5;15m   \x1b[m");
}));
