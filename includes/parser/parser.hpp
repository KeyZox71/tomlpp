/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjoly <adjoly@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:08:20 by adjoly            #+#    #+#             */
/*   Updated: 2025/02/21 07:37:08 by adjoly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "node/ANode.hpp"
#include "parser/tokenizer.hpp"

namespace toml {
namespace parser {

class parse {
  public:
	parse(std::string);
	~parse(void);

	ANode	getNode(void);

  protected:
  private:
	ANode				 _convertValue(std::string);
	tokenizer::Tokenizer _tokenizer;
};

} // namespace parser
} // namespace toml
