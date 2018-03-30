#pragma once

#include <Sequence.hpp>

struct FlashD7 : public Sequence
{
    ~FlashD7() override = default;

    void step() override {
        digitalWrite(D7, HIGH);
        delay(delays());
        digitalWrite(D7, LOW);
        delay(delays());
    }
};

struct InlineFour : public Sequence
{
    ~InlineFour() override = default;

    void step() override {
        ulong current = millis();
        if(delays() < current - last) {
            switch(state) {
                case LOW:
                    state = HIGH;
                    digitalWrite(D7, state);
                    digitalWrite(pin, state);
                    break;
                case HIGH:
                    state = LOW;
                    digitalWrite(D7, state);
                    digitalWrite(pin, state);
                    if(++pin == 4) pin = 0;
                    break;
            }
            last = current;
        }
    }

private:
    ulong last = 0;
    uint16_t pin = 0;
    PinState state = LOW;
};
