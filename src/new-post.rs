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

mod configure;
mod i18n;
mod log;
mod post_template;
mod verbose;

use std::{io::Write, path::Path};

/// Show the help message.
///
/// # Arguments
///
/// * `catalog` - The gettext catalog.
///
fn show_help(catalog: &gettext::Catalog) {
    print!(
        "{}",
        catalog.gettext("Usage: new-post [-h|--help] [-V|--version] [-v|--verbose]\n")
    );
    print!("\n");
    print!("{}", catalog.gettext("Options:\n"));
    print!(
        "{}",
        catalog.gettext("  -h, --help     Display this help and exit.\n")
    );
    print!(
        "{}",
        catalog.gettext("  -V, --version  Output version information and exit.\n")
    );
    print!(
        "{}",
        catalog.gettext("  -v, --verbose  Verbosely report processing.\n")
    );
}

/// Show the version information.
///
/// # Arguments
///
/// * `catalog` - The gettext catalog.
///
fn show_version(catalog: &gettext::Catalog) {
    print!("{}", catalog.gettext("new-post 0.1.0\n"));
    print!("{}", catalog.gettext("Copyright (C) 2025 ChenPi11\n"));
    print!(
        "{}",
        catalog.gettext(
            "License GPLv3+: GNU GPL version 3 or later <https://gnu.org/licenses/gpl.html>\n"
        )
    );
    print!(
        "{}",
        catalog.gettext("This is free software: you are free to change and redistribute it.\n")
    );
    print!(
        "{}",
        catalog.gettext("There is NO WARRANTY, to the extent permitted by law.\n")
    );
    print!("{}", catalog.gettext("Written by ChenPi11.\n"));
}

/// The main function.
///
/// # Arguments
///
/// * `args` - The command line arguments.
///
fn main() {
    let catalog = i18n::init_i18n();

    let args: Vec<String> = std::env::args().collect();
    if args.contains(&"-h".to_string()) || args.contains(&"--help".to_string()) {
        show_help(&catalog);
        std::process::exit(0);
    }
    if args.contains(&"-V".to_string()) || args.contains(&"--version".to_string()) {
        show_version(&catalog);
        std::process::exit(0);
    }
    if args.contains(&"-v".to_string()) || args.contains(&"--verbose".to_string()) {
        verbose::set_verbose(true);
    }

    let now = chrono::Local::now();
    let date = now.format("%Y/%m/%d");
    let filename = now.format("%Y-%m-%d");
    let prefix: String = format!("orig-posts/{}-", filename);
    let mut filename = String::from(prefix.clone());
    let mut cur_num: i32 = 0;
    loop {
        filename.push_str(&cur_num.to_string());
        if !std::path::Path::new(&(filename.clone() + ".md")).exists() {
            break;
        } else {
            filename = String::from(prefix.clone());
            cur_num += 1;
        }
    }

    let tmp = filename.clone();
    let filename_stem = Path::new(&tmp).file_stem().unwrap().to_str().unwrap();
    filename.push_str(".md");

    // Create the post.
    let mut vars = std::collections::HashMap::new();
    vars.insert("file".to_string(), filename.to_string());
    let message = strfmt::strfmt(catalog.gettext("Creating {file} ..."), &vars).unwrap();
    log::info(&catalog, message.as_str());

    let file = std::fs::File::create(filename.as_str());
    match file {
        Ok(_) => {}
        Err(e) => {
            let mut vars = std::collections::HashMap::new();
            vars.insert("file".to_string(), filename.to_string());
            vars.insert("error".to_string(), e.to_string());
            let message = strfmt::strfmt(
                catalog.gettext("Failed to create file {file}: {error}"),
                &vars,
            )
            .unwrap();
            log::error(&catalog, message.as_str());
            std::process::exit(1);
        }
    }
    let write_res = file
        .unwrap()
        .write_all(post_template::POST_TEMPLATE.as_bytes());
    match write_res {
        Ok(_) => {}
        Err(e) => {
            let mut vars = std::collections::HashMap::new();
            vars.insert("file".to_string(), filename.to_string());
            vars.insert("error".to_string(), e.to_string());
            let message = strfmt::strfmt(
                catalog.gettext("Failed to write to file {file}: {error}"),
                &vars,
            )
            .unwrap();
            log::error(&catalog, message.as_str());
            std::process::exit(1);
        }
    }

    // Configure the post.
    let mut configure_vars = std::collections::HashMap::new();
    configure_vars.insert("DATE".to_string(), date.to_string());
    configure::configure_file(&catalog, filename.as_str(), &configure_vars);

    // Create resource directory.
    let resource_dir = format!("orig-posts/res/{}", filename_stem);
    let mut vars = std::collections::HashMap::new();
    vars.insert("dir".to_string(), resource_dir.to_string());
    let message = strfmt::strfmt(
        catalog.gettext("Creating resource directory {dir} ..."),
        &vars,
    );
    log::info(&catalog, message.unwrap().as_str());
    let res = std::fs::create_dir_all(resource_dir.clone());
    match res {
        Ok(_) => {}
        Err(e) => {
            let mut vars = std::collections::HashMap::new();
            vars.insert("dir".to_string(), resource_dir.to_string());
            vars.insert("error".to_string(), e.to_string());
            let message = strfmt::strfmt(
                catalog.gettext("Failed to create directory {dir}: {error}"),
                &vars,
            );
            log::error(&catalog, message.unwrap().as_str());
            std::process::exit(1);
        }
    }

    // Create default background image.
    let default_bg = "res/default-post-image.png";
    let target_bg = format!("{}/background.png", resource_dir);
    let mut vars = std::collections::HashMap::new();
    vars.insert("file".to_string(), target_bg.to_string());
    let message = strfmt::strfmt(
        catalog.gettext("Creating default background image {file} ..."),
        &vars,
    );
    log::info(&catalog, message.unwrap().as_str());
    let res = std::fs::copy(default_bg, target_bg);
    match res {
        Ok(_) => {}
        Err(e) => {
            let mut vars = std::collections::HashMap::new();
            vars.insert("file".to_string(), default_bg.to_string());
            vars.insert("error".to_string(), e.to_string());
            let message = strfmt::strfmt(
                catalog.gettext("Failed to copy file {file}: {error}"),
                &vars,
            );
            log::error(&catalog, message.unwrap().as_str());
            std::process::exit(1);
        }
    }

    let res = std::process::Command::new("code")
        .arg(filename.as_str())
        .spawn();
    match res {
        Ok(mut child) => {
            let res = child.wait();
            match res {
                Ok(_) => {}
                Err(e) => {
                    let mut vars = std::collections::HashMap::new();
                    vars.insert("file".to_string(), filename.to_string());
                    vars.insert("error".to_string(), e.to_string());
                    let message = strfmt::strfmt(
                        catalog.gettext("Failed to wait for editor for file {file}: {error}"),
                        &vars,
                    );
                    log::error(&catalog, message.unwrap().as_str());
                    std::process::exit(1);
                }
            }
        }
        Err(e) => {
            let mut vars = std::collections::HashMap::new();
            vars.insert("file".to_string(), filename.to_string());
            vars.insert("error".to_string(), e.to_string());
            let message = strfmt::strfmt(
                catalog.gettext("Failed to open editor for file {file}: {error}"),
                &vars,
            );
            log::error(&catalog, message.unwrap().as_str());
            std::process::exit(1);
        }
    }
}
