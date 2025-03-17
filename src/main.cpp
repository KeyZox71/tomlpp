#include "node/ANode.hpp"
#include "tomlpp.hpp"

int main() {
	toml::Toml testFile = toml::Toml("test.toml");

	toml::ANode *test = testFile.getParsedFile();

	delete test;
	return 0;
}
