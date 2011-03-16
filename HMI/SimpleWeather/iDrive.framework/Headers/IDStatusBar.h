//
//  IDStatusBar.h
//  BMW
//
//  Created by Paul Doersch on 11/8/10.
//  Copyright 2010 BMW Technology Office Palo Alto. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "IDFlushProtocol.h"
@class IDApplication;


@interface IDStatusBar : NSObject <IDFlushProtocol> {
	IDApplication* mApplication;
	NSInteger mTextModel;
	NSInteger mUpdateEvent;
	NSString* mText;
	BOOL mDirty;
}



//////////////////////////////////////////////////////////////
// Public
//////////////////////////////////////////////////////////////

/**
 * IDStatusBar initializer.
 */
-(id)initWithApplication:(IDApplication*)application
			   textModel:(NSInteger)textModel
			 updateEvent:(NSInteger)updateEvent;


/**
 * Sets the text in the Status Bar
 * to text.
 */
-(void)setText:(NSString*)text;


//////////////////////////////////////////////////////////////
// Private
//////////////////////////////////////////////////////////////
@property(assign) IDApplication* application;
@property(retain) NSString* text;

@end
