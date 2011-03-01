//
//  GravityObject.m
//  BMW_iOS
//
//  Created by Rob Balian on 3/1/11.
//  Copyright 2011 Stanford University. All rights reserved.
//

#import "GravityObject.h"


@implementation GravityObject

-(id)initWithX:(float)x Y:(float)y andZ:(float)z {
	if (self) {
		_x = x;
		_y = y;
		_z = z;
	}
	return self;
}

-(void)encodeWithCoder:(NSCoder *)encoder {
	[encoder encodeFloat:_x forKey:@"x"];
	[encoder encodeFloat:_y forKey:@"y"];
	[encoder encodeFloat:_z forKey:@"z"];
}

-(id)initWithCoder:(NSCoder *)decoder {
	float x = [decoder decodeFloatForKey:@"x"];
	float y = [decoder decodeFloatForKey:@"y"];
	float z = [decoder decodeFloatForKey:@"z"];
	return [self initWithX:x Y:y andZ:z];
}
	
@end
