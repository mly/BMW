//
//  Forcast.h
//  SimpleWeather
//
//  Created by Paul Doersch on 1/24/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Day.h"

@interface Forecast : NSObject {
	NSString* locationName;
	NSArray* days;
}

@property(retain) NSString* locationName;
@property(retain) NSArray* days;

@end
