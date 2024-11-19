#pragma once
#ifndef JOIN_HPP
#define JOIN_HPP

# include "Command.hpp"

class JOIN : public Command {
public:
	JOIN(void);
	virtual ~JOIN(void);

	virtual void run(Client* client, Channel* channel, std::vector<std::string> params);
};

#endif
