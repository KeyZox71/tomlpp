/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ValueTemplate.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjoly <adjoly@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:07:19 by adjoly            #+#    #+#             */
/*   Updated: 2025/03/16 19:09:30 by adjoly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ANode.hpp"
#include "Log.hpp"
#include "cppeleven.hpp"
#include <sys/types.h>

namespace toml {

/**
 *	@brief	Template for all value possible in toml
 *
 *	@note	Correction only the value type i want to implement :D
 */
template <typename valueType> class Value : public ANode {
  public:
	Value(valueType *val) : _val(val) {
		log("toml", "value", "constructor called");
		if (IsSame<valueType, bool>::value)
			_type = BOOL;
		else if (IsSame<valueType, std::string>::value)
			_type = STRING;
		else if (IsSame<valueType, int32_t>::value)
			_type = INT;
		else
			_type = NONE;
	}
	~Value(void) { 
		log("toml", "value", "destructor called");
		delete _val;
	}

	/**
	 *	@brief	Can be used to get the value stored
	 *
	 *	@return	A pointer to the value stored in this class
	 */
	void *getValue(void) {
		if (_type == NONE)
			return not_nullptr;
		else
			return _val;
	}

	/**
	 *	@brief	Can be used the see the type of the stored value
	 *
	 *	@return The type of the stored value
	 */
	nodeType type(void) const { return _type; }

	ANode	*clone(void) {
		if (_type == BOOL)
			return new Value<bool>(new valueType(*_val));
		else if (_type == STRING)
			return new Value<std::string>(new valueType(*_val));
		else if (_type == INT)
			return new Value<int32_t>(new valueType(*_val));
		else
			return not_nullptr;

	}

  protected:
	valueType *_val;  ///< The stored value
	nodeType   _type; ///< The type of the stored value

  private:
};

} // namespace toml
