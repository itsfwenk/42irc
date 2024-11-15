#pragma once
#ifndef COMMAND_HPP
# define COMMAND_HPP

# include <vector>
# include "utils.hpp"

class Client;
class Command {
	private:
		std::string 	_name;
		int				_minargs;
		bool			_opcmd;
		bool			_mustbelogged;

	public:
		Command(std::string name, int minargs, bool opcmd, bool mustbelogged);
		virtual ~Command(void);

		// Getters
		std::string const& getName(void);
		int const& getMinArgs(void);
		bool const& isOpCMD(void);
		bool const& mustBeLogged(void);

		// Run
		virtual void run(Client& client, std::vector<std::string> params) = 0;
};

# include "Client.hpp"

#endif
