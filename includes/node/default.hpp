/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjoly <adjoly@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:12:05 by adjoly            #+#    #+#             */
/*   Updated: 2025/03/11 19:14:40 by adjoly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ANode.hpp"
#include "Array.hpp"
#include "Table.hpp"
#include "ValueTemplate.hpp"

namespace toml {

std::string nodeTypeToStr(nodeType type) {
	static std::map<nodeType, std::string> nodeTypeName;
	if (nodeTypeName.empty()) {
		nodeTypeName[TABLE] = "table";
		nodeTypeName[ARRAY] = "array";
		nodeTypeName[VALUE] = "value";
		nodeTypeName[BOOL] = "boolean";
		nodeTypeName[STRING] = "string";
		nodeTypeName[INT] = "int";
		nodeTypeName[NONE] = "nothing";
	}
	return nodeTypeName.at(type);
}

}; // namespace toml
