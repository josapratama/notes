# IoT Firmware & Notes (ESP32 & ESP8266) ⚡

> Koleksi firmware web server kontrol nirkabel dan telemetri sensor untuk mikrokontroler ESP32 dan ESP8266 (NodeMCU / Wemos D1).

---

## 📁 Isi Repositori

| File | Mikrokontroler | Deskripsi |
|:---|:---|:---|
| [`esp32.ino`](./esp32.ino) | ESP32 DevKit v1 | Web server standalone untuk kontrol GPIO (LED internal Pin 2) melalui HTTP GET. |
| [`esp8266.ino`](./esp8266.ino) | NodeMCU / ESP8266 | Web server standalone dengan penanganan active-low LED untuk ESP8266. |

---

## 🛠️ Persyaratan & Library

- **Arduino IDE** (v2.0+) atau **VS Code PlatformIO**
- Board Package:
  - ESP32 by Espressif Systems (`https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`)
  - ESP8266 by ESP8266 Community (`http://arduino.esp8266.com/stable/package_esp8266com_index.json`)

---

## 🚀 Panduan Flashing & Penggunaan

1. Buka file `.ino` pada Arduino IDE.
2. Ubah baris kredensial Wi-Fi:
   ```cpp
   const char* ssid = "Nama_Wifi_Anda";
   const char* password = "Password_Wifi_Anda";
   ```
3. Pilih tipe board dan COM Port yang sesuai di menu *Tools*.
4. Klik **Upload**.
5. Buka **Serial Monitor** pada baudrate `115200` untuk melihat alamat IP yang didapat (misal: `http://192.168.1.50`).
6. Buka IP tersebut di browser smartphone/laptop yang berada dalam jaringan Wi-Fi yang sama untuk mengontrol perangkat.
