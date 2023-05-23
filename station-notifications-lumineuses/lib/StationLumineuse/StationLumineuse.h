/**
 * @file StationLumineuse.h
 * @brief Déclaration de la classe StationLumineuse
 * @author Alexis Vaillen
 * @version 0.2
 */

#ifndef STATIONLUMINEUSE_H
#define STATIONLUMINEUSE_H

#include <Arduino.h>
#include <Preferences.h>
#include <Adafruit_NeoPixel.h>
#include <vector>

// #define DEBUG_STATION_LUMINEUSE

// Bandeau à Leds
#define PIN_BANDEAU                    16
#define NB_LEDS                        15
#define NB_LEDS_NOTIFICATION_MACHINES  6
#define NB_LEDS_NOTIFICATION_POUBELLES 5
#define NB_LEDS_NOTIFICATION_BOITE                                                                 \
    (NB_LEDS - NB_LEDS_NOTIFICATION_MACHINES - NB_LEDS_NOTIFICATION_POUBELLES)
#define INDEX_LEDS_NOTIFICATION_MACHINES 0
#define INDEX_LEDS_NOTIFICATION_POUBELLES                                                          \
    (INDEX_LEDS_NOTIFICATION_MACHINES + NB_LEDS_NOTIFICATION_MACHINES)
#define INDEX_LEDS_NOTIFICATION_BOITE                                                              \
    (INDEX_LEDS_NOTIFICATION_POUBELLES + NB_LEDS_NOTIFICATION_POUBELLES)

// RGB
#define ROUGE       0
#define VERT        1
#define BLEU        2
#define NB_COULEURS 3

/**
 * @class StationLumineuse
 * @brief Déclaration de la classe StationLumineuse 
 */
class StationLumineuse
{
  private:
    Adafruit_NeoPixel leds;                        //!< le bandeau à leds multi-couleurs
    Preferences       preferences;                 //!< pour le stockage interne
    bool              etatBoiteAuxLettres = false; //!< l'état de la boîte aux lettres
    bool              etatMachines[NB_LEDS_NOTIFICATION_MACHINES] = {
        false, false, false, false, false, false
    }; //!< l'état des machines
    bool     etatPoubelles[NB_LEDS_NOTIFICATION_POUBELLES] = { false,
                                                           false,
                                                           false,
                                                           false,
                                                           false }; //!< l'état des poubelles
    uint32_t couleursPoubelles[NB_LEDS_NOTIFICATION_POUBELLES]; //!< les couleurs des poubelles

    bool activationBoiteAuxLettres = true; //!< l'état d'activation de la boîte aux lettres
    bool activationMachines[NB_LEDS_NOTIFICATION_MACHINES] = {
        true, true, true, true, true, true
    }; //!< l'état d'activation des machines
    bool activationPoubelles[NB_LEDS_NOTIFICATION_POUBELLES] = {
        true, true, true, true, true
    }; //!< l'état d'activation des poubelles

  public:
    StationLumineuse();
    ~StationLumineuse();
    void initialiserPreferences();
    void initialiserNotifications();
    void initialiserCouleursPoubelles();
    void setActivationBoiteAuxLettres(bool etat);
    bool getActivationBoiteAuxLettres();
    void setActivationMachine(int id, bool etat);
    bool getActivationMachine(int id);
    void setActivationPoubelle(int id, bool etat);
    bool getActivationPoubelle(int id);

    bool getEtatBoiteAuxLettres();
    void setEtatBoiteAuxLettres(bool etat);
    void resetEtatBoiteAuxLettres();
    void allumerNotificationBoiteAuxLettres();
    void eteindreNotificationBoiteAuxLettres();
    bool estIdValideMachine(int numeroMachine);
    bool getEtatMachine(int numeroMachine);
    void setEtatMachine(int numeroMachine, bool etat);
    void resetEtatMachines(int numeroMachine);
    void allumerNotificationMachine(int numeroMachine);
    void allumerNotificationMachines();
    void eteindreNotificationMachine(int numeroMachine);
    void eteindreNotificationMachines();
    bool estIdValidePoubelle(int numeroPoubelle);
    bool getEtatPoubelle(int numeroPoubelle);
    void setEtatPoubelle(int numeroPoubelle, bool etat);
    void resetEtatPoubelles(int numeroPoubelle);
    void allumerNotificationPoubelle(int numeroPoubelle);
    void eteindreNotificationPoubelle(int numeroPoubelle);
};

#endif // STATIONLUMINEUSE_H
