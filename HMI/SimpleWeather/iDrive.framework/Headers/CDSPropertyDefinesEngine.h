/*
 *  CDSPropertyDefinesEngine.h
 *  iDrive
 *
 *  Created by Jeff Zabel on 10/29/09.
 *  Copyright 2009 BMW. All rights reserved.
 *
 *  $Id: CDSPropertyDefinesEngine.h 50949 2010-11-29 12:25:54Z q188463 $
 */

/* *************************
 ENGINE
 ************************* */
/*!
 @define     engine.info
 @abstract   Returns information about the current engine such as number of Cylinders, number of gears, fuel type and gearbox type(ccm).
 @discussion Stored in a response key "info" as a dictionary with keys "displacement" "numberOfCylinders", "numberOfGears", "fuelType", and "gearboxType". 
 Possible values for numberOfCylinders are CDSEngineInfoNumCylinders_4, CDSEngineInfoNumCylinders_5, CDSEngineInfoNumCylinders_6, CDSEngineInfoNumCylinders_8, CDSEngineInfoNumCylinders_10, CDSEngineInfoNumCylinders_12, CDSEngineInfoNumCylinders_INVALID
 Possible values for numberOfGears are CDSEngineInfoNumGears_CONTINUOUS, CDSEngineInfoNumGears_4, CDSEngineInfoNumGears_5, CDSEngineInfoNumGears_6, CDSEngineInfoNumGears_7, CDSEngineInfoNumGears_8, CDSEngineInfoNumGears_INVALID
 Possible values for fuelType are CDSEngineInfoFxuelType_NOINFO, CDSEngineInfoFuelType_DIRECT_INJ_BENZINE, CDSEngineInfoFuelType_CONVENTIONAL_BENZINE, CDSEngineInfoFuelType_DIRECT_INJ_DIESEL, CDSEngineInfoFuelType_CONVENTIONAL_DIESEL, CDSEngineInfoFuelType_INVALID
 Possible values for gearboxType are CDSEngineInfoGearboxType_MANUAL, CDSEngineInfoGearboxType_AUTOMATIC, CDSEngineInfoGearboxType_STEPTRONIC, CDSEngineInfoGearboxType_SMG, CDSEngineInfoGearboxType_DOUBLECLUTCH, CDSEngineInfoGearboxType_INVALID
 displacement is returned as a number in ccm.
 */
extern NSString* CDSEngineInfo;
enum eCDSEngineInfoNumCylinders
{
    CDSEngineInfoNumCylinders_4 = 4,
	CDSEngineInfoNumCylinders_5 = 5,
	CDSEngineInfoNumCylinders_6 = 6,
	CDSEngineInfoNumCylinders_8 = 8, 
	CDSEngineInfoNumCylinders_10 = 10, 
	CDSEngineInfoNumCylinders_12 = 12, 
	CDSEngineInfoNumCylinders_INVALID = 15
	
};
enum eCDSEngineInfoNumGears
{
	CDSEngineInfoNumGears_CONTINUOUS = 0,
	CDSEngineInfoNumGears_4 = 4,
	CDSEngineInfoNumGears_5 = 5, 
	CDSEngineInfoNumGears_6 = 6,
	CDSEngineInfoNumGears_7 = 7,
	CDSEngineInfoNumGears_8 = 8, 
	CDSEngineInfoNumGears_INVALID = 15
};
enum eCDSEngineInfoFuelType
{
	CDSEngineInfoFuelType_NOINFO = 0,
	CDSEngineInfoFuelType_DIRECT_INJ_BENZINE = 4, 
	CDSEngineInfoFuelType_CONVENTIONAL_BENZINE = 5,
	CDSEngineInfoFuelType_DIRECT_INJ_DIESEL = 6,
	CDSEngineInfoFuelType_CONVENTIONAL_DIESEL = 7, 
	CDSEngineInfoFuelType_INVALID = 15
};
enum eCDSEngineInfoGearboxType
{
	CDSEngineInfoGearboxType_MANUAL = 0,
	CDSEngineInfoGearboxType_AUTOMATIC = 1,
	CDSEngineInfoGearboxType_STEPTRONIC = 2,
	CDSEngineInfoGearboxType_SMG = 3,
	CDSEngineInfoGearboxType_DOUBLECLUTCH = 4,
	CDSEngineInfoGearboxType_INVALID = 15
	
};

/*!
 @define     engine.consumption
 @abstract   Returns the value of the engine's current fuel consumption.  This is returned in μL. //TODO - need to verify this unit.
 @discussion Stored in a response key "consumption" as a number.
 */
extern NSString* CDSEngineConsumption;

/*!
 @define     engine.RPMSpeed
 @abstract   Returns the value of the engine rotations per minute (RPM) speed in rotations per minute
 @discussion Stored in a response key "RPMSpeed" as a number.
 */
extern NSString* CDSEngineRPMSpeed;

/*!
 @define     engine.status
 @abstract   Returns the value of the engine status.
 @discussion Possible values are eCDSEngineStatus_OFF, eCDSEngineStatus_STARTING, eCDSEngineStatus_RUNNING, or eCDSEngineStatus_INVALID.
 */
extern NSString* CDSEngineStatus;
enum eCDSEngineStatus
{
    CDSEngineStatus_OFF = 0,
    CDSEngineStatus_STARTING = 1,
    CDSEngineStatus_RUNNING = 2,
    CDSEngineStatus_INVALID = 3
};

/*!
 @define     engine.torque
 @abstract   Returns the value of the engine torque in a signed value.  One increment in value equals 0.5Nm //TODO: Check these units to confirm
 @discussion Stored in a response key "torque" as a number.
 */
extern NSString* CDSEngineTorque;

/*!
 @define     engine.maxTorque
 @abstract   Returns the value of the maximum engine torque [N/m] in a signed value.  One increment in value equals 0.5Nm //TODO: Check these units to confirm
 @discussion Stored in a response key "maxTorque" as a number.
 */
extern NSString* CDSEngineMaxTorque;

/*!
 @define     engine.temperature
 @abstract   Returns the value of the engine and oil temperature.  Both are returned as numbers with units of degrees C.
 @discussion Stored in a response key "temperature" as a dictionary with keys "engine", and "oil".
 */
extern NSString* CDSEngineTemperature;

/*!
 @define     engine.powerclass
 @abstract   Returns the value of the engine power ouput.  This is defined as the performance class f the vehicle. 
 @discussion Stored in a response key "powerclass" as an enumeration with the following possible values CDSPowerclass_UL, CDSPowerclass_ML, CDSPowerclass_OL, CDSPowerclass_SL, CDSPowerclass_TL, CDSPowerclass_KL.
 */
extern NSString* CDSEnginePowerclass;
enum eCDSEnginePowerclass
{
    CDSPowerclass_KL = 3,
	CDSPowerclass_TL = 7,
	CDSPowerclass_SL = 11,
	CDSPowerclass_OL = 14, 
	CDSPowerclass_ML = 13,
	CDSPowerclass_UL = 12,
	CDSPowerclass_INVALID = 15
};
