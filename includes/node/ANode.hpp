/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ANode.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjoly <adjoly@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:33:58 by adjoly            #+#    #+#             */
/*   Updated: 2025/02/21 18:15:33 by adjoly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cppeleven.hpp>
#include <map>
#include <string>
#include <sys/types.h>
#include <vector>

namespace toml {

class Table;
class Array;
template <typename type> class Value;

typedef enum {
	EMPTY = -1, // ""
	TABLE,		// [table] || {asdf =f, fdfd = d}
	ARRAY,		// [ "", "" ]
	BOOL,		// true / false
	STRING,		// "wtf"
	INT,		// "1" / "0x3"
} valueType_t;

class ANode {
  public:
	//		return func
	virtual std::map<std::string, ANode> *getTable(void) { return not_nullptr; }
	virtual std::vector<ANode>			 *getArray(void) { return not_nullptr; }
	virtual void						 *getValue(void) { return not_nullptr; }

	//		is func
	virtual valueType_t type(void) const { return EMPTY; }
};

} // namespace toml
