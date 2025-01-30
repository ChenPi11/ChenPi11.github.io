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
#ifndef _I18N_HPP_
#define _I18N_HPP_

#include "config.hpp"

#if HAVE_LIBINTL_H
#include <libintl.h>
#endif // HAVE_LIBINTL_H

namespace i18n
{
/**
 * @brief Initialize the i18n module.
 */
extern void i18n_init();

/**
 * @brief Get the i18n string.
 * @param msg The message.
 * @return The i18n string.
 */
extern const char *gettext(const char *msg);

#if HAVE_LIBINTL_H
/**
 * @brief Get the i18n string.
 * @param msg The message.
 * @return The i18n string.
 */
#define _(msg) i18n::gettext(msg)
#else
/**
 * @brief i18n not supported.
 * @param msg The message.
 * @return The message.
 */
#define _(msg) msg
#endif // HAVE_LIBINTL_H

} // namespace i18n
#endif // _I18N_HPP_
