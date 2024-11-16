#pragma once
#ifndef NICK_HPP
# define NICK_HPP

# include "Command.hpp"

class NICK : public Command {
	public:
		NICK(void);
		virtual ~NICK(void);

		virtual void run(Client* client, std::vector<std::string> params);
};

#endif
