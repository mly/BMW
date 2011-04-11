/*
 *  RHResourceIdentifier.h
 *  iDrive
 *
 *  Created by Wolfram Manthey on 21.04.09.
 *  Copyright 2009 BMW Car IT GmbH. All rights reserved.
 *
 *  $Id: IDResourceIdentifier.h 50948 2010-11-29 12:20:12Z q188463 $
 */

#import <Foundation/Foundation.h>


typedef enum {
    IDResourceTypeHmiDescription,
    IDResourceTypeImageDatabase,
    IDResourceTypeTextDatabase
} IDResourceType;


@interface IDResourceIdentifier : NSObject
{
    IDResourceType  type;
    NSUInteger      identifier;
}

@property (nonatomic, assign) IDResourceType type;
@property (nonatomic, assign) NSUInteger identifier;

@end
