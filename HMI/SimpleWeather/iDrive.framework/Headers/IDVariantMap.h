/*
 *  RHVariantMap.h
 *  iDrive
 *
 *  Created by Wolfram Manthey on 10.08.09.
 *  Copyright 2009 BMW Car IT GmbH. All rights reserved.
 *
 *  $Id: IDVariantMap.h 50948 2010-11-29 12:20:12Z q188463 $
 */

#import <Foundation/Foundation.h>


@class IDVariantData;

/*!
 @class IDVariantMap
 */
@interface IDVariantMap : NSObject
{
    NSMutableDictionary* _content;
}

+ (IDVariantMap*)variantMapWithVariant:(IDVariantData*)variant forId:(NSInteger)theId;
+ (IDVariantMap*)variantMapWithDictionary:(NSDictionary*)dictionary;

- (id)initWithVariant:(IDVariantData*)variant forId:(NSInteger)theId;
- (id)initWithDictionary:(NSDictionary*)dictionary;

- (void)setVariant:(IDVariantData*)variant forId:(NSInteger)theId; // IDParameterTypes
- (IDVariantData*)variantForId:(NSInteger)theId; // IDParameterTypes

- (NSUInteger)count;

@end
