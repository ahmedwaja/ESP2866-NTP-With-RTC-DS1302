#include <Arduino.h>
#include <WiFiManager.h>
#include <WiFiUdp.h>
#include <Wire.h>
#include <NTPClient.h>
#include <TimeLib.h>
#include <virtuabotixRTC.h>

#define TRIGGER_PIN 0

short timeout = 120;
short interval = 1000;
unsigned long prevTime = 0;

String daysOfTheWeek[7] = {"Dim", "Lun", "Mar", "Mer", "Jeu", "Ven", "Sam"};

WiFiManager wm;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "time.nist.gov", 3600);
virtuabotixRTC myRTC(D5, D2, D1); // RST = D5 / DAT = D2 / CLK = D1

#include "setRtcTime.h"
#include "AutoConnectAP.h"
#include "OnDemandAP.h"
#include "print_Data_Time.h"

void setup()
{
  Serial.begin(9600);

  WiFi.mode(WIFI_STA);

  Serial.println("\n Starting");

  pinMode(TRIGGER_PIN, INPUT_PULLUP);

  autoConnectAP();

  delay(1000);
}

void loop()
{
  if (digitalRead(TRIGGER_PIN) == LOW)
  {
    onDemandAP();
  }

  unsigned long currentTime = millis();
  if (currentTime - prevTime >= interval)
  {
    print_Data_Time();

    prevTime = currentTime;
  }
}
