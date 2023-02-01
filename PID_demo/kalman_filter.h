#ifndef KALMAN_FILTER_H
#define KALMAN_FILTER_H

void InitKalmanFilter(float measurementUncertainty, float estimationUncertainty, float processNoise);
float UpdateKalmanEstimate(float measuredValue);

#endif