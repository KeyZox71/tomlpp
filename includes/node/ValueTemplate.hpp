/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ValueTemplate.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjoly <adjoly@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:07:19 by adjoly            #+#    #+#             */
/*   Updated: 2025/02/21 09:09:00 by adjoly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Log.hpp"
#include "cppeleven.hpp"
#include "node/ANode.hpp"
#include <sys/types.h>

namespace toml {

template <typename valueType> class Value : public ANode {
  public:
	Value(valueType);
	~Value(void);

	bool		*getBool(void);
	std::string	*getString(void);
	int16_t		*getInt(void);

	valueType_t type(void) const;

  protected:
	valueType  *_val;
	valueType_t _type;

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
		_type = EMPTY;
}

template <typename valueType> Value<valueType>::~Value(void) {
	log("tomlValue", "", "destructor called");
	delete _val;
}

template <typename valueType> bool *Value<valueType>::getBool(void) {
	if (IsSame<valueType, bool>::value)
		return _val;
	else
		return __nullptr;
}

template <typename valueType> std::string *Value<valueType>::getString(void) {
	if (IsSame<valueType, std::string>::value)
		return _val;
	else
		return ;
}

template <typename valueType> int16_t *Value<valueType>::getInt(void) {
	if (IsSame<valueType, int16_t>::value)
		return _val;
	else
		return NULL;
}

template <typename valueType> valueType_t Value<valueType>::type(void) const {
	return _type;
}

} // namespace toml
