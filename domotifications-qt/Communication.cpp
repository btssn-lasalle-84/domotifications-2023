/**
 * @file Communication.cpp
 *
 * @brief Définition de la classe Communication
 * @author Mathieu MOYAERTS
 * @version 0.2
 */

#include "Communication.h"

Communication::Communication(QObject* parent) :
    QObject(parent), accesReseau(new QNetworkAccessManager(this)), httpPort(PORT_HTTP)
{
    qDebug() << Q_FUNC_INFO;
    connect(accesReseau,
            SIGNAL(finished(QNetworkReply*)),
            this,
            SLOT(traiterReponseStation(QNetworkReply*)));
}

Communication::~Communication()
{
    qDebug() << Q_FUNC_INFO;
}

/**
 * @brief Envoie une requete http avec la méthode POST
 * @fn Communication::envoyerRequetePost
 * @param api le type de requête
 * @param json les données au format JSON envoyées via la requête
 */
void Communication::envoyerRequetePost(QString api, const QByteArray& json)
{
    QNetworkRequest requetePost;
    QUrl            url(URL_STATION + api);
    requetePost.setUrl(url);
    requetePost.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    requetePost.setRawHeader("Content-Type", "application/json");
    requetePost.setRawHeader("Content-Length", QByteArray::number(json.size()));
    qDebug() << Q_FUNC_INFO << "url" << url << "json" << json;
#ifndef SANS_STATION
    accesReseau->post(requetePost, json);
#endif
}

/**
 * @brief Slot qui envoie la requête avec la méthode GET pour récupérer les notifications
 * @fn Communication::recevoirNotifications
 */
void Communication::recupererNotifications()
{
    QString api = "notifications";

    traiterReponseStation(reponseReseau);
}

/**
 * @brief Slot qui traite les réponses renvoyées par la station
 * @fn Communication::traiterReponseStation
 */
void Communication::traiterReponseStation(QNetworkReply* reponseReseau)
{
    qDebug() << Q_FUNC_INFO << "reponse" << reponseReseau;
}
