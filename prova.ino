#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <DHT.h>

// Parametri WiFi
const char* ssid = "TUA_SSID";
const char* password = "TUA_PASSWORD";

// Pin del sensore DHT
#define DHTPIN 4 // Modifica in base al pin a cui è collegato il sensore
#define DHTTYPE DHT22 // Usa DHT11 se hai il DHT11

DHT dht(DHTPIN, DHTTYPE);

// Crea un server web asincrono sulla porta 80
AsyncWebServer server(80);

// Variabili per i dati del sensore
float temperature = 0.0;
float humidity = 0.0;

void setup() {
  // Inizializza seriale
  Serial.begin(115200);
  
  // Connessione al WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connessione al WiFi...");
  }
  Serial.println("Connesso al WiFi!");
  Serial.print("IP assegnato: ");
  Serial.println(WiFi.localIP());

  // Inizializza il sensore DHT
  dht.begin();

  // Imposta la pagina principale del server
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    // Leggi i valori del sensore
    temperature = dht.readTemperature();
    humidity = dht.readHumidity();

    // Controlla se i valori letti sono validi
    if (isnan(temperature) || isnan(humidity)) {
      temperature = 0.0;
      humidity = 0.0;
    }

    // Crea la risposta HTML con i dati del sensore
    String html = "<html><body>";
    html += "<h1>Valori del sensore</h1>";
    html += "<p>Temperatura: " + String(temperature) + " &deg;C</p>";
    html += "<p>Umidità: " + String(humidity) + " %</p>";
    html += "</body></html>";

    // Invia la risposta al client
    request->send(200, "text/html", html);
  });

  // Avvia il server
  server.begin();
}

void loop() {
  // Non è necessario fare nulla nel loop, il server web gestisce tutto asincronicamente
}
