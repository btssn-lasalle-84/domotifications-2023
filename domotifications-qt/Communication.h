#ifndef COMMUNICATION_H
#define COMMUNICATION_H

/**
 * @file Communication.h
 *
 * @brief Déclaration de la classe Communication
 * @author Mathieu MOYAERTS
 * @version 0.2
 */

#include <QObject>
#include <QString>
#include <QtNetwork/QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "Constantes.h"
#include "Domotification.h"

class Domotification;

class Communication : public QObject
{
    Q_OBJECT

  private:
    Domotification*        domotification;
    QNetworkAccessManager* accesReseau;
    QNetworkReply*         reponseReseau;
    QUrl                   urlStation;
    int                    httpPort;
    QString                requeteApi;

  public:
    Communication(QObject* parent = nullptr);
    ~Communication();

    void envoyerRequetePost(QString api, const QByteArray& json);
    QUrl getUrlStation();
    void setUrlStation(QUrl urlStation);

  public slots:
    void recupererNotifications();
    void traiterReponseStation(QNetworkReply* reponse);

  signals:
    void etatsNotifications(QVector<bool> machines, QVector<bool> poubelles, bool boite);
};

#endif // COMMUNICATION_H
