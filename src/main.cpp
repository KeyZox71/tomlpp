#include "cppeleven.hpp"
#include "node/ANode.hpp"
#include "tomlpp.hpp"
#include <stdexcept>



int main() {
	toml::Toml test = toml::Toml("test.toml");

	try {
		test.parse();
	} catch (std::runtime_error &e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}

	toml::ANode *uwu = test.getParsedFile();

	delete uwu;

	return 0;
}
