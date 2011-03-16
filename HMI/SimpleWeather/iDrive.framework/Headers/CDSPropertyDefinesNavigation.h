/*
 *  CDSPropertyDefinesNavigation.h
 *  iDrive
 *
 *  Created by Jeff Zabel on 10/29/09.
 *  Copyright 2009 BMW. All rights reserved.
 *
 *  $Id: CDSPropertyDefinesNavigation.h 50949 2010-11-29 12:25:54Z q188463 $
 */

/* ************************
 NAVIGATION
 *********************** */

/*!
 @define     navigation.currentPositionDetailedInfo
 @abstract   Provides info in human readable form about the current position of the vehicle.
 @discussion Stored in a response key "currentPositionDetailedInfo" as a dictionary with keys "street", "houseNumber", "crossStreet", "city" and "country".  All paramters are except houseNumber are strings. houseNumber is a number.
 */
extern NSString* CDSNavigationCurrentPositionDetailedInfo;

/*!
 @define     navigation.finalDestinationDetailedInfo
 @abstract   Provides info in human readable form about the final destination of the vehicle.
 @discussion Stored in a response key "finalDestinationDetailedInfo" as a dictionary with keys "street", "houseNumber", "crossStreet", "city" and "country".  All paramters are except houseNumber are strings. houseNumber is a number.
 */
extern NSString* CDSNavigationFinalDestinationDetailedInfo;

/*!
 @define     navigation.finalDestination
 @abstract   Returns the final destination of the vehicle as latitude, longitude coordinates.
 @discussion Stored in a response key "finalDestination" as a dictionary with keys "latitude" and "longitude".  Both paramters are numbers.
 */
extern NSString* CDSNavigationFinalDestination;

/*!
 @define     navigation.GPSExtendedInfo
 @abstract   Returns the extended information about the current position of the vehicle.  This information includes altitude (m), heading(0 to 255, counter-clockwise, north = 0), speed(cm/s) as measured by the GPS sensor, and a quality number.
 @discussion Stored in a response key "GPSExtendedInfo" as a dictionary with keys "altitude", "heading", "speed" and "quality".  All paramters are numbers.
			 NOTE: This property does not currently support GET, only BIND.
 */
extern NSString* CDSNavigationGPSExtendedInfo;

/*!
 @define     navigation.GPSPosition
 @abstract   Returns the current position of the vehicle assuming the vehicle has navigation.  This is the best known position of the vehicle including map-matched position.  It is not the raw GPS sensor value.  This value is the raw
 value from the bus.  To covert to WSG84 format, please use the following formula: latitude(longitude) = latitude(longitude) / Math.pow(2, 32) * 360.
 @discussion Stored in a response key "GPSPosition" as a dictionary with keys "latitude" and "longitude".  Both paramters are numbers.
			 NOTE: This property does not currently support GET, only BIND.
 */
extern NSString* CDSNavigationGPSPosition;

/*!
 @define     navigation.guidanceStatus
 @abstract   Returns the current state of the route guidance system.
 @discussion Stored in a response key "guidanceStatus" as a number representing a BOOL. Please use boolValue of NSNumber to obtain the result.
 */
extern NSString* CDSNavigationGuidanceStatus;

/*!
 @define     navigation.infoToNextDestination
 @abstract   Provides info in human readable form about the next destination of the guidance system..
 @discussion Stored in a response key "infoToNextDestination" as a dictionary with keys "airDistance" (in meters), "direction" (in degrees), "distance" (in meters), "remainingTime" (in minutes) and "routeHandle".  All values are numbers.
 */
extern NSString* CDSNavigationInfoToNextDestination;

/*!
 @define     navigation.infoToFinalDestination
 @abstract   Provides info in human readable form about the final destination of the guidance system..
 @discussion Stored in a response key "infoToFinalDestination" as a dictionary with keys "airDistance" (in meters), "direction" (in degrees), "distance" (in meters), "remainingTime" (in minutes) and "routeHandle".  All values are numbers.
 */
extern NSString* CDSNavigationInfoToFinalDestination;

/*!
 @define     navigation.nextDestination
 @abstract   Returns the next destination of the vehicle as latitude, longitude coordinates along with the name and type of the destination.
 @discussion Stored in a response key "nextDestination" as a dictionary with keys "latitude", "longitude" (both in numbers), "name" (as a string) and "type" (as an enum of type eCDSNavigationDestinationType).
			 NOTE: This property does not currently support GET, only BIND.
 */
extern NSString* CDSNavigationNextDestination;
enum eCDSNavigationDestinationType
{
	CDSNavigationDestinationType_UNKNOWN = 0,
	CDSNavigationDestinationType_COUNTRY = 1,
	CDSNavigationDestinationType_CITY = 2,
	CDSNavigationDestinationType_STREET = 3,
	CDSNavigationDestinationType_POINT = 4,
	CDSNavigationDestinationType_HOUSE_NUMBER = 5
};

/*!
 @define     navigation.nextDestinationDetailedInfo
 @abstract   Provides info in human readable form about the next destination of the vehicle.
 @discussion Stored in a response key "nextDestinationDetailedInfo" as a dictionary with keys "street", "houseNumber", "crossStreet", "city" and "country".  All paramters are except houseNumber are strings. houseNumber is a number.
 */
extern NSString* CDSNavigationNextDestinationDetailedInfo;

/*!
 @define     navigation.routeElapsedInfo
 @abstract   Returns the elapsed route info for the vehicle including distance traveled and time.
 @discussion Stored in a response key "routeElapsedInfo" as a dictionary with keys "distance" (in 100m) and "time" (in minutes). All values are numbers.
 */
extern NSString* CDSNavigationRouteElapsedInfo;

/*!
 @define     navigation.units
 @abstract   Returns the current units used in route guidance system.
 @discussion Stored in a response key "units" as an enum of type eCDSNavigationDestinationUnits.
 */
extern NSString* CDSNavigationUnits;
enum eCDSNavigationDestinationUnits
{
	CDSNavigationDestinationUnits_DEFAULT = 1,
	CDSNavigationDestinationUnits_METRIC = 2,
	CDSNavigationDestinationUnits_IMPERIAL_GB = 3,
	CDSNavigationDestinationUnits_IMPERIAL_USA = 4
};

