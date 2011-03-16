//
//  IDMultimediaInfo.h
//  BMW
//
//  Created by Paul Doersch on 11/3/10.
//  Copyright 2010 BMW Technology Office Palo Alto. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "IDFlushProtocol.h"
@class IDApplication;


@interface IDMultimediaInfo : NSObject <IDFlushProtocol> {
	IDApplication* mApplication;
	NSInteger mTextModel1;
	NSInteger mTextModel2;
	NSInteger mUpdateEvent;
	
	NSString* mText1;
	NSString* mText2;
	
	BOOL mDirty;
}



//////////////////////////////////////////////////////////////
// Public
//////////////////////////////////////////////////////////////

/**
 * IDMultimediaInfo initializer.
 */
-(id)initWithApplication:(IDApplication*)application
			  textModel1:(NSInteger)textModel1
			  textModel2:(NSInteger)textModel2
			 updateEvent:(NSInteger)updateEvent;


/**
 * Sets the two lines of text in
 * the Multimedia split view.
 */
-(void)setText1:(NSString*)text1 text2:(NSString*)text2;


//////////////////////////////////////////////////////////////
// Private
//////////////////////////////////////////////////////////////
@property(assign) IDApplication* application;
@property(retain) NSString* text1;
@property(retain) NSString* text2;

@end
