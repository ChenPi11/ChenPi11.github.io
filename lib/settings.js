import { listTermThemes, getTermTheme, getPreferredTermThemeName, setPreferredTermTheme } from '/lib/term-themes.js';
import { addThemeChangeCallback } from '/lib/theme-loader.js';
import { listCookies } from '/lib/cookie.js';

for (const [name, _] of listTermThemes()) {
    const option = $(`<label>
                        <input type="radio" name="theme" value="${name}">
                        ${name}
                        </label>`);
    $("#theme-option").append(option);
}

const currentTheme = getPreferredTermThemeName();
$(`input[value="${currentTheme}"]`).prop("checked", true);

let onThemeChanged = function () {}; // For updateCookieList.

$(`input[name="theme"]`).on("change", function () {
    setPreferredTermTheme($(this).val());
    const theme = $(`input[name="theme"]:checked`).val();
    const termTheme = getTermTheme(theme);
    term.options.theme = termTheme;
    onThemeChanged();
});

const term = new Terminal({
    fontFamily: "Meslo, monospace",
    fontSize: 14,
    scrollback: 9999999,
});
term.resize(30, 12);
term.open($("#term-preview").get(0));
term.writeln("\x1b[0m前景色\x1b[0m");
term.writeln("\x1b[30m黑色\x1b[0m\t\x1b[1;30m亮黑色\x1b[0m\t\x1b[40m黑色背景\x1b[0m");
term.writeln("\x1b[31m红色\x1b[0m\t\x1b[1;31m亮红色\x1b[0m\t\x1b[41m红色背景\x1b[0m");
term.writeln("\x1b[32m绿色\x1b[0m\t\x1b[1;32m亮绿色\x1b[0m\t\x1b[42m绿色背景\x1b[0m");
term.writeln("\x1b[33m黄色\x1b[0m\t\x1b[1;33m亮黄色\x1b[0m\t\x1b[43m黄色背景\x1b[0m");
term.writeln("\x1b[34m蓝色\x1b[0m\t\x1b[1;34m亮蓝色\x1b[0m\t\x1b[44m蓝色背景\x1b[0m");
term.writeln("\x1b[35m紫色\x1b[0m\t\x1b[1;35m亮紫色\x1b[0m\t\x1b[45m紫色背景\x1b[0m");
term.writeln("\x1b[36m青色\x1b[0m\t\x1b[1;36m亮青色\x1b[0m\t\x1b[46m青色背景\x1b[0m");
term.writeln("\x1b[37m白色\x1b[0m\t\x1b[1;37m亮白色\x1b[0m\t\x1b[47m白色背景\x1b[0m");
term.writeln("\uf31a \uf31b \uf31c \uf31d \uf31e \uf31f");

function updateCookieList() {
    const cookieList = $("#cookie-list");
    cookieList.empty();
    cookieList.append("<h2>Cookies</h2>");
    for (const [key, value] of listCookies()) {
        const listItem = $(`<div class="list-item">
                                <div class="item-content">
                                    <span class="item-name">${key}</span>
                                    <span class="item-value">${value}</span>
                                </div>
                            </div>`);
        cookieList.append(listItem);
    }
}

$(updateCookieList);
onThemeChanged = updateCookieList;
addThemeChangeCallback(updateCookieList);
