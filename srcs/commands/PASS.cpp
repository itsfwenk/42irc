#include "PASS.hpp"

PASS::PASS(void): Command("PASS", 1, false, false) {};
PASS::~PASS(void) {};

void PASS::run(Client& client, std::vector<std::string> params) {
	(void)client;
	(void)params;
};
