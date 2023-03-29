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
