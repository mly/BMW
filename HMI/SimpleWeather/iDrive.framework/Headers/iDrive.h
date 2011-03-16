/*
 *  iDrive.h
 *  iDrive
 *
 *  Created by Wolfram Manthey on 17.04.09.
 *  Copyright 2009 BMW Car IT GmbH. All rights reserved.
 *
 *  $Id: iDrive.h 51483 2010-12-09 16:31:09Z q188463 $
 */

/*!
 @header iDrive Framework
 @version 1.0.0 (0:52279M)
 */

#import <Foundation/Foundation.h>

#ifdef __cplusplus
extern "C" {
#endif

#import "IDVersionInfo.h"
#import "IDEventTypes.h"
#import "IDPropertyTypes.h"
#import "IDParameterTypes.h"
#import "IDKeyCodes.h"
#import "IDResourceIdentifier.h"
#import "IDVariantData.h"
#import "IDVariantMap.h"
#import "IDTableRow.h"
#import "IDTableData.h"
#import "IDConnection.h"
#import "IDApplication.h"
#import "IDSecureApp.h"
#import "IDViewControllerLayer.h"
#import "IDCarDataService.h"
#import "IDService.h"
#import "IDHmiService.h"
#import "IDSecurityAuthService.h"
#import "IDCarDataService.h"
//#import "IDOTFLogService.h"
#import "NSString+IDSBJSON.h"
#import "IDCarInfo.h"

#import "CDSPropertyDefines.h"
#import "ExternalAccessoryMonitor.h"

#import "IDAVService.h"
#import "IDOffBoardAVService.h"
#import "IDSocketLogAppender.h"
#import "IDApplicationWatchdog.h"	

extern NSString* IDriveSvnRevision;
extern NSString* IDriveSvnUrl;
extern NSString* IDriveBuildTime;
    
#ifdef __cplusplus
}
#endif
