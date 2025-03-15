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

extern crate libc;

/// The name of the package.
///
const PACKAGE_NAME: &str = "chenpi11-blog";

/// Check if the given directory is a valid chenpi11-blog locale directory.
/// 
/// # Arguments
/// 
/// * `dir` - The directory to check.
/// 
/// # Returns
/// 
/// Returns `true` if the directory is a valid chenpi11-blog locale directory, `false` otherwise.
///
fn is_chenpi11_blog_locale_dir(dir: &str) -> bool {
    let locale_file = format!("{}/en_US/LC_MESSAGES/{}.mo", dir, PACKAGE_NAME);
    return std::fs::File::open(locale_file).is_ok();
}

/// Initialize i18n module.
///
/// # Returns
///
/// Returns [`gettext::Catalog`] with the locale catalog.
/// If the locale couldn't be obtained, [`gettext::Catalog::empty()`] is returned instead.
///
pub fn init_i18n() -> gettext::Catalog {
    unsafe {
        // Why setlocale is unsafe?
        libc::setlocale(libc::LC_ALL, b"\0".as_ptr() as *const libc::c_char)
    };
    let locale = sys_locale::get_locale()
        .unwrap_or_else(|| String::from("en-US"))
        .replace("-", "_");

    let locale_dir;
    if is_chenpi11_blog_locale_dir(".venv/share/locale") {
        locale_dir = ".venv/share/locale".to_string();
    } else if is_chenpi11_blog_locale_dir("/usr/local/share/locale") {
        locale_dir = "/usr/local/share/locale".to_string();
    } else {
        locale_dir = "/usr/share/locale".to_string();
    }

    let locale_file = format!("{}/{}/LC_MESSAGES/{}.mo", locale_dir, locale, PACKAGE_NAME);

    let locale_fp = std::fs::File::open(locale_file);
    if locale_fp.is_err() {
        return gettext::Catalog::empty();
    }
    let catalog = gettext::Catalog::parse(locale_fp.unwrap());
    if catalog.is_err() {
        return gettext::Catalog::empty();
    }
    return catalog.unwrap();
}
