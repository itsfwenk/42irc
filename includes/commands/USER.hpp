#pragma once
#ifndef USER_HPP
# define USER_HPP

# include "Command.hpp"

class USER : public Command {
	public:
		USER(void);
		virtual ~USER(void);

		virtual void run(Client* client, Channel* channel, std::vector<std::string> params);
};

#endif
