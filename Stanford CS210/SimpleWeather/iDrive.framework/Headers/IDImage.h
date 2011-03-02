//
//  IDImage.h
//  BMW
//
//  Created by Paul Doersch on 10/28/10.
//  Copyright 2010 BMW Technology Office Palo Alto. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "IDWidget.h"

@interface IDImage : IDWidget {
	UIImage* mImage;
	BOOL mImage_dirty;
	
	NSInteger mImageID;
	BOOL mImageID_dirty;
	
	CGPoint mPosition;
	BOOL mPosition_dirty;
}


//////////////////////////////////////////////////////////////
// Public
//////////////////////////////////////////////////////////////


/**
 * Set the image.
 */
-(void)setImage:(UIImage*)image;


/**
 * Set the image.
 */
-(void)setImageID:(NSInteger)imageID;


/**
 * Set the Image's position.
 * 
 * Must call rhmiDidStart.
 */
-(void)setPosition:(CGPoint)position;


//////////////////////////////////////////////////////////////
// Private
//////////////////////////////////////////////////////////////

@property(retain) UIImage* image;

@end
