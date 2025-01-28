/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Log.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjoly <adjoly@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:35:36 by adjoly            #+#    #+#             */
/*   Updated: 2025/01/27 17:35:44 by adjoly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Log.hpp"
void	log(std::string emoji, std::string what, std::string who, std::string str) {
#ifdef VERBOSE
	if (who.empty())
		std::cout << "「" << emoji << "」" << what << ": " << str << std::endl;
	else
		std::cout << "「" << emoji << "」" << what << "(" << who << "): " << str << std::endl;
#else
	(void)emoji, (void)what, (void)who, (void)str;
#endif
}

