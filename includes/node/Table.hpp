/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Table.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjoly <adjoly@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:42:10 by adjoly            #+#    #+#             */
/*   Updated: 2025/01/27 21:08:57 by adjoly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ANode.hpp"
#include <map>

class Table : public ANode {
  public:
	Table(void);
	~Table(void);

	std::map<std::string, ANode> *getTable(void) { return _map; }
	bool						  isTable(void) const { return true; }
	valueType_t					  type(void) const { return _type; }

  protected:
  private:
	std::map<std::string, ANode> *_map;

	const valueType_t _type;
};
