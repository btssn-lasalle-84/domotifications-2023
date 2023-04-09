/**
 * @file Module.cpp
 *
 * @brief Définition de la classe Module
 * @author Mathieu MOYAERTS
 * @version 0.1
 */

#include "Module.h"

Module::Module(QObject* parent) :
    QObject(parent), nomModule(""), typeModule(TypeModule::Inconnu), estActive(false),
    estNotifie(false)
{
}

Module::~Module()
{
}
