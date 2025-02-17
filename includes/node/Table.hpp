/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Table.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjoly <adjoly@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:42:10 by adjoly            #+#    #+#             */
/*   Updated: 2025/02/14 10:26:34 by adjoly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ANode.hpp"
#include "Log.hpp"
#include <map>

namespace toml {

class Table : public ANode {
  public:
	Table(std::map<std::string, ANode>);
	~Table(void);

	std::map<std::string, ANode> *getTable(void) { return _map; }
	bool						  isTable(void) const { return true; }
	valueType_t					  type(void) const { return _type; }

  protected:
  private:
	std::map<std::string, ANode> *_map;

	const valueType_t _type;
};

Table::Table(std::map<std::string, ANode> map) : _type(TABLE) {
	log("tomlTable", "", "constructor called");
	_map = &map;
}

Table::~Table(void) {
	log("tomlTable", "", "destructor called");
}

} // namespace toml
