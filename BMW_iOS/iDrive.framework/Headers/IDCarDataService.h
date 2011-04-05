/*
 *  IDCarDataServer.h
 *  iDrive
 *
 *  Created by Wolfram Manthey on 07.12.09.
 *  Copyright 2009 BMW Car IT GmbH. All rights reserved.
 *
 *  $Id: IDCarDataService.h 51282 2010-12-06 13:56:07Z q265910 $
 */

#import <Foundation/Foundation.h>

#import "IDService.h"
#import "IDEventHandler.h"


@protocol IDConnection;

@class IDLogger;
@class IDVersionInfo;

@interface IDCarDataService : IDService <IDEventHandler>
{    
    NSMutableSet*        _propertyChangedEventObservers;
    NSMutableSet*        _propertyAsyncGetObservers;
    
    NSInteger			 _eventHandlerCount;
    
    IDVersionInfo*       _versionInfo;
}

- (IDVersionInfo*)versionInfo;

- (void)bindProperty:(NSString*)propertyName target:(id)target selector:(SEL)selector;

/*!
 @abstract		Binds to a property.	
 @param         propertyName Name of property.
 @param         interval Minimum time interval between to data updates in seconds.
 @param         target Target object.
 @param         selector Callback function for data updates. 
 */
- (void)bindProperty:(NSString*)propertyName interval:(NSTimeInterval)interval target:(id)target selector:(SEL)selector;

- (void)unbindProperty:(NSString*)propertyName target:(id)target selector:(SEL)selector;

- (void)asyncGetProperty:(NSString*)propertyName target:(id)target selector:(SEL)selector;

@end
