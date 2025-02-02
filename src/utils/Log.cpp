/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Log.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjoly <adjoly@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:35:36 by adjoly            #+#    #+#             */
/*   Updated: 2025/01/28 20:20:37 by adjoly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Log.hpp"

void log(std::string what, std::string who, std::string str) {
#ifdef VERBOSE
	if (who.empty())
		std::cout << what << ": " << str << std::endl;
	else
		std::cout << what << "(" << who << "): " << str << std::endl;
#else
	(void)what, (void)who, (void)str;
#endif
}

void logWarning(std::string what, std::string who, std::string str) {
	if (who.empty())
		std::cout << what << ": " << str << std::endl;
	else
		std::cout << what << "(" << who << "): " << str << std::endl;
}
