#ifndef CONSTANTES_H
#define CONSTANTES_H

/**
 * @file Constantes.h
 *
 * @brief Contient les constantes du projet
 * @author Mathieu MOYAERTS
 * @version 0.2
 */

#include <QString>

/**
 * @def CONFIGURATION_APPLICATION
 * @brief Le nom du fichier de configuration
 */
#define CONFIGURATION_APPLICATION "config.ini"

/**
 * @def TITRE_APPLICATION
 * @brief Le nom de l'application dans la barre de titre
 */
#define TITRE_APPLICATION "Domotifications"

/**
 * @def NOM_STATION
 * @brief Le nom de la station de notifications
 */
#define NOM_STATION QString("station-lumineuse.local")

/**
 * @def URL_STATION
 * @brief L'URL de la station de notifications
 */
#define URL_STATION (QString("http://") + QString(NOM_STATION) + QString("/"))

/**
 * @def PORT_HTTP
 * @brief Le numéro de port par défaut de la station de notifications
 */
#define PORT_HTTP 80

#define NON_TROUVE -1

// Pour l'IHM
#define CHEMIN_LOGO_PARAMETRE         ":/images-qt/logo-parametre.png"
#define CHEMIN_LOGO_POUBELLE          ":/images-qt/logo-poubelle-"
#define CHEMIN_LOGO_BOITE_AUX_LETTRES ":/images-qt/logo-boite-aux-lettres.png"
#define CHEMIN_LOGO_MACHINE           ":/images-qt/logo-machine.png"
#define CHEMIN_BOUTON_ACTIVATION      ":/images-qt/bouton-activation.png"
#define CHEMIN_BOUTON_DESACTIVATION   ":/images-qt/bouton-desactivation.png"
#define CHEMIN_BOUTON_ACQUITTEMENT    ":/images-qt/logo-acquittement.png"
#define CHEMIN_LOGO_BTS_SN            ":/images-qt/logo-bts-sn.png"

#define HAUTEUR_IMAGE 50
#define LARGEUR_IMAGE 30

/**
 * @def PERIODE_RECUPERATION_NOTIFICATIONS
 * @brief La période de récupération des notifications auprès de la station
 */
#define PERIODE_RECUPERATION_NOTIFICATIONS 10000 // en ms

// Pour les tests
// Pour définir la création initiale de modules
//#define SIMULATION_MODULES
//#define SANS_STATION
//#define TEST_NOTIFICATIONS

#endif // CONSTANTES_H
