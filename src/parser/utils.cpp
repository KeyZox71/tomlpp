/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjoly <adjoly@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:13:44 by adjoly            #+#    #+#             */
/*   Updated: 2025/02/02 13:33:13 by adjoly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>

bool checkForTripleQuote(std::string str, size_t index) {
   if (!str[index] || !str[index + 1] || !str[index + 2]) {
   	return false;
   } else if (str[index] == '\'' && str[index + 1] == '\'' &&
   		   str[index + 2] == '\'') {
   	return true;
   } else if (str[index] == '"' && str[index + 1] == '"' &&
   		   str[index + 2] == '"') {
   	return true;
   } else {
   	return false;
   }
}

std::string	getStr(std::string &_file, size_t _fileIndex) {
	size_t	start;

	start = _fileIndex;
	while (_file[_fileIndex] && !isspace(_file[_fileIndex])) {
		_fileIndex++;
	}
	return _file.substr(start, _fileIndex - start);
}

std::string getQuotedString(std::string _file, size_t index) {
}

std::string	getKeyString(std::string _file, size_t index) {

}
