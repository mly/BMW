/*
 *  IDService.h
 *  iDrive
 *
 *  Created by Wolfram Manthey on 06.04.10.
 *  Copyright 2010 BMW Car IT GmbH. All rights reserved.
 *
 *  $Id: IDService.h 51282 2010-12-06 13:56:07Z q265910 $
 */

#import <Foundation/Foundation.h>


@class IDApplication;
@protocol IDConnection;

@interface IDService : NSObject
{
    IDApplication* _application;
    NSUInteger     _serviceId;
}

- (id)initWithApplication:(IDApplication*)application;

@property (readonly) id<IDConnection> connection;
@property (readonly) IDApplication* application;
@property (readonly) NSUInteger serviceId;

@end
