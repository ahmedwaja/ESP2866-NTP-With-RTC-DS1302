#ifndef setRtcTime_H_
#define setRtcTime_H_

void setRtcTime()
{
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
#endif