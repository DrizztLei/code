#!/bin/bash

node ~/enviroment/iot-sol/node_modules/hope-http-broker/bin/start_broker 16666 &
node ~/enviroment/iot-sol/node_modules/hope-center/center ~/enviroment/iot-sol/node_modules/hope-demo/center/config.json &
