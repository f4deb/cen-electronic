#ifndef B_SPLINE_H
#define B_SPLINE_H

#include "../../common/2d/2d.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

/**
 * Extended motion to generate more complex trajectory like
 * Bezier / B-Spline curve, cycloid, and not only rotation, and translation move.
 * @author svanacker
 * @version 19/05/2010
 */

/**
 * The order in term of x^n of the B Spline curve.
 */
#define BSPLINE_POINT_COUNT 4

/**
 * Increment to compute in the time segment [0.1].
 * We use 2000 points to interpolate the curve.
 */
#define BSPLINE_TIME_INCREMENT 0.005f

/**
 * Store distance length at certain time.
 */
typedef struct BSplinePointData {
    // time in [0..1].
    float time;
    // distance in terms of curve length at this point
    // since the origin of the curve
    float length;
    // the stored Point
    Point point;
    // the orientation
    float orientation;
} BSplinePointData;

/**
 * Define a bezierCurve, with 4 points.
 */
typedef struct BSplineCurve {
    // first control point
    Point p0;
    // second control point
    Point p1;
    // third control point
    Point p2;
    // last control point
    Point p3;
    // if we go backward or not
    bool backward;
    // The length of the curve.
    float curveLength;
    // accelerationFactor (between 0 and 1.0, with 1.0 = maximal acceleration factor of the system (constraints by the motors)
    float accelerationFactor;
    // speedFactor (between 0 and 1.0, with 1.0 = maximal speed factor of the system (constraints by the motors)
    float speedFactor;
} BSplineCurve;

/**
 * Init a bSpline Curve with values, and all structures necessary to allocate memory.
 * @param bSplineCurve pointer on structure object (POO paradigm)
 */
void initFirstTimeBSplineCurve(BSplineCurve* bSplineCurve);

/**
 * Init a bSpline Curve with values, when the structures is already initialized.
 */
void resetBSplineCurve(BSplineCurve* bSplineCurve, float p0x, float p0y, bool backward);

// Low Level Point Computation

/**
 * Compute the value of bezier points, with the parametric value t.
 * @param bSplineCurve the curve we want to compute
 * @param t value in [0..1]
 */
void computeBSplinePoint(BSplineCurve* bSplineCurve, float time, Point* resultPoint);

// DERIVATIVE n (speed / orientation)

void computeBSplineDerivativeComponents(BSplineCurve* bSplineCurve, float t, Point* derivativeResult);

/**
 * Because of the curve, the speed or the acceleration is not the same 
 * between the center of the robot and the left and right wheels.
 * @param curve
 * @param time
 * @param distanceToCurve
 * @return 
 */
float computeSpeedFactorToCenterDueToCurve(BSplineCurve* curve, float time, float distanceToCurve);

/**
 * Compute the orientation of bezier points at the parametric value t.
 * @param bSplineCurve the curve we want to compute
 * @param t value in [0..1]
 */
float computeBSplineOrientationWithDerivative(BSplineCurve* bSplineCurve, float t);

// DERIVATIVE n + 1 (acceleration)

/**
 * Compute the parameterized components (x and y) of the derivative of the bspline.
 * @param bSplineCurve
 * @param t value in [0..1]
 * @param accelerationResult contains the result for the both components (x / y)
 */
void computeBSplineAccelerationComponent(BSplineCurve* bSplineCurve, float t, Point* accelerationResult);

/**
 * Because of the curve, the normal acceleration is not the same 
 * between the center of the robot and the left and right wheels.
 * @param curve
 * @param time
 * @param distanceToCurve
 * @return 
 */
float computeAccelerationFactorToCenterDueToCurve(BSplineCurve* curve, float time, float speedFactor);

// CURVATURE / RADIUS

/**
 * Compute the radius of the BSpline by a geometrical approach (3 points / center). 
 * @param bSplineCurve
 * @param t
 * @return 
 */
float computeBSplineCurveRadius(BSplineCurve* bSplineCurve, float t);

/**
 * Compute the curvature but by using the derivative / acceleration functions.
 * @param bSplineCurve
 * @param t
 * @return 
 */
float computeBSplineCurvature(BSplineCurve* bSplineCurve, float t);

// BSPlinePointData

/**
 * Copy the content of B-SplineData.
 * @param source the source of content which will be copy to target
 * @param target the target in which we copy source data
 */
void copyBSplineData(BSplinePointData* source, BSplinePointData* target);

/**
 * Compute the length of a bezier arc curve.
 * @param bSplineCurve the curve for which we compute the length
 * @param timeIncremnt between 0.0f and 1.0f (max for a bezier curve). If the value is very small,
 * the accuracy of length is better, but it takes more time to compute
 */
float computeBSplineArcLength(BSplineCurve* bSplineCurve, float timeIncrement);

/**
 * Compute the interpolation when the length is between two points corresponding to
 * 2 length.
 * @param bSplineCurve the curve for which we compute the length
 * @param beforePointData the previous Point which was computed
 * @param afterPointData the next computed Point
 * @param length a length which must be in the segment [lengthBefore..lengthAfter]
 */
float computeTimeWithInterpolation(BSplinePointData* beforePointData,
        BSplinePointData* afterPointData,
        float length);

/**
 * Computes the time at the distance.
 * @param bSplineCurve the curve for which we compute the time
 * @param distance the distance from which we must know the time
 * @return a value between 0 and 1 corresponding to the t parameter
 */
float computeBSplineTimeAtDistance(BSplineCurve* bSplineCurve, float distance);

/**
 * Parametrize a curve by providing source coordinates / angle, target coordinates / angle + controlDistance1 / 2 instead of 4 control points
 */
void parameterBSplineWithDistanceAndAngle(BSplineCurve* curve,
        float sourceX, float sourceY, float sourceAngle,
        float destX, float destY, float destAngle,
        float distance1, float distance2,
        float accelerationFactor, float speedFactor,
        bool relative);

#endif
