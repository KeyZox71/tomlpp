/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ValueTemplate.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjoly <adjoly@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:07:19 by adjoly            #+#    #+#             */
/*   Updated: 2025/02/10 15:17:59 by adjoly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Log.hpp"
#include "node/ANode.hpp"
#include <sys/types.h>
#include <typeinfo>

namespace toml {

template <typename valueType> class Value : public ANode {
  public:
	Value(valueType);
	~Value(void);

	bool		*getBool(void);
	std::string *getString(void);
	int16_t		*getInt(void);
	double		*getFloat(void);

	valueType_t type(void) const;

  protected:
	valueType  *_val;
	valueType_t _type;

  private:
};

template <typename valueType>
Value<valueType>::Value(valueType val) : _val(&val) {
	log("tomlValue", "", "constructor called");
	if (typeid(valueType) == typeid(bool))
		_type = BOOL;
	else if (typeid(valueType) == typeid(std::string))
		_type = STRING;
	else if (typeid(valueType) == typeid(int16_t))
		_type = INT;
	else if (typeid(valueType) == typeid(double))
		_type = FLOAT;
	else
		_type = EMPTY;
}

template <typename valueType> Value<valueType>::~Value(void) {
	log("tomlValue", "", "destructor called");
	delete _val;
}

template <typename valueType> bool *Value<valueType>::getBool(void) {
	if (typeid(valueType) == typeid(bool))
		return _val;
	else
		return NULL;
}

template <typename valueType> std::string *Value<valueType>::getString(void) {
	if (typeid(valueType) == typeid(std::string))
		return _val;
	else
		return NULL;
}

template <typename valueType> int16_t *Value<valueType>::getInt(void) {
	if (typeid(valueType) == typeid(int16_t))
		return _val;
	else
		return NULL;
}

template <typename valueType> double *Value<valueType>::getFloat(void) {
	if (typeid(valueType) == typeid(double))
		return _val;
	else
		return NULL;
}

template <typename valueType> valueType_t Value<valueType>::type(void) const {
	return _type;
}

} // namespace toml
