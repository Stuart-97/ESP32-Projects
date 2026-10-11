#include <Arduino.h>
#include <WiFi.h>

// Print a readable description of the advertised
// Wi-Fi authentication mode.
const char* getSecurityType(wifi_auth_mode_t security) {
    switch (security) {
        case WIFI_AUTH_OPEN:
            return "OPEN";

        case WIFI_AUTH_WEP:
            return "WEP";

        case WIFI_AUTH_WPA_PSK:
            return "WPA";

        case WIFI_AUTH_WPA2_PSK:
            return "WPA2";

        case WIFI_AUTH_WPA_WPA2_PSK:
            return "WPA/WPA2";

        case WIFI_AUTH_WPA2_ENTERPRISE:
            return "WPA2-ENT";

        case WIFI_AUTH_WPA3_PSK:
            return "WPA3";

        case WIFI_AUTH_WPA2_WPA3_PSK:
            return "WPA2/WPA3";

        default:
            return "OTHER";
    }
}

void printHeader() {
    Serial.println();
    Serial.println("==============================================================");
    Serial.println("               ESP32 WI-FI ENVIRONMENT SCANNER");
    Serial.println("==============================================================");

    Serial.printf(
        "%-3s %-28s %-18s %-4s %-6s %s\n",
        "#",
        "SSID",
        "BSSID",
        "CH",
        "RSSI",
        "SECURITY"
    );

    Serial.println("--------------------------------------------------------------");
}

void scanWiFi() {
    Serial.println("\nScanning nearby Wi-Fi networks...");

    // Scan without connecting to discovered networks.
    // The second argument requests hidden networks too.
    int networkCount = WiFi.scanNetworks(false, true);

    if (networkCount < 0) {
        Serial.printf("Scan failed. Error: %d\n", networkCount);
        WiFi.scanDelete();
        return;
    }

    Serial.printf("Networks discovered: %d\n\n", networkCount);

    printHeader();

    for (int i = 0; i < networkCount; i++) {
        String ssid = WiFi.SSID(i);

        if (ssid.length() == 0) {
            ssid = "<hidden>";
        }

        Serial.printf(
            "%-3d %-28.28s %-18s %-4d %-6d %s\n",
            i + 1,
            ssid.c_str(),
            WiFi.BSSIDstr(i).c_str(),
            WiFi.channel(i),
            WiFi.RSSI(i),
            getSecurityType(WiFi.encryptionType(i))
        );
    }

    Serial.println("--------------------------------------------------------------");
    Serial.println("Scan complete.");

    // Free memory used by the scan results.
    WiFi.scanDelete();
}

void setup() {
    Serial.begin(115200);
    delay(1000);

    Serial.println("\nStarting ESP32 Wi-Fi Environment Scanner...");

    // Enable station mode without connecting to an AP.
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();

    delay(200);

    Serial.println("Scanner initialized.");
}

void loop() {
    scanWiFi();

    // Wait 10 seconds between scans.
    delay(10000);
}