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

/// Replace variables in the source string.
///
/// # Arguments
///
/// * `source` - The source string.
/// * `variables` - The variables to replace.
///
/// # Returns
///
/// Returns the string with variables replaced.
///
pub fn configure(source: &str, variables: &std::collections::HashMap<String, String>) -> String {
    let mut result = String::from(source);
    for (key, value) in variables {
        let strkey = format!("@{}@", key.to_uppercase());
        result = result.replace(strkey.as_str(), value.as_str());
    }

    return result;
}

/// Configure a file.
///
/// # Arguments
///
/// * `catalog` - The catalog to get the translated message.
/// * `filepath` - The path of the file to configure.
/// * `variables` - The variables to replace.
///
/// # Exceptions
///
/// * [FmtError::Invalid] - The format string is structured incorrectly
/// * [FmtError::KeyError] - `vars` contains an invalid key
/// * [FmtError::TypeError] - the given format code for a section contains an unexpected option
///
pub fn configure_file(catalog: &gettext::Catalog, filepath: &str, variables: &std::collections::HashMap<String, String>) {
    let mut vars = std::collections::HashMap::new();
    vars.insert("file".to_string(), filepath.to_string());
    let message = strfmt::strfmt(catalog.gettext("Configuring {file} ..."), &vars).unwrap();
    crate::log::verbose(message.as_str());

    let source = std::fs::read_to_string(filepath);
    match source {
        Ok(_) => {}
        Err(e) => {
            let mut vars = std::collections::HashMap::new();
            vars.insert("file".to_string(), filepath.to_string());
            vars.insert("error".to_string(), e.to_string());

            let message = strfmt::strfmt(
                catalog.gettext("Failed to read file {file}: {error}"),
                &vars,
            )
            .unwrap();
            crate::log::error(&catalog, message.as_str());

            std::process::exit(1);
        }
    }
    let result = configure(&source.unwrap(), variables);
    let res = std::fs::write(filepath, result);
    match res {
        Ok(_) => {}
        Err(e) => {
            let mut vars = std::collections::HashMap::new();
            vars.insert("file".to_string(), filepath.to_string());
            vars.insert("error".to_string(), e.to_string());
            let message = strfmt::strfmt(
                catalog.gettext("Failed to write file {file}: {error}"),
                &vars,
            )
            .unwrap();
            crate::log::error(&catalog, message.as_str());
            std::process::exit(1);
        }
    }
}
