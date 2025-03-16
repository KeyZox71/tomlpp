/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjoly <adjoly@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:42:10 by adjoly            #+#    #+#             */
/*   Updated: 2025/03/16 19:16:57 by adjoly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ANode.hpp"
#include "Log.hpp"
#include "node/default.hpp"
#include <vector>

namespace toml {

/**
 *	@brief	A class (derived from ANode) that contains a toml array
 */
class Array : public ANode {
  public:
	Array(void) { log("toml", "array", "default constructor called"); }
	Array(std::vector<ANode *> *vec) {
		log("toml", "array", "constructor called");
		_vec = vec;
	}
	~Array(void) {
		for (std::vector<ANode *>::iterator it = _vec->begin();
			 it != _vec->end(); it++) {
			delete *it;
		}
		delete _vec;
		log("toml", "array", "destructor called");
	}

	/**
	 *	@brief	Can be used to get the stored array
	 *
	 *	@return	Pointer to the stored array
	 */
	std::vector<ANode *> *getArray(void) { return _vec; }
	/**
	 *	@brief	Can be used to get the type of the stored value(in this case
	 *ARRAY)
	 */
	nodeType type(void) const { return ARRAY; }

	/**
	 *	@brief	can be used to push back into the vector of the array
	 *
	 *	@param	the val that will be added
	 */
	void push_back(ANode *val) { _vec->push_back(val); }

	/**
	 *	@brief	can be used to clone the array
	 *
	 *	@return	a pointer to the newly cloned array
	 */
	ANode *clone(void) {
		std::vector<ANode *>::iterator it = _vec->begin();

		std::vector<ANode *> *newVec = new std::vector<ANode *>;
		for (; it != _vec->end(); it++) {
			if ((*it)->type() == BOOL) {
				newVec->push_back(
					new Value<bool>(new bool(*(bool *)(*it)->getValue())));
			} else if ((*it)->type() == STRING) {
				newVec->push_back(
					new Value<std::string>(new std::string(*(std::string *)(*it)->getValue())));
			} else if ((*it)->type() == INT) {
				newVec->push_back(
					new Value<int32_t>(new int32_t(*(int32_t *)(*it)->getValue())));
			}
		}
		return new Array(newVec);
	}

  protected:
  private:
	std::vector<ANode *> *_vec; ///< vector of the stored array
};

} // namespace toml
