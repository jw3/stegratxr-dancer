#pragma once

struct Sequence
{
    virtual ~Sequence() = default;
    virtual void step() = 0;

    virtual void delays(ulong millis) { m_delay = millis; }
    virtual ulong delays() const { return m_delay; }

    virtual void difficulty(int diff) { m_difficulty = diff; }
    virtual int difficulty() const { return m_difficulty; }

private:
    ulong m_delay = 1000;
    int m_difficulty = 1;
};

using SequencePtr = std::shared_ptr<Sequence>;
