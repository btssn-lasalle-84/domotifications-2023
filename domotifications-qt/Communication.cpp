/**
 * @file Communication.cpp
 *
 * @brief Définition de la classe Communication
 * @author Mathieu MOYAERTS
 * @version 0.1
 */

#include "Communication.h"

Communication::Communication(QObject* parent) :
    QObject(parent), identifiant(""), motDePasse(""), httpPort(PORT_HTTP), accesReseau(new QNetworkAccessManager(this))
{
}

Communication::~Communication()
{

}
/**
 * @brief Envoie une requete http en Post à la boite aux lettres
 * @fn Communication::envoyerRequetePostBoiteAuxLettres
 * @details Slots qui va envoyer une requête HTTP en Post à l'émission du signal d'activation ou de desactivation du module
 */
void Communication::envoyerRequetePostBoiteAuxLettres()
{
    qDebug() << Q_FUNC_INFO;
    QUrl            url(URL);
    QNetworkRequest requetePostBoiteAuxLettres;
    requetePostBoiteAuxLettres.setUrl(url);
    requetePostBoiteAuxLettres.setHeader(QNetworkRequest::ContentTypeHeader,
                                         "application/x-www-form-urlencoded");
    QByteArray json = "{\"boite\":true}";
    requetePostBoiteAuxLettres.setRawHeader("Content-Type", "application/json");
    requetePostBoiteAuxLettres.setRawHeader("Content-Length", QByteArray::number(json.size()));

    accesReseau->post(requetePostBoiteAuxLettres, json);

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
