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

"""Checking if the current working directory is ChenPi11's blog root directory."""

from pathlib import Path

from chenpi11_blog.i18n import _

__all__ = ["is_chenpi11_blog_rootdir"]


def is_chenpi11_blog_rootdir() -> bool:
    """Check the current working directory is ChenPi11's blog root directory.

    Returns:
        bool: True if the current path is ChenPi11's blog root directory,
            False otherwise.

    """
    return (
        Path.cwd().is_dir()
        and Path("requirements.txt").is_file()  # It's a Python project.
        and Path("pyproject.toml").is_file()
        and Path("Cargo.toml").is_file()  # It's a Rust project.
        and Path("Makefile.toml").is_file()
        and Path("configure.ac").is_file()  # It's an Autotools project.
        and Path("autogen.sh").is_file()
        and Path("CMakeLists.txt").is_file()  # It's a CMake project.
        and Path("package.json").is_file()  # It's a Node.js project.
        and Path("Makefile.in").is_file()  # It's an Autoconf+Makefile project.
        and Path("repo.json").is_file()  # It's a Rubisco project.
        and Path("tsconfig.json").is_file()  # It's a TypeScript project.
        and Path("go.mod").is_file()  # It's a Go project.
    )


if __name__ == "__main__":
    if not is_chenpi11_blog_rootdir():
        msg = _("You must run {prog} in project's root directory!\n").format(
            prog="is-chenpi11-blog-rootdir",
        )
        raise SystemExit(msg)
