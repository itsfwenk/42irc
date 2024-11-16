#pragma once
#ifndef CAP_HPP
# define CAP_HPP

# include "Command.hpp"

class CAP : public Command {
	public:
		CAP(void);
		virtual ~CAP(void);

		virtual void run(Client* client, std::vector<std::string> params);
};

#endif
