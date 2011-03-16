/*
 *  CDSPropertyDefines.h
 *  iDrive
 *
 *  Created by Michael Smochko on 20 Aug 2009.
 *  Copyright 2009 BMW. All rights reserved.
 *
 *  $Id: CDSPropertyDefines.h 50949 2010-11-29 12:25:54Z q188463 $
 */

#import <Foundation/Foundation.h>

#import "CDSPropertyDefinesClimate.h"
#import "CDSPropertyDefinesCommunication.h"
#import "CDSPropertyDefinesControls.h"
#import "CDSPropertyDefinesDriving.h"
#import "CDSPropertyDefinesEngine.h"
#import "CDSPropertyDefinesEntertainment.h"
#import "CDSPropertyDefinesNavigation.h"
#import "CDSPropertyDefinesSensors.h"
#import "CDSPropertyDefinesVehicle.h"
#import "CDSPropertyDefinesHMI.h"

// CDSError definitions
enum
{
	CDSErrorInvalidProperty = 400,
	CDSErrorPropertyUnavailable = 401,
	CDSErrorPropertyForbidden = 402
};
