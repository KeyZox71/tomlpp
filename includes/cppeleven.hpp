/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cppeleven.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjoly <adjoly@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 08:19:14 by adjoly            #+#    #+#             */
/*   Updated: 2025/02/21 08:48:20 by adjoly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 *	@brief	Just a random file to emulate cpp 11 behavior in cpp98 because 42 has no fun
 */

#define auto(value) typeof(value)

template <typename T, typename U>
struct IsSame {
    static const bool value = false;
};

template <typename T>
struct IsSame<T, T> {
    static const bool value = true;
};

// Emulating nullptr for C++98
const class {
public:
    template <class T>
    operator T*() const { return 0; }

    template <class C, class T>
    operator T C::*() const { return 0; }

private:
    void operator&() const;  // Prevent taking address
} nullptr = {};
