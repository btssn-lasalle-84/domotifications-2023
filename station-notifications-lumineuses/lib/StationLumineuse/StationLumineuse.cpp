/**
 * @file StationLumineuse.cpp
 * @brief Définition de la classe StationLumineuse
 * @author Alexis Vaillen
 * @version 0.1
 */

#include "StationLumineuse.h"

/**
 * @brief Constructeur par défaut de la classe StationLumineuse
 * @fn StationLumineuse::StationLumineuse
 * @details Initialise les attributs de la classe avec des valeurs par défaut.
 */

StationLumineuse::StationLumineuse() : leds(NB_LEDS, PIN_BANDEAU, NEO_GRB + NEO_KHZ800)
{
}

/**
 * @brief Initialise les préférences de la station lumineuse
 * @fn StationLumineuse::initialiserPreferences
 * @details Charge les préférences depuis la mémoire EEPROM ou les valeurs par défaut si les préférences n'ont pas été définies
 */

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

/**
 * @brief Initialisation de l'état des notifications
 * @fn  StationLumineuse::initialiserNotifications
 * @details Allumer/Eteindre les leds de notifications à partir des états sauvegardés
 */

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

/**
 * @brief Obtient l'état de la boîte aux lettres
 * @fn StationLumineuse::getEtatBoiteAuxLettres
 * @details Obtient l'état actuel de la boîte aux lettres, vrai si elle est pleine, faux sinon
 * @return etatBoiteAuxLettres
 */

bool StationLumineuse::getEtatBoiteAuxLettres()
{
    return etatBoiteAuxLettres;
}

/**
 * @brief Modifie l'état de la boîte aux lettres
 * @fn StationLumineuse::setEtatBoiteAuxLettres
 * @details Modifie l'état actuel de la boîte aux lettres et allume ou éteint les leds en fonction de celui-ci
 * @param etat 
 */

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

/**
 * @brief Réinitialise l'état de la boîte aux lettres
 * @fn StationLumineuse::resetEtatBoiteAuxLettres
 * @details Change l'état de boite aux lettres en false et eteint les leds attribuer a celle-ci
 */

void StationLumineuse::resetEtatBoiteAuxLettres()
{
    etatBoiteAuxLettres = false;
    preferences.putBool("boite", etatBoiteAuxLettres);
    eteindreNotificationBoiteAuxLettres();
}

/**
 * @brief Allume la notification lumineuse de la boîte aux lettres
 * @fn void StationLumineuse::allumerNotificationBoiteAuxLettres
 * @details Allume les LEDS de couleur rouge pour indiquer que la boîte aux lettres et pleine
 */


void StationLumineuse::allumerNotificationBoiteAuxLettres()
{
    for(int i = INDEX_LEDS_NOTIFICATION_BOITE;
        i < (INDEX_LEDS_NOTIFICATION_BOITE + NB_LEDS_NOTIFICATION_BOITE);
        ++i)
    {
        leds.setPixelColor(i, leds.Color(255, 0, 0));
        leds.show();
    }
}

/**
 * @brief Eteint la notification lumineuse de la boîte aux lettres
 * @fn void StationLumineuse::eteindreNotificationBoiteAuxLettre
 * @details Allume les LEDS de couleur rouge pour indiquer que la boîte aux lettres et pleine
 */

void StationLumineuse::eteindreNotificationBoiteAuxLettres()
{
    for(int i = INDEX_LEDS_NOTIFICATION_BOITE;
        i < (INDEX_LEDS_NOTIFICATION_BOITE + NB_LEDS_NOTIFICATION_BOITE);
        ++i)
    {
        leds.setPixelColor(i, leds.Color(0, 0, 0));
        leds.show();
    }
}

/**
 * @brief Vérifie si l'ID de la machine est valide
 * @fn StationLumineuse::estIdValideMachines
 * @param numeroMachine
 * @return bool true si l'ID est valide sinon false
 * @details renvoie Vrai si l'ID de la machine est compris entre 1 et NB_MACHINES, faux sinon
 */

bool StationLumineuse::estIdValideMachine(int numeroMachine)
{
    return (numeroMachine >= 0 && numeroMachine < NB_LEDS_NOTIFICATION_MACHINES);
}

/**
 * @brief Récupère l'état de la machine donnée
 * @fn  StationLumineuse::getEtatMachines
 * @param numeromachines Numéro de la machine
 * @return etatmachines[numeromachines];
 * @details renvoie l'etat de la machine si l'id et valide , faux sinon
 */

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

/**
 * @brief Modifie l'état de la machine donnée
 * @fn StationLumineuse::setEtatMachines
 * @param numeromachines
 * @param etat
 * @details Modifie l'état de la machine spécifiée par le numéro donné. Enregistre l'état dans les préférences,
   et allume ou éteint la notification de la machine en fonction de son nouvel état.
 */

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

/**
 * @brief Réinitialise l'état de la machine donnée
 * @fn StationLumineuse::resetEtatMachines
 * @param numeromachines
 * @details Change l'état de la machine donnée en false et éteint la notification associée
 */

void StationLumineuse::resetEtatMachines()
{
}



void StationLumineuse::allumerNotificationMachine(int numeroMachine)
{
}

/**
 * @brief Allume la notification de la machine donnée
 * @fn StationLumineuse::allumerNotificationMachines
 * @param numeromachines
 * @details Allume les LEDs de couleur verte pour indiquer que la machine spécifiée est finit
 */

void StationLumineuse::allumerNotificationMachines()
{
    for(int i = INDEX_LEDS_NOTIFICATION_MACHINES;
        i < (INDEX_LEDS_NOTIFICATION_MACHINES + NB_LEDS_NOTIFICATION_MACHINES);
        ++i)
    {
        leds.setPixelColor(i, leds.Color(0, 255, 0));
        leds.show();
    }
}

void StationLumineuse::eteindreNotificationMachine(int numeroMachine)
{
}

/**
 * @brief Éteint la notification de la machine donnée
 * @fn StationLumineuse::eteindreNotificationMachines
 * @param numeromachines
 * @details Éteint les LEDS associées à la notification de la machine donnée en les mettant à la couleur noire (0,0,0)
 */

void StationLumineuse::eteindreNotificationMachines()
{
    for(int i = INDEX_LEDS_NOTIFICATION_MACHINES;
        i < (INDEX_LEDS_NOTIFICATION_MACHINES + NB_LEDS_NOTIFICATION_MACHINES);
        ++i)
    {
        leds.setPixelColor(i, leds.Color(0, 0, 0));
        leds.show();
    }
}

/**
 * @brief Vérifie si le numero de la poubelle est valide
 * @fn StationLumineuse::estIdValidePoubelle
 * @param numeroPoubelles
 * @return bool true si le numeroPoubelle est valide sinon false
 * @details renvoie Vrai si l'numeroPoubelle de la poubelle est compris entre 1 et NB_POUBELLES, faux sinon
 */

bool StationLumineuse::estIdValidePoubelle(int numeroPoubelles)
{
    return (numeroPoubelles >= 0 && numeroPoubelles< NB_LEDS_NOTIFICATION_POUBELLES);
}

/**
 * @brief Récupère l'état de la poubelle donnée
 * @fn  StationLumineuse::getEtatMachines
 * @param numeroPoubelles Numéro de la poubelle
 * @return etatPoubelles[numeroPoubelles];
 * @details renvoie l'etat de la machine si l'id et valide , faux sinon
 */

bool StationLumineuse::getEtatPoubelle(int numeroPoubelles)
{
        if(estIdValidePoubelle(numeroPoubelles))
    {
        return etatPoubelles[numeroPoubelles];
    }
    else
    {
        return false;
    }
}

/**
 * @brief Modifie l'état de la poubelle donnée
 * @fn StationLumineuse::setEtatPoubelle
 * @param numeroPoubelles
 * @param etat
 * @details Modifie l'état de la poubelle spécifiée par le numéro donné. Enregistre l'état dans les préférences,
   et allume ou éteint la notification de la poubelle en fonction de son nouvel état.
 */

void StationLumineuse::setEtatPoubelle(int numeroPoubelles, bool etat)
{
        if(!estIdValidePoubelle(numeroPoubelles))
        return;
    etatPoubelles[numeroPoubelles] = etat;
    char cle[64]                = "";
    sprintf((char*)cle, "%s%d", "poubelle", numeroPoubelles);
    preferences.putBool(cle, etatPoubelles[numeroPoubelles]);
    if(etat)
    {
        allumerNotificationMachine(numeroPoubelles);
    }
    else
    {
        eteindreNotificationMachine(numeroPoubelles);
    }
}

/**
 * @brief Réinitialise l'état de la poubelle donnée
 * @fn StationLumineuse::resetEtatPoubelles
 * @details Change l'état de la poubelle donnée en false et éteint la notification associée
 */

void StationLumineuse::resetEtatPoubelles()
{
}

/**
 * @brief Allume la notification de la poubelle donnée
 * @fn StationLumineuse::allumerNotificationPoubelle
 * @param numeroPoubelles
 * @details Allume les LEDS en fonction de la couleur correspond aux Poublles 0 ROUGE 1 VERT 2 BLEU 3 GRIS 4 JAUNE
   pour indiquer quelles poubelles sortir
 */

void StationLumineuse::allumerNotificationPoubelle(int numeroPoubelles)
{
    if (estIdValidePoubelle(numeroPoubelles))
    {
        etatPoubelles[numeroPoubelles] = true;
        switch (numeroPoubelles)
        {
            case 0:
                leds.setPixelColor(INDEX_LEDS_NOTIFICATION_POUBELLES, leds.Color(255, 0, 0)); // LED de la poubelle verte en rouge
                break;
            case 1:
                leds.setPixelColor(INDEX_LEDS_NOTIFICATION_POUBELLES + 1, leds.Color(0, 255, 0)); // LED de la poubelle bleue en vert
                break;
            case 2:
                leds.setPixelColor(INDEX_LEDS_NOTIFICATION_POUBELLES + 2, leds.Color(0, 0, 255)); // LED de la poubelle verte en bleu
                break;
            case 3:
                leds.setPixelColor(INDEX_LEDS_NOTIFICATION_POUBELLES + 3, leds.Color(128, 128, 128)); // LED de la poubelle grise en gris
                break;
            case 4:
                leds.setPixelColor(INDEX_LEDS_NOTIFICATION_POUBELLES + 4, leds.Color(255, 255, 0)); // LED de la poubelle jaune en jaune
                break;
            default:
                break;
        }
        leds.show(); // Allume le bandeau
    }
}

void StationLumineuse::allumerNotificationPoubelles()
{
}

/**
 * @brief Éteint la notification de la poubelle donnée
 * @fn StationLumineuse::eteindreNotificationPoubelle
 * @param numeroPoubelles
 * @details Éteint les LEDS associées à la notification de la poubelle donnée en les mettant à la couleur noire (0,0,0)
 */

void StationLumineuse::eteindreNotificationPoubelle(int numeroPoubelles)
{
     if (estIdValidePoubelle(numeroPoubelles))
    {
        int indexLed = INDEX_LEDS_NOTIFICATION_POUBELLES + numeroPoubelles - 1;
        leds.setPixelColor(indexLed, leds.Color(0, 0, 0));
        leds.show();
        setEtatPoubelle(numeroPoubelles, false);
    }
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
