#ifndef SRC_PARSER_PARSEERROR_H_
#define SRC_PARSER_PARSEERROR_H_

#include <stdexcept>

class ParseError : public std::runtime_error {
public:
	ParseError() throw(): std::runtime_error("") {}

	char const* what() const throw() {
		return std::runtime_error::what();
	}
};

#endif /* SRC_PARSER_PARSEERROR_H_ */
