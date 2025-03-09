"use strict";

import { getTerminal, fprintf, input } from "/lib/terminal.js";

$(function () {
    const _ = getTerminal("80x25");
    const term = _.terminal;
    const stdin = _.stdin;

    for (let i = 0; i < 22; i++) {
        term.writeln("00000000000000000000000000000000000000000000000000000000000000000000000000000000");
    }
    async function loop()
    {
        let x = 0;
        while (true)
        {
            const inp = await input(term, stdin, "Input: ");
            fprintf(term, "Output: %s\x07\n", inp);
            x++;
        }
    }
    loop();
});
