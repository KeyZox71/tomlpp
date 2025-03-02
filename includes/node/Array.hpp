/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjoly <adjoly@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:42:10 by adjoly            #+#    #+#             */
/*   Updated: 2025/02/28 09:03:07 by adjoly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ANode.hpp"
#include "Log.hpp"
#include <vector>

namespace toml {

/**
 *	@brief	A class (derived from ANode) that contains a toml array
 */
class Array : public ANode {
  public:
	Array(std::vector<ANode> *vec) {
		log("toml", "array", "constructor called");
		_vec = vec;
	}
	~Array(void) { log("toml", "array", "destructor called"); }

	/**
	 *	@brief	Can be used to get the stored array
	 *
	 *	@return	Pointer to the stored array
	 */
	std::vector<ANode> *getArray(void) { return _vec; }
	/**
	 *	@brief	Can be used to get the type of the stored value(in this case
	 *ARRAY)
	 */
	nodeType type(void) const { return ARRAY; }

  protected:
  private:
	std::vector<ANode> *_vec; ///< vector of the stored array
};

} // namespace toml
