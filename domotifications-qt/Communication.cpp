/**
 * @file Communication.cpp
 *
 * @brief Définition de la classe Communication
 * @author Mathieu MOYAERTS
 * @version 0.1
 */

#include "Communication.h"

Communication::Communication(QObject* parent) :
    QObject(parent), identifiant(""), motDePasse(""), httpPort(PORT_HTTP)
{
}

Communication::~Communication()
{
}

void Communication::envoyerNotification()
{
}

void Communication::recevoirNotification()
{
}

void Communication::configurer(QString identifiant, QString motDePasse, int httpPort)
{
}

void Communication::connecter()
{
}
