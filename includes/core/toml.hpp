/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toml.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjoly <adjoly@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:38:20 by adjoly            #+#    #+#             */
/*   Updated: 2025/01/25 15:24:02 by adjoly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstdlib>
#include <fstream>
#include <string>

typedef	std::string tomlKey;

typedef	struct {
	tomlKey	key;
	void	*val;
}	tomlPair_t;

class toml {
public:
	toml	*parse(std::string fileName);

private:
	tomlPair_t*		table;
};
