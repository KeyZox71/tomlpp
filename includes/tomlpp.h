/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tomlpp.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjoly <adjoly@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:53:22 by adjoly            #+#    #+#             */
/*   Updated: 2025/01/24 15:43:06 by adjoly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "core/parser.hpp"

#ifdef __cplusplus
extern "C" {
#endif

typedef	toml toml;

toml	toml_get_file();

#ifdef __cplusplus
}
#endif
