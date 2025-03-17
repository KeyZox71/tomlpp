#include "cppeleven.hpp"
#include "node/ANode.hpp"
#include "tomlpp.hpp"
#include <stdexcept>


toml::Toml *getParsedFile(void) {
	try {
		toml::Toml *test = new toml::Toml("test.toml");
		return test;
	} catch (std::runtime_error &e) {
		std::cerr << e.what() << std::endl;
		return not_nullptr;
	}
}

int main() {
	toml::Toml *test = getParsedFile();
	if (test == not_nullptr) {
		return 1;
	}

	toml::ANode *uwu = test->getParsedFile();

	delete uwu;
	delete test;

	return 0;
}
