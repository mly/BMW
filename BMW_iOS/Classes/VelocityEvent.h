//
//  VelocityEvent.h
//  BMW_iOS
//
//  Created by Rob Balian on 3/8/11.
//  Copyright 2011 Stanford University. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface VelocityEvent : NSObject {
	double latitude,longitude,velocity,heading;
	NSString *device_id;
	NSDate *time;
}

@property double latitude,longitude,velocity,heading;
@property (nonatomic, retain) NSString *device_id;

@end
