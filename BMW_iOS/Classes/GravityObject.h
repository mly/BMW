//
//  GravityObject.h
//  BMW_iOS
//
//  Created by Rob Balian on 3/1/11.
//  Copyright 2011 Stanford University. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface GravityObject : NSObject <NSCoding> {
	float _x,_y,_z;
}

-(id)initWithX:(float)x Y:(float)y andZ:(float)z;


@end
