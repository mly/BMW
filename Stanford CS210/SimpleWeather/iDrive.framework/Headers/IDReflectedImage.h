//
//  IDReflectedImage.h
//  BMW
//
//  Created by patyo-mbp-7 on 11/9/10.
//  Copyright 2010 BMW Technology Office Palo Alto. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "IDImage.h"


@interface IDReflectedImage : IDImage {
	NSInteger mReflectionWidgetID;
	NSInteger mReflectionModelID;
	CGPoint mReflectionPositionCached;
	float mGloss;
}

-(id)initWithViewController:(IDViewController*)viewController 
				   widgetID:(NSInteger)widgetID 
					modelID:(NSInteger)modelID 
		 reflectionWidgetID:(NSInteger)reflectionWidgetID
		  reflectionModelID:(NSInteger)reflectionModelID
					  gloss:(float)gloss;
@end
