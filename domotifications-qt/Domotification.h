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
#include <QTimer>

#include "Constantes.h"
#include "Module.h"

// Pour définir la création initiale de modules
#define SIMULATION_MODULES

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
    QTimer*             minuteurRecuperationNotifications;

  public:
    Domotification(IHMDomotifications* ihm = nullptr);
    ~Domotification();

    int              recupererIndexModule(QString typeModule, int id = 0);
    bool             getActivationModule(QString typeModule, int id = 0);
    bool             getNotificationModule(QString typeModule, int id);
    void             ajouterModule(QString nomModule, Module::TypeModule type);
    void             notifier(QString message);
    QVector<Module*> getPoubelles() const;
    QVector<Module*> getMachines() const;
    Module*          getBoite() const;
    void             chargerModules();
    void             initialiserRecuperationNotifications();

  signals:
    void nouvelleNotification(QString message);

  public slots:
    void gererAcquittement(QString typeModule, int id);
    void gererActivationModule(QString typeModule, int id);
    void gererNotifications(QVector<bool> machines, QVector<bool> poubelles, bool boite);
};

#endif // DOMOTIFICATION_H
