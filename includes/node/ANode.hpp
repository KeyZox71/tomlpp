/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ANode.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjoly <adjoly@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:33:58 by adjoly            #+#    #+#             */
/*   Updated: 2025/02/14 17:25:31 by adjoly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

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
	virtual std::map<std::string, ANode> *getTable(void) { return NULL; }
	virtual std::vector<ANode>			 *getArray(void) { return NULL; }
	virtual bool						 *getBool(void) { return NULL; }
	virtual std::string					 *getString(void) { return NULL; }
	virtual int16_t						 *getInt(void) { return NULL; }

	//		is func
	virtual valueType_t type(void) const { return EMPTY; }
};

} // namespace toml
