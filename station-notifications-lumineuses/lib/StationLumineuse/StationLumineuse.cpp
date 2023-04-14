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
 * @details Initialise les attributs de la classe avec des valeurs par défaut et le bandeau de leds.
 */
StationLumineuse::StationLumineuse() : leds(NB_LEDS, PIN_BANDEAU, NEO_GRB + NEO_KHZ800)
{
}

/**
 * @brief Initialise les préférences de la station lumineuse
 * @fn StationLumineuse::initialiserPreferences
 * @details Charge les préférences depuis la mémoire EEPROM ou les valeurs par défaut si les
 * préférences n'ont pas été définies
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
 * @details Modifie l'état actuel de la boîte aux lettres et allume ou éteint les leds en fonction
 * de celui-ci
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
 * @details Allume les LEDS de couleur rouge pour indiquer que la boîte aux lettres est pleine
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
 * @details Eteint les LEDS de couleur rouge pour indiquer que la boîte aux lettres est vide
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
 * @param numeromachine Numéro de la machine
 * @return l'état true ou false de la machine
 * @details renvoie l'etat de la machine si l'id et valide, faux sinon
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
 * @fn StationLumineuse::setEtatMachine
 * @param numeromachine
 * @param etat
 * @details Modifie l'état de la machine spécifiée par le numéro donné. Enregistre l'état dans les
 préférences, et allume ou éteint la notification de la machine en fonction de son nouvel état.
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
 * @brief Réinitialise l'état de toutes les machines
 * @fn StationLumineuse::resetEtatMachines
 * @details Change l'état de toutes les machines en false et éteint les notifications associées
 */
void StationLumineuse::resetEtatMachines()
{
}

/**
 * @brief Allume la notification de la machine donnée
 * @fn StationLumineuse::allumerNotificationMachine
 * @param numeromachine
 * @details Allume les LEDs de couleur verte pour indiquer que la machine spécifiée est finie
 */
void StationLumineuse::allumerNotificationMachine(int numeroMachine)
{
}

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

/**
 * @brief Éteint la notification de la machine donnée
 * @fn StationLumineuse::eteindreNotificationMachine
 * @param numeromachine
 * @details Éteint les LEDS associées à la notification de la machine donnée
 */
void StationLumineuse::eteindreNotificationMachine(int numeroMachine)
{
}

/**
 * @brief Éteint la notification de toutes les machines
 * @fn StationLumineuse::eteindreNotificationMachines
 * @details Éteint les LEDS associées à la notification de toutes les machines
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
 * @param numeroPoubelle
 * @return bool true si le numeroPoubelle est valide sinon false
 * @details renvoie Vrai si l'numeroPoubelle de la poubelle est compris entre 1 et NB_POUBELLES,
 * faux sinon
 */
bool StationLumineuse::estIdValidePoubelle(int numeroPoubelle)
{
    return (numeroPoubelle >= 0 && numeroPoubelle < NB_LEDS_NOTIFICATION_POUBELLES);
}

/**
 * @brief Récupère l'état de la poubelle donnée
 * @fn  StationLumineuse::getEtatPoubelle
 * @param numeroPoubelle Numéro de la poubelle
 * @return etatPoubelle[numeroPoubelle]
 * @details renvoie l'etat de la poubelle si l'id et valide, faux sinon
 */

bool StationLumineuse::getEtatPoubelle(int numeroPoubelle)
{
    if(estIdValidePoubelle(numeroPoubelle))
    {
        return etatPoubelles[numeroPoubelle];
    }
    else
    {
        return false;
    }
}

/**
 * @brief Modifie l'état de la poubelle donnée
 * @fn StationLumineuse::setEtatPoubelle
 * @param numeroPoubelle
 * @param etat
 * @details Modifie l'état de la poubelle spécifiée par le numéro donné. Enregistre l'état dans les
 préférences, et allume ou éteint la notification de la poubelle en fonction de son nouvel état.
 */

void StationLumineuse::setEtatPoubelle(int numeroPoubelle, bool etat)
{
    if(!estIdValidePoubelle(numeroPoubelle))
        return;
    etatPoubelles[numeroPoubelle] = etat;
    char cle[64]                  = "";
    sprintf((char*)cle, "%s%d", "poubelle", numeroPoubelle);
    preferences.putBool(cle, etatPoubelles[numeroPoubelle]);
    if(etat)
    {
        allumerNotificationPoubelle(numeroPoubelle);
    }
    else
    {
        eteindreNotificationPoubelle(numeroPoubelle);
    }
}

/**
 * @brief Réinitialise l'état de toutes les poubelles
 * @fn StationLumineuse::resetEtatPoubelles
 * @details Change l'état de toutes les poubelles et éteint les notifications associées
 */
void StationLumineuse::resetEtatPoubelles()
{
}

/**
 * @brief Allume la notification de la poubelle donnée
 * @fn StationLumineuse::allumerNotificationPoubelle
 * @param numeroPoubelle
 * @details Allume les LEDS en fonction de la couleur correspond aux poublles 0 ROUGE 1 VERT 2 BLEU
 3 GRIS 4 JAUNE pour indiquer quelle poubelle sortir
 */

void StationLumineuse::allumerNotificationPoubelle(int numeroPoubelle)
{
    if(estIdValidePoubelle(numeroPoubelle))
    {
        switch(numeroPoubelle)
        {
            case 0:
                leds.setPixelColor(INDEX_LEDS_NOTIFICATION_POUBELLES,
                                   leds.Color(0, 255, 0)); // LED de la poubelle verte
                break;
            case 1:
                leds.setPixelColor(INDEX_LEDS_NOTIFICATION_POUBELLES + 1,
                                   leds.Color(0, 0, 255)); // LED de la poubelle bleue
                break;
            case 2:
                leds.setPixelColor(INDEX_LEDS_NOTIFICATION_POUBELLES + 2,
                                   leds.Color(0, 255, 0)); // LED de la poubelle verte
                break;
            case 3:
                leds.setPixelColor(INDEX_LEDS_NOTIFICATION_POUBELLES + 3,
                                   leds.Color(128, 128, 128)); // LED de la poubelle grise
                break;
            case 4:
                leds.setPixelColor(INDEX_LEDS_NOTIFICATION_POUBELLES + 4,
                                   leds.Color(255, 255, 0)); // LED de la poubelle jaune
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
 * @param numeroPoubelle
 * @details Éteint les LEDS associées à la notification de la poubelle donnée
 */
void StationLumineuse::eteindreNotificationPoubelle(int numeroPoubelle)
{
    if(estIdValidePoubelle(numeroPoubelle))
    {
        int indexLed = INDEX_LEDS_NOTIFICATION_POUBELLES + numeroPoubelle;
        leds.setPixelColor(indexLed, leds.Color(0, 0, 0));
        leds.show();
        setEtatPoubelle(numeroPoubelle, false);
    }
}

void StationLumineuse::eteindreNotificationPoubelles()
{
}
