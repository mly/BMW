//
//  IDButton.h
//  BMW
//
//  Created by Paul Doersch on 11/2/10.
//  Copyright 2010 BMW Technology Office Palo Alto. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "IDWidget.h"
#import "iDrive.h"

@interface IDButton : IDWidget {
	NSInteger mActionID;
	NSInteger mImageModelID;
	id mTarget;
	SEL mSelector;
	
	NSInteger mTargetModelID;
	NSInteger mTargetHmiStateID;
	BOOL mTargetHmiStateID_dirty;
	
	NSString* mTitle;
	BOOL mTitle_dirty;
	
	NSInteger mImageID;
	BOOL mImageID_dirty;
}


//////////////////////////////////////////////////////////////
// Public
//////////////////////////////////////////////////////////////

/**
 * UIButton initializer.
 */
-(id)initWithViewController:(IDViewController*)viewController 
				   widgetID:(NSInteger)widgetID 
					modelID:(NSInteger)modelID 
			   imageModelID:(NSInteger)imageModelID 
				   actionID:(NSInteger)actionID
			  targetModelID:(NSInteger)targetModelID;


/**
 * Set the callback taarget and selector
 * for a button click. This must be
 * called rhmiDidStart.
 */
-(void)setTarget:(id)target selector:(SEL)selector;


/**
 * Set the target view. When an element from 
 * the tabel is selected, this view is 
 * presented automtically.
 */
-(void)setTargetView:(IDViewController*)viewController;


/**
 * Set the Title of a button.
 * This must be called rhmiDidStart.
 * The selector must have the following 
 * signature -(void)yourMethod:(IDButton*)button
 */
-(void)setTitle:(NSString*)title;


/**
 * Set the Image of a button.
 * This must be called rhmiDidStart.
 */
-(void)setImageID:(NSInteger)imageID;



//////////////////////////////////////////////////////////////
// Private
//////////////////////////////////////////////////////////////

@property(retain) NSString* title;

-(void)buttonWasClicked:(IDVariantMap *)infoMap;

@end
