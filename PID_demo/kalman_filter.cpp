#include "kalman_filter.h"
#include "utils.h"

static float measurementUncertainty = 0;
static float estimationUncertainty = 0;
static float processNoise = 0;
static float gain = 0;
static float lastEstimate = 0;

void InitKalmanFilter(float mUncertainty, float eUncertainty, float pNoise) {
    measurementUncertainty = mUncertainty;
    estimationUncertainty = eUncertainty;
    processNoise = pNoise;
}

float UpdateKalmanEstimate(float measuredValue) {
    gain = estimationUncertainty/(estimationUncertainty + measurementUncertainty);
    float currentEstimate = lastEstimate + gain * (measuredValue - lastEstimate);
    estimationUncertainty = (1.0 - gain) * estimationUncertainty + absf(lastEstimate - currentEstimate) * processNoise;
    lastEstimate = currentEstimate;
    return currentEstimate;
}
