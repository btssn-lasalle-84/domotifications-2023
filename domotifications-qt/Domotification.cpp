/**
 * @file Domotification.cpp
 *
 * @brief Définition de la classe Domotification
 * @author Mathieu MOYAERTS
 * @version 0.2
 */
#include "Domotification.h"
#include "Communication.h"
#include "IhmDomotifications.h"
#include <QDebug>

Domotification::Domotification(IHMDomotifications* ihm) :
    QObject(ihm), communication(new Communication(this)), ihm(ihm)
{
    qDebug() << Q_FUNC_INFO;
    /**
     * @todo Gérer un fichier de configuration INI pour les modules
     */
    // Pour les tests : 5 modules
    // 2 machines (0..6)
    modules.push_back(new Module("Machine", Module::TypeModule::Machine, 0, this));
    modules.push_back(new Module("Machine", Module::TypeModule::Machine, 1, this));
    // 2 poubelles (0..5)
    modules.push_back(new Module("Poubelle", Module::TypeModule::Poubelle, 0, this));
    modules.push_back(new Module("Poubelle", Module::TypeModule::Poubelle, 1, this));
    // 1 boite (0..1)
    modules.push_back(new Module("BoiteAuxLettres", Module::TypeModule::BoiteAuxLettres, 0, this));
    qDebug() << Q_FUNC_INFO << "modules" << modules;
}

Domotification::~Domotification()
{
    qDebug() << Q_FUNC_INFO;
}

// Slots

void Domotification::gererActivationModule(QString nomModule, int id)
{
    qDebug() << Q_FUNC_INFO << "nomModule" << nomModule << "id" << id;
    for(auto i = 0; i < modules.size(); ++i)
    {
        if(modules[i]->getNom() == nomModule && modules[i]->getId() == id)
        {
            modules[i]->setActif(!modules[i]->estActif());
            // Exemple
            QByteArray json = "{";
            json += "\"id\":" + QString::number(modules[i]->getId()) + QString(",");
            if(modules[i]->estActif())
                json += "\"etat\":true";
            else
                json += "\"etat\":false";
            json += "}";
            communication->envoyerRequetePost(Module::getType(modules[i]->getType()), json);
        }
    }
}

// Méthodes

bool Domotification::getActivationModule(QString nomModule, int id)
{
    qDebug() << Q_FUNC_INFO << "nomModule" << nomModule << "id" << id;
    for(int i = 0; i < modules.size(); ++i)
    {
        if(modules[i]->getNom() == nomModule && modules[i]->getId() == id)
            return modules[i]->estActif();
    }
    return false;
}
void Domotification::gererNotification(QString nomModule)
{
    qDebug() << Q_FUNC_INFO << "nomModule" << nomModule;
}

void Domotification::ajouterModule(QString nomModule, Module::TypeModule type)
{
    qDebug() << Q_FUNC_INFO << "nomModule" << nomModule << "TypeModule" << type;
}

void Domotification::notifier(QString message)
{
    qDebug() << Q_FUNC_INFO << "message" << message;
    emit nouvelleNotification(message);
}

QVector<Module*> Domotification::getMachines() const
{
    QVector<Module*> machines;
    for(auto i = 0; i < modules.size(); i++)
    {
        if(modules[i]->getType() == Module::Machine)
        {
            qDebug() << Q_FUNC_INFO << "module" << modules[i]->getNom() << "id"
                     << modules[i]->getId();
            machines.push_back(modules[i]);
        }
    }
    return machines;
}

QVector<Module*> Domotification::getPoubelles() const
{
    QVector<Module*> poubelles;
    for(auto i = 0; i < modules.size(); i++)
    {
        if(modules[i]->getType() == Module::Poubelle)
        {
            qDebug() << Q_FUNC_INFO << "module" << modules[i]->getNom() << "id"
                     << modules[i]->getId();
            poubelles.push_back(modules[i]);
        }
    }
    return poubelles;
}

Module* Domotification::getBoite() const
{
    for(auto i = 0; i < modules.size(); i++)
    {
        if(modules[i]->getType() == Module::BoiteAuxLettres)
        {
            return modules[i];
        }
    }
    return nullptr;
}
