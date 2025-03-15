void setup() {
    Serial.begin(115200);
    Serial.println("Ciao Mondo! L'ESP32-C3 è pronto!");
}

void loop() {
    Serial.println("Ciao Mondo!");
    delay(10000);
}
