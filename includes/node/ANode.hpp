/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ANode.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjoly <adjoly@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:33:58 by adjoly            #+#    #+#             */
/*   Updated: 2025/02/27 11:07:16 by adjoly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "parser/tokenizer.hpp"
#include <cppeleven.hpp>
#include <map>
#include <string>
#include <sys/types.h>
#include <vector>

namespace toml {

/**
 *	@brief	Enum for specifying node type
 *
 *	@see	ANode class and all subsequent class
 */
enum nodeType { TABLE, ARRAY, VALUE, BOOL, STRING, INT, NONE };

class Table;
class Array;
template <typename type> class Value;

class ANode {
  public:
	//		return func
	virtual std::map<std::string, ANode> *getTable(void) { return not_nullptr; }
	virtual std::vector<ANode>			 *getArray(void) { return not_nullptr; }
	virtual void						 *getValue(void) { return not_nullptr; }

	//		is func
	virtual nodeType type(void) const { return NONE; }
};

} // namespace toml
