/*
 *  CDSPropertyDefinesDriving.h
 *  iDrive
 *
 *  Created by Jeff Zabel on 10/29/09.
 *  Copyright 2009 BMW. All rights reserved.
 *
 *  $Id: CDSPropertyDefinesDriving.h 50949 2010-11-29 12:25:54Z q188463 $
 */

/* ********************
 DRIVING
 ********************** */


/*!
 @define     driving.acceleration
 @abstract   The current vehicle acceleration in lateral and longitudinal direction reported in m/s^2 (value is signed).
 @discussion Stored in response key "acceleration" as dictionary with keys "lateral" and "longitudinal".
 */
extern NSString* CDSDrivingAcceleration;

/*!
 @define     driving.acceleratorPedal
 @abstract   The current angle of the accelerator pedal as a percentage of fully depressed 0-100%.
 @discussion Stored in response key "acceleratorPedal" as dictionary with key "position".
 */
extern NSString* CDSDrivingAcceleratorPedal;

/*!
 @define     driving.averageConsumption
 @abstract   Returns the two on-board average consumption values.
 @discussion Stored in response key "averageConsumption" as dictionary with keys "averageConsumption1", "averageConsumption2", and "unit". The averages are represented as floating-point numbers and the units is of type eCDSDrivingAverageConsumptionUnit. 
 */
extern NSString* CDSDrivingAverageConsumption;
enum eCDSDrivingAverageConsumption
{
    CDSDrivingAverageConsumptionUnit_DEFAULT = 0,
    CDSDrivingAverageConsumptionUnit_L_100KM = 1,
    CDSDrivingAverageConsumptionUnit_MPGUK = 2,
    CDSDrivingAverageConsumptionUnit_MPGUS = 3,
    CDSDrivingAverageConsumptionUnit_KM_L = 4,
    CDSDrivingAverageConsumptionUnit_INVALID = 7
};

/*!
 @define     driving.averageSpeed
 @abstract   Returns the two on-board average speed values.
 @discussion Stored in response key "averageSpeed" as dictionary with keys "averageSpeed1", "averageSpeed2", and "unit". The averages are represented as floating-point numbers and the units is of type eCDSDrivingAverageSpeedUnit. 
 */
extern NSString* CDSDrivingAverageSpeed;
enum eCDSDrivingAverageSpeed
{
    CDSDrivingAverageSpeedUnit_DEFAULT = 0,
    CDSDrivingAverageSpeedUnit_KM_H = 1,
    CDSDrivingAverageSpeedUnit_MPH = 2,
    CDSDrivingAverageSpeedUnit_INVALID = 3
};

/*!
 @define     driving.brakeContact
 @abstract   The values of the dual-channel brake light switch.  When the brake pedal is pressed, this property is updated.  In the case of startup and for keyPosition{starting} invalid, undefined or incorrect values can be output.
 @discussion Stored in response key "brakeContact" emeration with possible values: CDSDrivingBrakeContact_NOCONTACT, CDSDrivingBrakeContact_CONTACT, CDSDrivingBrakeContact_BRAKETEST, CDSDrivingBrakeContact_INVALID.
 */
extern NSString* CDSDrivingBrakeContact;
enum eCDSDrivingBrakeContact
{
	CDSDrivingBrakeContact_NOCONTACT = 0,
	CDSDrivingBrakeContact_BRAKENOTEST = 1,
	CDSDrivingBrakeContact_BRAKETEST = 2,
	CDSDrivingBrakeContact_CONTACT = 3,
	CDSDrivingBrakeContact_INVALID = 7
};

/*!
 @define     driving.clutchPedal
 @abstract   The current status and information about the vehicle's clutch.
 @discussion Stored in response key "clutchPedal" as dictionary with key "position".  
 "position" is returned as an emeration with possible values: CDSDrivingClutchPedal_ENGAGED, CDSDrivingClutchPedal_DISENGAGED, CDSDrivingClutchPedal_UNAVAILABLE
 */
extern NSString* CDSDrivingClutchPedal;
enum eCDSDrivingClutchPedal
{
	CDSDrivingClutchPedal_DISENGAGED = 0,
	CDSDrivingClutchPedal_ENGAGED = 1,
	CDSDrivingClutchPedal_UNAVAILABLE = 3
};

/*!
 @define     driving.DSCActive
 @abstract   The activity status of the vehicles dynamic stability control system (DSC).  When the system is active and assisting the driver, this will be active or on.  
 @discussion Stored in response key "DSCActive" as an enumeration.  Possible values are: CDSDrivingDSCActive_OFF, CDSDrivingDSCActive_ON, CDSDrivingDSCActive_INVALID
 */
extern NSString* CDSDrivingDSCActive;
enum eCDSDrivingDSCActive
{
	CDSDrivingDSCActive_OFF = 1,
	CDSDrivingDSCActive_ON = 0,
	CDSDrivingDSCActive_INVALID = 3
};

/*!
 @define     driving.ecoTip
 @abstract   An ecoTip available for the current driving condition, if applicable.
 @discussion Stored in response key "ecoTip" as an enumeration of type eCDSEcoTip
 */
extern NSString* CDSDrivingEcoTip;
enum eCDSDrivingEcoTip
{
    CDSDrivingEcoTip_NO_TIP = 0,
    CDSDrivingEcoTip_REDUCE_ACCEL = 1,
    CDSDrivingEcoTip_REDUCE_SPEED = 2,
    CDSDrivingEcoTip_ANTICIPATE_BRAKE = 3,
    CDSDrivingEcoTip_CHANGE_TO_RECOMMENDED_GEAR = 4,
    CDSDrivingEcoTip_SELECT_GEAR_DRIVE = 5,
    CDSDrivingEcoTip_NEUTRAL_WHILE_IDLE = 6,
    CDSDrivingEcoTip_USE_BRAKE_WHILE_STANDING = 7,
    CDSDrivingEcoTip_INVALID = 63,
};

/*!
 @define     driving.gear
 @abstract   The current gear of the vehicle for automatic or manual transmissions.  
 @discussion Stored in response key "gear" as an enumeration.  Possible values are: CDSDrivingGear_PARK, CDSDrivingGear_REVERSE, CDSDrivingGear_NEUTRAL, CDSDrivingGear_1, CDSDrivingGear_2, CDSDrivingGear_3
 CDSDrivingGear_4, CDSDrivingGear_5, CDSDrivingGear_6, CDSDrivingGear_7, CDSDrivingGear_8, CDSDrivingGear_9, CDSDrivingGear_INVALID
 */
extern NSString* CDSDrivingGear;
enum eCDSDrivingGear
{
	CDSDrivingGear_NEUTRAL = 1,
	CDSDrivingGear_REVERSE = 2,
	CDSDrivingGear_PARK = 3,
	CDSDrivingGear_1 = 5, 
	CDSDrivingGear_2 = 6, 
	CDSDrivingGear_3 = 7, 
	CDSDrivingGear_4 = 8, 
	CDSDrivingGear_5 = 9, 
	CDSDrivingGear_6 = 10, 
	CDSDrivingGear_7 = 11,
	CDSDrivingGear_8 = 12, 
	CDSDrivingGear_9 = 13,
	CDSDrivingGear_INVALID = 15
};

/*!
 @define     driving.keyPosition
 @abstract   The status of the key position with respect to running, accessory, and starting positions.
 @discussion Stored in response key "keyPosition" with the following keys "running", "accessory", and "starting".
 "running" has the following possible values: CDSDrivingKeyPositionRunning_OFF, CDSDrivingKeyPositionRunning_ON, CDSDrivingKeyPositionRunning_INVALID
 "starting" has the following possible values: CDSDrivingKeyPositionStarting_OFF, CDSDrivingKeyPositionStarting_ON, CDSDrivingKeyPositionStarting_NOT_ENALBED, CDSDrivingKeyPositionStarting_INVALID
 "accessory" has the following possible vlaues: CDSDrivingKeyPositionAccessory_OFF, CDSDrivingKeyPositionAccessory_ON, CDSDrivingKeyPositionAccessory_INVALID
 */
extern NSString* CDSDrivingKeyPosition;
enum eCDSDrivingKeyPositionRunning
{
	CDSDrivingKeyPositionRunning_OFF = 0,
	CDSDrivingKeyPositionRunning_ON = 1,
	CDSDrivingKeyPositionRunning_INVALID = 3
};
enum eCDSDrivingKeyPositionStarting
{
	CDSDrivingKeyPositionStarting_OFF = 0,
	CDSDrivingKeyPositionStarting_ON = 1,
	CDSDrivingKeyPositionStarting_NOT_ENABLED = 2,
	CDSDrivingKeyPositionStarting_INVALID = 3
};
enum eCDSDrivingKeyPositionAccessory
{
	CDSDrivingKeyPositionAccessory_OFF = 0,
	CDSDrivingKeyPositionAccessory_ON = 1,
	CDSDrivingKeyPositionAccessory_INVALID = 3
};

/*!
 @define     driving.keyNumber
 @abstract   The number of the active key being used.
 @discussion Stored in response key "keyNumber" as an enumeration with possible values: CDSDrivingKeyNumber_0, CDSDrivingKeyNumber_1, CDSDrivingKeyNumber_2, CDSDrivingKeyNumber_3, CDSDrivingKeyNumber_UNPERSONALIZED, 
 CDSDrivingKeyNumber_DEFAULT, CDSDrivingKeyNumber_INVALID
 */
extern NSString* CDSDrivingKeyNumber;
enum eCDSDrivingKeyNumber
{
	CDSDrivingKeyNumber_0 = 0,
	CDSDrivingKeyNumber_1 = 1,
	CDSDrivingKeyNumber_2 = 2,
	CDSDrivingKeyNumber_3 = 3,
	CDSDrivingKeyNumber_NOTPERSONALIZED = 10,
	CDSDrivingKeyNumber_DEFAULT = 14,
	CDSDrivingKeyNumber_INVALID = 15
};

/*!
 @define     driving.mode
 @abstract   The current status of the vehicle's set "driving mode".  For example, sport, comfort, etc.
 @discussion Stored in response key "mode" as an enumeration with possible values: CDSDrivingMode_COMFORT, CDSDrivingMode_SPORT, CDSDrivingMode_ENHANCED_COMFORT, CDSDrivingMode_ENHANCED_SPORT, CDSDrivingMode_INVALID
 */
extern NSString* CDSDrivingMode;
enum eCDSDrivingMode
{
	CDSDrivingMode_COMFORT = 1,
	CDSDrivingMode_SPORT = 2,
	CDSDrivingMode_ENHANCED_COMFORT = 9,
	CDSDrivingMode_ENHANCED_SPORT = 10,
	CDSDrivingMode_INVALID = 15
};

/*!
 @define     driving.odometer
 @abstract   The total number of kilometers on a vehicle.  Should miles be required, the client should be responsible for the conversion.
 @discussion Stored in response key "odometer" as a number.
 */
extern NSString* CDSDrivingOdometer;

/*!
 @define     driving.parkingBrake
 @abstract   The current status and information about the vehicle's parking brake.
 @discussion Stored in response key "parkingBrake" as an enumeration with possible values: CDSDrivingParkingBrake_UNAVAILABLE, CDSDrivingParkingBrake_DISENGAGED, CDSDrivingParkingBrake_ENGAGED, CDSDrivingParkingBrake_INVALID
 */
extern NSString* CDSDrivingParkingBrake;
enum eCDSDrivingParkingBrake
{
	CDSDrivingParkingBrake_UNAVAILABLE = 0,
	CDSDrivingParkingBrake_DISENGAGED = 1,
	CDSDrivingParkingBrake_ENGAGED = 2,
	CDSDrivingParkingBrake_INVALID = 3
};

/*!
 @define     driving.speedActual
 @abstract   The current actual driving speed reported in km/h.
 @discussion Value is stored in response key "speedActual" as a number.
 */
extern NSString* CDSDrivingSpeedActual;

/*!
 @define     driving.speedDisplayed
 @abstract   The current displayed driving speed reported in km/h.
 @discussion Value is stored in response key "speedDisplayed" as a number.
 */
extern NSString* CDSDrivingSpeedDisplayed;

/*!
 @define     driving.shiftIndicator
 @abstract   This is an indicator alerting the driver to shift up or down from the current gear.
 @discussion Stored in a response key of "shiftIndicator".  Possible values are: CDSDrivingShiftIndicator_HIGHER, CDSDrivingShiftIndicator_LOWER, CDSDrivingShiftIndicator_NOADVICE, CDSDrivingShiftIndicator_INVALID
 */

extern NSString* CDSDrivingShiftIndicator;
enum eCDSDrivingShiftIndicator
{
	CDSDrivingShiftIndicator_NOADVICE = 0,
	CDSDrivingShiftIndicator_LOWER = 1,
	CDSDrivingShiftIndicator_HIGHER = 2, 
	CDSDrivingShiftIndicator_INVALID = 3
};

/*!
 @define     driving.steeringWheel
 @abstract   The steering wheel angle and the speed of the steering wheel angle when turning. It is measured in degrees and degrees/sec and is a signed value.
 @discussion Stored in response key "steeringWheel" as dictionary with keys "angle", "speed", and "error".
 */
extern NSString* CDSDrivingSteeringwheel;
