//
//  IDTable.h
//  BMW
//
//  Created by Paul Doersch on 11/4/10.
//  Copyright 2010 BMW Technology Office Palo Alto. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "iDrive.h"
#import "IDWidget.h"
@class IDTableCell;
@class IDTableLocation;

@interface IDTable : IDWidget {
	NSInteger mActionID;
	id mTarget;
	SEL mSelector;
	
	NSInteger mTargetModelID;
	NSInteger mTargetHmiStateID;
	BOOL mTargetHmiStateID_dirty;
	
	NSString* mColumnWidths;
	BOOL mColumnWidths_dirty;
	
	int mRows;
	int mCols;
	NSMutableDictionary* mCells;
	BOOL mTable_dirty;
	BOOL mClearTable_dirty;
	NSTimer* mTimer;
	
	int mSelectedRow;
	BOOL mSelectedRow_dirty;
}



//////////////////////////////////////////////////////////////
// Public
//////////////////////////////////////////////////////////////

/**
 * UITable initializer.
 */
-(id)initWithViewController:(IDViewController*)viewController 
				   widgetID:(NSInteger)widgetID 
					modelID:(NSInteger)modelID 
				   actionID:(NSInteger)actionID
			  targetModelID:(NSInteger)targetModelID;



/**
 * Set the callback target and selector
 * for a table selection. This must be
 * called rhmiDidStart.
 * The selector must have the following 
 * signature -(void)yourMethod:(NSNumber*)index
 */
-(void)setTarget:(id)target selector:(SEL)selector;


/**
 * Set the target view. When an element from 
 * the tabel is selected, this view is 
 * presented automtically.
 */
-(void)setTargetView:(IDViewController*)viewController;


/**
 * Artificially place the highlighter
 * over a particular row.
 *
 * Doesn't work on some of the initail
 * A4A release builds. Fails silently.
 */
-(void)selectRow:(int)row;


/**
 * Clear the table.
 */
-(void)clear;


/**
 * Set the table's dimensions.
 *
 * If the dimentions are different truly
 * new, this implicitly calls -clear as
 * well.
 */
-(void)setRows:(int)rows columns:(int)columns;


/**
 * Set an individual cell.
 */
-(void)setCell:(IDTableCell*)cell row:(int)row column:(int)column;


/**
 * Set the columns widths.
 *
 * Format is an NSString,
 * each width seperated by
 * a comma.
 * e.g. @"50,370"
 * janky I know..
 */
-(void)setColumnWidths:(NSString*)widths;


//////////////////////////////////////////////////////////////
// Public
//////////////////////////////////////////////////////////////
-(void)rowWasSelected:(IDVariantMap *)infoMap;
@property(retain) NSString* columnWidths;
@property(retain) NSMutableDictionary* cells;
@property(retain) NSTimer* timer;
-(void)markTableDirty_setNeedsFlush;
-(void)sendEmptyTable;
-(void)setData:(IDVariantData*)data location:(IDTableLocation*)loc;
@end
