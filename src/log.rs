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

use std::io::IsTerminal;

use gettext::Catalog;

use crate::verbose::get_verbose;

/// Output log message.
///
/// # Arguments
///
/// * `color` - The color of the log message.
/// * `level_string` - The level string of the log message.
/// * `message` - The message to output.
/// * `to_stderr` - Whether to output the message to stderr.
///
fn output_log(color: &str, level_string: &str, message: &str, to_stderr: bool) {
    if to_stderr {
        if std::io::stderr().is_terminal() {
            eprintln!("\x1b[{}m{}{}\x1b[0m", color, level_string, message);
            return;
        }
        eprintln!("{}{}", level_string, message);
    } else {
        if std::io::stdout().is_terminal() {
            eprintln!("\x1b[{}m{}{}\x1b[0m", color, level_string, message);
            return;
        }
        println!("{}{}", level_string, message);
    }
}

/// Output verbose log message.
///
/// # Arguments
///
/// * `message` - The message to output.
///
pub fn verbose(message: &str) {
    if get_verbose() {
        output_log("32", "", message, false);
    }
}

/// Output info log message.
///
/// # Arguments
///
/// * `catalog` - The catalog to get the translated message.
/// * `message` - The message to output.
///
pub fn info(catalog: &Catalog, message: &str) {
    output_log("34", &catalog.gettext("INFO: "), message, false);
}

/// Output error log message.
///
/// # Arguments
///
/// * `catalog` - The catalog to get the translated message.
/// * `message` - The message to output.
///
pub fn error(catalog: &Catalog, message: &str) {
    output_log("31", &catalog.gettext("ERROR: "), message, true);
}
