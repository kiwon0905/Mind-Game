#pragma once
#include <SFML/System.hpp>

enum Packet: sf::Int32
{
	Accept,
	Decline,
	Game
};

template <typename Enum>
typename std::enable_if<std::is_enum<Enum>::value, sf::Packet&>::type
operator<< (sf::Packet& packet, Enum t)
{
	return packet << static_cast<typename std::underlying_type<Enum>::type>(t);
}

template <typename Enum>
typename std::enable_if<std::is_enum<Enum>::value, sf::Packet&>::type
operator>> (sf::Packet& packet, Enum & t)
{
	typename std::underlying_type<Enum>::type i;
	packet >> i;
	t = static_cast<Enum>(i);
	return packet;
}