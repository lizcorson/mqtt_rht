# mqtt_rht
A network of sensors to monitor the temperature in various parts of my home.

## Overview
I'd like to monitor the temperature in various parts of my home, so I'm setting up a bunch of little wifi-enabled RHT (relative humidity/temperature) sensors in various rooms. Data will be published to MQTT. I'm running an MQTT server on my Raspberry Pi. I'd also like to create a dashboard webpage to chart the data, and I'd also like to log it to disk either as a text file or maybe to a MySQL database.

## Status
I've currently written the initial code for the microcontroller board, but I have yet to install the sensors.

## Parts Used
- NodeMCU Clone http://www.aliexpress.com/item/NodeMcu-Lua-WIFI-development-board-based-on-the-ESP8266-Internet-of-things/32339203041.html - can't say I enthusiastically recommend these as the quality is somewhat questionable. But they're cheap and I needed a bunch.
- HTU21D clone http://www.ebay.com/itm/201496730282 (original: https://www.sparkfun.com/products/12064)
- Raspberry Pi 3 - Jessie Lite

## Libraries
- PubSubClient https://github.com/knolleary/pubsubclient
- HTU21D https://github.com/sparkfun/HTU21D_Breakout/tree/V_H1.2_L1.1.0/Libraries/Arduino

## Other

Follow this tutorial to install Mosquitto on your Raspberry Pi from the Debian repositories, which will let you access a much newer version: http://mosquitto.org/2013/01/mosquitto-debian-repository/

I like the apps MQTT Dashboard and MyMQTT, which are free on Google Play for Android. These can be helpful for troubleshooting.
