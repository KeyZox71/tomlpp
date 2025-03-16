#include "cppeleven.hpp"
#include "node/ANode.hpp"
#include "node/default.hpp"
#include <stdexcept>
#include <tomlpp.hpp>
#include <vector>

int main(void) {
	toml::Toml file("test.toml");

	toml::ANode *node = file.getParsedFile();

	if (node->getTable() == not_nullptr ) {
		throw std::runtime_error("nique tes mort");
	}

	toml::ANode *test = (*node->getTable())["hola"];

	std::vector<toml::ANode *> *ff = test->getArray();

	for (std::vector<toml::ANode *>::iterator it = ff->begin(); it != ff->end(); it++) {
		std::cout << *(bool *)(*it.base())->getValue() << std::endl;
	}

	delete node;

}
