#ifndef COMMUNICATION_H
#define COMMUNICATION_H

class Communication : public QObject
{
    Q_OBJECT

  private:
    QString identifiant;
    QString motDePasse;
    int     httpPort;

  public:
    Communication::Communication(QWidget* parent = nullptr);
    ~Communication();
    void connecter();
    void envoyerNotification();
    void recevoirNotification();
    void configurer(QString identifiant, QString motDePasse, int httpPort);
};

#endif // COMMUNICATION_H
