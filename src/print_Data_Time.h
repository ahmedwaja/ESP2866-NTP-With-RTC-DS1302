#ifndef print_Data_Time_H_
#define print_Data_Time_H_

void print_Data_Time()
{
  myRTC.updateTime();

    Serial.println("Time RTC :");

    Serial.println(String(daysOfTheWeek[myRTC.dayofweek - 1]) + " " + String(myRTC.dayofmonth) + "/" + String(myRTC.month) + "/" + String(myRTC.year));
    Serial.println(String(myRTC.hours) + ":" + String(myRTC.minutes) + ":" + String(myRTC.seconds));

}
#endif