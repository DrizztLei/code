#!/bin/bash

node ~/environment/iot-sol/node_modules/hope-http-broker/bin/start_broker 16666 &
node ~/environment/iot-sol/node_modules/hope-center/center ~/environment/iot-sol/node_modules/hope-demo/center/config.json &
