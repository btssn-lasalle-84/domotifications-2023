/**
 * @file ServeurWeb.cpp
 * @brief Définition de la classe ServeurWeb
 * @author Alexis Vaillen
 * @version 0.1
 */

#include "ServeurWeb.h"
#include "StationLumineuse.h"
#include <ESPmDNS.h>

ServeurWeb::ServeurWeb(StationLumineuse* stationLumineuse) :
    WebServer(PORT_SERVEUR_WEB), stationLumineuse(stationLumineuse)
{
}

void ServeurWeb::setNom()
{
    // Pour un accès : http://NOM_SERVEUR_WEB.local/
    if(!MDNS.begin(NOM_SERVEUR_WEB))
    {
#ifdef DEBUG_SERVEUR_WEB
        Serial.println("ServeurWeb() : Erreur mDNS !");
#endif
    }
}

void ServeurWeb::demarrer()
{
    setNom();

    // Installe les gestionnaires de requêtes
    on("/", HTTP_GET, std::bind(&ServeurWeb::afficherAccueil, this));
    on("/notifications", std::bind(&ServeurWeb::traiterRequeteGETNotifications, this));
    on("/boite", HTTP_GET, std::bind(&ServeurWeb::traiterRequeteGETBoite, this));
    on("/boite", HTTP_POST, std::bind(&ServeurWeb::traiterRequetePOSTBoite, this));
    on("/machine",
       HTTP_POST,
       std::bind(&ServeurWeb::traiterRequetePOSTMachine,
                 this)); // Ajout de la route /machine en POST
    onNotFound(std::bind(&ServeurWeb::traiterRequeteNonTrouvee, this));

    // Démarre le serveur
    begin();

#ifdef DEBUG_SERVEUR_WEB
    Serial.print("ServeurWeb::demarrer() : nom = ");
    Serial.println(NOM_SERVEUR_WEB);
    Serial.print("ServeurWeb::demarrer() : adresse IP = ");
    Serial.println(WiFi.localIP());
#endif
}

void ServeurWeb::traiterRequetes()
{
    handleClient();
}

void ServeurWeb::afficherAccueil()
{
#ifdef DEBUG_SERVEUR_WEB
    Serial.print("ServeurWeb::afficherAccueil() : requête = ");
    Serial.println((method() == HTTP_GET) ? "GET" : "POST");
    Serial.print("URI : ");
    Serial.println(uri());
#endif
    String message = "<h1>Bienvenue sur la station de notifications lumineuses</h1>\n";
    message += "<p>LaSalle Avignon v0.1</p>\n";
    send(200, F("text/html"), message);
}

void ServeurWeb::traiterRequeteGETNotifications()
{
#ifdef DEBUG_SERVEUR_WEB
    Serial.print("ServeurWeb::traiterRequeteGETNotifications() : requête = ");
    Serial.println((method() == HTTP_GET) ? "GET" : "POST");
    Serial.print("URI : ");
    Serial.println(uri());
#endif

    documentJSON.clear();
    documentJSON["boite"] = stationLumineuse->getEtatBoiteAuxLettres();
    JsonArray machines    = documentJSON.createNestedArray("machines");
    for(int i = 0; i < NB_LEDS_NOTIFICATION_MACHINES; ++i)
    {
        machines.add(stationLumineuse->getEtatMachine(i));
    }
    JsonArray poubelle = documentJSON.createNestedArray("poubelle");
    for(int i = 0; i < NB_LEDS_NOTIFICATION_POUBELLES; ++i)
    {
        poubelle.add(stationLumineuse->getEtatPoubelle(i));
    }

#ifdef DEBUG_SERVEUR_WEB
    Serial.print(F("JSON : "));
    serializeJson(documentJSON, Serial);
    Serial.println();
#endif
    char buffer[TAILLE_JSON];
    serializeJson(documentJSON, buffer);
    send(200, "application/json", buffer);
}

void ServeurWeb::traiterRequeteGETBoite()
{
#ifdef DEBUG_SERVEUR_WEB
    Serial.print("ServeurWeb::traiterRequeteGETBoite() : requête = ");
    Serial.println((method() == HTTP_GET) ? "GET" : "POST");
    Serial.print("URI : ");
    Serial.println(uri());
#endif

    /**
     * @todo Répondre à la requête
     */
}

void ServeurWeb::traiterRequetePOSTBoite()
{
#ifdef DEBUG_SERVEUR_WEB
    Serial.print("ServeurWeb::traiterRequetePOSTBoite() : requête = ");
    Serial.println((method() == HTTP_GET) ? "GET" : "POST");
    Serial.print("URI : ");
    Serial.println(uri());
#endif

    if(hasArg("plain") == false)
    {
#ifdef DEBUG_SERVEUR_WEB
        Serial.println(F("Erreur !"));
#endif
        send(400,
             "application/json",
             "{\"error\": { \"code\": \"invalidRequest\", \"message\": "
             "\" La demande est vide ou incorrecte.\"}}");
        return;
    }

    String body = arg("plain");
#ifdef DEBUG_SERVEUR_WEB
    Serial.println(body);
#endif
    DeserializationError erreur = deserializeJson(documentJSON, body);
    if(erreur)
    {
#ifdef DEBUG_SERVEUR_WEB
        Serial.print(F("Erreur deserializeJson() : "));
        Serial.println(erreur.f_str());
#endif
        send(400,
             "application/json",
             "{\"error\": { \"code\": \"invalidRequest\", \"message\": "
             "\"La demande est mal exprimée ou incorrecte.\"}}");
        return;
    }
    else
    {
        JsonObject objetJSON = documentJSON.as<JsonObject>();
        if(objetJSON.containsKey("etat"))
        {
#ifdef DEBUG_SERVEUR_WEB
            Serial.print("etat : ");
            Serial.println(documentJSON["etat"].as<bool>());
#endif

            stationLumineuse->setEtatBoiteAuxLettres(documentJSON["etat"].as<bool>());

            send(200,
                 "application/json",
                 "{\"message\": "
                 "\"ok\"}");
        }
        else
        {
#ifdef DEBUG_SERVEUR_WEB
            Serial.print(F("Erreur : champ etat manquant"));
#endif
            send(400,
                 "application/json",
                 "{\"error\": { \"code\": \"invalidRequest\", \"message\": "
                 "\"La demande est incomplète.\"}}");
            return;
        }
    }
}

void ServeurWeb::traiterRequetePOSTMachine()
{
#ifdef DEBUG_SERVEUR_WEB
    Serial.print("ServeurWeb::traiterRequetePOSTMachine() : requête = ");
    Serial.println((method() == HTTP_GET) ? "GET" : "POST");
    Serial.print("URI : ");
    Serial.println(uri());
#endif

    if(hasArg("plain") == false)
    {
#ifdef DEBUG_SERVEUR_WEB
        Serial.println(F("Erreur !"));
#endif
        send(400,
             "application/json",
             "{\"error\": { \"code\": \"invalidRequest\", \"message\": "
             "\"La demande est vide ou incorrecte.\"}}");
        return;
    }

    String body = arg("plain");
#ifdef DEBUG_SERVEUR_WEB
    Serial.println(body);
#endif
    DeserializationError erreur = deserializeJson(documentJSON, body);
    if(erreur)
    {
#ifdef DEBUG_SERVEUR_WEB
        Serial.print(F("Erreur deserializeJson() : "));
        Serial.println(erreur.f_str());
#endif
        send(400,
             "application/json",
             "{\"error\": { \"code\": \"invalidRequest\", \"message\": "
             "\"La demande est mal exprimée ou incorrecte.\"}}");
        return;
    }
    else
    {
        JsonObject objetJSON = documentJSON.as<JsonObject>();
        if(objetJSON.containsKey("etat") && objetJSON.containsKey("numeroMachine"))
        {
#ifdef DEBUG_SERVEUR_WEB
            Serial.print("numeroMachine : ");
            Serial.println(documentJSON["numeroMachine"].as<int>());
            Serial.print("etat : ");
            Serial.println(documentJSON["etat"].as<bool>());
#endif

            // Modifier l'état de la machine ici
            int  numeroMachine = documentJSON["numeroMachine"].as<int>();
            bool etatMachine   = documentJSON["etat"].as<bool>();

            if(stationLumineuse->estIdValideMachine(numeroMachine))
            {
                stationLumineuse->setEtatMachine(numeroMachine, etatMachine);

                send(200,
                     "application/json",
                     "{\"message\": "
                     "\"ok\"}");
            }
            else
            {
                send(404,
                     "application/json",
                     "{\"error\": { \"code\": \"notFound\", \"message\": "
                     "\"La machine demandée n'existe pas.\"}}");
            }
        }
        else
        {
#ifdef DEBUG_SERVEUR_WEB
            Serial.print(F("Erreur : champ etat ou numeroMachine manquant"));
#endif
            send(400,
                 "application/json",
                 "{\"error\": { \"code\": \"invalidRequest\", \"message\": "
                 "\"La demande est incomplète.\"}}");
            return;
        }
    }
}

void ServeurWeb::traiterRequeteNonTrouvee()
{
#ifdef DEBUG_SERVEUR_WEB
    Serial.print("ServeurWeb::traiterRequeteNonTrouvee() : requête = ");
    Serial.println((method() == HTTP_GET) ? "GET" : "POST");
    Serial.print("URI : ");
    Serial.println(uri());
#endif

    String message = "404 File Not Found\n\n";
    message += "URI: ";
    message += uri();
    message += "\nMethod: ";
    message += (method() == HTTP_GET) ? "GET" : "POST";
    message += "\nArguments: ";
    message += args();
    message += "\n";
    for(uint8_t i = 0; i < args(); i++)
    {
        message += " " + argName(i) + ": " + arg(i) + "\n";
    }
    send(404, "text/plain", message);
}
