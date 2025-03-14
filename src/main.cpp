#include <tomlpp.hpp>

int main(void) {
	toml::Toml file("test.toml");

	toml::ANode *node = file.getParsedFile();

	void *content = (*node->getTable())["test"]->getValue();

	std::cout << "test = " << (std::string *)content << std::endl;
}
