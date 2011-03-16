/*
 *  CDSPropertyDefinesControls.h
 *  iDrive
 *
 *  Created by Jeff Zabel on 10/29/09.
 *  Copyright 2009 BMW. All rights reserved.
 *
 *  $Id: CDSPropertyDefinesControls.h 50949 2010-11-29 12:25:54Z q188463 $
 */

/* ********************
 CONTROLS
 ********************** */
/*!
 @define     controls.convertibleTop
 @abstract   This give the value pertaining to the current status of the vehicle's convertible top position should the vehicle be a convertible.
 @discussion Stored in response key "convertibleTop" as an enumeration.  
 Possible values are: CDSControlsConvertibleTop_CLOSED, CDSControlsConvertibleTop_INTERMEDIATE, CDSControlsConvertibleTop_REMOVED, CDSControlsConvertibleTop_OPEN, CDSControlsConvertibleTop_HARDTOPATTACHED, CDSControlsConvertibleTop_INVALID
 */
extern NSString* CDSControlsConvertibleTop;
enum eCDSControlsConvertibleTop
{
	CDSControlsConvertibleTop_CLOSED = 0,
	CDSControlsConvertibleTop_INTERMEDIATE = 1,
	CDSControlsConvertibleTop_OPEN = 2,
	CDSControlsConvertibleTop_REMOVED = 3,
	CDSControlsConvertibleTop_HARDTOPATTACHED = 4,
	CDSControlsConvertibleTop_INVALID = 15
};

/*!
 @define     controls.cruiseControl
 @abstract   This give the value pertaining to the current status of the vehicle's cruise control state (on/off) as well as the desired cruise control speed setting.
 @discussion Stored in response key "cruiseControl" as dictionary with keys "desiredSpeed" and "status".
 Status is returned as an enum with the possible values CDSControlsCruiseControl_OFF, CDSControlsCruiseControl_ON, CDSControlsCruiseControl_INVALID
 */
extern NSString* CDSControlsCruiseControl;
enum eCDSControlsCruiseControl
{
	CDSControlsCruiseControl_OFF = 0,
	CDSControlsCruiseControl_INACTIVE = 1,
	CDSControlsCruiseControl_ON = 2,
	CDSControlsCruiseControl_INVALID = 7
};

/*!
 @define     controls.defrostRear
 @abstract   This give the value pertaining to the current status of the vehicle's rear window defrost system.
 @discussion Stored in response key "defrostRear" as an enumeration.  
 Possible values are: CDSControlsDefrost_OFF, CDSControlsDefrost_ON, CDSControlsDefrost_INVALID
 */
extern NSString* CDSControlsDefrostRear;
enum eCDSControlsDefrost
{
	CDSControlsDefrost_OFF = 0,
	CDSControlsDefrost_ON = 1,
	CDSControlsDefrost_INVALID = 3
};

/*!
 @define     controls.defrostFront
 @abstract   This give the value pertaining to the current status of the vehicle's front windshield defrost system.
 @discussion Stored in response key "defrostFront" as an enumeration.  
 Possible values are: CDSControlsDefrost_OFF, CDSControlsDefrost_ON, CDSControlsDefrost_INVALID
 */
extern NSString* CDSControlsDefrostFront;

/*!
 @define     controls.headlights
 @abstract   This give the value pertaining to the current status of the vehicle's exterior headlight status
 @discussion Stored in response key "headlights" as an enumeration. Possible values are: CDSControlsLights_ON, CDSControlsLights_OFF
 */
extern NSString* CDSControlsHeadlights;
enum eCDSControlsLights
{
	CDSControlsLights_OFF = 0,
	CDSControlsLights_ON = 1
};

/*!
 @define     controls.interiorLights
 @abstract   This give the value pertaining to the current color and brightness of the vehicle's interior mood lights.  Additionally, it gives information
 if the lights are cycling through all of their colors.
 @discussion Stored in response key "interiorLights" as dictionary with keys "brightness", "color", "colorCycleSpeed" and "colorCycle"
 */

extern NSString* CDSControlsInteriorLights;
enum eCDSControlsInteriorLightsRunning
{
	CDSControlsInteriorLightsRunning_INACTIVE= 0,
	CDSControlsInteriorLightsRunning_ACTIVE   = 1,
	CDSControlsInteriorLightsRunning_INVALID = 15
};

enum eCDSVehicleInteriorLightsRunningSpeed
{
	CDSControlsInteriorLightsRunningSpeed_DEFAULT   = 0,
	CDSControlsInteriorLightsRunningSpeed_1TO60SEC  = 1,
	CDSControlsInteriorLightsRunningSpeed_INVALID   = 63
};

/*!
 @define     controls.lights
 @abstract   This give the value pertaining to the current status of the vehicle's exterior light status (brights, parking lights, etc.)
 @discussion Stored in response key "lights" as a dictionary with keys "brights", "frontFog", "rearFog"
 Possible values are: CDSControlsLights_ON, CDSControlsLights_OFF
 */
extern NSString* CDSControlsLights;

/*!
 @define     controls.startStopLEDs
 @abstract   This returns information about the vehicles start/stop feature LED status.
 @discussion Stored in response key "startStopLEDs" as an enumeration of type eCDSControlsStartStopLEDs.
 Possible values are: CDSControlsStartStopLEDs_ON, CDSControlsStartStopLEDs_OFF, CDSControlsStartStopLEDs_INVALID
 */
extern NSString* CDSControlsStartStopLEDs;
enum eCDSControlsStartStopLEDs
{
	CDSControlsStartStopLEDs_ON = 0,
	CDSControlsStartStopLEDs_OFF = 1,
	CDSControlsStartStopLEDs_INVALID = 3
};

/*!
 @define     controls.startStopStatus
 @abstract   This returns information about the vehicles start/stop functionality and the status of the engine when this feature is activated
 @discussion Stored in response key "startStopStatus"  as an enumeration of type eCDSControlsStartStopStatus.
 Possible values are: CDSControlsStartStopStatus_OFF, CDSControlsStartStopStatus_ON, CDSControlsStartStopStatus_INVALID
 CDSControlsStartStopLED_ON, CDSControlsStartStopLED_OFF, CDSControlsStartStopLED_INVALID
 */
extern NSString* CDSControlsStartStopStatus;
enum eCDSControlsStartStopStatus
{
	CDSControlsStartStopStatus_DEACTIVATED = 0,
	CDSControlsStartStopStatus_ACTIVE_NO_MOTOR_STOP = 1,
	CDSControlsStartStopStatus_ACTIVE_MOTOR_STOP = 2,
	CDSControlsStartStopStatus_INVALID = 3
};

/*!
 @define     controls.sunroof
 @abstract   This returns information about the position of the vehicle's sunroof.
 @discussion Stored in response key "sunroof" as a dictionary with keys "status", "openPosition" and "tiltPosition".  Status is an enumeration
 while openPosition and tiltPosition are returned as numbers.
 Possible values for status are: CDSControlsSunroofStatus_CLOSED, CDSControlsSunroofStatus_MOVING, CDSControlsSunroofStatus_OPEN, CDSControlsSunroofStatus_INVALID
 */
extern NSString* CDSControlsSunroof;
enum eCDSControlsSunroofStatus
{
	CDSControlsSunroofStatus_CLOSED = 0,
	CDSControlsSunroofStatus_MOVING = 1,
	CDSControlsSunroofStatus_OPEN = 2,
	CDSControlsSunroofStatus_INVALID = 3
};

/*!
 @define     controls.turnSignal
 @abstract   This returns information about the status of the vehicle turn indicator singal or blinker.
 @discussion Stored in response key "turnSignal" as an enumeration.
 Possible values are: CDSControlsTurnSignal_OFF, CDSControlsTurnSignal_ONLEFT, CDSControlsTurnSignal_ONRIGHT, CDSControlsTurnSignal_ONBOTH, CDSControlsTurnSignal_INVALID
 */
extern NSString* CDSControlsTurnSignal;
enum eCDSControlsTurnSignal
{
	CDSControlsTurnSignal_OFF = 0,
	CDSControlsTurnSignal_ONLEFT = 1,
	CDSControlsTurnSignal_ONRIGHT = 2,
	CDSControlsTurnSignal_ONBOTH = 3, 
	CDSControlsTurnSignal_INVALID = 4,
};

/*!
 @define     controls.windowDriverFront
 @abstract   This returns information about the status and position of the driver side front window.
 @discussion Stored in response key "windowDriverFront" as a dictionary with keys "position" and "status".  Position is returned as a number of cm open.
 Status is returned as enumeration with possible valuese: CDSControlsWindowStatus_CLOSED, CDSControlsWindowStatus_MOVING, CDSControlsWindowStatus_OPEN, CDSControlsWindowStatus_INVALID
 */
extern NSString* CDSControlsWindowDriverFront;
enum eCDSControlsWindowStatus
{
	CDSControlsWindowStatus_CLOSED = 0,
	CDSControlsWindowStatus_MOVING = 1,
	CDSControlsWindowStatus_OPEN = 2,
	CDSControlsWindowStatus_INVALID = 3
};

/*!
 @define     controls.windowDriverRear
 @abstract   This returns information about the status and position of the driver side rear window.
 @discussion Stored in response key "windowDriverRear" as an enumeration with possible valuese: CDSControlsWindowStatus_CLOSED, CDSControlsWindowStatus_MOVING, CDSControlsWindowStatus_OPEN, CDSControlsWindowStatus_INVALID
 */
extern NSString* CDSControlsWindowDriverRear;

/*!
 @define     controls.windowPassengerFront
 @abstract   This returns information about the status and position of the passenger side front window.
 @discussion Stored in response key "windowPassengerFront" as a dictionary with keys "position" and "status".  Position is returned as a number of cm open.
 Status is returned as enumeration with possible valuese: CDSControlsWindowStatus_CLOSED, CDSControlsWindowStatus_MOVING, CDSControlsWindowStatus_OPEN, CDSControlsWindowStatus_INVALID
 */
extern NSString* CDSControlsWindowPassengerFront;

/*!
 @define     controls.windowPassengerRear
 @abstract   This returns information about the status and position of the passenger side rear window.
 @discussion Stored in response key "windowPassengerRear" as an eumeration with possible valuese: CDSControlsWindowStatus_CLOSED, CDSControlsWindowStatus_MOVING, CDSControlsWindowStatus_OPEN, CDSControlsWindowStatus_INVALID
 */
extern NSString* CDSControlsWindowPassengerRear;

/*!
 @define     controls.windshieldWiper
 @abstract   This returns information about the status of the vehicle's windshield wipers on the front windshield.
 @discussion Stored in response key "windshieldWiper" as an enumeration with possible valuese: 
 CDSControlsWindshieldWiper_OFF, CDSControlsWindshieldWiper_ON, CDSControlsWindshieldWiper_LOW, CDSControlsWindshieldWiper_HIGH, CDSControlsWindshieldWiper_TRIGGER, 
 CDSControlsWindshieldWiper_FRONTWASH, CDSControlsWindshieldWiper_REAR, CDSControlsWindshieldWiper_REARWASH, CDSControlsWindshieldWiper_INVALID.
 */
extern NSString* CDSControlsWindshieldWiper;
enum eCDSControlsWindshieldWiper
{
	CDSControlsWindshieldWiper_OFF = 0,
	CDSControlsWindshieldWiper_AUTOMATIC = 1,
	CDSControlsWindshieldWiper_LOW = 2,
	CDSControlsWindshieldWiper_HIGH = 3,
	CDSControlsWindshieldWiper_TRIGGER = 8,
	CDSControlsWindshieldWiper_FRONTWASH = 16,
	CDSControlsWindshieldWiper_REAR = 64,
	CDSControlsWindshieldWiper_REARWASH = 128,
	CDSControlsWindshieldWiper_INVALID = 255
};

