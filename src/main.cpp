#include "cppeleven.hpp"
#include "node/ANode.hpp"
#include <stdexcept>
#include <tomlpp.hpp>

int main(void) {
	toml::Toml file("test.toml");

	toml::ANode *node = file.getParsedFile();

	if (node->getTable() == not_nullptr ) {
		throw std::runtime_error("nique tes mort");
	}
	if ((*(node->getTable()))["hola"] == not_nullptr ) {
		throw std::runtime_error("je vais me suicider");
	}

	//std::cout << *(std::string *)(*node->getTable())["hola"]->getValue() << std::endl;

	//std::cout << "test = " << content << std::endl;
	delete node;
}
