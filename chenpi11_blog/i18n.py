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

"""i18n support."""

import gettext
import locale
from pathlib import Path

__all__ = ["_"]

PACKAGE_NAME = "chenpi11-blog"

def _(msg: str) -> str:
    """Translate a string.

    Args:
        msg (str): Message to translate.

    Returns:
        str: Translated string.

    """
    return gettext.gettext(msg)

def is_chenpi11_blog_locale_dir(path: Path) -> bool:
    """Check if the path is a chenpi11-blog locale directory.

    Args:
        path (Path): Path to check.

    Returns:
        bool: True if the path is a chenpi11-blog locale directory.

    """
    return (path / "zh_CN" / "LC_MESSAGES" / f"{PACKAGE_NAME}.mo").is_file()


def init_i18n() -> None:
    """Initialize i18n module."""
    localedir = "/usr/share/locale"
    repo_localedir = Path(__file__).parent.parent / ".venv" / "share" / "locale"
    venv_localedir = Path.cwd() / ".venv" / "share" / "locale"
    if is_chenpi11_blog_locale_dir(repo_localedir):
        localedir = repo_localedir
    elif is_chenpi11_blog_locale_dir(venv_localedir):
        localedir = venv_localedir
    elif is_chenpi11_blog_locale_dir(Path("/usr/local/share/locale")):
        localedir = "/usr/local/share/locale"

    locale.setlocale(locale.LC_ALL, "")
    gettext.bindtextdomain(PACKAGE_NAME, localedir)
    gettext.textdomain(PACKAGE_NAME)
    gettext.install(PACKAGE_NAME, localedir)


init_i18n()
