#ifndef CONSTANTES_H
#define CONSTANTES_H

/**
 * @file Constantes.h
 *
 * @brief Contient les constantes du projet
 * @author Mathieu MOYAERTS
 * @version 0.1
 */

#include <QString>

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

// Pour l'IHM
#define CHEMIN_LOGO_PARAMETRE         ":/images-qt/logo-parametre.png"
#define CHEMIN_LOGO_POUBELLE          ":/images-qt/logo-poubelle.png"
#define CHEMIN_LOGO_BOITE_AUX_LETTRES ":/images-qt/logo-boite-aux-lettres.png"
#define CHEMIN_LOGO_MACHINE           ":/images-qt/logo-machine.png"
#define CHEMIN_BOUTON_ACTIVATION      ":/images-qt/bouton-activation"
#define CHEMIN_BOUTON_DESACTIVATION   ":/images-qt/bouton-desactivation"
#define CHEMIN_BOUTON_ACQUITTEMENT    ":/images-qt/logo-acquittement"
#define CHEMIN_LOGO_BTS_SN            ":/images-qt/logo-bts-sn.png"

#define HAUTEUR_IMAGE 50
#define LARGEUR_IMAGE 30

// Pour les tests
#define SANS_STATION
//#define TEST_NOTIFICATIONS

#endif // CONSTANTES_H
