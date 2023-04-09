/**
 * @file StationLumineuse.cpp
 * @brief Définition de la classe StationLumineuse
 * @author Alexis Vaillen
 * @version 0.1
 */

#include "StationLumineuse.h"

StationLumineuse::StationLumineuse() : leds(NB_LEDS, PIN_BANDEAU, NEO_GRB + NEO_KHZ800)
{
}

void StationLumineuse::initialiserPreferences()
{
    preferences.begin("eeprom", false); // false pour r/w
    etatBoiteAuxLettres = preferences.getBool("boite", false);
    char cle[64]        = "";
    for(int i = 0; i < NB_LEDS_NOTIFICATION_MACHINES; ++i)
    {
        // machine0, machine1, etc..
        sprintf((char*)cle, "%s%d", "machine", i);
        etatMachines[i] = preferences.getBool(cle, false);
    }
    for(int i = 0; i < NB_LEDS_NOTIFICATION_POUBELLES; ++i)
    {
        // poubelle0, poubelle1, etc..
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
     * Allumer/Eteindre les leds de notifications à partir des états
     * sauvegardés
     */
    if(etatBoiteAuxLettres)
    {
        allumerNotificationBoiteAuxLettres();
    }
    else
    {
        eteindreNotificationBoiteAuxLettres();
    }

    for(int i = 0; i < NB_LEDS_NOTIFICATION_MACHINES; i++)
    {
        if(etatMachines[i])
        {
            allumerNotificationMachine(i);
        }
        else
        {
            eteindreNotificationMachine(i);
        }
    }

    for(int i = 0; i < NB_LEDS_NOTIFICATION_POUBELLES; i++)
    {
        if(etatPoubelles[i])
        {
            allumerNotificationPoubelle(i);
        }
        else
        {
            eteindreNotificationPoubelle(i);
        }
    }
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
         *  Définir des constantes pour les couleurs
         */
        leds.setPixelColor(i, leds.Color(255, 0, 0));
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

bool StationLumineuse::estIdValideMachine(int numeroMachine)
{
    return (numeroMachine >= 0 && numeroMachine < NB_LEDS_NOTIFICATION_MACHINES);
}

bool StationLumineuse::getEtatMachine(int numeroMachine)
{
    if(estIdValideMachine(numeroMachine))
    {
        return etatMachines[numeroMachine];
    }
    else
    {
        return false;
    }
}

void StationLumineuse::setEtatMachine(int numeroMachine, bool etat)
{
    if(!estIdValideMachine(numeroMachine))
        return;
    etatMachines[numeroMachine] = etat;
    char cle[64]                = "";
    sprintf((char*)cle, "%s%d", "machine", numeroMachine);
    preferences.putBool(cle, etatMachines[numeroMachine]);
    if(etat)
    {
        allumerNotificationMachine(numeroMachine);
    }
    else
    {
        eteindreNotificationMachine(numeroMachine);
    }
}

void StationLumineuse::resetEtatMachines()
{
}

void StationLumineuse::allumerNotificationMachine(int numeroMachine)
{
}

void StationLumineuse::allumerNotificationMachines()
{
    for(int i = INDEX_LEDS_NOTIFICATION_MACHINES;
        i < (INDEX_LEDS_NOTIFICATION_MACHINES + NB_LEDS_NOTIFICATION_MACHINES);
        ++i)
    {
        /**
         * Définir des constantes pour les couleurs
         */
        leds.setPixelColor(i, leds.Color(0, 255, 0));
        leds.show();
    }
}

void StationLumineuse::eteindreNotificationMachine(int numeroMachine)
{
}

void StationLumineuse::eteindreNotificationMachines()
{
    for(int i = INDEX_LEDS_NOTIFICATION_MACHINES;
        i < (INDEX_LEDS_NOTIFICATION_MACHINES + NB_LEDS_NOTIFICATION_MACHINES);
        ++i)
    {
        /**
         * @todo Définir des constantes pour les couleurs
         */
        leds.setPixelColor(i, leds.Color(0, 0, 0));
        leds.show();
    }
}

bool StationLumineuse::estIdValidePoubelle(int id)
{
    return false;
}

bool StationLumineuse::getEtatPoubelle(int numeroPoubelle)
{
    return false;
}

void StationLumineuse::setEtatPoubelle(int numeroPoubelles, bool etat)
{
}

void StationLumineuse::resetEtatPoubelles()
{
}

void StationLumineuse::allumerNotificationPoubelle(int numeroPoubelle)
{
}

void StationLumineuse::allumerNotificationPoubelles()
{
}

void StationLumineuse::eteindreNotificationPoubelle(int numeroPoubelle)
{
}

void StationLumineuse::eteindreNotificationPoubelles()
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
        leds.setPixelColor(i, leds.Color(255, 0, 0));
        leds.show();
    }
    delay(1000);
}

void StationLumineuse::testerMachines()
{
    for(int i = INDEX_LEDS_NOTIFICATION_machines;
        i < (INDEX_LEDS_NOTIFICATION_machines + NB_LEDS_NOTIFICATION_machines);
        ++i)
    {
        leds.setPixelColor(i, leds.Color(0, 255, 0)); // RGB
        leds.show();
        delay(1000);
    }
}

void StationLumineuse::testerPoubelles()
{
    for(int i = INDEX_LEDS_NOTIFICATION_POUBELLES;
        i < (INDEX_LEDS_NOTIFICATION_POUBELLES + NB_LEDS_NOTIFICATION_POUBELLES);
        ++i)
    {
        leds.setPixelColor(i, leds.Color(0, 255, 0)); // RGB vert
        leds.show();
        delay(1000);
        leds.setPixelcolor(in leds.Color(255, 0, 0)); // rouge
        leds.show();
        delay(1000);
        leds.setPixelcolor(in leds.Color(0, 0, 255)); // bleu
        leds.show();
        delay(1000);
        leds.setPixelColor(i, leds.Color(128, 128, 128)); // gris
        leds.show();
        delay(1000);
        leds.setPixelColor(i, leds.Color(255, 255, 0)); // jaune
        leds.show();
        delay(1000);
    }
}
#endif
