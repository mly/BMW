//
//  SimpleWeatherApp.h
//  SimpleWeather
//
//  Created by Paul Doersch on 1/6/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MainVC.h"
#import <iDrive/iDrive.h>

@interface SimpleWeatherApp : IDApplication {
	MainVC* mainVC;
}
@property(retain) MainVC* mainVC;


@end
