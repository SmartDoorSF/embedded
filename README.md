Embedded code running on hardware platforms

# Particle Photon

## Configuration

### Device Management & Ownership

How do I find my Device ID?

[Device Management & Ownership](https://docs.particle.io/support/troubleshooting/device-management/photon/)

Current Access Token is in never-expire mode

Learn how to generate token here

[Generate an access token](https://docs.particle.io/reference/api/#generate-an-access-token)

## Voodospark 

"VoodooSpark" is a customized firmware build for Photon and Core to allow a remote interface 
definition of the firmware API over a local TCP connection. The intent is to allow client-side
programs to directly control the 'Particle' devices in real-time regardless of their programming
language."

[VoodooSpark getting started](https://github.com/voodootikigod/voodoospark#getting-started)

### Troubleshoot

When querying Particle api for device connection

If timeout response was received by using below query command/string

```bash
curl https://api.particle.io/v1/devices/{DEVICE-ID}/endpoint?access_token={ACCESS-TOKEN}
```

Make sure the Photon is actually connecting to the internet in standard mode (breathing cyan)

Using 

```bash
particle setup
```
to Setup SSID and PW when necessary

```bash
{
    "cmd": "VarReturn",
    "name": "endpoint",
    "result": "192.168.1.117:48879",
    "coreInfo": {
      "last_app": "",
      "last_heard": "2016-01-31T21:16:37.974Z",
      "connected": true,
      "last_handshake_at": "2016-01-31T21:14:52.869Z",
      "deviceID": "1b0034000b47343432313031",
      "product_id": 6
    }
}
```

Default local listening port
48879 (0xBEEF)

## Connect to VoodooSpark 

[What is Telnet](https://kb.iu.edu/d/aayd)

```bash
telnet host port
```

# RedBearLab

Environment Setup dependencies

1. GNU Tools for ARM Embedded Processors
  current version: 
2. srec_cat
  "is used to assemble the given input files into a single output file."
