#pragma once
#ifndef BOT_HPP
# define BOT_HPP

# include "Command.hpp"

class BOT : public Command {
	public:
		BOT(void);
		virtual ~BOT(void);

		virtual void run(Client* client, Channel* channel, std::vector<std::string> params);
};

#endif
