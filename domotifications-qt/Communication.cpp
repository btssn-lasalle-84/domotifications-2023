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
    QUrl            url = this->urlStation.resolved(QUrl(api));
    requetePost.setUrl(url);
    requetePost.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    requetePost.setRawHeader("Content-Type", "application/json");
    requetePost.setRawHeader("Content-Length", QByteArray::number(json.size()));
    qDebug() << Q_FUNC_INFO << "url" << url << "json" << json;
    requeteApi = api;
#ifndef SANS_STATION
    accesReseau->post(requetePost, json);
#endif
}

/**
 * @brief Retourne l'URL de la station
 * @fn Communication::getUrlStation
 * @return QString
 */
QUrl Communication::getUrlStation()
{
    return this->urlStation;
}

/**
 * @brief Modifie l'URL de la station
 * @fn Communication::setUrlStation
 * @param urlStation
 */
void Communication::setUrlStation(QUrl urlStation)
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
    QNetworkRequest requeteGet;
    QUrl            url = this->urlStation.resolved(QUrl(api));
    requeteGet.setUrl(url);
    // requeteGet.setHeader(QNetworkRequest::ContentTypeHeader,
    // "application/x-www-form-urlencoded");
    // requeteGet.setRawHeader("Content-Type", "application/json");
    qDebug() << Q_FUNC_INFO << "url" << url;
    requeteApi = api;
#ifndef SANS_STATION
    reponseReseau = accesReseau->get(requeteGet);
#endif
}

/**
 * @brief Slot qui traite les réponses renvoyées par la station
 * @fn Communication::traiterReponseStation
 */
void Communication::traiterReponseStation(QNetworkReply* reponseStation)
{
    QByteArray donneesReponse = reponseStation->readAll();
    qDebug() << Q_FUNC_INFO << "donneesReponse" << donneesReponse;

    /*
     {
        "boite":true,
        "machines":[false,false,false,false,false,false],
        "poubelles":[false,false,false,false,false]
     }
     */

    QJsonDocument documentJson = QJsonDocument::fromJson(donneesReponse);
    QJsonObject   objetJson    = documentJson.object();

    if(objetJson.contains("boite") && objetJson.contains("machines") &&
       objetJson.contains("poubelles"))
    {
        QJsonArray    etatsPoubelles = objetJson["poubelles"].toArray();
        QVector<bool> poubelles;
        for(int i = 0; i < etatsPoubelles.size(); ++i)
        {
            poubelles.push_back(etatsPoubelles.at(i).toBool());
        }
        qDebug() << Q_FUNC_INFO << "poubelles" << poubelles;

        QJsonArray    etatsMachines = objetJson["machines"].toArray();
        QVector<bool> machines;
        for(int i = 0; i < etatsMachines.size(); i++)
        {
            machines.push_back(etatsMachines.at(i).toBool());
        }
        qDebug() << Q_FUNC_INFO << "machines" << machines;

        bool boite = objetJson["boite"].toBool();

        qDebug() << Q_FUNC_INFO << "boite" << boite;

        if(requeteApi == "notifications")
        {
            emit etatsNotifications(machines, poubelles, boite);
            requeteApi.clear();
        }
        else if(requeteApi == "activations")
        {
            // emit etatsActivations(machines, poubelles, boite);
            requeteApi.clear();
        }
    }
}
