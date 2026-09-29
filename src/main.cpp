#include <Arduino.h>
#include <ChaCha.h>
#include <Ascon128.h>

// Payload configuration (64 Bytes)
uint8_t plaintext[64];
uint8_t ciphertext[64];
uint8_t key[32] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
                   0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10,
                   0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18,
                   0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20};
uint8_t iv[12]  = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
                   0x09, 0x0A, 0x0B, 0x0C};

void benchmarkChaCha20() {
    ChaCha chacha;
    chacha.setKey(key, 32);
    chacha.setIV(iv, 8);

    unsigned long start = micros();
    chacha.encrypt(ciphertext, plaintext, sizeof(plaintext));
    unsigned long duration = micros() - start;

    Serial.print("ChaCha20 (64B) Encryption Time: ");
    Serial.print(duration);
    Serial.println(" µs");
}

void benchmarkAscon128() {
    Ascon128 ascon;
    ascon.setKey(key, 16);
    ascon.setIV(iv, 12);

    unsigned long start = micros();
    ascon.encrypt(ciphertext, plaintext, sizeof(plaintext));
    unsigned long duration = micros() - start;

    Serial.print("Ascon-128 (64B) Encryption Time: ");
    Serial.print(duration);
    Serial.println(" µs");
}

void setup() {
    Serial.begin(115200);
    while (!Serial);
    delay(2000);

    Serial.println("=== ESP32-S3 Crypto Benchmark Started ===");
    memset(plaintext, 0xAA, sizeof(plaintext));

    benchmarkChaCha20();
    benchmarkAscon128();

    Serial.print("Free Heap RAM: ");
    Serial.print(ESP.getFreeHeap() / 1024.0);
    Serial.println(" KB");
}

void loop() {
    // Idle
}
