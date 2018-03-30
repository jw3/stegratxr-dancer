#pragma once

struct Sequence
{
    virtual ~Sequence() = default;
    virtual void step() = 0;

    void delays(ulong millis) { m_delay = millis; }
    ulong delays() const { return m_delay; }

private:
    ulong m_delay = 1000;
};

using SequencePtr = std::shared_ptr<Sequence>;
