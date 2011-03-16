/*
 *  IDVariantData.h
 *  iDrive
 *
 *  Created by Wolfram Manthey on 15.10.09.
 *  Copyright 2009 BMW Car IT GmbH. All rights reserved.
 *
 *  $Id: IDVariantData.h 50948 2010-11-29 12:20:12Z q188463 $
 */

#import <Foundation/Foundation.h>


extern NSString* IDVariantMismatchException;

typedef enum
{
    IDVariantTypeInvalid = 0,
    IDVariantTypeBoolean,
    IDVariantTypeInteger,
    IDVariantTypeString,
    IDVariantTypeDate,
    IDVariantTypeTextId,
    IDVariantTypePreInstTextId,
    IDVariantTypeImageId,
    IDVariantTypePreInstImageId,
    IDVariantTypeImageData,
    IDVariantTypeResource,
} IDVariantType;

@class IDResourceIdentifier;

/*!
 @class IDVariantData
 */
@interface IDVariantData : NSObject
{
    id             _variant;
    IDVariantType  _variantType;
}

+ (IDVariantData*)variantWithBoolean:(BOOL)data;
+ (IDVariantData*)variantWithInteger:(NSInteger)data;
+ (IDVariantData*)variantWithString:(NSString*)data;
+ (IDVariantData*)variantWithDate:(NSDateComponents*)data;
+ (IDVariantData*)variantWithTextId:(NSInteger)data;
+ (IDVariantData*)variantWithPreInstTextId:(NSInteger)data;
+ (IDVariantData*)variantWithImageId:(NSInteger)data;
+ (IDVariantData*)variantWithPreInstImageId:(NSInteger)data;
+ (IDVariantData*)variantWithImageData:(NSData*)data;
+ (IDVariantData*)variantWithResource:(IDResourceIdentifier*)data;

- (id)initWithBoolean:(BOOL)data;
- (id)initWithInteger:(NSInteger)data;
- (id)initWithString:(NSString*)data;
- (id)initWithDate:(NSDateComponents*)data;
- (id)initWithTextId:(NSInteger)data;
- (id)initWithPreInstTextId:(NSInteger)data;
- (id)initWithImageId:(NSInteger)data;
- (id)initWithPreInstImageId:(NSInteger)data;
- (id)initWithImageData:(NSData*)data;
- (id)initWithResource:(IDResourceIdentifier*)data;

- (BOOL)booleanValue;
- (NSInteger)integerValue;
- (NSString*)string;
- (NSDateComponents*)date;
- (NSInteger)textId;
- (NSInteger)imageId;
- (NSData*)imageData;
- (IDResourceIdentifier*)resource;

- (BOOL)isTypeOf:(IDVariantType)type;

@property (readonly) IDVariantType type;

@end
