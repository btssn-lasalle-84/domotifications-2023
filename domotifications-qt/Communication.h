#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <QObject>
#include <QString>

/**
 * @def PORT_HTTP
 * @brief Définit le port par défaut pour HTTP
 */
#define PORT_HTTP 80

class Communication : public QObject
{
    Q_OBJECT

  private:
    QString identifiant;
    QString motDePasse;
    int     httpPort;

  public:
    Communication(QObject* parent = nullptr);
    ~Communication();
    void connecter();
    void envoyerNotification();
    void recevoirNotification();
    void configurer(QString identifiant, QString motDePasse, int httpPort);
};

#endif // COMMUNICATION_H
