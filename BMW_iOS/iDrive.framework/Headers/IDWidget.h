//
//  IDWidget.h
//  BMW
//
//  Created by Paul Doersch on 10/28/10.
//  Copyright 2010 BMW Technology Office Palo Alto. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "IDFlushProtocol.h"
@class IDViewController;

@interface IDWidget : NSObject <IDFlushProtocol> {
	IDViewController* mViewController;
	NSInteger mWidgetID;
	NSInteger mModelID;
	
	BOOL mVisible;
	BOOL mVisible_dirty;
	
	BOOL mEnabled;
	BOOL mEnabled_dirty;
}


//////////////////////////////////////////////////////////////
// Public
//////////////////////////////////////////////////////////////

/**
 * IDWidget initializer.
 */
-(id)initWithViewController:(IDViewController*)viewController widgetID:(NSInteger)widgetID modelID:(NSInteger)modelID;


/**
 * Sets the widget to visible
 * or invisible.
 */
-(void)setVisible:(BOOL)visible;


/**
 * Sets the widget to enabled
 * or not enabled.
 */
-(void)setEnabled:(BOOL)enabled;



//////////////////////////////////////////////////////////////
// Private
//////////////////////////////////////////////////////////////
-(void)doDisconnect;
@property(assign) IDViewController* viewController;


@end
