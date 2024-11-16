#pragma once
#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "utils.hpp"

class Channel {
	private:
		int _id;
		std::string _name;

	public:
		int const& getID(void);
		std::string const& getName(void);
};

#endif
