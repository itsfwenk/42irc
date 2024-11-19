#pragma once
#ifndef PRIVMSG_HPP
# define PRIVMSG_HPP

# include "Command.hpp"

class PRIVMSG : public Command {
	public:
		PRIVMSG(void);
		virtual ~PRIVMSG(void);

		virtual void run(Client* client, Channel* channel, std::vector<std::string> params);
};

#endif
