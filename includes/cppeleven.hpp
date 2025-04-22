/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cppeleven.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjoly <adjoly@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 08:19:14 by adjoly            #+#    #+#             */
/*   Updated: 2025/04/22 11:43:11 by adjoly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 *	@brief	Just a random file to emulate cpp 11 behavior in cpp98 because 42
 *			has no fun
 */
#pragma once

/**
 *	@brief	IsSame in cpp98 ;D
 */
template <typename T, typename U> struct IsSame {
	static const bool value = false;
};

template <typename T> struct IsSame<T, T> {
	static const bool value = true;
};

#if __cplusplus == 199711L

#define auto __auto_type

#ifndef range
#define range(x) x.begin(); it != x.end(); it++
#endif
#ifndef prange
#define prange(x) x->begin(); it != x->end(); it++
#endif

#undef nullptr

/**
 * @brief Emulating nullptr for C++98
 */
struct nullptr_t {
	template <typename T> operator T *() const { return 0; }

	template <typename C, typename T> operator T C::*() const { return 0; }

  private:
	// Prevent taking the address of nullptr
	void operator&() const;
};

const nullptr_t not_nullptr = {};

#define nullptr not_nullptr

#else
#define not_nullptr nullptr

#endif
