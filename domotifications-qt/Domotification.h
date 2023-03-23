#ifndef DOMOTIFICATION_H
#define DOMOTIFICATION_H

class Domotification : public QObject
{
    Q_OBJECT
  private:
    vector<string> notifications;
    QString        module;

  public:
    Domotification::Domotification(QWidget* parent = nullptr);
    ~Domotification();
    void gererActivationModule(QString nomModule, bool etatActivation);
    void gererNotification(QString nomModule, bool etatActivation);
    void ajouterModule(QString nomModule, TypeModule type);
};

#endif // DOMOTIFICATION_H
