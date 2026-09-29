# ESP32-S3 Cryptographic Performance Benchmark: ChaCha20 vs. Ascon-128

This repository presents an empirical benchmarking study comparing two modern cryptographic algorithms—**ChaCha20** (Stream Cipher) and **Ascon-128** (NIST-standardized Lightweight AEAD)—implemented on an ESP32-S3 microcontroller.

## 📌 Test Environment & Hardware Setup
* **Microcontroller:** ESP32-S3-DevKitC-1 (Xtensa® 32-bit LX7 Dual-Core @ 240MHz)
* **Framework:** Arduino / PlatformIO
* **Libraries Used:** `rweather/Crypto` & `rweather/CryptoLW`
* **Payload Size:** 64 Bytes
* **Baud Rate:** 115200

---

## 📊 Benchmark Results

| Metric | ChaCha20 | Ascon-128 |
| :--- | :--- | :--- |
| **Algorithm Type** | Stream Cipher (Encryption Only) | Lightweight AEAD (Encryption + Auth Tag) |
| **Avg. Encryption Time (64B)** | **14.23 µs** | **47.73 µs** |
| **Throughput** | **~4395 KB/s** | **1309.42 KB/s** |
| **Free Heap RAM** | **~373 KB** | **373.36 KB** |

---

## 🔍 Key Technical Takeaways

1. **ChaCha20 Performance Advantage:**
   * Demonstrates ~3.3x higher throughput compared to Ascon-128 on this platform.
   * Its ARX (Add-Rotate-XOR) design natively aligns with the 32-bit execution units of the Xtensa LX7 processor.
   * Best suited for high-bandwidth applications like live media streaming or rapid network transmission.

2. **Ascon-128 Security & Overhead:**
   * Provides **Authenticated Encryption with Associated Data (AEAD)**, ensuring message integrity and authenticity alongside confidentiality.
   * Standardized by NIST for lightweight cryptography (LWC), optimized for low-resource hardware/ASIC footprints.
   * Ideal for resource-constrained IoT sensors, telemetry, and secure command verification where data integrity is paramount.

---

## ⚙️ Project Structure & Reproduction
1. Clone this repository.
2. Open in **VS Code** with **PlatformIO** extension.
3. Build and upload to your ESP32-S3 development board.
4. Open Serial Monitor at `115200` baud rate to observe the real-time execution metrics.
---

## ⚠️ Methodological Limitation

This benchmark compares **ChaCha20 in isolation (encryption-only)** against **Ascon-128 as a full AEAD construction (encryption + authentication tag generation)**. This is not a strictly equivalent comparison, since Ascon-128 performs additional computation per call — generating and verifying an authentication tag — that raw ChaCha20 does not.

A more precise, protocol-equivalent comparison would benchmark **ChaCha20-Poly1305** (the AEAD construction actually used in WireGuard) against **Ascon-128**, since both would then provide the same security guarantees (confidentiality + integrity + authenticity). Some portion of the throughput gap reported above is therefore attributable to this difference in functional scope, not purely to raw cipher speed.

---

## 🔭 Ongoing Development

An adaptive cipher-selection extension is currently in progress, where an on-device decision layer (a compact classifier running directly on the ESP32-S3) chooses between ChaCha20 and Ascon-128 dynamically based on runtime system metrics (free heap, battery level, payload size, and priority). Early implementation is available in a separate branch/repository.
