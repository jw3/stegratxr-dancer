/*
 ******************************************************************************
  Copyright (c) 2015 Particle Industries, Inc.  All rights reserved.

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation, either
  version 3 of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this program; if not, see <http://www.gnu.org/licenses/>.
  ******************************************************************************
 */

#include "application.h"

int tinkerDigitalRead(String pin);
int tinkerDigitalWrite(String command);
int tinkerAnalogRead(String pin);
int tinkerAnalogWrite(String command);


void setup() {
    Particle.function("digitalread", tinkerDigitalRead);
    Particle.function("digitalwrite", tinkerDigitalWrite);
    Particle.function("analogread", tinkerAnalogRead);
    Particle.function("analogwrite", tinkerAnalogWrite);
}

int delayms = 1000;

void loop() {
    digitalWrite(D7, HIGH);
    delay(delayms);
    digitalWrite(D7, LOW);
    delay(delayms);
}

int tinkerDigitalRead(String pin) {
    //convert ascii to integer
    int pinNumber = pin.charAt(1) - '0';
    //Sanity check to see if the pin numbers are within limits
    if(pinNumber < 0 || pinNumber > 7) return -1;

    if(pin.startsWith("D")) {
        return 0;
    }
    else if(pin.startsWith("A")) {
        return 0;
    }
    return -2;
}

int tinkerDigitalWrite(String command) {
    bool value = 0;
    int pinNumber = command.charAt(1) - '0';
    if(pinNumber < 0 || pinNumber > 7) return -1;

    if(command.substring(3, 7) == "HIGH") value = 1;
    else if(command.substring(3, 6) == "LOW") value = 0;
    else return -2;

    if(command.startsWith("D")) {
        pinMode(pinNumber, OUTPUT);
        digitalWrite(pinNumber, value);
        return 1;
    }
    else if(command.startsWith("A")) {
        return 1;
    }
    else return -3;
}

int tinkerAnalogRead(String pin)
{
    return 0;
}


int tinkerAnalogWrite(String command) {
    String value = command.substring(3);
    int pinNumber = command.charAt(1) - '0';
    if(pinNumber < 0 || pinNumber > 7) return -1;

    if(command.startsWith("D")) {
        return 1;
    }
    else if(command.startsWith("A")) {
        delayms = value.toInt();
        return 1;
    }
    else return -2;
}
