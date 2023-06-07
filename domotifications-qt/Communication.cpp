/**
 * @file Communication.cpp
 *
 * @brief Définition de la classe Communication
 * @author Mathieu MOYAERTS
 * @version 0.2
 */

#include "Communication.h"
#include <QNetworkReply>

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
    QUrl            url(urlStation + api);
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
 * @brief Retourne l'URL de la station
 * @fn Communication::getUrlStation
 * @return QString
 */
QString Communication::getUrlStation()
{
    return this->urlStation;
}

/**
 * @brief Modifie l'URL de la station
 * @fn Communication::se-tUrlStation
 * @param urlStation
 */
void Communication::setUrlStation(QString urlStation)
{
    this->urlStation = urlStation;
}

/**
 * @brief Slot qui envoie la requête avec la méthode GET pour récupérer les notifications
 * @fn Communication::recevoirNotifications
 */
void Communication::recupererNotifications()
{
    QString         api = "notifications";
    QNetworkRequest requetePost;
    QUrl            url(URL_STATION + api);
    requetePost.setUrl(url);
    requetePost.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    requetePost.setRawHeader("Content-Type", "application/json");
    qDebug() << Q_FUNC_INFO << "url" << url;
#ifndef SANS_STATION
    reponseReseau = accesReseau->get(requetePost);
#endif

    traiterReponseStation(reponseReseau);
}

/**
 * @brief Slot qui traite les réponses renvoyées par la station
 * @fn Communication::traiterReponseStation
 */
void Communication::traiterReponseStation(QNetworkReply* reponseStation)
{
    QByteArray donneesReponse = reponseStation->readAll();
    qDebug() << Q_FUNC_INFO << "donneesReponse" << donneesReponse;

    QJsonDocument jsonDocument = QJsonDocument::fromJson(donneesReponse);
    QJsonObject   jsonObject   = jsonDocument.object();

    bool boite = jsonObject["boite"].toBool();
    if(boite)
    {
        domotification->notifier(NOTIFICATION_BOITE);
    }

    QJsonArray machinesArray = jsonObject["machines"].toArray();
    for(int i = 0; i < machinesArray.size(); ++i)
    {
        bool machine = machinesArray.at(i).toBool();
        if(machine)
        {
            domotification->notifier(NOTIFICATION_MACHINE);
        }
    }

    QJsonArray poubellesArray = jsonObject["poubelles"].toArray();
    for(int i = 0; i < poubellesArray.size(); ++i)
    {
        bool poubelle = poubellesArray.at(i).toBool();
        if(poubelle)
        {
            switch(i)
            {
                case 0:
                    domotification->notifier(NOTIFICATION_POUBELLE_BLEUE);
                    break;
                case 1:
                    domotification->notifier(NOTIFICATION_POUBELLE_VERTE);
                    break;
                case 2:
                    domotification->notifier(NOTIFICATION_POUBELLE_JAUNE);
                    break;
                case 3:
                    domotification->notifier(NOTIFICATION_POUBELLE_ROUGE);
                    break;
                case 4:
                    domotification->notifier(NOTIFICATION_POUBELLE_GRISE);
                    break;
                default:
                    break;
            }
        }
    }
}
