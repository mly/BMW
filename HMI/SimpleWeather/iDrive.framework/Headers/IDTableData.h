/*
 *  IDTableData.h
 *  iDrive
 *
 *  Created by Wolfram Manthey on 22.04.09.
 *  Copyright 2009 BMW Car IT GmbH. All rights reserved.
 *
 *  $Id: IDTableData.h 50948 2010-11-29 12:20:12Z q188463 $
 */

#import <Foundation/Foundation.h>


@class IDTableRow;

/*!
 @class IDTableData
 */
@interface IDTableData : NSObject
{
    NSMutableArray* rows;
    NSUInteger columns;
}

+ (id)tableDataWithCapacity:(NSUInteger)capacity columns:(NSUInteger)maxColumns;

- (id)initWithCapacity:(NSUInteger)capacity columns:(NSUInteger)maxColumns;

- (void)addRow:(IDTableRow*)row;

@property (nonatomic, readonly) NSUInteger columns;
@property (nonatomic, readonly) NSArray* rows;

@end
