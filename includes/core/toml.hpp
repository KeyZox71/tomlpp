/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toml.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjoly <adjoly@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:38:20 by adjoly            #+#    #+#             */
/*   Updated: 2025/01/24 15:57:59 by adjoly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstdlib>
#include <string>

typedef	std::string tomlKey;

typedef	struct {
	tomlKey	key;
	void	*val;
}	tomlPair_t;

class toml {
public:
	toml();

	~toml();
	tomlPair_t	getPair(std::string keyName);
	tomlKey		getKey(std::string keyName);
private:
	tomlPair_t* val;
};
