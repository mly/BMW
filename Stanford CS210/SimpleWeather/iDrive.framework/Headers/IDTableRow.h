/*
 *  IDTableRow.h
 *  iDrive
 *
 *  Created by Wolfram Manthey on 22.04.09.
 *  Copyright 2009 BMW Car IT GmbH. All rights reserved.
 *
 *  $Id: IDTableRow.h 50948 2010-11-29 12:20:12Z q188463 $
 */

#import <Foundation/Foundation.h>


@class IDVariantData;

/*!
 @class IDTableRow
 */
@interface IDTableRow : NSObject
{
    NSMutableArray* _variants;
}

+ (IDTableRow*)rowWithColumns:(NSUInteger)columns;

- (id)initWithColumns:(NSUInteger)columns;

- (void)setItem:(IDVariantData*)data atColumn:(NSInteger)column;
- (IDVariantData*)itemAtColumn:(NSInteger)column;
- (NSEnumerator*) objectEnumerator;

@property (nonatomic, readonly) NSUInteger columns;

@end
