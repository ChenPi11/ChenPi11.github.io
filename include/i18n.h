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
#ifndef _I18N_H_
#define _I18N_H_

#include "defines.h"

#if ENABLE_NLS
#include "gettext.h"
#endif // ENABLE_NLS

EXTERN_C_BEG

/* Initialize the i18n module. */
extern void i18n_init();

#if ENABLE_NLS
/* Get the i18n string. */
#define _(msg) gettext(msg)
#else
/* i18n not supported. */
#define _(msg) msg
#endif // ENABLE_NLS

EXTERN_C_END

#endif // _I18N_H_
