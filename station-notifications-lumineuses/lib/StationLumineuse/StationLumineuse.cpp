/**
 * @file StationLumineuse.cpp
 * @brief Définition de la classe StationLumineuse
 * @author Alexis Vaillen
 * @version 0.2
 */

#include "StationLumineuse.h"

/**
* @brief Constructeur de la classe StationLumineuse
* @fn StationLumineuse::StationLumineuse()
* @details Initialise la bande de LEDs, ainsi que les couleurs associées aux poubelles. Les couleurs sont définies dans le tableau couleursPoubelles.
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

/**
 * @brief Récupère les états des notifications depuis les préférences
 * @fn StationLumineuse::recupererEtatsNotifications()
 * @details Récupère les états des différentes notifications (boîte aux lettres, machines, poubelles) depuis les préférences enregistrées dans la mémoire. 
 * Ces états sont stockés dans les variables correspondantes de la classe.
 */
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

/**
 * @brief Récupère les états d'activation depuis les préférences
 * @fn StationLumineuse::recupererEtatsActivations()
 * @details Récupère les états d'activation des différentes fonctionnalités (boîte aux lettres, machines, poubelles) depuis les
 *  préférences enregistrées dans la mémoire. Ces états d'activation sont stockés dans les variables correspondantes de la classe.
 */
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
 * @fn StationLumineuse::initialiserPreferences()
 * @details Démarre la gestion des préférences en utilisant la mémoire EEPROM. Ensuite, appelle les fonctions pour récupérer les états des notifications
 * et les états d'activation depuis les préférences enregistrées dans la mémoire.
 */
void StationLumineuse::initialiserPreferences()
{
    preferences.begin("eeprom", false); // false pour r/w
    recupererEtatsNotifications();
    recupererEtatsActivations();
}

/**
 * @brief Initialise les notifications lumineuses
 * @fn StationLumineuse::initialiserNotifications()
 * @details Initialise les LEDs et configure les notifications lumineuses en fonction des états et des activations enregistrés.
 * Les notifications des différents capteurs sont allumées ou éteintes en fonction de ces paramètres.
 */
void StationLumineuse::initialiserNotifications()
{
    leds.begin();
    leds.clear();

    if(activationBoiteAuxLettres)
    {
        if(etatBoiteAuxLettres)
        {
            allumerNotificationBoiteAuxLettres();
        }
        else
        {
            eteindreNotificationBoiteAuxLettres();
        }
    }

    for(int i = 0; i < NB_LEDS_NOTIFICATION_MACHINES; i++)
    {
        if(activationMachines[i])
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
    }

    for(int i = 0; i < NB_LEDS_NOTIFICATION_POUBELLES; i++)
    {
        if(activationPoubelles[i])
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
 * @brief Modifie l'état d'activation de la boîte aux lettres
 * @fn StationLumineuse::setActivationBoiteAuxLettres(bool etat)
 * @param etat Nouvel état d'activation de la boîte aux lettres
 * @details Modifie l'état d'activation de la boîte aux lettres et enregistre cette valeur dans les préférences.
 * L'état d'activation détermine si la notification lumineuse de la boîte aux lettres sera activée ou désactivée.
 */
void StationLumineuse::setActivationBoiteAuxLettres(bool etat)
{
    activationBoiteAuxLettres = etat;
    preferences.putBool("activationBoite", etat);
}


/**
 * @brief Obtient l'état d'activation de la boîte aux lettres
 * @fn bool StationLumineuse::getActivationBoiteAuxLettres()
 * @details Renvoie l'état d'activation actuel de la boîte aux lettres. L'état d'activation détermine si la notification lumineuse de la boîte aux lettres 
 * est activée ou désactivée.
 * @return activationBoiteAuxLettres État d'activation de la boîte aux lettres (true si activée, false sinon).
 */
bool StationLumineuse::getActivationBoiteAuxLettres()
{
    return activationBoiteAuxLettres;
}

/**
 * @brief Obtient l'état de la boîte aux lettres
 * @fn StationLumineuse::getEtatBoiteAuxLettres
 * @details Obtient l'état actuel de la boîte aux lettres, vrai si elle est pleine, faux sinon
 * @return etatBoiteAuxLettres État de la boîte aux lettres (true si ouverte, false si fermée).
 */
bool StationLumineuse::getEtatBoiteAuxLettres()
{
    return etatBoiteAuxLettres;
}

/**
 * @brief Modifie l'état de la boîte aux lettres
 * @fn void StationLumineuse::setEtatBoiteAuxLettres(bool etat)
 * @param etat Nouvel état de la boîte aux lettres (true si ouverte, false si fermée)
 * @details Modifie l'état de la boîte aux lettres et enregistre cette valeur dans les préférences. Si l'activation de la boîte aux lettres est activée,
 * la notification lumineuse sera allumée ou éteinte en fonction de l'état spécifié.
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
 * @fn void StationLumineuse::resetEtatBoiteAuxLettres()
 * @details Rétablit l'état de la boîte aux lettres à sa valeur par défaut, c'est-à-dire fermée. Enregistre cette valeur dans les préférences et éteint 
 * la notification lumineuse de la boîte aux lettres.
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

/**
 * @brief Modifie l'état d'activation de la machine spécifiée
 * @fn void StationLumineuse::setActivationMachine(int id, bool etat)
 * @param id Identifiant de la machine à modifier
 * @param etat Nouvel état d'activation de la machine
 * @details Modifie l'état d'activation de la machine spécifiée par son identifiant. Si l'identifiant de la machine est valide,
 * l'état d'activation est mis à jour et enregistré dans les préférences. Sinon, un message d'erreur est affiché dans la console.
 */
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

/**
 * @brief Obtient l'état d'activation de la machine spécifiée
 * @fn bool StationLumineuse::getActivationMachine(int id)
 * @param id Identifiant de la machine
 * @details Renvoie l'état d'activation actuel de la machine spécifiée par son identifiant. Si l'identifiant de la machine est valide,
 * l'état d'activation correspondant est renvoyé. Sinon, un message d'erreur est affiché dans la console et la valeur par défaut (false) est renvoyée.
 * @return État d'activation de la machine (true si activée, false sinon).
 */
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
 * @param numeroMachine Identifiant de la machine à vérifier
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
 * @brief Modifie l'état de la machine spécifiée
 * @fn void StationLumineuse::setEtatMachine(int numeroMachine, bool etat)
 * @param numeroMachine Numéro de la machine à modifier
 * @param etat Nouvel état de la machine (true si allumée, false sinon)
 * @details Modifie l'état de la machine spécifiée par son numéro. Si l'activation de la machine est activée et si l'identifiant de la machine est valide,
 * l'état de la machine est mis à jour et enregistré dans les préférences. En fonction du nouvel état, la notification lumineuse de la machine est allumée ou éteinte.
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
 * @brief Réinitialise l'état de la machine spécifiée
 * @fn void StationLumineuse::resetEtatMachines(int numeroMachine)
 * @param numeroMachine Numéro de la machine à réinitialiser
 * @details Rétablit l'état de la machine spécifiée par son numéro à la valeur par défaut (false). Enregistre cette valeur dans les préférences et éteint 
 * la notification lumineuse de la machine.
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
 * @param numeroMachine Numéro de la machine  a allumer
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
 * @param numeroMachine Numéro de la machine a éteindre
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

/**
 * @brief Modifie l'état d'activation de la poubelle spécifiée
 * @fn void StationLumineuse::setActivationPoubelle(int id, bool etat)
 * @param id Identifiant de la poubelle à modifier
 * @param etat Nouvel état d'activation de la poubelle
 * @details Modifie l'état d'activation de la poubelle spécifiée par son identifiant. Si l'identifiant de la poubelle est valide, l'état d'activation
 *  est mis à jour et enregistré dans les préférences. Sinon, un message d'erreur est affiché dans la console.
 */
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

/**
  * @brief Obtient l'état d'activation de la poubelle spécifiée
  * @fn bool StationLumineuse::getActivationPoubelle(int id)
  * @param id Identifiant de la poubelle
  * @details Renvoie l'état d'activation actuel de la poubelle spécifiée par son identifiant. Si l'identifiant de la poubelle est valide, l'état d'activation
  * correspondant est renvoyé. Sinon, un message d'erreur est affiché dans la console et la valeur par défaut (false) est renvoyée.
  * @return État d'activation de la poubelle (true si activée, false sinon).
  */
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
  * @brief Vérifie si l'identifiant de la poubelle est valide
  * @fn bool StationLumineuse::estIdValidePoubelle(int numeroPoubelle)
  * @param numeroPoubelle Identifiant de la poubelle à vérifier
  * @details Vérifie si l'identifiant de la poubelle est compris entre 0 et le nombre maximum de poubelles (NB_LEDS_NOTIFICATION_POUBELLES).
  * Renvoie true si l'identifiant est valide, sinon renvoie false.
  * @return true si l'identifiant de la poubelle est valide, false sinon.
  */
bool StationLumineuse::estIdValidePoubelle(int numeroPoubelle)
{
    return (numeroPoubelle >= 0 && numeroPoubelle < NB_LEDS_NOTIFICATION_POUBELLES);
}

/**
  * @brief Obtient l'état de la poubelle spécifiée
  * @fn bool StationLumineuse::getEtatPoubelle(int numeroPoubelle)
  * @param numeroPoubelle Numéro de la poubelle
  * @details Renvoie l'état actuel de la poubelle spécifiée par son numéro. Si l'identifiant de la poubelle est valide, l'état correspondant est renvoyé. 
  * Sinon, false est renvoyé.
  * @return État de la poubelle (true si pleine, false si vide ou si l'identifiant est invalide).
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
  * @brief Modifie l'état de la poubelle spécifiée
  * @fn void StationLumineuse::setEtatPoubelle(int numeroPoubelle, bool etat)
  * @param numeroPoubelle Numéro de la poubelle à modifier
  * @param etat Nouvel état de la poubelle (true si pleine, false si vide)
  * @details Modifie l'état de la poubelle spécifiée par son numéro. Si l'activation de la poubelle est activée et si l'identifiant de la poubelle est valide, 
  * l'état de la poubelle est mis à jour et enregistré dans les préférences. En fonction du nouvel état, la notification lumineuse de la poubelle est allumée ou éteinte.
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
 * @brief Réinitialise l'état de la poubelle spécifiée
 * @fn void StationLumineuse::resetEtatPoubelles(int numeroPoubelle)
 * @param numeroPoubelle Numéro de la poubelle à réinitialiser
 * @details Rétablit l'état de la poubelle spécifiée par son numéro à la valeur par défaut (false). Enregistre cette valeur dans les préférences 
 * et éteint la notification lumineuse de la poubelle.
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
  * @brief Allume la notification lumineuse de la poubelle spécifiée
  * @fn void StationLumineuse::allumerNotificationPoubelle(int numeroPoubelle)
  * @param numeroPoubelle Numéro de la poubelle
  * @details Allume la notification lumineuse de la poubelle spécifiée par son numéro. Si l'identifiant de la poubelle est valide, 
  * la couleur correspondante est appliquée aux LED de la poubelle et le bandeau lumineux est mis à jour pour afficher la notification.
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
 * @brief Éteint la notification lumineuse de la poubelle spécifiée
 * @fn void StationLumineuse::eteindreNotificationPoubelle(int numeroPoubelle)
 * @param numeroPoubelle Numéro de la poubelle
 * @details Éteint la notification lumineuse de la poubelle spécifiée par son numéro. Si l'identifiant de la poubelle est valide, 
 * la LED correspondante est éteinte en attribuant la couleur noire (0, 0, 0). Le bandeau lumineux est mis à jour pour refléter cette modification.
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
