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

#include "Constantes.h"

class Communication : public QObject
{
    Q_OBJECT

  private:
    QNetworkAccessManager* accesReseau;
    QNetworkReply*         reponseReseau;
    QString                urlStation;
    int                    httpPort;
    QString                requeteJSON;

  public:
    Communication(QObject* parent = nullptr);
    ~Communication();

    void envoyerRequetePost(QString api, const QByteArray& json);

  public slots:
    void recupererNotifications();
    void traiterReponseStation(QNetworkReply* reponse);

  signals:
    void etatsNotifications(QVector<bool> machines, QVector<bool> poubelles, bool boite);
};

#endif // COMMUNICATION_H
