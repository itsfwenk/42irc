#pragma once
#ifndef INVITE_HPP
# define INVITE_HPP

# include "Command.hpp"

class INVITE : public Command {
	public:
		INVITE(void);
		virtual ~INVITE(void);

		virtual void run(Client* client, Channel* channel, std::vector<std::string> params);
};

#endif
