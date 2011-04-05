/*
 *  IDRemoteHmiService.h
 *  iDrive
 *
 *  Created by Wolfram Manthey on 06.04.10.
 *  Copyright 2010 BMW Car IT GmbH. All rights reserved.
 *
 *  $Id: IDHmiService.h 50948 2010-11-29 12:20:12Z q188463 $
 */

#import <Foundation/Foundation.h>

#import "IDService.h"
#import "IDPropertyTypes.h"
#import "IDResourceIdentifier.h"
#import "IDEventHandler.h"


@class IDVariantData;
@class IDVariantMap;
@class IDTableData;

@interface IDHmiService : IDService <IDEventHandler>
{
@private        
    
    NSMutableSet*  _hmiEventObservers;
    NSMutableSet*  _actionEventObservers;
        
    IDVariantMap* _yesMap;
    IDVariantMap* _noMap;
}

- (void)startWithError:(NSError**)error;

// Special for HMI LUM (the regular removeHandler works for this as well.
- (void)addHandlerForHmiEvent:(NSUInteger)eventId component:(NSUInteger)componentId target:(id)target selector:(SEL)selector queue:(NSOperationQueue*)queue;

- (void)addHandlerForHmiEvent:(NSUInteger)eventId component:(NSUInteger)componentId target:(id)target selector:(SEL)selector;
- (void)addHandlerForActionEvent:(NSUInteger)actionId target:(id)target selector:(SEL)selector;
- (void)removeHandlerForHmiEvent:(NSUInteger)eventId component:(NSUInteger)componentId target:(id)target selector:(SEL)selector;
- (void)removeHandlerForActionEvent:(NSUInteger)actionId target:(id)target selector:(SEL)selector;

- (void)setDataModel:(NSInteger)modelId variantData:(IDVariantData*)data;
- (void)setListModel:(NSInteger)modelId tableData:(IDTableData*)data;
- (void)setListModel:(NSInteger)modelId tableData:(IDTableData*)data fromRow:(NSUInteger)fromRow rows:(NSUInteger)rows fromColumn:(NSUInteger)fromColumn columns:(NSUInteger)columns;
- (void)setListModel:(NSInteger)modelId tableData:(IDTableData*)data fromRow:(NSUInteger)fromRow rows:(NSUInteger)rows fromColumn:(NSUInteger)fromColumn columns:(NSUInteger)columns totalRows:(NSUInteger)totalRows totalColumns:(NSUInteger)totalColumns;
- (void)setProperty:(IDPropertyType)propertyId forComponent:(NSInteger)componentId variantMap:(IDVariantMap*)map;
//- (void)setResource:(IDResourceType)type data:(NSData*)data checkBefore:(BOOL)check;
- (NSDictionary*)capabilities:(NSString*)component;
- (void)setComponent:(NSInteger)modelId visible:(BOOL)visible;

- (void)triggerHmiEvent:(NSUInteger)eventId;
- (void)triggerHmiEvent:(NSUInteger)eventId parameterMap:(IDVariantMap*)params;

//@property (retain) NSData* hmiDescription;
//@property (retain) NSArray* textDatabases;
//@property (retain) NSArray* imageDatabases;

@end
