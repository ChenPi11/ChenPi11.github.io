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

"""Copy files to wwwroot."""

import os
import sys
from pathlib import Path
from subprocess import PIPE, Popen

IGNORE_LIST = [
    "xterm.js",
    "xterm.css",
    "prism-dark.js",
    "prism-light.js",
    "prism-dark.css",
    "prism-light.css",
    "jquery.js",
]

HTML_MINIFIER_CMD = [
    "npx",
    "html-minifier",
    "--collapse-boolean-attributes",
    "--collapse-inline-tag-whitespace",
    "--collapse-whitespace",
    "--conservative-collapse",
    "--remove-attribute-quotes",
    "--remove-comments",
    "--sort-attributes",
    "--sort-class-name",
]

TERSER_CMD = [
    "npx",
    "terser",
]

CLEANCSS_CMD = [
    "npx",
    "cleancss",
    "-O2",
]


def trim_html(file_path: Path) -> None:
    """Minify HTML file.

    Args:
        file_path (Path): HTML file path.

    """
    cmd = " ".join([*HTML_MINIFIER_CMD, str(file_path)])
    msg = f"========== Minifying {file_path}... ==========\n"
    sys.stdout.write(msg)
    sys.stdout.write(f"Running command: {cmd}\n")
    with Popen(  # noqa: S602
        cmd,
        shell=True,
        stdout=PIPE,
        encoding="UTF-8",
    ) as proc:
        if (proc.wait() != 0) or (proc.stdout is None):
            sys.exit("Minify command run failed.")
        with Path.open(file_path, "w", encoding="UTF-8") as f:
            f.write(proc.stdout.read())


def trim_js(file_path: Path) -> None:
    """Minify JS file.

    Args:
        file_path (Path): JS file path.

    """
    cmd = " ".join([*TERSER_CMD, str(file_path)])
    msg = f"========== Minifying {file_path}... ==========\n"
    sys.stdout.write(msg)
    sys.stdout.write(f"Running command: {cmd}\n")
    with Popen(  # noqa: S602
        cmd,
        shell=True,
        stdout=PIPE,
        encoding="UTF-8",
    ) as proc:
        if (proc.wait() != 0) or (proc.stdout is None):
            sys.exit("Minify command run failed.")
        with Path.open(file_path, "w", encoding="UTF-8") as f:
            f.write(proc.stdout.read())


def trim_css(file_path: Path) -> None:
    """Minify CSS file.

    Args:
        file_path (Path): CSS file path.

    """
    cmd = " ".join([*CLEANCSS_CMD, str(file_path)])
    msg = f"========== Minifying {file_path}... ==========\n"
    sys.stdout.write(msg)
    sys.stdout.write(f"Running command: {cmd}\n")
    with Popen(  # noqa: S602
        cmd,
        shell=True,
        stdout=PIPE,
        encoding="UTF-8",
    ) as proc:
        if (proc.wait() != 0) or (proc.stdout is None):
            sys.exit("Minify command run failed.")
        with Path.open(file_path, "w", encoding="UTF-8") as f:
            f.write(proc.stdout.read())


def trim_wwwroot_main() -> None:
    """Copy files to wwwroot."""
    wwwroot = Path("wwwroot")
    if not wwwroot.exists():
        sys.exit("'wwwroot' not exists.")

    # Walk wwwroot recursively
    for root, _, files in os.walk(wwwroot):
        for file in files:
            file_path = Path(root) / file
            # Skip non-HTML files
            if file_path.suffix not in [".html", ".htm", ".js", ".css"]:
                continue
            if file_path.name in IGNORE_LIST:
                continue
            if file_path.suffix in [".html", ".htm"]:
                trim_html(file_path)
            elif file_path.suffix in [".js"]:
                trim_js(file_path)
            elif file_path.suffix in [".css"]:
                trim_css(file_path)


if __name__ == "__main__":
    trim_wwwroot_main()
