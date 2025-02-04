/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjoly <adjoly@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:32:45 by adjoly            #+#    #+#             */
/*   Updated: 2025/02/04 12:41:52 by adjoly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>

bool		checkForTripleQuote(std::string, size_t &);
std::string getStr(std::string, size_t &);
std::string getQuotedString(std::string, size_t &);
std::string getTableString(std::string, size_t &);
