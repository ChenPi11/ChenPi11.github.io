#!/usr/bin/awk -f

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

function get_license_element(license) {
    if (license == "CC-BY-4.0") {
        url = "https://creativecommons.org/licenses/by-nc-sa/4.0"
    }
    else if (license == "CC-BY-SA-4.0") {
        url = "https://creativecommons.org/licenses/by-sa/4.0"
    }
    else if (license == "CC-BY-NC-4.0") {
        url = "https://creativecommons.org/licenses/by-nc/4.0"
    }
    else if (license == "The Unlicense") {
        url = "https://unlicense.org"
    }
    else {
        print "\x1b[31mCannot find license \"" license "\"\x1b[0m" > "/dev/stderr"
        exit 1
    }

    element = "<a class=\"post-license-link\" href=\"" url "\" target=\"_blank\">" license "</a>"
    res = "本文章采用 " element " 许可协议。"
    if (license != "The Unlicense") {
        element = "<a class=\"post-license-link\" href=\"https://chenpi11.github.io\">ChenPi11's Blog</a>"
        res = res "转载请注明来源 " element " ！"
    }
    return res
}

{
    line++
    if (line == 2) {
        post_date = "<span class=\"post-info-title\">&#61463; 发布时间：</span>"
        post_date = post_date "<span class=\"post-info-content\">"$0"</span>"
        next
    }
    if (line == 5) {
        license = get_license_element($0)
        post_copyright = "<span class=\"post-info-title\">&#61945; 版权声明：</span>"
        post_copyright = post_copyright "<span class=\"post-info-content\">" license "</span>"
        next
    }
    if (line == 6) {
        post_last = "<span class=\"post-info-title\">&#61741; 最后修改：</span>"
        post_last = post_last "<span class=\"post-info-content\">"$0"</span>"
        next
    }
}

END {
    print "<div class=\"post-info\">"
    print "   <div>"
    print "       " post_date
    print "   </div>"
    print "   <div>"
    print "       " post_last
    print "   </div>"
    print "   <div>"
    print "       " post_copyright
    print "   </div>"
    print "</div>"
}
