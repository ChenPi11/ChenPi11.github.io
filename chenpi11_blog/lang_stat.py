#!/usr/bin/env python3

# -*- mode: python -*-
# vi: set ft=python :
# Copyright (C) 2025 ChenPi11.
# This file is part of chenpi11-blog.
#
# chenpi11-blog is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# chenpi11-blog is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with chenpi11-blog.  If not, see <https://www.gnu.org/licenses/>.

"""Statistics on programming languages in the repository."""
from __future__ import annotations

import copy
import dataclasses
import enum
import json
import os
import sys
from pathlib import Path
from subprocess import PIPE, Popen

from chenpi11_blog import languages
from chenpi11_blog.i18n import _

CLOC_FLAGS = ["--autoconf", "--json"]


class LangStatScope(enum.Enum):
    """Language statistics scope."""

    REPO = "repo"
    ALL = "all"


@dataclasses.dataclass
class RGB:
    """RGB color."""

    r: int
    g: int
    b: int


def web_color_to_rgb(web_color: str) -> RGB:
    """Convert web color to RGB color.

    Args:
        web_color (str): Web color.

    Returns:
        RGB: RGB color.

    """
    web_color = web_color.removeprefix("#")
    if len(web_color) == 3:  # noqa: PLR2004
        web_color = "".join([c * 2 for c in web_color])
    return RGB(
        int(web_color[0:2], 16),
        int(web_color[2:4], 16),
        int(web_color[4:6], 16),
    )


def rgb_tty_color(rgb: RGB) -> str:
    """Convert RGB color to tty color.

    Args:
        rgb (RGB): RGB color.

    Returns:
        str: TTY color.

    """
    return f"\033[38;2;{rgb.r};{rgb.g};{rgb.b}m"


def get_lang_color(lang: str) -> RGB:
    """Get language color.

    Args:
        lang (str): Language name.

    Returns:
        RGB: Language color.

    """
    return web_color_to_rgb(languages.COLORS[lang.lower()])


def get_lang_stat(scope: LangStatScope) -> dict:
    """Get language statistics.

    Returns:
        dict: Language statistics.

    """
    if scope == LangStatScope.REPO:
        git_cmd = ["git", "ls-files", "--exclude-standard"]
        cloc_cmd = ["cloc", *CLOC_FLAGS, "--list-file=-"]
    else:
        git_cmd = ["false"]
        cloc_cmd = ["cloc", *CLOC_FLAGS, str(Path.cwd().absolute())]

    with (
        Popen(  # noqa: S602
            " ".join(git_cmd),
            stdout=PIPE,
            shell=True,
        ) as git_proc,
        Popen(  # noqa: S602
            " ".join(cloc_cmd),
            stdin=git_proc.stdout if scope == LangStatScope.REPO else None,
            stdout=PIPE,
            shell=True,
        ) as cloc_proc,
    ):
        if git_proc.wait() != 0 and scope == LangStatScope.REPO:
            sys.exit(_("Git command failed."))
        if cloc_proc.wait() != 0:
            sys.exit(_("Cloc command failed."))
        return json.loads(cloc_proc.stdout.read().decode("utf-8"))


@dataclasses.dataclass
class LangStatInfo:
    """Language statistics info."""

    count: int
    percent: float


@dataclasses.dataclass
class Statistics:
    """Statistics info."""

    total_count: int
    langs: dict[LangStatInfo]
    appeared_langs: list[str]


def _get_statistics(statistics: dict) -> Statistics:
    langs_code: dict[LangStatInfo] = {}
    for lang, info in statistics.items():
        langs_code[lang] = LangStatInfo(info["code"], 0)

    total_code_count: int = 0
    for lang in langs_code.values():
        total_code_count += lang.count

    langs_code = dict(
        sorted(langs_code.items(), key=lambda x: x[1].count, reverse=True),
    )

    return Statistics(
        total_code_count,
        langs_code,
        list(langs_code.keys()),
    )


def merge_langinfo(stats: Statistics, lang_src: str, lang_dst: str) -> None:
    """Merge language info.

    Args:
        stats (Statistics): Statistics info.
        lang_src (str): Source language.
        lang_dst (str): Destination language.

    """
    if stats.langs.get(lang_src) is None:
        return
    if stats.langs.get(lang_dst) is None:
        stats.langs[lang_dst] = LangStatInfo(0, 0)
    stats.langs[lang_dst].count += stats.langs[lang_src].count
    # Recalculate percent to avoid float error.
    percent = stats.langs[lang_dst].count / stats.total_count
    stats.langs[lang_dst].percent = percent  # Avoid line too long.
    stats.langs.pop(lang_src)
    stats.appeared_langs.remove(lang_src)

    # Resort langs.
    stats.langs = dict(
        sorted(
            stats.langs.items(),
            key=lambda x: x[1].count,
            reverse=True,
        ),
    )
    stats.appeared_langs = list(stats.langs.keys())


def get_statistics(scope: LangStatScope) -> Statistics:
    """Get statistics info.

    Args:
        scope (LangStatScope): Statistical scope.

    Returns:
        Statistics: Code statistics.

    """
    statistics = get_lang_stat(scope)
    statistics.pop("SUM")
    statistics.pop("header")

    code_statistics = _get_statistics(statistics)
    for info in code_statistics.langs.values():
        info.percent = info.count / code_statistics.total_count

    return code_statistics


BAR_WIDTH = os.get_terminal_size().columns - 10


def output_stat(stats: Statistics) -> Statistics | None:
    """Output statistics info.

    Args:
        stats (Statistics): Statistics info.

    Returns:
        Statistics | None: The statistics that cannot be output in this term.
            If None, all statistics can be output in this term.

    """
    need_return = False
    printed_length = 0
    res_stats = Statistics(0, {}, stats.appeared_langs)
    for lang, info in stats.langs.items():
        bar_percent = int(info.percent * BAR_WIDTH)
        if bar_percent == 0:
            need_return = True
            res_stats.langs[lang] = info
            res_stats.total_count += info.count
            continue
        color_control = rgb_tty_color(get_lang_color(lang))
        sys.stdout.write(color_control)
        sys.stdout.write(bar_percent * "\u2588")
        sys.stdout.write("\033[0m")
        printed_length += bar_percent
    if need_return:
        remain_size = BAR_WIDTH - printed_length
        sys.stdout.write(f"{"\u2591" * remain_size}\n{" " * printed_length}V")
        # Make cannot printed languages percents' sum equal to 1
        for info in res_stats.langs.values():
            info.percent = info.count / res_stats.total_count
    sys.stdout.write("\n")

    return res_stats if need_return else None


def output_legend(stats: Statistics) -> None:
    """Output statistics legend.

    Args:
        stats (Statistics): Statistics info.

    """
    max_lang_len = max(len(lang) for lang in stats.appeared_langs)
    for lang in stats.appeared_langs:
        color_control = rgb_tty_color(get_lang_color(lang))
        spaces = max_lang_len + 2
        lang_out = lang + " " * (spaces - len(lang))
        sys.stdout.write(f"{lang_out} {color_control}{"\u2588" * 10}\x1b[0m")
        sys.stdout.write(f" {stats.langs[lang].percent * 100:.4f}%\n")
    sys.stdout.write("\n")


def lang_stat_main() -> None:
    """Statistics on programming languages in the repository."""
    scope = LangStatScope.ALL if "--all" in sys.argv else LangStatScope.REPO
    str_scope = "All" if scope == LangStatScope.ALL else "Repo"
    stat = get_statistics(scope)
    sys.stdout.write(f"{BAR_WIDTH * "\u2550"}\n{str_scope} Codes:\n")
    # Merge some languages.
    merge_langinfo(stat, "C/C++ Header", "C")
    merge_langinfo(stat, "Bourne Shell", "Shell")
    merge_langinfo(stat, "Bourne Again Shell", "Shell")

    remains = output_stat(copy.deepcopy(stat))
    while remains:
        remains = output_stat(remains)
    sys.stdout.write(BAR_WIDTH * "\u2550" + "\n")
    output_legend(stat)


if __name__ == "__main__":
    lang_stat_main()
