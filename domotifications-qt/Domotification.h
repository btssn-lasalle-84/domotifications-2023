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

#define NON_TROUVE -1

class Module;
class Communication;
class IHMDomotifications;

class Domotification : public QObject
{
    Q_OBJECT
  private:
    QVector<Module*>    modules;
    Communication*      communication;
    IHMDomotifications* ihm;

  public:
    Domotification(IHMDomotifications* ihm = nullptr);
    ~Domotification();

    int              recupererIndexModule(QString typeModule, int id = 0);
    bool             getActivationModule(QString typeModule, int id = 0);
    void             gererNotification(QString nomModule);
    void             ajouterModule(QString nomModule, Module::TypeModule type);
    void             notifier(QString message);
    QVector<Module*> getPoubelles() const;
    QVector<Module*> getMachines() const;
    Module*          getBoite() const;
    void             chargerModules();

  signals:
    void nouvelleNotification(QString message);

  public slots:
    void gererActivationModule(QString typeModule, int id);
};

#endif // DOMOTIFICATION_H
