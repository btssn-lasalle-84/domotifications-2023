/**
 * @file StationLumineuse.cpp
 * @brief Définition de la classe StationLumineuse
 * @author Alexis Vaillen
 * @version 0.2
 */

#include "StationLumineuse.h"

/**
 * @brief Constructeur par défaut de la classe StationLumineuse.
 * @fn StationLumineuse::StationLumineuse
 * @details Ce constructeur initialise les attributs de la classe
 */
StationLumineuse::StationLumineuse() :
    leds(NB_LEDS, PIN_BANDEAU, NEO_GRB + NEO_KHZ800), couleursPoubelles{
        leds.Color(0, 0, 255),     // Couleur poubelle 0 (bleue)
        leds.Color(0, 255, 0),     // Couleur poubelle 1 (verte)
        leds.Color(255, 255, 0),   // Couleur poubelle 2 (jaune)
        leds.Color(128, 128, 128), // Couleur poubelle 3 (grise)
        leds.Color(255, 0, 0)      // Couleur poubelle 4 (rouge)
    }
{
    // initialiserCouleursPoubelles();
}

/**
 * @brief Destructeur de la classe StationLumineuse.
 * @fn StationLumineuse::~StationLumineuse
 * @details Libère les ressources de la classe
 */
StationLumineuse::~StationLumineuse()
{
}

void StationLumineuse::recupererEtatsNotifications() 
{
    char cle[64] = "";
    etatBoiteAuxLettres = preferences.getBool("boite", false);
    
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

void StationLumineuse::recupererEtatsActivations()
{
    char cle[64] = "";
    activationBoiteAuxLettres = preferences.getBool("activationBoite", true);
    for(int i = 0; i < NB_LEDS_NOTIFICATION_MACHINES; ++i)
    {
        sprintf((char*)cle, "%s%d", "activationMachine", i);
        activationMachines[i] = preferences.getBool(cle, true);
    }

    for(int i = 0; i < NB_LEDS_NOTIFICATION_POUBELLES; ++i)
    {
        sprintf((char*)cle, "%s%d", "activationPoubelle", i);
        activationPoubelles[i] = preferences.getBool(cle, true);
    }
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
    recupererEtatsNotifications();
    recupererEtatsActivations();
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

    if(activationBoiteAuxLettres && etatBoiteAuxLettres)
    {
        allumerNotificationBoiteAuxLettres();
    }
    else
    {
        eteindreNotificationBoiteAuxLettres();
    }

    for(int i = 0; i < NB_LEDS_NOTIFICATION_MACHINES; i++)
    {
        if(activationMachines[i] && etatMachines[i])
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
        if(activationPoubelles[i] && etatPoubelles[i])
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
 * @brief Définit les couleurs pour les notifications de poubelles.
 * @fn void StationLumineuse::initialiserCouleursPoubelles
 * @details Cette fonction initialise le tableau des couleurs pour les notifications de poubelles
 * avec les valeurs RGB correspondantes. Le tableau de couleurs peut ensuite être utilisé pour
 * contrôler les couleurs des LEDs.
 */
void StationLumineuse::initialiserCouleursPoubelles()
{
    const uint8_t couleursRGB[NB_LEDS_NOTIFICATION_POUBELLES][NB_COULEURS] = {
        { 0, 0, 255 },    // Couleur poubelle 0 (bleue)
        { 0, 255, 0 },    // Couleur poubelle 1 (verte)
        { 255, 255, 0 },  // Couleur poubelle 2 (jaune)
        { 255, 0, 0 },    // Couleur poubelle 3 (rouge)
        { 128, 128, 128 } // Couleur poubelle 4 (grise)
    };

    for(uint8_t i = 0; i < NB_LEDS_NOTIFICATION_POUBELLES; i++)
    {
        couleursPoubelles[i] =
          leds.Color(couleursRGB[i][ROUGE], couleursRGB[i][VERT], couleursRGB[i][BLEU]);
    }
}

/**
 * @brief Définit l'état d'activation de la boîte aux lettres.
 * @fn void StationLumineuse::setActivationBoiteAuxLettres(bool etat)
 * @details Cette méthode modifie l'état d'activation de la boîte aux lettres. Si l'état est défini
 * sur false, elle réinitialise également l'état de la boîte aux lettres.
 * @param etat
 */
void StationLumineuse::setActivationBoiteAuxLettres(bool etat)
{
    activationBoiteAuxLettres = etat;
    preferences.putBool("activationBoite", etat);
}


/**
 * @brief Obtient l'état d'activation de la boîte aux lettres.
 * @fn bool StationLumineuse::getActivationBoiteAuxLettres()
 * @details Cette méthode renvoie l'état d'activation actuel de la boîte aux lettres.
 * @return activationBoiteAuxLettres
 */
bool StationLumineuse::getActivationBoiteAuxLettres()
{
    return activationBoiteAuxLettres;
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
    if(activationBoiteAuxLettres)
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
 * @fn void StationLumineuse::eteindreNotificationBoiteAuxLettres
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

void StationLumineuse::setActivationMachine(int id, bool etat)
{
    if(estIdValideMachine(id))
    {
        activationMachines[id] = etat;
        char cle[64] = "";
        sprintf((char*)cle, "%s%d", "activationMachine", id);
        preferences.putBool(cle, etat);
    }
    else
    {
        Serial.println(F("Erreur: Identifiant de machine invalide"));
    }
}


bool StationLumineuse::getActivationMachine(int id)
{
    if(estIdValideMachine(id))
    {
        return activationMachines[id];
    }
    else
    {
        Serial.println(F("Erreur: Identifiant de machine invalide"));
        return false;
    }
}

/**
 * @brief Vérifie si l'ID de la machine est valide
 * @fn StationLumineuse::estIdValideMachine
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
 * @fn  StationLumineuse::getEtatMachine
 * @param numeroMachine Numéro de la machine
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
 * @param numeroMachine
 * @param etat
 * @details Modifie l'état de la machine spécifiée par le numéro donné. Enregistre l'état dans les
 préférences, et allume ou éteint la notification de la machine en fonction de son nouvel état.
 */
void StationLumineuse::setEtatMachine(int numeroMachine, bool etat)
{
    if(activationMachines[numeroMachine])
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
}

/**
 * @brief Réinitialise l'état de toutes les machines
 * @fn StationLumineuse::resetEtatMachines
 * @details Change l'état de toutes les machines en false et éteint les notifications associées
 */
void StationLumineuse::resetEtatMachines(int numeroMachine)
{
    if(estIdValideMachine(numeroMachine))
    {
        etatMachines[numeroMachine] = false;
        char cle[64]                = "";
        sprintf((char*)cle, "%s%d", "machine", numeroMachine);
        preferences.putBool(cle, etatMachines[numeroMachine]);
        eteindreNotificationMachine(numeroMachine);
    }
    else
    {
        Serial.println(F("Erreur: Identifiant de machine invalide"));
    }
}

/**
 * @brief Allume la notification de la machine donnée
 * @fn StationLumineuse::allumerNotificationMachine
 * @param numeroMachine
 * @details Allume les LEDs de couleur verte pour indiquer que la machine spécifiée est finie
 */
void StationLumineuse::allumerNotificationMachine(int numeroMachine)
{
    if(estIdValideMachine(numeroMachine))
    {
        leds.setPixelColor(INDEX_LEDS_NOTIFICATION_MACHINES + numeroMachine,
                           leds.Color(0, 255, 0)); // Appliquer la couleur correspondante
        leds.show();                               // Allume le bandeau
    }
}

/**
 * @brief Éteint la notification de la machine donnée
 * @fn StationLumineuse::eteindreNotificationMachine
 * @param numeroMachine
 * @details Éteint les LEDS associées à la notification de la machine donnée
 */
void StationLumineuse::eteindreNotificationMachine(int numeroMachine)
{
    if(estIdValideMachine(numeroMachine))
    {
        int indexLed = INDEX_LEDS_NOTIFICATION_MACHINES + numeroMachine;
        leds.setPixelColor(indexLed, leds.Color(0, 0, 0));
        leds.show();
    }
}

void StationLumineuse::setActivationPoubelle(int id, bool etat)
{
    if(estIdValidePoubelle(id))
    {
        activationPoubelles[id] = etat;
        char cle[64] = "";
        sprintf((char*)cle, "%s%d", "activationPoubelle", id);
        preferences.putBool(cle, etat);
    }
    else
    {
        Serial.println(F("Erreur: Identifiant de poubelle invalide"));
    }
}


bool StationLumineuse::getActivationPoubelle(int id)
{
    if(estIdValidePoubelle(id))
    {
        return activationPoubelles[id];
    }
    else
    {
        Serial.println(F("Erreur: Identifiant de poubelle invalide"));
        return false;
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
    if(activationPoubelles[numeroPoubelle])
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
}

/**
 * @brief Réinitialise l'état de toutes les poubelles
 * @fn StationLumineuse::resetEtatPoubelles
 * @details Change l'état de toutes les poubelles et éteint les notifications associées
 */
void StationLumineuse::resetEtatPoubelles(int numeroPoubelle)
{
    if(estIdValidePoubelle(numeroPoubelle))
    {
        etatPoubelles[numeroPoubelle] = false;
        char cle[64]                  = "";
        sprintf((char*)cle, "%s%d", "poubelle", numeroPoubelle);
        preferences.putBool(cle, etatPoubelles[numeroPoubelle]);
        eteindreNotificationPoubelle(numeroPoubelle);
    }
    else
    {
        Serial.println(F("Erreur: Identifiant de poubelle invalide"));
    }
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
        leds.setPixelColor(
          INDEX_LEDS_NOTIFICATION_POUBELLES + numeroPoubelle,
          couleursPoubelles[numeroPoubelle]); // Appliquer la couleur correspondante
        leds.show();                          // Allume le bandeau
    }
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
    }
}
