#pragma once
#ifndef CAP_HPP
# define CAP_HPP

# include "Command.hpp"

class CAP : public Command {
	public:
		CAP(void);
		virtual ~CAP(void);

		virtual void run(Client* client, Channel* channel, std::vector<std::string> params);
};

#endif
