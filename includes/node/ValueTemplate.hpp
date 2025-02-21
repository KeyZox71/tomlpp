/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ValueTemplate.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjoly <adjoly@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:07:19 by adjoly            #+#    #+#             */
/*   Updated: 2025/02/21 18:15:14 by adjoly           ###   ########.fr       */
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

	void *getValue(void);

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

template <typename valueType> void	*Value<valueType>::getValue(void) {
	if (_type == EMPTY)
		return not_nullptr;
	else
		return _val;
}

template <typename valueType> valueType_t Value<valueType>::type(void) const {
	return _type;
}

} // namespace toml
