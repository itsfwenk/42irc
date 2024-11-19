#pragma once
#ifndef WHOIS_HPP
# define WHOIS_HPP

# include "Command.hpp"

class WHOIS : public Command {
	public:
		WHOIS(void);
		virtual ~WHOIS(void);

		virtual void run(Client* client, Channel* channel, std::vector<std::string> params);
};

#endif
