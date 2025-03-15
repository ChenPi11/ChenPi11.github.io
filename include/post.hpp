/**
 * @file post.hpp
 * @brief Post info class.
 * @author ChenPi11
 * @copyright Copyright (C) 2025 ChenPi11
 */
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

#pragma once
#ifndef _POST_INFO_HPP_
#define _POST_INFO_HPP_

#include <filesystem>
#include <string>
#include <vector>

#define POST_DIR_NAME "posts"
#define POST_TEMPLATE_NAME "post-template.html.in"
#define TAG_TEMPLATE_NAME "tag-template.html.in"

namespace post
{

/**
 * @brief The post metadata.
 */
class PostInfo
{
  private:
    std::string m_title;
    std::string m_date;
    std::string m_filename;
    std::vector<std::string> m_tags;
    std::string m_description;

  public:
    PostInfo() = delete;

    /**
     * @brief Construct a new PostInfo object.
     * @param metafile The metadata file.
     * @throw std::runtime_error If the metadata file is not valid.
     */
    PostInfo(const std::filesystem::path &metafile);

    /**
     * @brief Get the title of the post.
     * @return The title of the post.
     */
    std::string get_title() const noexcept
    {
        return m_title;
    }

    /**
     * @brief Get the date of the post.
     * @return The date of the post.
     */
    std::string get_date() const noexcept
    {
        return m_date;
    }

    /**
     * @brief Get the filename of the post.
     * @return The filename of the post.
     */
    std::vector<std::string> get_tags() const noexcept
    {
        return m_tags;
    }

    /**
     * @brief Get the filename of the post.
     * @return The filename of the post.
     */
    std::string get_description() const noexcept
    {
        return m_description;
    }

    /**
     * @brief Get the filename of the post.
     * @return The filename of the post.
     */
    std::string generate_tags() const;

    /**
     * @brief Get the filename of the post.
     * @return The filename of the post.
     */
    std::string generate() const;
};

/**
 * @brief Load all the posts.
 * @return The vector of all the posts.
 */
extern std::vector<post::PostInfo> load_posts();

} // namespace post

#endif // _POST_INFO_HPP_
