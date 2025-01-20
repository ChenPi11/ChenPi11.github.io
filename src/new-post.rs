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

use std::{io::Write, process::exit};

use chrono::prelude::*;

static POST_TEMPLATE: &str = r#"# 标题
<!-- date: @DATE@ -->
<!-- tag: 标签1,2 -->
"#;

fn main() {
    let now = Local::now();
    let date = now.format("%Y/%m/%d");
    let prefix: String = format!("orig-posts/{}-", now.format("%Y-%m-%d"));
    let mut filename = String::from(prefix.clone());
    let mut cur_num: i32 = 0;
    let mut post_tempate = String::from(POST_TEMPLATE);
    post_tempate = post_tempate.replace("@DATE@", date.to_string().as_str());
    loop {
        filename.push_str(&cur_num.to_string());
        filename.push_str(".md");
        if !std::path::Path::new(&filename).exists() {
            break;
        } else {
            filename = String::from(prefix.clone());
            cur_num += 1;
        }
    }
    println!("Creating {}", filename);
    let mut file = std::fs::File::create(filename.as_str()).unwrap();
    file.write_all(post_tempate.as_bytes()).unwrap();

    let res = std::process::Command::new("code").arg(filename).spawn();
    match res {
        Ok(_) => {}
        Err(e) => {
            println!("Error: {}", e);
            exit(1);
        }
    }
    match res {
        Ok(mut child) => {
            child.wait().unwrap();
        }
        Err(e) => {
            println!("Error: {}", e);
            exit(1);
        }
    }
    exit(0);
}
