//
// Created by Ivan on 28-Feb-23.
//

#ifndef OPENGL_EXAMPLES_LERP_H
#define OPENGL_EXAMPLES_LERP_H

#include <glm/glm.hpp>

// value: target for interpolation
// cycles: integer, how many cycle it should take for a value to change to final
// rate: the rate at which the value should change at each cycle
class Lerp {
private:
    float mCurrentValue;    // begin value of interpolation
    float mFinalValue;      // final value of interpolation
    int mCycles;
    float mRate;

    // if there is a new value to interpolate to, number of cycles left for interpolation
    int mCyclesLeft = 0;
public:
    Lerp(float value, int cycles, float rate) {
        mCurrentValue = value;    // begin value of interpolation
        mFinalValue = value;      // final value of interpolation
        mCycles = cycles;
        mRate = rate;

        // if there is a new value to interpolate to, number of cycles left for interpolation
        mCyclesLeft = 0;
    }

    [[nodiscard]] float get() const { return mCurrentValue; }
    void setFinal(float v) {
            mFinalValue = v;
            mCyclesLeft = mCycles;     // will trigger interpolation
    }

    void update() {
        if (mCyclesLeft <= 0) {
            return;
        }

        mCyclesLeft--;
        if (mCyclesLeft == 0) {
            mCurrentValue = mFinalValue;
        } else {
            _interpolateValue();
        }
    }

    // stiffness '1' switches off interpolation
    void config(float stiffness, int duration) {
        mRate = stiffness;
        mCycles = duration;
    }

    // subclass should override this function for non-scalar values
    void _interpolateValue() {
        mCurrentValue = mCurrentValue + mRate * (mFinalValue - mCurrentValue);
    }
};

class LerpVec2  {
private:
    glm::vec2 mCurrentValue;    // begin value of interpolation
    glm::vec2 mFinalValue;      // final value of interpolation
    int mCycles;
    float mRate;

    // if there is a new value to interpolate to, number of cycles left for interpolation
    int mCyclesLeft = 0;
public:
    LerpVec2 (glm::vec2 value, int cycles, float rate) {
        mCurrentValue = value;    // begin value of interpolation
        mFinalValue = value;      // final value of interpolation
        mCycles = cycles;
        mRate = rate;

        // if there is a new value to interpolate to, number of cycles left for interpolation
        mCyclesLeft = 0;
    }

    glm::vec2 get() { return mCurrentValue; }
    void setFinal(glm::vec2 v) {
        mFinalValue = v;
        mCyclesLeft = mCycles;     // will trigger interpolation
    }

    void update() {
        if (mCyclesLeft <= 0) {
            return;
        }

        mCyclesLeft--;
        if (mCyclesLeft == 0) {
            mCurrentValue = mFinalValue;
        } else {
            _interpolateValue();
        }
    }

    // stiffness '1' switches off interpolation
    void config(float stiffness, int duration) {
        mRate = stiffness;
        mCycles = duration;
    }

    // subclass should override this function for non-scalar values
    void _interpolateValue() {
        mCurrentValue = mCurrentValue + mRate * (mFinalValue - mCurrentValue);
    }
};

#endif //OPENGL_EXAMPLES_LERP_H
