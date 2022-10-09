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

const char ssid[] = "NetBox-A64A";
const char password[] = "YBQ0BR92FHN";
String daysOfTheWeek[7] = {"Dim", "Lun", "Mar", "Mer", "Jeu", "Ven", "Sam"};

WiFiManager wm;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "time.nist.gov", 3600);
virtuabotixRTC myRTC(D5, D2, D1);

void setup()
{
  Serial.begin(9600);

  WiFi.mode(WIFI_STA);

  Serial.println("\n Starting");

  pinMode(TRIGGER_PIN, INPUT_PULLUP);

  wm.setConfigPortalTimeout(timeout);

  if (!wm.autoConnect("AutoConnectAP"))
  {
    Serial.println("Failed to connect");
  }
  else
  {
    Serial.println("connected...yeey :)");

    timeClient.begin();

    timeClient.update();

    String time_string = timeClient.getFormattedTime();
    unsigned long secs = timeClient.getEpochTime();
    setTime(secs);

    Serial.println("Time Network Protocol :");

    Serial.println(daysOfTheWeek[weekday(secs) - 1] + " " + String(day()) + "/" + String(month()) + "/" + String(year()));

    Serial.println(String(hour()) + ":" + String(minute()) + ":" + String(second()));

    myRTC.setDS1302Time(second(), minute(), hour(), weekday(secs), day(), month(), year());
  }

  delay(1000);
}

void loop()
{
  if (digitalRead(TRIGGER_PIN) == LOW)
  {
    wm.setConfigPortalTimeout(timeout);

    if (!wm.startConfigPortal("OnDemandAP"))
    {
      Serial.println("failed to connect and hit timeout");
      delay(3000);

      ESP.restart();

      delay(5000);
    }
    Serial.println("connected...yeey :)");

    timeClient.begin();

    timeClient.update();

    String time_string = timeClient.getFormattedTime();
    unsigned long secs = timeClient.getEpochTime();
    setTime(secs);

    myRTC.setDS1302Time(second(), minute(), hour(), weekday(secs), day(), month(), year());
  }

  unsigned long currentTime = millis();
  if (currentTime - prevTime >= interval)
  {
    myRTC.updateTime();

    Serial.println("Time RTC :");

    Serial.println(String(daysOfTheWeek[myRTC.dayofweek - 1]) + " " + String(myRTC.dayofmonth) + "/" + String(myRTC.month) + "/" + String(myRTC.year));
    Serial.println(String(myRTC.hours) + ":" + String(myRTC.minutes) + ":" + String(myRTC.seconds));

    prevTime = currentTime;
  }
}
