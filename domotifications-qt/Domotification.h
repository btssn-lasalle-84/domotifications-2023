#ifndef DOMOTIFICATION_H
#define DOMOTIFICATION_H

#include <QObject>
#include <QString>
#include <QMap>
#include <QPushButton>

#include "Module.h"
#include "IhmDomotifications.h"

class IHMDomotifications;

class Domotification : public QObject
{
    Q_OBJECT
  private:
    QMap<QString, Module*> modules;
    IHMDomotifications*    ihmDomotification;
    QPushButton*           boutonNotifier;
    QWidget*               widget;
    QLineEdit*             notification;

  public:
    Domotification(QObject* parent = nullptr);
    ~Domotification();
    void gererActivationModule(QString nomModule, bool etatActivation);
    void gererNotification(QString nomModule, bool etatActivation);
    void ajouterModule(QString nomModule, Module::TypeModule type);
};

#endif // DOMOTIFICATION_H
