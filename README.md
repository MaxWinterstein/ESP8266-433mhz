# ESP8266-433mhz

I needed some really simple gateway to toggle cheap 433mhz power plugs (in germay mostly manufactured by Intertechno) from pimatic.
I have no need to read anything back or be fancy. 
I needed something simple. 
I made something simple.

## Build

See [instructables.com](https://www.instructables.com/id/Using-an-ESP8266-to-Control-Mains-Sockets-Using-43/) or for a good german tutoral [alexbloggt.com](https://alexbloggt.com/funksteckdosensteuerung-mit-esp8266/).

## Install

* Change `ssid` and `password` according your needs
* Install libraries if needed 
  * `ESP8266WiFi`
  * `ESP8266WebServer`
  * `ESP8266mDNS`
  * `rc-switch`
* Double check your `DATA_PIN`, for me it is `D2`
* Upload via Arduino.cc 

## Usage

Simply curl the api with the correct housecode and socketcode. 
I made usage of binary codes, as i can just read the dips without thinking.

```bash
curl -s "http://ESP-433-Gateway/changestate?housecode=<housecode>&socketcode=<socketcode>&state=<state>"
```
e.g.:
```bash
curl -s "http://ESP-433-Gateway/changestate?housecode=10001&socketcode=00100&state=on"
```


Pimatic device config could look like this:
```json
{
  "onCommand": "curl -s  \"http://ESP-433-Gateway/changestate?housecode=10001&socketcode=00100&state=on\"",
  "offCommand": "curl -s  \"http://ESP-433-Gateway/changestate?housecode=10001&socketcode=00100&state=off\"",
  "echo": {
	"additionalNames": []
  },
  "id": "fusion_reactor",
  "name": "fusion reactor",
  "class": "ShellSwitch"
},
```

## Credits
This is mostly inspired by [alexbloggt.com](https://alexbloggt.com/funksteckdosensteuerung-mit-esp8266/) - thanks for your work!  
Also thanks to [techtutorialsx.com](https://techtutorialsx.com/2016/10/22/esp8266-webserver-getting-query-parameters/) for the explanation of arg usage!