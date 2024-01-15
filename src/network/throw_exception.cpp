#include "boost/throw_exception.hpp"

#include <iostream>

namespace boost {
	void throw_exception(std::exception const& e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	void throw_exception(std::exception const&, boost::source_location const& loc) {
		std::cout << "Exception: " << loc.file_name() << ":" << loc.line() << std::endl;
	}
};