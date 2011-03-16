//
//  Day.h
//  SimpleWeather
//
//  Created by Paul Doersch on 1/24/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef enum WeatherType {
	Snow,
	Rain,
	Sun,
	Sun_Cloud,
	Cloud,
	Lightning
} WeatherType;

@interface Day : NSObject {
	float highTemp;
	float lowTemp;
	float wind;
	float snowBase;
	WeatherType weatherType;
}

@property float highTemp;
@property float lowTemp;
@property float wind;
@property float snowBase;
@property WeatherType weatherType;

@end
