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
    QString                identifiant;
    QString                motDePasse;
    int                    httpPort;
    QNetworkAccessManager* accesReseau;
    QNetworkReply*         reponseReseau;
    QString                urlStation;
    QString                requeteJSON;

  public:
    Communication(QObject* parent = nullptr);
    ~Communication();
    void connecter();
    void envoyerRequetePost(QString api, const QByteArray& json);
    void recevoirNotification();
    void configurer(QString identifiant, QString motDePasse, int httpPort);
};

#endif // COMMUNICATION_H
