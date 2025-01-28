/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjoly <adjoly@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:42:10 by adjoly            #+#    #+#             */
/*   Updated: 2025/01/27 21:40:34 by adjoly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ANode.hpp"
#include "vector"
#include <vector>

class Array : public ANode {
  public:
	Array(void);
	~Array(void);

	std::vector<ANode> *getArray(void) { return _vec; }
	bool				isArray(void) const { return true; }
	valueType_t			type(void) const { return _type; }
	bool				isHomogeneous() const;

  protected:
  private:
	std::vector<ANode> *_vec;

	const valueType_t _type;
};
