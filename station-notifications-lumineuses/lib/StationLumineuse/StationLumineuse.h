#ifndef STATIONLUMINEUSE_H
#define STATIONLUMINEUSE_H

/**
 * @file StationLumineuse.h
 * @brief Déclaration de la classe StationLumineuse
 * @author Alexis Vaillen
 * @version 0.1
 */

#include <Arduino.h>
#include <Preferences.h>
#include <Adafruit_NeoPixel.h>

#define DEBUG_STATION_LUMINEUSE

// Bandeau à Leds
// #define TEST_BANDEAU

#define PIN_BANDEAU                      16
#define NB_LEDS                          16
#define NB_LEDS_NOTIFICATION_MACHINES    6
#define NB_LEDS_NOTIFICATION_POUBELLES   5
#define NB_LEDS_NOTIFICATION_BOITE       5
#define INDEX_LEDS_NOTIFICATION_MACHINES 0
#define INDEX_LEDS_NOTIFICATION_POUBELLES                                      \
    (INDEX_LEDS_NOTIFICATION_MACHINES + NB_LEDS_NOTIFICATION_MACHINES)
#define INDEX_LEDS_NOTIFICATION_BOITE                                          \
    (INDEX_LEDS_NOTIFICATION_POUBELLES + NB_LEDS_NOTIFICATION_POUBELLES)

/**
 * @class StationLumineuse
 * @brief Déclaration de la classe StationLumineuse
 */
class StationLumineuse
{
  private:
    Adafruit_NeoPixel leds;           //!< le bandeau à leds multi-couleurs
    Preferences       preferences;    //!< pour le stockage interne
    bool etatBoiteAuxLettres = false; //!< l'état de la boîte aux lettres
    bool etatMachines[NB_LEDS_NOTIFICATION_MACHINES]   = { false, false, false,
                                                           false, false, false };
    bool etatPoubelles[NB_LEDS_NOTIFICATION_POUBELLES] = { false,
                                                           false,
                                                           false,
                                                           false,
                                                           false };

  public:
    StationLumineuse();

    void initialiserPreferences();
    void initialiserNotifications();

    bool getEtatBoiteAuxLettres();
    void setEtatBoiteAuxLettres(bool etat);
    void resetEtatBoiteAuxLettres();
    void allumerNotificationBoiteAuxLettres();
    void eteindreNotificationBoiteAuxLettres();
    bool estIdValideMachine(int id);
    bool getEtatMachine(int numeroMachine);
    void setEtatMachine(int numeroMachine, bool etat);
    void setEtatMachines();
    void resetEtatMachines();
    void allumerNotificationMachine(int numeroMachine);
    void eteindreNotificationMachine(int numeroMachine);
    void allumerNotificationMachines();
    void eteindreNotificationMachines();
    bool estIdValidePoubelle(int id);
    bool getEtatPoubelle(int numeroPoubelle);
    void setEtatPoubelle(int numeroPoubelle, bool etat);
    void setEtatPoubelle();
    void resetEtatPoubelle();
    void allumerNotificationPoubelle(int numeroPoubelle);
    void eteindreNotificationPoubelle(int numeroPoubelle);
    void allumerNotificationPoubelle();
    void eteindreNotificationPoubelle();

#ifdef TEST_BANDEAU
    // Fonctions de test
    void testerBoiteAuxLettres();
    void testerMachines();
    void testerPoubelles();
#endif
};

#endif // STATIONLUMINEUSE_H