#pragma once

#include <Sequence.hpp>

#include <vector>

struct FlashD7 : public Sequence
{
    FlashD7() {}
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
    explicit InlineFour(const std::vector<uint16_t>& pins) : pins(pins) {}
    ~InlineFour() override = default;

    void step() override {
        ulong current = millis();
        if(delays() < current - last) {
            switch(state) {
                case LOW:
                    state = HIGH;
                    digitalWrite(D7, state);
                    digitalWrite(pins[pin], state);
                    break;
                case HIGH:
                    state = LOW;
                    digitalWrite(D7, state);
                    digitalWrite(pins[pin], state);
                    if(++pin >= pins.size()) pin = 0;
                    break;
            }
            last = current;
        }
    }

private:
    ulong last = 0;
    uint16_t pin = 0;
    PinState state = LOW;
    const std::vector<uint16_t>& pins;
};


struct AllUpDown : public Sequence
{
    explicit AllUpDown(const std::vector<uint16_t>& pins) : pins(pins) {}
    ~AllUpDown() override = default;

    void step() override {
        ulong current = millis();
        if(delays() < current - last) {
            switch(state) {
                case LOW:
                    state = HIGH;
                    for(auto pin: pins) digitalWrite(pin, state);
                    break;
                case HIGH:
                    state = LOW;
                    for(auto pin: pins) digitalWrite(pin, state);
                    break;
            }
            last = current;
        }
    }

private:
    ulong last = 0;
    PinState state = LOW;
    const std::vector<uint16_t>& pins;
};
