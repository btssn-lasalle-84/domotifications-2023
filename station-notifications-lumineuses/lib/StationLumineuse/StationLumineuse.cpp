#include "StationLumineuse.h"

StationLumineuse::StationLumineuse() :
    leds(NB_LEDS, PIN_BANDEAU, NEO_GRB + NEO_KHZ800)
{
}

void StationLumineuse::initialiserPreferences()
{
    preferences.begin("eeprom", false); // false pour r/w
    etatBoiteAuxLettres = preferences.getBool("boite", false);
    char cle[64]        = "";
    for(int i = 0; i < NB_LEDS_NOTIFICATION_MACHINES; ++i)
    {
        sprintf((char*)cle, "%s%d", "machines", i);
        etatmachines[i] = preferences.getBool(cle, false);
    }
    for(int i = 0; i < NB_LEDS_NOTIFICATION_POUBELLES; ++i)
    {
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
    testermachines();
    testerPoubelles();
#endif

    /**
     * Allumer/Eteindre les leds de notifications à partir des états
     * sauvegardés
     */
    if(etatBoiteAuxLettres){
        allumerNotificationBoiteAuxLettres();
    }
    else {
        eteindreNotificationBoiteAuxLettres();
    }

    for(int i = 0 ;i < NB_LEDS_NOTIFICATION_MACHINES; i++ )
    {
        if(etatmachines[i])
        {
            allumerNotificationMachines(i);
        }
        else {
            eteindreNotificationMachines(i);
        }
    }

    for(int i = 0; i< NB_LEDS_NOTIFICATION_POUBELLES; i++)
    {
        if(etatPoubelles[i])
        {
            allumerNotificationPoubelles(i);
        }
        else{
            eteindreNotificationPoubelles(i);
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

bool StationLumineuse::estIdValideMachines(int numeromachines)
{
}

bool StationLumineuse::getEtatMachines(int numeromachines)
{

}

void StationLumineuse::setEtatMachines(int numeromachines, bool etat)
{
}

void StationLumineuse::resetEtatMachines(int numeromachines)
{
}


void StationLumineuse::allumerNotificationMachines(int numeromachines)
{
}

void StationLumineuse::eteindreNotificationMachines(int numeromachines)
{
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

void StationLumineuse::setEtatPoubelle()
{
}

void StationLumineuse::resetEtatPoubelle()
{
}



void StationLumineuse::allumerNotificationPoubelles(int numeroPoubelles)
{
}

void StationLumineuse::eteindreNotificationPoubelles(int numeroPoubelles)
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

void StationLumineuse::testermachines()
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
        leds.setPixelcolor (in leds.Color(255,0,0)); //rouge
        leds.show();
        delay(1000);
          leds.setPixelcolor (in leds.Color(0,0,255)); //bleu
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
