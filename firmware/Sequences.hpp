#pragma once

#include <Sequence.hpp>

#include <vector>
#include <cstdlib>

static constexpr PinState Up = LOW;
static constexpr PinState Down = HIGH;

struct AllDown : public Sequence
{
   explicit AllDown(const std::vector<uint16_t>& pins) : pins(pins) {}
   ~AllDown() override = default;

   void step() override {
      if(!done) {
         for(auto pin: pins) digitalWrite(pin, Down);
         done = true;
      }
   }

private:
   bool done = false;
   const std::vector<uint16_t>& pins;
};

struct FlashD7 : public Sequence
{
   FlashD7(uint16_t pin) : pin(pin) {
   }
   ~FlashD7() override = default;

   void step() override {
      digitalWrite(pin, Down);
      delay(delays());
      digitalWrite(pin, Up);
      delay(delays());
   }

private:
   uint16_t pin;
};

struct InlineFour : public Sequence
{
   InlineFour() = delete;
   explicit InlineFour(const std::vector<uint16_t>& pins) : pins(pins) {
      for(auto pin : pins) digitalWrite(pin, Down);
   }
   ~InlineFour() override = default;

   void step() override {
      ulong current = millis();
      if(delays() < current - last) {
         switch(state) {
            case Up:
               state = Down;
               digitalWrite(pins[pin], state);
               break;
            case Down:
               state = Up;
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
   PinState state = Up;
   const std::vector<uint16_t>& pins;
};


struct AllUpDown : public Sequence
{
   AllUpDown() = delete;
   explicit AllUpDown(const std::vector<uint16_t>& pins) : pins(pins) {
      for(auto pin : pins) digitalWrite(pin, Down);
   }
   ~AllUpDown() override = default;

   void step() override {
      ulong current = millis();
      if(delays() < current - last) {
         switch(state) {
            case Up:
               state = Down;
               for(auto pin: pins) digitalWrite(pin, state);
               break;
            case Down:
               state = Up;
               for(auto pin: pins) digitalWrite(pin, state);
               break;
         }
         last = current;
      }
   }

private:
   ulong last = 0;
   PinState state = Up;
   const std::vector<uint16_t>& pins;
};


struct Randomly : public Sequence
{
   Randomly() = delete;
   explicit Randomly(const std::vector<uint16_t>& pins) : pins(pins), pin(randomPin()) {
      for(auto pin : pins) digitalWrite(pin, Down);
   }
   ~Randomly() override = default;

   void step() override {
      ulong current = millis();
      ulong delay = delays();
      if(Up == state) delay -= difficulty();

      if(delay < current - last) {
         switch(state) {
            case Down:
               state = Up;
               digitalWrite(pin, state);
               break;
            case Up:
               state = Down;
               digitalWrite(pin, state);
               pin = randomPin();
               break;
         }
         last = current;
      }
   }

private:
   ulong last = 0;
   PinState state = Down;
   const std::vector<uint16_t>& pins;
   uint16_t pin;

   uint16_t randomPin() const {
      return (std::rand() % pins.size()) + 4;
   }
};
