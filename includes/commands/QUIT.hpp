#pragma once
#ifndef QUIT_HPP
# define QUIT_HPP

# include "Command.hpp"

class QUIT : public Command {
	public:
		QUIT(void);
		virtual ~QUIT(void);

		virtual void run(Client* client, Channel* channel, std::vector<std::string> params);
};

#endif
