#ifndef DOMOTIFICATION_H
#define DOMOTIFICATION_H

/**
 * @file Domotification.h
 *
 * @brief Déclaration de la classe Domotification
 * @author Mathieu MOYAERTS
 * @version 0.2
 */

#include <QObject>
#include <QString>
#include <QVector>

#include "Constantes.h"
#include "Module.h"

class Module;
class Communication;
class IHMDomotifications;

class Domotification : public QObject
{
    Q_OBJECT
  private:
    QVector<Module*>       modules;
    Communication*         communication;
    IHMDomotifications*    ihm;

  public:
    Domotification(IHMDomotifications* ihm = nullptr);
    ~Domotification();

    bool getActivationModule(QString nomModule);
    void gererNotification(QString nomModule);
    void ajouterModule(QString nomModule, Module::TypeModule type);
    void notifier(QString message);
    QVector<Module*> getMachines() const ;
    QVector<Module*> getPoubelles() const;
    Module* getBoite() const;

  signals:
    void nouvelleNotification(QString message);

  public slots:
    void gererActivationModule(QString nomModule);
};

#endif // DOMOTIFICATION_H
