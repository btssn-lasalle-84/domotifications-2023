#ifndef DOMOTIFICATION_H
#define DOMOTIFICATION_H

#include <QObject>
#include <QString>
#include <QMap>

#include "Module.h"

class Domotification : public QObject
{
    Q_OBJECT
  private:
    QMap<QString, Module*> modules;

  public:
    Domotification(QObject* parent = nullptr);
    ~Domotification();
    void gererActivationModule(QString nomModule, bool etatActivation);
    void gererNotification(QString nomModule, bool etatActivation);
    void ajouterModule(QString nomModule, Module::TypeModule type);
    void notifier(QString message);

  signals:
    void nouvelleNotification(QString message);
};

#endif // DOMOTIFICATION_H
