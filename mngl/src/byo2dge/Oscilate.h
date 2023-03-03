//
// Created by Ivan on 01-Mar-23.
//

#ifndef OPENGL_EXAMPLES_OSCILATE_H
#define OPENGL_EXAMPLES_OSCILATE_H

/* 
 * traces the locus of a damped simple harmonic function
 */
#include <cmath>
#include <glm/glm.hpp>

//
// damped simple harmonic oscillation
// delta: how large an oscillate
// frequency: how many times to oscillate
// duration: for how long in number of update cycles
//
class Oscillate {
protected:
    float mMag;
    int mCycles;
    float mOmega;
    int mNumCyclesLeft;

public:
    Oscillate(float delta, float frequency, int duration) {
        mMag = delta;

        mCycles = duration; // number of cycles to complete the transition
        mOmega = frequency * 2.0f * (float) M_PI; // Converts frequency to radians

        mNumCyclesLeft = duration;
    }

    void reStart() {
        mNumCyclesLeft = mCycles;
    }

    bool done() {
        return (mNumCyclesLeft <= 0);
    }

    float getNext() {
        mNumCyclesLeft--;
        float v = 0;
        if (!done()) {
            v = _nextValue();
        }
        return (v * mMag);
    }

    // local/protected methods
    virtual float _nextValue() {
        return (_nextDampedHarmonic());
    }

    [[nodiscard]] float _nextDampedHarmonic() const {
        // computes (Cycles) * cos(  Omega * t )
        float frac = (float) mNumCyclesLeft / (float) mCycles;
        return frac * frac * std::cos((1 - frac) * mOmega);
    }
};


class Shake : public Oscillate {
public:
    Shake(float delta, float frequency, int duration)
            : Oscillate(delta, frequency, duration) {}

// randomize the sign of the oscillation magnitude
    float _nextValue() override {
        float v = _nextDampedHarmonic();
        // float fx = (random() > 0.5) ? -v : v;
        float fx = (rand() % 2 == 0) ? -v : v;
        return fx;
    }
};

// deltas, and freqs: are vec2
// duration is a float
class ShakeVec2 {
public:
    ShakeVec2(glm::vec2 deltas, glm::vec2 freqs, int duration)
            : xShake(deltas.x, freqs.x, duration),
              yShake(deltas.y, freqs.y, duration) {
    }

    void reStart() {
        xShake.reStart();
        yShake.reStart();
    }

    bool done() {
        return xShake.done(); // could be yShake also, they are synchronized
    }

    glm::vec2 getNext() {
        float x = xShake.getNext();
        float y = yShake.getNext();
        return {x, y};
    }

private:
    Shake xShake;
    Shake yShake;
};

#endif //OPENGL_EXAMPLES_OSCILATE_H
