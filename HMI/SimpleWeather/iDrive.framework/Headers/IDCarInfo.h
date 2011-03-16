//
//  IDCarInfo.h
//  iDrive
//
//  Created by Paul Doersch on 1/6/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "IDConnection.h"
#import "IDVersionInfo.h"

@interface IDCarInfo : NSObject {
	NSDictionary* mCachedSystemInfo;
}
@property(retain) NSDictionary* cachedSystemInfo;

+(IDCarInfo*)currentCar;
-(BOOL)bmw;
-(BOOL)mini;

-(BOOL)release_0711;
-(BOOL)release_0311;
-(BOOL)release_1110;

+(void)resetWithConnection:(id<IDConnection>)connection error:(NSError**)error; // blocking call if connection != nil
+(NSString*)carInfoLogPath;
@end
