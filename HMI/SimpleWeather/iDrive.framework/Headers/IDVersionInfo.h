//
//  IDVersionInfo.h
//  iDrive
//
//  Created by Brian Jensen on 12/6/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//
//  $Id: IDVersionInfo.h 51282 2010-12-06 13:56:07Z q265910 $
//

#import <Foundation/Foundation.h>


@interface IDVersionInfo : NSObject
{
}

+ (IDVersionInfo*)versionInfoWithMajor:(NSUInteger)major minor:(NSUInteger)minor revision:(NSUInteger)revision;
- (id)initWithMajor:(NSUInteger)major minor:(NSUInteger)minor revision:(NSUInteger)revision;

@property (assign) NSUInteger major;
@property (assign) NSUInteger minor;
@property (assign) NSUInteger revision;
@property (readonly) NSString* stringValue;

@end
