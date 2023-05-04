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
    modules.push_back(new Module("Machine à laver", Module::TypeModule::Machine, 0, this));
    modules.push_back(new Module("Lave-vaisselle", Module::TypeModule::Machine, 1, this));
    // 2 poubelles (0..5)
    modules.push_back(new Module("Poubelle", Module::TypeModule::Poubelle, 0, this));
    modules.push_back(new Module("Poubelle", Module::TypeModule::Poubelle, 1, this));
    // 1 boite (0..1)
    modules.push_back(new Module("BoiteAuxLettres", Module::TypeModule::BoiteAuxLettres, 0, this));
}

Domotification::~Domotification()
{
    qDebug() << Q_FUNC_INFO;
}

// Slots

void Domotification::gererActivationModule(QString nomModule)
{
    qDebug() << Q_FUNC_INFO << "nomModule" << nomModule;
    for(auto i = 0 ; i < modules.size() ; ++i)
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

// Méthodes

bool Domotification::getActivationModule(QString nomModule)
{
    for(int i = 0 ; i < modules.size() ; ++i)
    {
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
    Module::TypeModule typeModule;
    QVector<Module*> machines;
    for(auto i = 0 ; i < modules.size() ; i++)
    {
        if(typeModule == Module::Machine)
        {
            machines.append(modules);
        }
    }
    return machines;
}

QVector<Module*> Domotification::getPoubelles() const
{
    Module::TypeModule typeModule;
     QVector<Module*> poubelles;
     for(auto i = 0 ; i < modules.size() ; i++)
     {
         if(typeModule == Module::Poubelle)
         {
             poubelles.append(modules);
         }
     }
     return poubelles;
}

Module* Domotification::getBoite() const
{
    Module* boite;
    Module::TypeModule typeModule;
    for(auto i = 0 ; i < modules.size() ; i++)
    {
        if(typeModule == Module::BoiteAuxLettres)
        {
            return boite;
        }
    }
}

