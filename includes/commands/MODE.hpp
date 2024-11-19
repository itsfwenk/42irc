#pragma once
#ifndef MODE_HPP
# define MODE_HPP

# include "Command.hpp"

class MODE : public Command {
	public:
	MODE(void);
	virtual ~MODE(void);

	virtual void run(Client* client, Channel* channel, std::vector<std::string> params);
};

#endif
