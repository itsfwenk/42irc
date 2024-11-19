#pragma once
#ifndef TOPIC_HPP
# define TOPIC_HPP

# include "Command.hpp"

class TOPIC : public Command {
	public:
	TOPIC(void);
	virtual ~TOPIC(void);

	virtual void run(Client* client, Channel* channel, std::vector<std::string> params);
};

#endif
