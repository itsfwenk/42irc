#pragma once
#ifndef COMMAND_HPP
# define COMMAND_HPP

# include <vector>
# include "utils.hpp"

class Channel;
class Client;
class Command {
	private:
		std::string 	_name;
		int				_reqargs;
		bool			_opcmd;
		bool			_mustbelogged;
		bool			_insidechannel;

	public:
		Command(std::string name, int reqargs, bool opcmd, bool mustbelogged, bool insidechannel);
		virtual ~Command(void);

		// Getters
		std::string const& getName(void);
		int const& getReqArgs(void);
		bool const& isOpCMD(void);
		bool const& mustBeLogged(void);
		bool const& insideChannel(void);

		// Run
		virtual void run(Client* client, Channel* channel, std::vector<std::string> params) = 0;
};

# include "Channel.hpp"
# include "Client.hpp"

#endif
