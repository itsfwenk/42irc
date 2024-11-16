#include "Command.hpp"

Command::Command(std::string name, int reqargs, bool opcmd, bool mustbelogged, bool insidechannel): _name(name), _reqargs(reqargs), _opcmd(opcmd), _mustbelogged(mustbelogged), _insidechannel(insidechannel) {
	ft_print_info("Command " + name + " loaded!");
};

Command::~Command(void) {};

// Getters
std::string const& Command::getName(void) {
	return this->_name;
};

int const& Command::getReqArgs(void) {
	return this->_reqargs;
};

bool const& Command::isOpCMD(void) {
	return this->_opcmd;
};

bool const& Command::mustBeLogged(void) {
	return this->_mustbelogged;
};

bool const& Command::insideChannel(void) {
	return this->_insidechannel;
};
