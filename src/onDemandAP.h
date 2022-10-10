#ifndef onDemandAP_H_
#define onDemandAP_H_

void onDemandAP()
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

  setRtcTime();
}
#endif