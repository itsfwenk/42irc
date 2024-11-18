#pragma once
#ifndef PING_HPP
# define PING_HPP

# include "Command.hpp"

class PING : public Command {
	public:
		PING(void);
		virtual ~PING(void);

		virtual void run(Client* client, Channel* channel, std::vector<std::string> params);
};

#endif
