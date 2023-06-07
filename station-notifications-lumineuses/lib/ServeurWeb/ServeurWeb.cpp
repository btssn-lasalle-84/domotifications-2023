/**
 * @file ServeurWeb.cpp
 * @brief Définition de la classe ServeurWeb
 * @author Alexis Vaillen
 * @version 0.2
 */

#include "ServeurWeb.h"
#include "StationLumineuse.h"
#include <ESPmDNS.h>

/**
 * @brief Constructeur de la classe ServeurWeb
 * @fn ServeurWeb::ServeurWeb
 * @param stationLumineuse Pointeur vers l'objet de la classe StationLumineuse
 * @details Initialise un nouvel objet ServeurWeb en utilisant le constructeur de la classe de base WebServer. Le pointeur vers l'objet de la classe StationLumineuse 
 * est stocké dans la variable membre stationLumineuse.
 */
ServeurWeb::ServeurWeb(StationLumineuse* stationLumineuse) :
    WebServer(PORT_SERVEUR_WEB), stationLumineuse(stationLumineuse)
{
}

/**
 * @brief Démarre le serveur web et installe les gestionnaires de requêtes
 * @fn ServeurWeb::demarrer
 * @details Cette méthode configure et démarre le serveur Web. Elle définit les gestionnaires de requêtes pour les différentes routes, puis démarre le serveur 
 * en utilisant la méthode begin(). Le serveur sera accessible à partir de l'adresse IP locale obtenue via la connexion WiFi.
 */
void ServeurWeb::demarrer()
{
    setNom();
#ifdef DEBUG_SERVEUR_WEB
    Serial.print(F("ServeurWeb::demarrer() : adresse IP = "));
    Serial.println(WiFi.localIP());
#endif
    // Installe les gestionnaires de requêtes
    on("/", HTTP_GET, std::bind(&ServeurWeb::afficherAccueil, this));
    on("/notifications", std::bind(&ServeurWeb::traiterRequeteGETNotifications, this));
    on("/notification",std::bind(&ServeurWeb::traiterRequetePOSTNotifications, this));


    on("/activations", HTTP_GET, std::bind(&ServeurWeb::traiterRequeteGETActivations, this));
    on("/activation", HTTP_POST, std::bind(&ServeurWeb::traiterRequetePOSTActivation, this));

    on("/boite", HTTP_GET, std::bind(&ServeurWeb::traiterRequeteGETBoite, this));
    on("/boite", HTTP_POST, std::bind(&ServeurWeb::traiterRequetePOSTBoite, this));
    on("/machine", HTTP_GET, std::bind(&ServeurWeb::traiterRequeteGETMachine, this));
    on("/machine",
       HTTP_POST,
       std::bind(&ServeurWeb::traiterRequetePOSTMachine,
                 this)); // Ajout de la route /machine en POST
    on("/poubelle", HTTP_GET, std::bind(&ServeurWeb::traiterRequeteGETPoubelle, this));
    on("/poubelle",
       HTTP_POST,
       std::bind(&ServeurWeb::traiterRequetePOSTPoubelle,
                 this)); // Ajout de la route /poubelle en POST
    on("/intervallePoubelle", HTTP_POST, std::bind(&ServeurWeb::traiterRequetePOSTIntervallePoubelle, this));

    onNotFound(std::bind(&ServeurWeb::traiterRequeteNonTrouvee, this));

    // Démarre le serveur
    begin();

#ifdef DEBUG_SERVEUR_WEB
    Serial.println(F("ServeurWeb::demarrer() ok"));
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
  * @brief Définit le nom du serveur Web
  * @fn ServeurWeb::setNom
  * @param nomStationLumineuse Le nom du serveur Web à utiliser
  * @details Cette méthode permet de définir le nom du serveur Web. Si aucun nom n'est spécifié, le nom par défaut NOM_SERVEUR_WEB sera utilisé. 
  *  Le serveur sera accessible à partir de l'adresse http://nomStationLumineuse.local/. La méthode utilise le service mDNS pour permettre 
  *  l'accès au serveur avec un nom d'hôte convivial.
  */
void ServeurWeb::setNom(String nomStationLumineuse)
{
    if(nomStationLumineuse.isEmpty())
        nomStationLumineuse = NOM_SERVEUR_WEB;
    // Pour un accès : http://nomStationLumineuse.local/
    if(!MDNS.begin(nomStationLumineuse.c_str()))
    {
#ifdef DEBUG_SERVEUR_WEB
        Serial.println(F("setNom() Erreur mDNS !"));
#endif
    }
    else
    {
#ifdef DEBUG_SERVEUR_WEB
        Serial.println("setNom() http://" + nomStationLumineuse + ".local/");
#endif
    }
}

/**
  * @brief Installe les gestionnaires de requêtes
  * @fn ServeurWeb::installerGestionnairesRequetes
  * @details Cette méthode installe les gestionnaires de requêtes pour les différentes routes du serveur Web. Les gestionnaires sont définis à l'aide de la méthode
  *  on(). Les routes sont associées aux méthodes de traitement des requêtes correspondantes.
  */
void ServeurWeb::installerGestionnairesRequetes()
{

    on("/", HTTP_GET, std::bind(&ServeurWeb::afficherAccueil, this));
    on("/notifications", std::bind(&ServeurWeb::traiterRequeteGETNotifications, this));
    on("/notification",std::bind(&ServeurWeb::traiterRequetePOSTNotifications, this));

    on("/activations", HTTP_GET, std::bind(&ServeurWeb::traiterRequeteGETActivations, this));
    on("/activation", HTTP_POST, std::bind(&ServeurWeb::traiterRequetePOSTActivation, this));

    on("/boite", HTTP_GET, std::bind(&ServeurWeb::traiterRequeteGETBoite, this));
    on("/boite", HTTP_POST, std::bind(&ServeurWeb::traiterRequetePOSTBoite, this));
    on("/machine", HTTP_GET, std::bind(&ServeurWeb::traiterRequeteGETMachine, this));
    on("/machine",
       HTTP_POST,
       std::bind(&ServeurWeb::traiterRequetePOSTMachine,
                 this)); // Ajout de la route /machine en POST
    on("/poubelle", HTTP_GET, std::bind(&ServeurWeb::traiterRequeteGETPoubelle, this));
    on("/poubelle",
       HTTP_POST,
       std::bind(&ServeurWeb::traiterRequetePOSTPoubelle,
                 this)); // Ajout de la route /poubelle en POST
    on("/intervallePoubelle", HTTP_POST, std::bind(&ServeurWeb::traiterRequetePOSTIntervallePoubelle, this));
    onNotFound(std::bind(&ServeurWeb::traiterRequeteNonTrouvee, this));
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
    message += "<p>LaSalle Avignon v1.0</p>\n";
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
    JsonArray poubelle = documentJSON.createNestedArray("poubelles");
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

void ServeurWeb::traiterRequetePOSTNotifications()
{
#ifdef DEBUG_SERVEUR_WEB
    Serial.print(F("ServeurWeb::traiterRequetePOSTNotifications() : requête = "));
    Serial.println((method() == HTTP_POST) ? "POST" : "GET");
    Serial.print(F("URI : "));
    Serial.println(uri());
#endif

    if(method() == HTTP_POST)
    {
        documentJSON.clear();
        documentJSON["boite"] = stationLumineuse->getEtatBoiteAuxLettres();
        JsonArray machines    = documentJSON.createNestedArray("machines");
        for(int i = 0; i < NB_LEDS_NOTIFICATION_MACHINES; ++i)
        {
            machines.add(stationLumineuse->getEtatMachine(i));
        }
        JsonArray poubelle = documentJSON.createNestedArray("poubelles");
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
    else
    {
        String message = "400 Bad Request\n\n";
        message += "URI: ";
        message += uri();
        message += "\nMethod: ";
        message += (method() == HTTP_POST) ? "POST" : "GET";
        message += "\nArguments: ";
        message += args();
        message += "\n";
        for(uint8_t i = 0; i < args(); i++)
        {
            message += " " + argName(i) + ": " + arg(i) + "\n";
        }
        send(400, "text/plain", message);
    }
}


/**
  * @brief Traite une requête GET pour obtenir les états d'activation
  * @fn ServeurWeb::traiterRequeteGETActivations
  * @details Cette méthode traite une requête GET pour obtenir les états d'activation de la station lumineuse. Elle récupère les états d'activation 
  * de la boîte aux lettres, des machines et des poubelles à l'aide des méthodes appropriées de la classe StationLumineuse, puis les stocke dans un document JSON.
  * Le document JSON est ensuite envoyé en réponse à la requête.
  */
void ServeurWeb::traiterRequeteGETActivations()
{
#ifdef DEBUG_SERVEUR_WEB
    Serial.print(F("ServeurWeb::traiterRequeteGETActivations() : requête = "));
    Serial.println((method() == HTTP_GET) ? "GET" : "POST");
    Serial.print(F("URI : "));
    Serial.println(uri());
#endif

    documentJSON.clear();
    documentJSON["boite"] =
      stationLumineuse
        ->getActivationBoiteAuxLettres(); // Remplacez par la méthode appropriée pour obtenir l'état
                                          // d'activation de la boîte aux lettres
    JsonArray machines = documentJSON.createNestedArray("machines");
    for(int i = 0; i < NB_LEDS_NOTIFICATION_MACHINES; ++i)
    {
        machines.add(stationLumineuse->getActivationMachine(
          i)); // Remplacez par la méthode appropriée pour obtenir l'état d'activation de la machine
    }
    JsonArray poubelles = documentJSON.createNestedArray("poubelles");
    for(int i = 0; i < NB_LEDS_NOTIFICATION_POUBELLES; ++i)
    {
        poubelles.add(
          stationLumineuse->getActivationPoubelle(i)); // Remplacez par la méthode appropriée pour
                                                       // obtenir l'état d'activation de la poubelle
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
  * @brief Traite une requête POST pour modifier les activations
  * @fn ServeurWeb::traiterRequetePOSTActivation
  * @details Cette méthode traite une requête POST pour modifier les activations de la station lumineuse. Elle récupère les données de la requête, 
  * telles que l'état, l'ID et le module concernés, à l'aide de la méthode arg() de la classe WebServer. Ensuite, elle utilise les méthodes appropriées 
  * de la classe StationLumineuse pour modifier les activations correspondantes. La méthode renvoie une réponse JSON indiquant le succès de l'opération ou une 
  * erreur si les données de la requête sont incorrectes ou invalides.
  */
void ServeurWeb::traiterRequetePOSTActivation()
{
#ifdef DEBUG_SERVEUR_WEB
    Serial.print(F("ServeurWeb::traiterRequetePOSTActivation() : requête = "));
    Serial.println((method() == HTTP_GET) ? "GET" : "POST");
    Serial.print(F("URI : "));
    Serial.println(uri());
#endif

    if (hasArg("plain") == false)
    {
#ifdef DEBUG_SERVEUR_WEB
        Serial.println(F("Erreur !"));
#endif
        send(400,
             "application/json",
             "{\"error\": { \"code\": \"invalidRequest\", \"message\": \"La demande est vide ou "
             "incorrecte.\"}}");
        return;
    }

    String body = arg("plain");
#ifdef DEBUG_SERVEUR_WEB
    Serial.println(body);
#endif
    DeserializationError erreur = deserializeJson(documentJSON, body);
    if (erreur)
    {
#ifdef DEBUG_SERVEUR_WEB
        Serial.print(F("Erreur deserializeJson() : "));
        Serial.println(erreur.f_str());
#endif
        send(400,
             "application/json",
             "{\"error\": { \"code\": \"invalidRequest\", \"message\": \"La demande est mal "
             "exprimée ou incorrecte.\"}}");
        return;
    }
    else
    {
        JsonObject objetJSON = documentJSON.as<JsonObject>();
        if (objetJSON.containsKey("etat") && objetJSON.containsKey("id") &&
            objetJSON.containsKey("module"))
        {
#ifdef DEBUG_SERVEUR_WEB
            Serial.print(F("module : "));
            Serial.println(documentJSON["module"].as<String>());
            Serial.print(F("id : "));
            Serial.println(documentJSON["id"].as<int>());
            Serial.print(F("etat : "));
            Serial.println(documentJSON["etat"].as<bool>());
#endif

            String module = documentJSON["module"].as<String>();
            int id = documentJSON["id"].as<int>();
            bool etat = documentJSON["etat"].as<bool>();

            if (module == "machine")
            {
                if (stationLumineuse->estIdValideMachine(id))
                {
                    // Vérifier si l'état a changé
                    if (stationLumineuse->getActivationMachine(id) != etat)
                    {
                        // Réinitialiser l'état des LED
                        stationLumineuse->resetEtatMachines(id);
                    }
                    stationLumineuse->setActivationMachine(id, etat);
                    send(200, "application/json", "{\"machine\": \"ok\"}");
                }
                else
                {
                    send(404,
                         "application/json",
                         "{\"error\": { \"code\": \"notFound\", \"message\": \"La machine demandée "
                         "n'existe pas.\"}}");
                }
            }
            else if (module == "poubelle")
            {
                if (stationLumineuse->estIdValidePoubelle(id))
                {
                    // Vérifier si l'état a changé
                    if (stationLumineuse->getActivationPoubelle(id) != etat)
                    {
                        // Réinitialiser l'état des LED
                        stationLumineuse->resetEtatPoubelles(id);
                    }
                    stationLumineuse->setActivationPoubelle(id, etat);
                    send(200, "application/json", "{\"poubelle\": \"ok\"}");
                }
                else
                {
                    send(404,
                         "application/json",
                         "{\"error\": { \"code\": \"notFound\", \"message\": \"La poubelle "
                         "demandée n'existe pas.\"}}");
                }
            }
            else if (module == "boite")
            {
                // Vérifier si l'état a changé
                if (stationLumineuse->getActivationBoiteAuxLettres() != etat)
                {
                    // Réinitialiser l'état des LED
                    stationLumineuse->resetEtatBoiteAuxLettres();
                }
                stationLumineuse->setActivationBoiteAuxLettres(etat);
                send(200, "application/json", "{\"boite\": \"ok\"}");
            }
            else
            {
#ifdef DEBUG_SERVEUR_WEB
                Serial.print(F("Erreur : module non reconnu"));
#endif
                send(400,
                     "application/json",
                     "{\"error\": { \"code\": \"invalidRequest\", \"message\": \"Le module "
                     "spécifié n'est pas reconnu.\"}}");
                return;
            }
        }
        else
        {
#ifdef DEBUG_SERVEUR_WEB
            Serial.print(F("Erreur : champ etat, id ou module manquant"));
#endif
            send(400,
                 "application/json",
                 "{\"error\": { \"code\": \"invalidRequest\", \"message\": \"La demande est "
                 "incomplète.\"}}");
            return;
        }
    }
}


/**
 * @brief Traite une requête HTTP GET relative à la boîte aux lettres
 * @fn ServeurWeb::traiterRequeteGETBoite
 * @details Cette méthode est appelée lorsqu'une requête HTTP GET relative à la boîte aux
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
    // les arguments du type : /boite?etat=true
    for(int i = 0; i < args(); ++i)
    {
        Serial.print("argument : ");
        Serial.print(argName(i));
        Serial.print(" -> ");
        Serial.println(arg(i));
    }
#endif

    if(hasArg("etat"))
    {
        bool etat = (arg("etat") == "1") || (arg("etat") == "true");

#ifdef DEBUG_SERVEUR_WEB
        Serial.print(F("etat : "));
        Serial.println(etat);
#endif

        // Modifie l'état de la boîte
        stationLumineuse->setEtatBoiteAuxLettres(etat);

        send(200,
             "application/json",
             "{\"boite\": "
             "\"ok\"}");
    }
    else
    {
        // Récupérer l'état actuel de la boîte aux lettres
        bool etat = stationLumineuse->getEtatBoiteAuxLettres();

        // Répondre à la requête en donnant l'état de la boîte aux lettres
        String jsonResponse = "{\"etat\": ";
        jsonResponse += etat ? "true" : "false";
        jsonResponse += "}";
        send(200, "application/json", jsonResponse);
    }
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
                 "{\"boite\": "
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
 * @brief Traite une requête HTTP GET relative à une machine
 * @fn ServeurWeb::traiterRequeteGETMachine
 * @details Cette méthode est appelée lorsqu'une requête HTTP GET relative à une machine est reçue
 * par le serveur web.
 */
void ServeurWeb::traiterRequeteGETMachine()
{
#ifdef DEBUG_SERVEUR_WEB
    Serial.print(F("ServeurWeb::traiterRequeteGETMachine() : requête = "));
    Serial.println((method() == HTTP_GET) ? "GET" : "POST");
    Serial.print(F("URI : "));
    Serial.println(uri());
    Serial.print(F("Nb arguments : "));
    Serial.println(args());
    // les arguments du type : /machine?id=x&etat=true
    for(int i = 0; i < args(); ++i)
    {
        Serial.print("argument : ");
        Serial.print(argName(i));
        Serial.print(" -> ");
        Serial.println(arg(i));
    }
#endif

    if(hasArg("id") && hasArg("etat"))
    {
        int  id   = arg("id").toInt();
        bool etat = (arg("etat") == "1") || (arg("etat") == "true");

#ifdef DEBUG_SERVEUR_WEB
        Serial.print(F("id : "));
        Serial.println(id);
        Serial.print(F("etat : "));
        Serial.println(etat);
#endif

        if(stationLumineuse->estIdValideMachine(id))
        {
            // Modifie l'état de la machine
            stationLumineuse->setEtatMachine(id, etat);

            send(200,
                 "application/json",
                 "{\"machine\": "
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
    else if(hasArg("id"))
    {
        int id = arg("id").toInt();
        if(stationLumineuse->estIdValideMachine(id))
        {
            // Récupérer l'état actuel de la machine
            bool etat = stationLumineuse->getEtatMachine(id);

            // Répondre à la requête en donnant l'état de la machine
            String jsonResponse = "{\"id\": ";
            jsonResponse += id;
            jsonResponse += ", \"etat\": ";
            jsonResponse += etat ? "true" : "false";
            jsonResponse += "}";
            send(200, "application/json", jsonResponse);
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
        // Construire le JSON de réponse
        String jsonResponse = "{ \"machines\": {";
        for(int i = 0; i < NB_LEDS_NOTIFICATION_MACHINES; ++i)
        {
            bool etat = stationLumineuse->getEtatMachine(i);
            jsonResponse += "\"";
            jsonResponse += i;
            jsonResponse += "\": ";
            jsonResponse += etat ? "true" : "false";

            if(i < NB_LEDS_NOTIFICATION_MACHINES - 1)
            {
                jsonResponse += ",";
            }
        }
        jsonResponse += "} }";
        send(200, "application/json", jsonResponse);
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
        int  numeroMachine = extraireId();
        bool etatMachine   = extraireEtat();

        if(stationLumineuse->estIdValideMachine(numeroMachine))
        {
            stationLumineuse->setEtatMachine(numeroMachine, etatMachine);

            send(200,
                 "application/json",
                 "{\"machine\": "
                 "\"ok\"}");
        }
        else
        {
#ifdef DEBUG_SERVEUR_WEB
            Serial.print(F("Erreur : champ id invalide"));
#endif
            send(400,
                 "application/json",
                 "{\"error\": { \"code\": \"invalidRequest\", \"message\": "
                 "\"La demande est invalide.\"}}");
        }
    }
}

/**
 * @brief Traite une requête HTTP GET relative à une poubelle
 * @fn ServeurWeb::traiterRequeteGETPoubelle
 * @details Cette méthode est appelée lorsqu'une requête HTTP GET relative à une poubelle est reçue
 * par le serveur web.
 */
void ServeurWeb::traiterRequeteGETPoubelle()
{
#ifdef DEBUG_SERVEUR_WEB
    Serial.print(F("ServeurWeb::traiterRequeteGETPoubelle() : requête = "));
    Serial.println((method() == HTTP_GET) ? "GET" : "POST");
    Serial.print(F("URI : "));
    Serial.println(uri());
    Serial.print(F("Nb arguments : "));
    Serial.println(args());
    // les arguments du type : /poubelle?id=x&etat=true
    for(int i = 0; i < args(); ++i)
    {
        Serial.print("argument : ");
        Serial.print(argName(i));
        Serial.print(" -> ");
        Serial.println(arg(i));
    }
#endif

    if(hasArg("id") && hasArg("etat"))
    {
        int  id   = arg("id").toInt();
        bool etat = (arg("etat") == "1") || (arg("etat") == "true");

#ifdef DEBUG_SERVEUR_WEB
        Serial.print(F("id : "));
        Serial.println(id);
        Serial.print(F("etat : "));
        Serial.println(etat);
#endif

        if(stationLumineuse->estIdValidePoubelle(id))
        {
            // Modifie l'état de la poubelle
            stationLumineuse->setEtatPoubelle(id, etat);

            send(200,
                 "application/json",
                 "{\"poubelle\": "
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
    else if(hasArg("id"))
    {
        int id = arg("id").toInt();
        if(stationLumineuse->estIdValidePoubelle(id))
        {
            // Récupérer l'état actuel de la poubelle
            bool etat = stationLumineuse->getEtatPoubelle(id);

            // Répondre à la requête en donnant l'état de la Poubelle
            String jsonResponse = "{\"id\": ";
            jsonResponse += id;
            jsonResponse += ", \"etat\": ";
            jsonResponse += etat ? "true" : "false";
            jsonResponse += "}";
            send(200, "application/json", jsonResponse);
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
        // Construire le JSON de réponse
        String jsonResponse = "{ \"poubelles\": {";
        for(int i = 0; i < NB_LEDS_NOTIFICATION_POUBELLES; ++i)
        {
            bool etat = stationLumineuse->getEtatPoubelle(i);
            jsonResponse += "\"";
            jsonResponse += i;
            jsonResponse += "\": ";
            jsonResponse += etat ? "true" : "false";

            if(i < NB_LEDS_NOTIFICATION_POUBELLES - 1)
            {
                jsonResponse += ",";
            }
        }
        jsonResponse += "} }";
        send(200, "application/json", jsonResponse);
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
        if(objetJSON.containsKey("etat") && objetJSON.containsKey("id"))
        {
#ifdef DEBUG_SERVEUR_WEB
            Serial.print(F("id : "));
            Serial.println(documentJSON["id"].as<int>());
            Serial.print(F("etat : "));
            Serial.println(documentJSON["etat"].as<bool>());
#endif

            // Modifier l'état de la Poubelle ici
            int  numeroPoubelle = documentJSON["id"].as<int>();
            bool etatPoubelle   = documentJSON["etat"].as<bool>();

            if(stationLumineuse->estIdValidePoubelle(numeroPoubelle))
            {
                stationLumineuse->setEtatPoubelle(numeroPoubelle, etatPoubelle);

                send(200,
                     "application/json",
                     "{\"poubelle\": "
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
  * @brief Traite une requête POST pour modifier l'intervalle d'une poubelle
  * @fn ServeurWeb::traiterRequetePOSTIntervallePoubelle
  * @details Cette méthode traite une requête POST pour modifier l'intervalle d'une poubelle de la station lumineuse. Elle récupère les paramètres "intervalle"
  * et "id" de la requête, puis utilise ces valeurs pour modifier l'intervalle de la poubelle correspondante en appelant la méthode setIntervallePoubelle de
  * la classe StationLumineuse. Si la poubelle spécifiée n'existe pas, elle renvoie une réponse d'erreur. Sinon, elle renvoie une réponse indiquant que la
  * modification a été effectuée avec succès.
  * @return Aucune valeur de retour.
  */
void ServeurWeb::traiterRequetePOSTIntervallePoubelle()
{
#ifdef DEBUG_SERVEUR_WEB
    Serial.print(F("ServeurWeb::traiterRequetePOSTIntervallePoubelle() : requête = "));
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
        if(objetJSON.containsKey("intervalle") && objetJSON.containsKey("id"))
        {
#ifdef DEBUG_SERVEUR_WEB
            Serial.print(F("id : "));
            Serial.println(documentJSON["id"].as<int>());
            Serial.print(F("intervalle : "));
            Serial.println(documentJSON["intervalle"].as<int>());
#endif

            // Modifier l'intervalle de la Poubelle ici
            int  numeroPoubelle = documentJSON["id"].as<int>();
            int  intervallePoubelle   = documentJSON["intervalle"].as<int>();

            if(stationLumineuse->estIdValidePoubelle(numeroPoubelle))
            {
                stationLumineuse->setIntervallePoubelle(numeroPoubelle, intervallePoubelle);

                send(200,
                     "application/json",
                     "{\"poubelle\": "
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
            Serial.print(F("Erreur : champ intervalle ou numeroPoubelle manquant"));
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

/**
 * @brief Extrait l'id dans les données JSON
 * @fn ServeurWeb::extraireId
 * @return int l'id du module ou -1
 */
int ServeurWeb::extraireId()
{
    JsonObject objetJSON = documentJSON.as<JsonObject>();
    if(objetJSON.containsKey("id"))
    {
#ifdef DEBUG_SERVEUR_WEB
        Serial.print(F("id : "));
        Serial.println(documentJSON["id"].as<int>());
#endif
        return documentJSON["id"].as<int>();
    }
    return -1;
}

/**
 * @brief Extrait l'état dans les données JSON
 * @fn ServeurWeb::extraireEtat
 * @return bool
 */
bool ServeurWeb::extraireEtat()
{
    JsonObject objetJSON = documentJSON.as<JsonObject>();
    if(objetJSON.containsKey("etat"))
    {
#ifdef DEBUG_SERVEUR_WEB
        Serial.print(F("etat : "));
        Serial.println(documentJSON["etat"].as<bool>());
#endif

        return documentJSON["etat"].as<bool>();
    }
    return false;
}