/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseValue.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjoly <adjoly@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:42:23 by adjoly            #+#    #+#             */
/*   Updated: 2025/03/07 15:18:38 by adjoly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "node/ValueTemplate.hpp"
#include <parser/default.hpp>
#include <node/default.hpp>

using namespace toml::parser;

bool	convertBool(std::string	boolean) {
	if (boolean == "true")
		return true;
	else
		return false;
}

