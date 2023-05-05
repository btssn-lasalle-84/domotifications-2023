/**
 * @file Module.cpp
 *
 * @brief Définition de la classe Module
 * @author Mathieu MOYAERTS
 * @version 0.2
 */

#include "Module.h"
#include <QDebug>

/**
 * @brief Constructeur de la classe Module
 * @fn    Module::Module
 * @param nomModule
 * @param type
 * @param id
 * @param parent
 */
Module::Module(QString nomModule, Module::TypeModule type,  int id, QObject* parent) :
    QObject(parent), id(0), nomModule(nomModule), typeModule(type), actif(true), notifie(false)
{
    qDebug() << Q_FUNC_INFO << "id" << id << "nomModule" << nomModule << "TypeModule" << typeModule;
}

/**
 * @brief Destructeur de la classe Module
 * @fn Module::~Module
 *
 */
Module::~Module()
{
    qDebug() << Q_FUNC_INFO << "id" << id << "nomModule" << nomModule << "TypeModule" << typeModule;
}

/**
 * @brief retourn l'id du module
 * @fn Module::getId
 * @return entier : id
 */
int Module::getId() const
{
    return id;
}

/**
 * @brief Retourne le type du module
 * @fn Module::getType
 * @return un Type module d'un module
 */
Module::TypeModule Module::getType() const
{
    return typeModule;
}

/**
 * @brief Module::estActif
 * @return l'état du module
 */

bool Module::estActif() const
{
    return actif;
}

/**
 * @brief Module::estNotifie
 * @return si le module est notifié
 */
bool Module::estNotifie() const
{
    return notifie;
}

/**
 * @brief Module::setActif
 * @param actif
 */
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
            return QString("poubelle");
            break;
        case Module::TypeModule::BoiteAuxLettres:
            return QString("boite");
            break;
        default:
            return QString();
            break;
    }
}
