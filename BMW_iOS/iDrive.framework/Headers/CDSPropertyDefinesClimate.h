/*
 *  CDSPropertyDefinesClimate.h
 *  iDrive
 *
 *  Created by Jeff Zabel on 10/29/09.
 *  Copyright 2009 BMW. All rights reserved.
 *
 *  $Id: CDSPropertyDefinesClimate.h 50949 2010-11-29 12:25:54Z q188463 $
 */


/* ********************
 CLIMATE
 ********************** */

/*!
 @define     climate.ACCompressor
 @abstract   This give the value pertaining to the status of the vehicle's air conditioner compressor.  
 @discussion Stored in response key "ACCompressor" as an enumeration.  
 Possible values are: CDSClimateACCompressor_OFF, CDSClimateACCompressor_ON, CDSClimateACCompressor_INVALID
 */
extern NSString* CDSClimateACCompressor;
enum eCDSClimateACCompressor
{
	CDSClimateACCompressor_OFF = 0,
	CDSClimateACCompressor_ON = 1,
	CDSClimateACCompressor_INVALID = 3
};

/*!
 @define     climate.ACHeatFlux
 @abstract   Information regarding the heat flux status of the airconditioning system and the amount of heat required by the system or the amount of heat that can be returned.  
 @discussion Stored in response key "ACHeatFlux" as an number within the range of 0-255.  
 */
extern NSString* CDSClimateACHeatFlux;

/*!
 @define     climate.ACMode
 @abstract   This gives information about the mode selected for the vehicle's airconditioning system.  It gives the status of MaxCool, air recirculation and front window defrost controls. 
 @discussion Stored in response key "ACMode" as a dictionary with keys "maxCool", "recirculation", and "defrost".  All values are retured as enumerations.  
 Possible values for maxCool and defrost are: CDSClimateACMode_OFF, CDSClimateACMode_ON, CDSClimateACMode_INVALID
 Possible values for recirculation are: CDSClimateACModeRecirculation_OFF, CDSClimateACModeRecirculation_ON, CDSClimateACModeRecirculation_BLOWERONLY, CDSClimateACModeRecirculation_INVALID //TODO - check what these really mean, the blower only is not clear
 */
extern NSString* CDSClimateACMode;
enum eCDSClimateACMode
{
	CDSClimateACMode_OFF = 0,
	CDSClimateACMode_ON = 1,
	CDSClimateACMode_INVALID = 3
};
enum eCDSClimateACModeRecirculation
{
	CDSClimateACModeRecirculation_OFF = 0,
	CDSClimateACModeRecirculation_ON = 1,
	CDSClimateACModeRecirculation_BLOWERONLY = 2,
	CDSClimateACModeRecirculation_INVALID = 3
};

/*!
 @define     climate.ACSystemTemperatures
 @abstract   This gives information about the temperatures of the evaporator and heat exchanger in the climate control system. These values are useful for efficient dynamic calculations.
 @discussion Stored in response key "ACSystemTemperatures" as a dictionary with keys "evaporator" and heatExchanger".  Both are returned as numbers in degrees Centigrade.
 */
extern NSString* CDSClimateACSystemTemperatures;

/*!
 @define     climate.driverSettings
 @abstract   This gives information about the driver settings for the climate control system.  It reports the setting for the desired temperature, the chosen program and the status of the automatic blower.
 @discussion Stored in response key "driverSettings" as a dictionary with keys "desiredTemperature", "program" and "automaticBlower".  desiredTemperature is a number and returned in degrees C //TODO - check to make sure this is true
 program is returned as an enumeration with possible values: CDSClimateSettingsProgram_AUTO, CDSClimateSettingsProgram_TOPMIDDLEBOTTOM, CDSClimateSettingsProgram_TOPMIDDLE, CDSClimateSettingsProgram_TOPBOTTOM, CDSClimateSettingsProgram_TOP, CDSClimateSettingsProgram_MIDDLEBOTTOM, CDSClimateSettingsProgram_MIDDLE
 CDSClimateSettingsProgram_BOTTOM, CDSClimateSettingsProgram_DEFAULT, CDSClimateSettingsProgram_HEAT, CDSClimateSettingsProgram_BILEVEL, CDSClimateSettingsProgram_VENT, CDSClimateSettingsProgram_FLOOR, CDSClimateSettingsProgram_INDIVIDUAL, CDSClimateSettingsProgram_OFF, CDSClimateSettingsProgram_DEFROST
 CDSClimateSettingsProgram_MAXAC, CDSClimateSettingsProgram_SPECIAL, CDSClimateSettingsProgram_MANUAL, CDSClimateSettingsProgram_INVALID
 automaticblower is returned as an enumeration with possible values: CDSClimateSettingsAutoBlower_OFF, CDSClimateSettingsAutoBlower_ON, CDSClimateSettingsAutoBlower_RESERVED, CDSClimateSettingsAutoBlower_INVALID
 */
extern NSString* CDSClimateDriverSettings;
enum eCDSClimateSettingsProgram
{
	CDSClimateSettingsProgram_AUTO = 0,
	CDSClimateSettingsProgram_TOPMIDDLEBOTTOM = 1,
	CDSClimateSettingsProgram_TOPMIDDLE = 2,
	CDSClimateSettingsProgram_TOPBOTTOM = 3,
	CDSClimateSettingsProgram_TOP = 4,
	CDSClimateSettingsProgram_MIDDLEBOTTOM = 5,
	CDSClimateSettingsProgram_MIDDLE = 6,
	CDSClimateSettingsProgram_BOTTOM = 7,
	CDSClimateSettingsProgram_DEFAULT = 8,
	CDSClimateSettingsProgram_HEAT = 9,
	CDSClimateSettingsProgram_BILEVEL = 10,
	CDSClimateSettingsProgram_VENT = 11,
	CDSClimateSettingsProgram_FLOOR = 12,
	CDSClimateSettingsProgram_INDIVIDUAL = 13,
	CDSClimateSettingsProgram_OFF = 14,
	CDSClimateSettingsProgram_DEFROST = 15,
	CDSClimateSettingsProgram_MAXAC = 16,
	CDSClimateSettingsProgram_SPECIAL = 17,
	CDSClimateSettingsProgram_MANUAL = 18,
	CDSClimateSettingsProgram_INVALID = 19
};
enum eCDSClimateSettingsAutoBlower
{
	CDSClimateSettingsAutoBlower_OFF = 0,
	CDSClimateSettingsAutoBlower_ON = 1,
	CDSClimateSettingsAutoBlower_RESERVED = 2,
	CDSClimateSettingsAutoBlower_INVALID = 3
};

/*!
 @define     climate.passengerSettings
 @abstract This gives information about the passenger settings for the climate control system.  It reports the setting for the desired temperature, the chosen program and the status of the automatic blower.
 @discussion Stored in response key "passengerSettings" as a dictionary with keys "desiredTemperature", "program" and "automaticBlower".  desiredTemperature is a number and returned in degrees C //TODO - check to make sure this is true
 program is returned as an enumeration with possible values: CDSClimateSettingsProgram_AUTO, CDSClimateSettingsProgram_TOPMIDDLEBOTTOM, CDSClimateSettingsProgram_TOPMIDDLE, CDSClimateSettingsProgram_TOPBOTTOM, CDSClimateSettingsProgram_TOP, CDSClimateSettingsProgram_MIDDLEBOTTOM, CDSClimateSettingsProgram_MIDDLE
 CDSClimateSettingsProgram_BOTTOM, CDSClimateSettingsProgram_DEFAULT, CDSClimateSettingsProgram_HEAT, CDSClimateSettingsProgram_BILEVEL, CDSClimateSettingsProgram_VENT, CDSClimateSettingsProgram_FLOOR, CDSClimateSettingsProgram_INDIVIDUAL, CDSClimateSettingsProgram_OFF, CDSClimateSettingsProgram_DEFROST
 CDSClimateSettingsProgram_MAXAC, CDSClimateSettingsProgram_SPECIAL, CDSClimateSettingsProgram_MANUAL, CDSClimateSettingsProgram_INVALID
 automaticblower is returned as an enumeration with possible values: CDSClimateSettingsAutoBlower_OFF, CDSClimateSettingsAutoBlower_ON, CDSClimateSettingsAutoBlower_RESERVED, CDSClimateSettingsAutoBlower_INVALID
 */
extern NSString* CDSClimatePassengerSettings;

/*!
 @define     climate.seatHeatDriver
 @abstract This gives information regarding the seat heating information for the driver.  
 @discussion Stored in response key "seatHeatDriver" as an enumeration.  Possible values are: CDSClimateSeatHeat_OFF, CDSClimateSeatHeat_LOW, CDSClimateSeatHeat_MED, CDSClimateSeatHeat_HIGH, CDSClimateSeatHeat_INVALID
 */
extern NSString* CDSClimateSeatHeatDriver;
enum eCDSClimateSeatHeating
{
	CDSClimateSeatHeat_OFF = 0,
	CDSClimateSeatHeat_LOW = 1,
	CDSClimateSeatHeat_MED = 2,
	CDSClimateSeatHeat_HIGH = 3,
	CDSClimateSeatHeat_INVALID = 15
};

/*!
 @define     climate.seatHeatPassenger
 @abstract This gives information regarding the seat heating information for the passenger.
 @discussion Stored in response key "seatHeatPassenger" as an enumeration.  Possible values are: CDSClimateSeatHeat_OFF, CDSClimateSeatHeat_LOW, CDSClimateSeatHeat_MED, CDSClimateSeatHeat_HIGH, CDSClimateSeatHeat_INVALID
 */
extern NSString* CDSClimateSeatHeatPassenger;

/*!
 @define     climate.residualHeat
 @abstract This gives information regarding the residual heat information.  
 @discussion Stored in response key "residualHeat" as an enumeration.  Possible values are: CDSClimateResidualHeat_OFF, CDSClimateResidualHeat_ON, CDSClimateResidualHeat_INVALID
 */
extern NSString* CDSClimateResidualHeat;
enum eCDSClimateResidualHeat
{
	CDSClimateResidualHeat_OFF = 0,
	CDSClimateResidualHeat_ON = 1,
	CDSClimateResidualHeat_INVALID = 3
};
