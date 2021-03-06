/*===============================================================================
Copyright (c) 2014 Qualcomm Connected Experiences, Inc. All Rights Reserved.

Vuforia is a trademark of PTC Inc., registered in the United States and other 
countries.

@file 
    EyewearUserCalibrator.h

@brief
    Header file for EyewearUserCalibrator class.
===============================================================================*/
#ifndef _QCAR_EYEWEARUSERCALIBRATOR_H_
#define _QCAR_EYEWEARUSERCALIBRATOR_H_

// Include files
#include <QCAR/NonCopyable.h>
#include <QCAR/QCAR.h>
#include <QCAR/EyeID.h>
#include <QCAR/EyewearCalibrationReading.h>

namespace QCAR
{

/// A class for creating custom user calibration procedures for see-through eyewear
/**
 *
 * <br><b>This API is only supported in the Vuforia SDK for Digital %Eyewear.</b><br><br>
 *
 *  - Users of optical see-through eyewear devices need to perform a calibration
 *    to determine how to project an augmentation such that it will appear
 *    registered with the real world.  This calibration is both user and
 *    device specific.  Vuforia provides a default calibration but to obtain
 *    the best possible AR experience the user should calibrate Vuforia for
 *    their own eyes and device.
   
 *  - To write your own calibration app you should draw a calibration shape
 *    (rectangle) on the display and prompt the user to align the edges of
 *    of the calibration shape with a Vuforia image target.  This step should
 *    then be repeated with a different size shape.  A minimum of two steps are
 *    required for a good result although further steps can be included to get
 *    an improved calibration result.
 *
 *  - If the eyewear device is a stereo then the calibration needs to be
 *    carried out independently on each eye.
 *
 *  - Millimeters must be used as the unit of measurement throughout
 *    calibration.  The calibration image target used should have its size
 *    specified in millimetres when initialising this object.  This size
 *    must match the size specified in the dataset for the target and the
 *    printed size of the target.
 *
 *  - The projection matrix generated by the calibration process includes
 *    OpenGL clip planes which will cause augmentations very close or far
 *    from the user to be clipped.
 */
class QCAR_API EyewearUserCalibrator : private NonCopyable
{
public:
    /**
     * Initialises the eyewear calibrator.
     *
     * - This function must be called before any other members of this class.
     *
     *  \param surfaceWidth  The width of the rendering surface that the calibration is running in
     *  \param surfaceHeight  The height of the rendering surface that the calibration is running in 
     *  \param targetWidth  The width of the image target being used in millimetres
     *  \param targetHeight  The height of the image target being used in millimetres
     *
     *  \return True if initialisation is successful, false otherwise
     *
     **/
    virtual bool init(int surfaceWidth, int surfaceHeight,
                      int targetWidth,  int targetHeight) = 0;

    /** 
     * Gets a hint of the minimum size a calibration shape should be drawn
     *
     * - The smaller a calibration shape is drawn the further the user needs to
     *   stand away from a target during calibration.  The minimum size that
     *   can be drawn is device specific and this API provide a hint as to what
     *   minimum scale shape is practical.
     *
     * \return The minimum scale of the shape in the range 0.0 - 1.0
     **/
    virtual float getMinScaleHint() = 0;

    /**
     * Gets a hint of the maximum size a calibration shape should be drawn
     *  - Drawing a large calibration shape means the sides of the shape will
     *    near to the sides of the display.  Some eyewear devices have
     *    distortion towards the edge of the display.  This API provides a hint
     *    as to the maximum size a calibration shape should be drawn.
     *
     * \return The maximum scale of the shape in the range 0.0 - 1.0
     **/
    virtual float getMaxScaleHint() = 0;


    /**
     * Gets the aspect ratio that should be used to draw a calibration shape
     * - Some eyewear devices introduce distortion in the calibration shapes,
     *   for example in the form of horizontal or vertical stretch.  This value
     *   should be used to draw calibration shapes that closely match the
     *   aspect ratio of the real world calibration target.
     *
     * \return The aspect ratio for calibration shapes
     **/
    virtual float getDrawingAspectRatio(int surfaceWidth, int surfaceHeight) const = 0;


    /**
     * Checks whether a device stretches the display to create a stereoscopic effect
     *  - When a device enters 3D it may join the displays together to create one
     *    big display.  If the resolution of the display appears the same then the
     *    display is effectively stretched
     *
     * \return True if the display is stretched, otherwise false
     **/
    virtual bool isStereoStretched() = 0;

    /**
     * Gets a projection matrix calibrated for eyewear
     *
     *  - Calculates and returns a calibrated projection matrix.
     *  - init must be called before calling this function.
     * 
     * \param readings  An array of calibration readings
     * \param numReadings  The number of readings taken, poseReadings and scales must be this length
     * \param calibrationResult  Output matrix for the calibrated matrix
     *
     * \return  True if the call is successful, otherwise false
     **/
    virtual bool getProjectionMatrix(EyewearCalibrationReading reading[],
                                     int numReadings, Matrix44F& calibrationResult) = 0;
};

} // namespace QCAR

#endif //_QCAR_EYEWEARUSERCALIBRATOR_H_
