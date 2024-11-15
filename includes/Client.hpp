#pragma once
#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <sstream>
# include "utils.hpp"

class Client {
	private:
		int 			_id;
		std::string		_messageData;

	public:
		Client(int id);

		// Getters
		int const& getID(void);

		// Setters
		void parseMessageData(std::string messageData);
};

#endif
