//
//  WeatherRenderer.h
//  SimpleWeather
//
//  Created by Paul Doersch on 1/24/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Forecast.h"

@interface WeatherRenderer : NSObject {

}

+(UIImage*)renderWithForecast:(Forecast*)forecast;

@end
