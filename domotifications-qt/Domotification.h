#ifndef DOMOTIFICATION_H
#define DOMOTIFICATION_H

#include <QObject>
#include <QString>
#include <QMap>

#include "Constantes.h"
#include "Module.h"

class Communication;
class IHMDomotifications;

class Domotification : public QObject
{
    Q_OBJECT
  private:
    QMap<QString, Module*> modules;
    Communication*         communication;
    IHMDomotifications*    ihm;

  public:
    Domotification(IHMDomotifications* ihm = nullptr);
    ~Domotification();

    bool getActivationModule(QString nomModule);
    void gererNotification(QString nomModule);
    void ajouterModule(QString nomModule, Module::TypeModule type);
    void notifier(QString message);

  signals:
    void nouvelleNotification(QString message);

  public slots:
    void gererActivationModule(QString nomModule);
};

#endif // DOMOTIFICATION_H
