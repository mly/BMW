//
//  VelocityEvent.m
//  BMW_iOS
//
//  Created by Rob Balian on 3/8/11.
//  Copyright 2011 Stanford University. All rights reserved.
//

#import "VelocityEvent.h"


@implementation VelocityEvent

@synthesize latitude,longitude,velocity,heading, device_id;

-(id)init {
	if (self) {
		self.device_id = [[UIDevice currentDevice] uniqueIdentifier];
		/*NSDate *date = [NSDate date];
		NSDateFormatter *df = [[NSDateFormatter alloc] init];
		NSLog(@"%@", [df stringFromDate:date]);*/
	}
	return self;
}


@end
