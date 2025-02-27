/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Log.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjoly <adjoly@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:36:21 by adjoly            #+#    #+#             */
/*   Updated: 2025/02/27 12:35:00 by adjoly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>

/**
 *	@brief	Used to log debug message
 *
 *	@note	Only work
 */
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
/**
 *	@brief	Used to log warning message
 */
void logWarning(std::string what, std::string who, std::string str) {
	if (who.empty())
		std::cout << what << ": " << str << std::endl;
	else
		std::cout << what << "(" << who << "): " << str << std::endl;
}
