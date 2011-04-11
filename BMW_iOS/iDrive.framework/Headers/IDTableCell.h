//
//  IDTableCell.h
//  BMW
//
//  Created by Paul Doersch on 11/4/10.
//  Copyright 2010 BMW Technology Office Palo Alto. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "iDrive.h"

typedef enum IDTableCellType {
	IDTableCellTypeString,
	IDTableCellTypeImage,
	IDTableCellTypeImageID,
	IDTableCellTypePreInstalledImageID
} IDTableCellType;


@interface IDTableCell : NSObject {
	IDTableCellType mType;
	IDVariantData* mData;
	BOOL mDirty;
	
	// Image Case
	UIImage* mImage;
	CGSize mSize;
	NSInteger mPlaceholderImageID;
	BOOL mPlaceholderImageID_dirty;
	BOOL mWithFrame;
}

//////////////////////////////////////////////////////////////
// Public
//////////////////////////////////////////////////////////////

/**
 * Create a table cell with a string.
 */
+(IDTableCell*)tableCellWithString:(NSString*)string;


/**
 * Create a table cell with an image.
 */
+(IDTableCell*)tableCellWithImage:(UIImage*)image size:(CGSize)size withFrame:(BOOL)frame;

/**
 * Creat a table cell with an image and allow for a fast 
 * image placeholder before loading the actual data.
 */
+(IDTableCell*)tableCellWithImage:(UIImage*)image size:(CGSize)size withFrame:(BOOL)frame placeholderImageID:(NSInteger)imageID;


/**
 * Create a table cell with an image id.
 */
+(IDTableCell*)tableCellWithImageID:(NSInteger)imageID;


/**
 * Create a table cell with an image id.
 */
+(IDTableCell*)tableCellWithPreInstalledImageID:(NSInteger)imageID;

//////////////////////////////////////////////////////////////
// Private
//////////////////////////////////////////////////////////////
@property(retain) IDVariantData* data;
@property(retain) UIImage* image;
@property BOOL dirty;
@property CGSize size;
@property NSInteger placeholderImageID;
@property BOOL placeholderImageID_dirty;
@property BOOL withFrame;
@property IDTableCellType type;
@end
