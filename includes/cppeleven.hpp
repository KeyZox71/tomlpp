/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cppeleven.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjoly <adjoly@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 08:19:14 by adjoly            #+#    #+#             */
/*   Updated: 2025/02/21 09:23:25 by adjoly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 *	@brief	Just a random file to emulate cpp 11 behavior in cpp98 because 42
 *has no fun
 */
#pragma once

#if __cplusplus == 199711L

/**
 *	@brief	IsSame in cpp98 ;D
 */
template <typename T, typename U> struct IsSame {
	static const bool value = false;
};

template <typename T> struct IsSame<T, T> {
	static const bool value = true;
};

/**
 * @brief Emulating nullptr for C++98
 */
const class {
  public:
	template <class T> operator T *() const { return 0; }

	template <class C, class T> operator T C::*() const { return 0; }

  private:
	void operator&() const;
} nullptr = {};

#endif
