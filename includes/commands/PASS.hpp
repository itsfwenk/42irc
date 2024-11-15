#pragma once
#ifndef PASS_HPP
# define PASS_HPP

# include "Command.hpp"

class PASS : public Command {
	public:
		PASS(void);
		virtual ~PASS(void);

		virtual void run(Client& client, std::vector<std::string> params);
};

#endif
