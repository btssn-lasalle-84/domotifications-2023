#include "StationLumineuse.h"

StationLumineuse::StationLumineuse() :
    leds(NB_LEDS, PIN_BANDEAU, NEO_GRB + NEO_KHZ800)
{
}

void StationLumineuse::initialiserPreferences()
{
    preferences.begin("eeprom", false); // false pour r/w
    etatBoiteAuxLettres = preferences.getBool("boite", false);
    char cle[64]        = "";
    for(int i = 0; i < NB_LEDS_NOTIFICATION_MACHINES; ++i)
    {
        sprintf((char*)cle, "%s%d", "machine", i);
        etatMachines[i] = preferences.getBool(cle, false);
    }
    for(int i = 0; i < NB_LEDS_NOTIFICATION_POUBELLES; ++i)
    {
        sprintf((char*)cle, "%s%d", "poubelle", i);
        etatPoubelles[i] = preferences.getBool(cle, false);
    }
}

void StationLumineuse::initialiserNotifications()
{
    leds.begin();
    leds.clear();

#ifdef TEST_BANDEAU
    testerBoiteAuxLettres();
    testerMachines();
    testerPoubelles();
#endif

    /**
     * @todo Allumer/Eteindre les leds de notifications à partir des états
     * sauvegardés
     */
}

bool StationLumineuse::getEtatBoiteAuxLettres()
{
    return etatBoiteAuxLettres;
}

void StationLumineuse::setEtatBoiteAuxLettres(bool etat)
{
    etatBoiteAuxLettres = etat;
    preferences.putBool("boite", etatBoiteAuxLettres);
    if(etat)
    {
        allumerNotificationBoiteAuxLettres();
    }
    else
    {
        eteindreNotificationBoiteAuxLettres();
    }
}

void StationLumineuse::resetEtatBoiteAuxLettres()
{
    etatBoiteAuxLettres = false;
    preferences.putBool("boite", etatBoiteAuxLettres);
    eteindreNotificationBoiteAuxLettres();
}

void StationLumineuse::allumerNotificationBoiteAuxLettres()
{
    for(int i = INDEX_LEDS_NOTIFICATION_BOITE;
        i < (INDEX_LEDS_NOTIFICATION_BOITE + NB_LEDS_NOTIFICATION_BOITE);
        ++i)
    {
        /**
         * @todo Définir des constantes pour les couleurs
         */
        leds.setPixelColor(i, leds.Color(150, 0, 0));
        leds.show();
    }
}

void StationLumineuse::eteindreNotificationBoiteAuxLettres()
{
    for(int i = INDEX_LEDS_NOTIFICATION_BOITE;
        i < (INDEX_LEDS_NOTIFICATION_BOITE + NB_LEDS_NOTIFICATION_BOITE);
        ++i)
    {
        /**
         * @todo Définir des constantes pour les couleurs
         */
        leds.setPixelColor(i, leds.Color(0, 0, 0));
        leds.show();
    }
}

bool StationLumineuse::estIdValideMachine(int id)
{
    return false;
}

bool StationLumineuse::getEtatMachine(int numeroMachine)
{
    return false;
}

void StationLumineuse::setEtatMachine(int numeroMachine, bool etat)
{
}

void StationLumineuse::setEtatMachines()
{
}

void StationLumineuse::resetEtatMachines()
{
}

void StationLumineuse::allumerNotificationMachine(int numeroMachine)
{
}

void StationLumineuse::eteindreNotificationMachine(int numeroMachine)
{
}

void StationLumineuse::allumerNotificationMachines()
{
}

void StationLumineuse::eteindreNotificationMachines()
{
}

bool StationLumineuse::estIdValidePoubelle(int id)
{
    return false;
}

bool StationLumineuse::getEtatPoubelle(int numeroPoubelle)
{
    return false;
}

void StationLumineuse::setEtatPoubelle(int numeroPoubelle, bool etat)
{
}

void StationLumineuse::setEtatPoubelle()
{
}

void StationLumineuse::resetEtatPoubelle()
{
}

void StationLumineuse::allumerNotificationPoubelle(int numeroPoubelle)
{
}

void StationLumineuse::eteindreNotificationPoubelle(int numeroPoubelle)
{
}

void StationLumineuse::allumerNotificationPoubelle()
{
}

void StationLumineuse::eteindreNotificationPoubelle()
{
}

#ifdef TEST_BANDEAU
// Fonctions de test
void StationLumineuse::testerBoiteAuxLettres()
{
    for(int i = INDEX_LEDS_NOTIFICATION_BOITE;
        i < (INDEX_LEDS_NOTIFICATION_BOITE + NB_LEDS_NOTIFICATION_BOITE);
        ++i)
    {
        leds.setPixelColor(i, leds.Color(150, 150, 0));
        leds.show();
    }
    delay(1000);
}

void StationLumineuse::testerMachines()
{
    for(int i = INDEX_LEDS_NOTIFICATION_MACHINES;
        i < (INDEX_LEDS_NOTIFICATION_MACHINES + NB_LEDS_NOTIFICATION_MACHINES);
        ++i)
    {
        leds.setPixelColor(i, leds.Color(0, 150, 0)); // RGB
        leds.show();
        delay(1000);
    }
}

void StationLumineuse::testerPoubelles()
{
    /**
     * @todo Idm pour les leds des poubelles
     */
}
#endif
