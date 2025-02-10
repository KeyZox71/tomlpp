/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjoly <adjoly@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:08:20 by adjoly            #+#    #+#             */
/*   Updated: 2025/02/10 16:03:28 by adjoly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/tokenizer.hpp"

namespace toml {
namespace parser {
class parse {
  public:
	parse(std::string);
	~parse(void);

  protected:
  private:
	ANode				 _convertToken(std::string);
	tokenizer::Tokenizer _tokenizer;
};
} // namespace parser
} // namespace toml
