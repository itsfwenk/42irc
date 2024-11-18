#pragma once
#ifndef KICK_HPP
# define KICK_HPP

# include "Command.hpp"

class KICK : public Command {
	public:
		KICK(void);
		virtual ~KICK(void);

		virtual void run(Client* client, Channel* channel, std::vector<std::string> params);
};

#endif
