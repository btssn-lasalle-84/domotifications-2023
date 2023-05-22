/**
 * @file Communication.cpp
 *
 * @brief Définition de la classe Communication
 * @author Mathieu MOYAERTS
 * @version 0.2
 */

#include "Communication.h"

Communication::Communication(QObject* parent) :
    QObject(parent), identifiant(""), motDePasse(""), httpPort(PORT_HTTP),
    accesReseau(new QNetworkAccessManager(this))
{
    qDebug() << Q_FUNC_INFO;
}

Communication::~Communication()
{
    qDebug() << Q_FUNC_INFO;
}

void Communication::connecter()
{
}

/**
 * @brief Envoie une requete http avec la méthode Post
 * @fn Communication::envoyerRequetePost
 * @param api le type de requête
 * @param json les données au format JSON envoyées via la requête
 */
void Communication::envoyerRequetePost(QString api, const QByteArray& json)
{
    api = "activation";
    QUrl url(URL_STATION + api);
    qDebug() << Q_FUNC_INFO << "url" << url.toString();
    qDebug() << Q_FUNC_INFO << "json" << json;
    QNetworkRequest requetePost;
    requetePost.setUrl(url);
    requetePost.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    requetePost.setRawHeader("Content-Type", "application/json");
    requetePost.setRawHeader("Content-Length", QByteArray::number(json.size()));
#ifndef SANS_STATION
    qDebug() << Q_FUNC_INFO << url << json;
    accesReseau->post(requetePost, json);
#endif
}

void Communication::recevoirNotification()
{
}

void Communication::configurer(QString identifiant, QString motDePasse, int httpPort)
{
}
