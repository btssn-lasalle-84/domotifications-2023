#include "Module.h"

Module::Module(QObject* parent) :
    QObject(parent), nomModule(""), typeModule(TypeModule::Inconnu),
    estActive(false), estNotifie(false)
{
}

Module::~Module()
{
}
