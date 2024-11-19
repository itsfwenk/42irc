#pragma once
#ifndef UTILS_HPP
# define UTILS_HPP

// Couleurs
# define RED "\e[31m"
# define GREEN "\e[32m"
# define YELLOW "\e[33m"
# define BLUE "\e[34m"
# define PURPLE "\e[35m"
# define CYAN "\e[36m"
# define WHITE "\e[0m"
# define END_COLOR "\e[0m"
# define BOLD "\e[1m"

// Erreurs IRC
# define RPL_WELCOME            "001" // Bienvenue sur le serveur
# define RPL_YOURHOST           "002" // Informations sur l'hôte
# define RPL_CREATED            "003" // Date de création du serveur
# define RPL_MYINFO             "004" // Informations générales sur le serveur
# define ERR_NOSUCHNICK         "401" // Aucun utilisateur trouvé
# define ERR_NOSUCHSERVER       "402" // Aucun serveur trouvé
# define ERR_NOSUCHCHANNEL      "403" // Aucun canal trouvé
# define ERR_CANNOTSENDTOCHAN   "404" // Impossible d'envoyer vers ce canal
# define ERR_TOOMANYCHANNELS    "405" // Trop de canaux rejoints
# define ERR_UNKNOWNCOMMAND     "421" // Commande inconnue
# define ERR_NONICKNAMEGIVEN    "431" // Aucun pseudonyme fourni
# define ERR_ERRONEUSNICKNAME   "432" // Pseudonyme incorrect
# define ERR_NICKNAMEINUSE      "433" // Pseudonyme déjà utilisé
# define ERR_USERNOTINCHANNEL   "441" // Utilisateur non présent dans le canal
# define ERR_NOTONCHANNEL       "442" // Non présent sur le canal
# define ERR_USERONCHANNEL      "443" // Utilisateur déjà sur le canal
# define ERR_NOTREGISTERED      "451" // Utilisateur non enregistré
# define ERR_NEEDMOREPARAMS     "461" // Paramètres insuffisants
# define ERR_ALREADYREGISTERED  "462" // Déjà enregistré
# define ERR_PASSWDMISMATCH     "464" // Mot de passe incorrect
# define ERR_CHANNELISFULL      "471" // channel full
# define ERR_CHANOPRIVSNEEDED   "482" // client attempted to perform an action that requires channel operator privileges
# define ERR_NOOPERHOST         "491" // Aucun hôte d'opérateur disponible
# define ERR_UMODEUNKNOWNFLAG   "501" // Mode utilisateur inconnu
# define ERR_USERSDONTMATCH     "502" // Tentative d'une opération interdite

# include <iostream>
# include <string>
# include <stdlib.h>
# include <ifaddrs.h>
# include <arpa/inet.h>
# include <poll.h>

# include "RPN.hpp"

class Channel;
class Client;

// ft_convert.cpp
int ft_get_converted_port(std::string port);

// ft_formatmessage.cpp
std::string ft_formatmessage(std::string code, std::string message, Client* client);
std::string ft_formatmessage(std::string code, std::string message, Client* client, Channel* channel);

// ft_print.cpp
void ft_print_logo(void);
void ft_print_message(std::string msg, std::string color);
void ft_print_success(std::string success);
void ft_print_info(std::string info);
void ft_print_warning(std::string warning);
void ft_print_error(std::string error);

// ft_setsockopts.cpp
void ft_setsockopts(int sockfd);

#endif
