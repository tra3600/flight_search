# flight_search
programme en C++ qui se connecte aux sites de companies aérienne et détermine le prix aller retour le moins cher pour aller en Thaïlande en temps réel avec une fenêtre temporelle de réservation de 6 a  10 mois

Écrire un programme en C++ qui se connecte aux sites de compagnies aériennes pour déterminer le prix aller-retour le moins cher pour aller en Thaïlande est une tâche complexe. Cela nécessite des fonctionnalités avancées telles que l'interaction avec des API web, la gestion des données en temps réel, et la manipulation des dates. De plus, accéder aux données de vol en temps réel implique souvent l'utilisation d'API fournies par des services de recherche de vols comme Skyscanner, Kiwi, ou Google Flights.

Voici les étapes pour créer un tel programme :

Utilisation d'une API de recherche de vols : Utiliser une API comme celle de Skyscanner, Kiwi, ou Google Flights pour obtenir les données de vol.
Manipulation des dates : Calculer les dates de départ et de retour dans une fenêtre de réservation de 6 à 10 mois à partir de la date actuelle.
Gestion des requêtes HTTP : Envoyer des requêtes HTTP à l'API et traiter les réponses JSON.
Pour cet exemple, nous allons utiliser l'API de Skyscanner. Vous devez vous inscrire sur leur site web pour obtenir une clé API.

Exemple de Code
Configuration de l'environnement
Installer les bibliothèques nécessaires : Vous aurez besoin de libcurl pour les requêtes HTTP et de jsoncpp pour traiter les réponses JSON.

sudo apt-get install libcurl4-openssl-dev libjsoncpp-dev

Explications
FlightSearch Class:

Constructeur : Initialise la clé API.
sendRequest : Envoie une requête HTTP à l'API Skyscanner et récupère la réponse.
generateDateRange : Génère une plage de dates pour les 6 à 10 prochains mois.
findCheapestFlight : Recherche le vol aller-retour le moins cher pour une plage de dates donnée.
Main Function:

Initialise la classe FlightSearch avec la clé API.
Génère une plage de dates pour les 6 à 10 prochains mois.
Recherche et affiche le vol aller-retour le moins cher de Paris et de Rome à Bangkok.
Compilation et Exécution
Assurez-vous d'avoir installé les bibliothèques libcurl et jsoncpp, puis compilez et exécutez le programme avec :

g++ -o flight_search main.cpp FlightSearch.cpp -lcurl -ljsoncpp
./flight_search

Note
Pour utiliser ce programme, vous devez remplacer "YOUR_API_KEY" par votre propre clé API Skyscanner. De plus, l'API Skyscanner peut avoir des limitations d'accès et des conditions d'utilisation qu'il est important de respecter. Pour des prédictions et des analyses plus précises, des modèles économiques avancés et des données en temps réel seraient nécessaires.
