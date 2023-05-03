/**
 * @file Module.cpp
 *
 * @brief Définition de la classe Module
 * @author Mathieu MOYAERTS
 * @version 0.2
 */

#include "Module.h"
#include <QDebug>

Module::Module(QString nomModule, Module::TypeModule type, QObject* parent) :
    QObject(parent), id(0), nomModule(nomModule), typeModule(type), actif(true), notifie(false)
{
    qDebug() << Q_FUNC_INFO << "id" << id << "nomModule" << nomModule << "TypeModule" << typeModule;
}

Module::~Module()
{
    qDebug() << Q_FUNC_INFO << "id" << id << "nomModule" << nomModule << "TypeModule" << typeModule;
}

int Module::getId() const
{
    return id;
}

Module::TypeModule Module::getType() const
{
    return typeModule;
}

bool Module::estActif() const
{
    return actif;
}

bool Module::estNotifie() const
{
    return notifie;
}

void Module::setActif(bool actif)
{
    this->actif = actif;
}

/**
 * @brief Récupère le nom du type de module à utiliser dans une requête HTTP
 * @param type le type de module
 * @return QString le nom du type à utiliser dans une requête HTTP
 */
QString Module::getType(Module::TypeModule type)
{

    switch(type)
    {
        case Module::TypeModule::Machine:
            return QString("machine");
            break;
        case Module::TypeModule::Poubelle:
            return QString("Poubelle");
        break;
    case Module::TypeModule::BoiteAuxLettres:
        return QString("Boite Aux Lettres");
        default:
            return QString();
            break;
    }
}
