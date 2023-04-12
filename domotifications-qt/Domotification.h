#ifndef DOMOTIFICATION_H
#define DOMOTIFICATION_H

#include <QObject>
#include <QString>
#include <QMap>

#include "Constantes.h"
#include "Module.h"
#include "Communication.h"

class Communication;

class Domotification : public QObject
{
    Q_OBJECT
  private:
    QMap<QString, Module*> modules;
    Communication*         reseau;

  public:
    Domotification(QObject* parent = nullptr);
    ~Domotification();

    void gererNotification(QString nomModule, bool etatActivation);
    void ajouterModule(QString nomModule, Module::TypeModule type);
    void notifier(QString message);

  signals:
    void nouvelleNotification(QString message);

  public slots:
    void gererActivationModule();
};

#endif // DOMOTIFICATION_H
