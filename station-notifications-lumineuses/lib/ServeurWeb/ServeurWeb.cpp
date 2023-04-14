/**
 * @file ServeurWeb.cpp
 * @brief Définition de la classe ServeurWeb
 * @author Alexis Vaillen
 * @version 0.1
 */

#include "ServeurWeb.h"
#include "StationLumineuse.h"
#include <ESPmDNS.h>

/**
 * @brief Constructeur de la classe ServeurWeb
 * @fn ServeurWeb::ServeurWeb
 * @param stationLumineuse
 * @details Initialise un serveur web sur le port PORT_SERVEUR_WEB et l'association avec la classe
 * StationLumineuse
 */
ServeurWeb::ServeurWeb(StationLumineuse* stationLumineuse) :
    WebServer(PORT_SERVEUR_WEB), stationLumineuse(stationLumineuse)
{
}

/**
 * @brief Définit le nom du serveur web
 * @fn ServeurWeb::setNom
 * @param stationLumineuse
 * @details Utilise le protocole mDNS pour définir le nom du serveur web.
    Le nom sera utilisé pour accéder au serveur via l'adresse http://NOM_SERVEUR_WEB.local/.
 */
void ServeurWeb::setNom()
{
    // Pour un accès : http://NOM_SERVEUR_WEB.local/
    if(!MDNS.begin(NOM_SERVEUR_WEB))
    {
#ifdef DEBUG_SERVEUR_WEB
        Serial.println(F("ServeurWeb() : Erreur mDNS !"));
#endif
    }
}

/**
 * @brief Démarre le serveur web et installe les gestionnaires de requêtes
 * @fn ServeurWeb::demarrer
 * @details Configure les routes pour les différentes requêtes HTTP
    et démarre le serveur web. Elle utilise des fonctions de liaison std::bind pour attacher les
 méthodes membres à chaque route.
 */
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
    on("/poubelle",
       HTTP_POST,
       std::bind(&ServeurWeb::traiterRequetePOSTPoubelle,
                 this)); // Ajout de la route /poubelle en POST
    onNotFound(std::bind(&ServeurWeb::traiterRequeteNonTrouvee, this));

    // Démarre le serveur
    begin();

#ifdef DEBUG_SERVEUR_WEB
    Serial.print(F("ServeurWeb::demarrer() : nom = "));
    Serial.println(NOM_SERVEUR_WEB);
    Serial.print(F("ServeurWeb::demarrer() : adresse IP = "));
    Serial.println(WiFi.localIP());
#endif
}

/**
 * @brief traite les requêtes reçues par le serveur web
 * @fn ServeurWeb::traiterRequetes
 * @details Appelle la méthode handleClient() du serveur web pour traiter les requêtes reçues par le
 * serveur.
 */
void ServeurWeb::traiterRequetes()
{
    handleClient();
}

/**
 * @brief Affiche la page d'accueil du serveur web
 * @fn ServeurWeb::afficherAccueil
 * @details Affiche la page d'accueil du serveur web contenant un titre
   "Bienvenue sur la station de notifications lumineuses" ainsi qu'un message indiquant
   la version de la station ("LaSalle Avignon v0.1"). La méthode utilise la fonction send()
   pour envoyer la réponse au client HTTP avec un code de statut 200 et un type de contenu
 "text/html"
 */
void ServeurWeb::afficherAccueil()
{
#ifdef DEBUG_SERVEUR_WEB
    Serial.print(F("ServeurWeb::afficherAccueil() : requête = "));
    Serial.println((method() == HTTP_GET) ? "GET" : "POST");
    Serial.print(F("URI : "));
    Serial.println(uri());
#endif
    String message = "<h1>Bienvenue sur la station de notifications lumineuses</h1>\n";
    message += "<p>LaSalle Avignon v0.1</p>\n";
    send(200, F("text/html"), message);
}

/**
 * @brief Traite la requête GET pour obtenir l'état des notifications
 * @fn ServeurWeb::traiterRequeteGETNotifications
 * @details Crée un objet JSON contenant l'état de la boîte aux lettres, des machines et des
 poubelles. Elle utilise les méthodes getEtatBoiteAuxLettres(), getEtatMachines() et
 getEtatPoubelle() de l'objet stationLumineuse pour remplir l'objet JSON. Ensuite, elle sérialise
 cet objet JSON et le renvoie en tant que réponse à la requête GET sous forme d'un document JSON.
 */
void ServeurWeb::traiterRequeteGETNotifications()
{
#ifdef DEBUG_SERVEUR_WEB
    Serial.print(F("ServeurWeb::traiterRequeteGETNotifications() : requête = "));
    Serial.println((method() == HTTP_GET) ? "GET" : "POST");
    Serial.print(F("URI : "));
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

/**
 * @brief Traite une requête HTTP GET relative à l'état de la boîte aux lettres
 * @fn ServeurWeb::traiterRequeteGETBoite
 * @details Cette méthode est appelée lorsqu'une requête HTTP GET relative à l'état de la boîte aux
 lettres est reçue par le serveur web.
 */
void ServeurWeb::traiterRequeteGETBoite()
{
#ifdef DEBUG_SERVEUR_WEB
    Serial.print(F("ServeurWeb::traiterRequeteGETBoite() : requête = "));
    Serial.println((method() == HTTP_GET) ? "GET" : "POST");
    Serial.print(F("URI : "));
    Serial.println(uri());
    Serial.print(F("Nb arguments : "));
    Serial.println(args());
    for(int i = 0; i < args(); ++i)
    {
        Serial.print("argument : ");
        Serial.print(argName(i));
        Serial.print(" -> ");
        Serial.println(arg(i));
    }
#endif

    /**
     * @todo Répondre à la requête
     */
}

/**
 * @brief Traite la requête POST de la boîte aux lettres
 * @fn ServeurWeb::traiterRequetePOSTBoite
 * @details Récupère la demande POST de la boîte aux lettres envoyée par le client et vérifie si
 elle est correcte. Ensuite, détermine l'état de la boîte aux lettres et l'enregistre dans l'objet
 StationLumineuse. Si la demande est correcte, envoie une réponse JSON de confirmation au client. Si
 la demande est incorrecte, envoie une réponse JSON d'erreur correspondante au client.
 */
void ServeurWeb::traiterRequetePOSTBoite()
{
#ifdef DEBUG_SERVEUR_WEB
    Serial.print(F("ServeurWeb::traiterRequetePOSTBoite() : requête = "));
    Serial.println((method() == HTTP_GET) ? "GET" : "POST");
    Serial.print(F("URI : "));
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
            Serial.print(F("etat : "));
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

/**
 * @brief Traite la requête POST pour modifier l'état d'une machine
 * @fn ServeurWeb::traiterRequetePOSTMachine
 * @details Récupère la demande POST de la machine envoyée par le client et vérifie si elle est
 correcte. Ensuite, détermine l'état de la machine et l'enregistre dans l'objet StationLumineuse. Si
 la demande est correcte, envoie une réponse JSON de confirmation au client. Si la demande est
 incorrecte, envoie une réponse JSON d'erreur correspondante au client.
 */
void ServeurWeb::traiterRequetePOSTMachine()
{
#ifdef DEBUG_SERVEUR_WEB
    Serial.print(F("ServeurWeb::traiterRequetePOSTMachine() : requête = "));
    Serial.println((method() == HTTP_GET) ? "GET" : "POST");
    Serial.print(F("URI : "));
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
            Serial.print(F("numeroMachine : "));
            Serial.println(documentJSON["numeroMachine"].as<int>());
            Serial.print(F("etat : "));
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

/**
 * @brief Traite la requête POST pour modifier l'état d'une poubelle
 * @fn ServeurWeb::traiterRequetePOSTPoubelle
 * @details Récupère la demande POST de la poubelle envoyée par le client et vérifie si elle est
 correcte. Ensuite, détermine l'état de la poubelle et l'enregistre dans l'objet StationLumineuse.
    Si la demande est correcte, envoie une réponse JSON de confirmation au client.
    Si la demande est incorrecte, envoie une réponse JSON d'erreur correspondante au client.
 */
void ServeurWeb::traiterRequetePOSTPoubelle()
{
#ifdef DEBUG_SERVEUR_WEB
    Serial.print(F("ServeurWeb::traiterRequetePOSTPoubelle() : requête = "));
    Serial.println((method() == HTTP_GET) ? "GET" : "POST");
    Serial.print(F("URI : "));
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
        if(objetJSON.containsKey("etat") && objetJSON.containsKey("numeroPoubelle"))
        {
#ifdef DEBUG_SERVEUR_WEB
            Serial.print(F("numeroPoubelle : "));
            Serial.println(documentJSON["numeroPoubelle"].as<int>());
            Serial.print(F("etat : "));
            Serial.println(documentJSON["etat"].as<bool>());
#endif

            // Modifier l'état de la Poubelle ici
            int  numeroPoubelle = documentJSON["numeroPoubelle"].as<int>();
            bool etatPoubelle   = documentJSON["etat"].as<bool>();

            if(stationLumineuse->estIdValidePoubelle(numeroPoubelle))
            {
                stationLumineuse->setEtatPoubelle(numeroPoubelle, etatPoubelle);

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
                     "\"La poubelle demandée n'existe pas.\"}}");
            }
        }
        else
        {
#ifdef DEBUG_SERVEUR_WEB
            Serial.print(F("Erreur : champ etat ou numeroPoubelle manquant"));
#endif
            send(400,
                 "application/json",
                 "{\"error\": { \"code\": \"invalidRequest\", \"message\": "
                 "\"La demande est incomplète.\"}}");
            return;
        }
    }
}

/**
 * @brief Traite une requête qui n'a pas été trouvée
 * @fn ServeurWeb::traiterRequeteNonTrouvee
 * @details Récupère les informations de la requête (URI, méthode, arguments) et les concatène dans
 un message d'erreur de type 404. Envoie ensuite ce message au client qui a effectué la requête.
 */
void ServeurWeb::traiterRequeteNonTrouvee()
{
#ifdef DEBUG_SERVEUR_WEB
    Serial.print(F("ServeurWeb::traiterRequeteNonTrouvee() : requête = "));
    Serial.println((method() == HTTP_GET) ? "GET" : "POST");
    Serial.print(F("URI : "));
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
