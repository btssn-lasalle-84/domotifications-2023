/**
 * @file src/main.cpp
 * @brief Programme principal de la station de notifications lumineuses
 * @author Alexis Vaillen
 * @version 0.2
 */

#define ERREUR_BROWNOUT

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiManager.h>
#include "ServeurWeb.h"
#include "StationLumineuse.h"
#ifdef ERREUR_BROWNOUT
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"
#endif

// Configuration du WiFi avec WiFiManager
WiFiManager wm;
WiFiClient  espClient;
// Projet Station de notifications lumineuses
StationLumineuse stationLumineuse;
ServeurWeb       serveurWeb(&stationLumineuse);

void setup()
{
#ifdef ERREUR_BROWNOUT
    WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
#endif

    Serial.begin(115200);
    Serial.println(F("Station de notifications lumineuses"));

    stationLumineuse.initialiserPreferences();

    // Configuration du WiFi avec WiFiManager
    WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP
    // reset settings - wipe credentials for testing
    // wm.resetSettings();
    wm.setTitle("Station de notifications lumineuses");
    // wm.setDarkMode(true);
    bool resultat = false;
    resultat      = wm.autoConnect(); // auto generated AP name from chipid
    if(!resultat)
    {
        Serial.println(F("Erreur de connexion !"));
        // ESP.restart();
    }
    // fin de la configuration du WiFi avec WiFiManager

    stationLumineuse.initialiserNotifications();

    serveurWeb.demarrer();
}

void loop()
{
    serveurWeb.traiterRequetes();
}
