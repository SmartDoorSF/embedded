# Lightbluebean Beacon Setup

Beacons use 128-bit UUIDs, but Bean is limited to selecting 16 of those 128 bits:

A495____-C5B1-4B44-B512-1370F02D74DE


```c
void setup() {
    Bean.enableConfigSave(false);
      Bean.setBeaconParameters(0xDEAD, 0xBEEF, 0xCAFE);
        Bean.setBeaconEnable(true);
}

void loop() {
    Bean.sleep(0xFFFFFFFF);
}
```


0xDEAD is configurable UUID

MajorID:
  0XBEEF 

and

MinorID:
  0XCAFE

The Core Location framework in iOS limits you to monitoring 20 regions at once. Regions are usually specificed by UUID. To differentiate between lots of devices. 
iBeacons have two 16-bit fields name "major" and "minor".

Beacon --> Advertising

References:
[Punch Through Design iBeacon Intro](https://punchthrough.com/bean/guides/features/ibeacon/)
