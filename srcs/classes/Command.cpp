#include "Command.hpp"

Command::Command(std::string name, int minargs, bool opcmd, bool mustbelogged): _name(name), _minargs(minargs), _opcmd(opcmd), _mustbelogged(mustbelogged) {
	ft_print_info("Command " + name + " loaded!");
};

Command::~Command(void) {};

// Getters
std::string const& Command::getName(void) {
	return this->_name;
};

int const& Command::getMinArgs(void) {
	return this->_minargs;
};

bool const& Command::isOpCMD(void) {
	return this->_opcmd;
};

bool const& Command::mustBeLogged(void) {
	return this->_mustbelogged;
};
