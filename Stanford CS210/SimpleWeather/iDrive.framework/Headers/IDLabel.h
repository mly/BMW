//
//  IDLabel.h
//  BMW
//
//  Created by Paul Doersch on 10/28/10.
//  Copyright 2010 BMW Technology Office Palo Alto. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "IDWidget.h"
#import "IDVariantMap.h"
#import "IDVariantData.h"

typedef enum IDAlignment {
	IDAlignmentLeft,
	IDAlignmentCenter,
	IDAlignmentRight
} IDAlignment;

@interface IDLabel : IDWidget {
	IDAlignment mAlignment;
	BOOL mAlignment_dirty;
	CGPoint mPosition;
	BOOL mPosition_dirty;
	NSString* mText;
	BOOL mText_dirty;
}

//////////////////////////////////////////////////////////////
// Public
//////////////////////////////////////////////////////////////

/**
 * Set the text.
 */
-(void)setText:(NSString*)text;


/**
 * Set the alignment of the text.
 */
-(void)setAlignment:(IDAlignment)alignment;


/**
 * Set the location of the label.
 *   Left alignment case:
 *     defines top left corner
 *   Center alignment case:
 *     defines top center
 *   Right alignment case:
 *     defines top right corner
 */
-(void)setPosition:(CGPoint)point;


//////////////////////////////////////////////////////////////
// Private
//////////////////////////////////////////////////////////////

@property(retain) NSString* text;


@end
