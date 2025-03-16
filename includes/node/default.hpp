/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjoly <adjoly@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:12:05 by adjoly            #+#    #+#             */
/*   Updated: 2025/03/16 19:19:18 by adjoly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ANode.hpp"
#include "Table.hpp"
#include "ValueTemplate.hpp"
#include "Array.hpp"

namespace toml {

static inline std::string nodeTypeToStr(nodeType type) {
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
