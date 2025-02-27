/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ValueTemplate.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjoly <adjoly@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:07:19 by adjoly            #+#    #+#             */
/*   Updated: 2025/02/27 11:12:09 by adjoly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Log.hpp"
#include "cppeleven.hpp"
#include "ANode.hpp"
#include <sys/types.h>

namespace toml {

/**
 *	@brief	Template for all value possible in toml
 *
 *	@note	Correction only the value type i want to implement :D
 */
template <typename valueType> class Value : public ANode {
  public:
	Value(valueType);
	~Value(void);

	/**
	 *	@brief	Can be used to get the value stored
	 *
	 *	@return	A pointer to the value stored in this class
	 */
	void *getValue(void);

	/**
	 *	@brief	Can be used the see the type of the stored value
	 *
	 *	@return The type of the stored value
	 */
	nodeType type(void) const;

  protected:
	valueType *_val;
	nodeType   _type;

  private:
};

template <typename valueType>
Value<valueType>::Value(valueType val) : _val(&val) {
	log("tomlValue", "", "constructor called");
	if (IsSame<valueType, bool>::value)
		_type = BOOL;
	else if (IsSame<valueType, std::string>::value)
		_type = STRING;
	else if (IsSame<valueType, int16_t>::value)
		_type = INT;
	else
		_type = NONE;
}

template <typename valueType> Value<valueType>::~Value(void) {
	log("tomlValue", "", "destructor called");
	delete _val;
}

template <typename valueType> void *Value<valueType>::getValue(void) {
	if (_type == NONE)
		return not_nullptr;
	else
		return _val;
}

template <typename valueType> nodeType Value<valueType>::type(void) const {
	return _type;
}

} // namespace toml
