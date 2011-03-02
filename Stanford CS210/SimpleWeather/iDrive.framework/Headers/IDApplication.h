/*
 *  IDApplication.h
 *  iDrive
 *
 *  Created by Wolfram Manthey on 03.12.09.
 *  Copyright 2009 BMW Car IT GmbH. All rights reserved.
 *
 *  $Id: IDApplication.h 50948 2010-11-29 12:20:12Z q188463 $
 */

#import <Foundation/Foundation.h>

#import "IDEventHandler.h"
#import "IDResourceIdentifier.h"
#import "IDPropertyTypes.h"
#import "IDHmiService.h"
#import "IDSecurityAuthService.h"
#import "IDApplicationDelegate.h"
#import "IDViewController.h"

typedef enum {
	IDApplicationStateNil,
	IDApplicationStateInitialized,
	IDApplicationStateStarted,
	IDApplicationStateConnected,
} IDApplicationState;
extern NSString* IDApplicationDidFinishInitializationNotification;
extern NSString* IDSecurityAuthService_Denial;

@protocol IDConnection;
@class IDVariantMap;
@class IDVariantData;
@class IDTableData;
@class IDScheduler;
@class IDApplication;
@class IDAudioLine;


@protocol IDApplicationDelegate
	-(void)idApplicationDidConnect:(IDApplication*)appication;
	-(void)idApplication:(IDApplication*)appication connectionFailedWithError:(NSError*)error;
	-(void)idApplicationDidDisconnect:(IDApplication*)appication;
@end


/*!
 @class IDApplication
 @abstract This is the base class for any RHMI conforming remote application.
 */
@interface IDApplication : NSObject
{
    id<IDConnection>  _connection;
	NSString*      _identifier;
    NSDictionary*  _audioSettings;
    
	NSString* _hmiDescriptionName;
	NSString* _imageDatabaseAllName;
	NSString* _imageDatabaseBmwName;
	NSString* _imageDatabaseMiniName;
	NSString* _textDatabaseAllName;
	NSString* _textDatabaseBmwName;
	NSString* _textDatabaseMiniName;
	BOOL _devCertificates;
	
    NSData*  _hmiDescription;
    NSArray* _textDatabases;
    NSArray* _imageDatabases;
    
    IDSecurityAuthService* _authService;
    IDHmiService* _hmiService;
	IDAudioLine* _audioLine;
    IDApplicationState _applicationState;
	
	IDScheduler* _scheduler;
	NSThread* _clientThread;
	NSOperationQueue* _connectionQueue;
	id<IDApplicationDelegate> _delegate;
	NSMutableSet* _viewControllers;
}



////////////////////////////////////////////////////////////////////////////////////////
// Public
///////////


/**
 * Initializes the IDApplication.
 *
 * The hmiDescriptionName is required.
 * All other parameters are optional.
 *
 */
- (id)initWithHmiDescription:(NSString*)hmiDescriptionName
			imageDatabaseAll:(NSString*)imageDatabaseAllName
			imageDatabaseBMW:(NSString*)imageDatabaseBmwName
		   imageDatabaseMINI:(NSString*)imageDatabaseMiniName
			 textDatabaseAll:(NSString*)textDatabaseAllName
			 textDatabaseBMW:(NSString*)textDatabaseBmwName
			textDatabaseMINI:(NSString*)textDatabaseMiniName
			 devCertificates:(BOOL)devCertificates
					delegate:(id<IDApplicationDelegate>)delegate;


/**
 * Connect to car. 
 * Asynchronously calls IDApplicationDelegate back with result.
 *
 * Waiting for	-idApplicationDidConnect:
 * or			-idApplication: connectionFailedWithError:
 *
 */
- (void)connectWithHostname:(NSString*)hostname;


/**
 * Disconnects from car. 
 * Asynchronously calls IDApplicationDelegate back with result.
 *
 * Waiting for	-idApplicationDidDisconnect:
 * or			-idApplication: connectionFailedWithError:
 *
 */
- (void)disconnect;


/**
 * Adds a view controller to the Application.
 * Typically the Application owns one main view
 * controller, which owns the rest in a tree-like
 * structure.
 *
 */
- (void)addViewController:(IDViewController*)viewController;


/**
 * Removes a view controller from the Application.
 *
 */
- (void)removeViewController:(IDViewController*)viewController;



#pragma mark -
#pragma mark must be implemented

/*!
 @group meta information
 */

/*!
 @property name
 @abstract Name of the remote application.
 @discussion The name of the remote application will be shown in the list of applications inside the HMI.
 <p>This property must be implemented. Throws an exception if returns <code>nil</code>.</p>
 */
@property (readonly) NSString* name;

/*!
 @property vendor
 @abstract Vendor of the remote application.
 @discussion This property must be implemented. Throws an exception if returns <code>nil</code>.
 */
@property (readonly) NSString* vendor;

/*!
 @property version
 @abstract Version of the remote application.
 @discussion This property must be implemented. Throws an exception if returns <code>nil</code>.
 */
@property (readonly) NSString* version;

/*!
 @property passphrase
 @discussion This property must be implemented. Throws an exception if returns <code>nil</code>.
 *
 * When using a *blessed* iDrive.framework, subclass IDSecureApp instead and do not override -passphrase.
 *
 */
@property (readonly) NSString* passphrase;

#pragma mark -
#pragma mark can be overridden

/**
 *
 */
- (void)doInit;


/**
 *
 */
- (void)connectionDidComplete;


/**
 *
 */
- (void)beforeStartOfRhmi;


/**
 * Called after the Remote Application has successfully 
 * connected and started.
 *
 * Must call [super rhmiDidStart] at some point
 * if ovverriden.
 *
 */
- (void)rhmiDidStart;


/**
 *
 */
- (void)lastUserMode:(NSArray*)componentPath;


/**
 * Called when the Remote Application is disconnecting
 * (or was unplugged). Handle clean up here.
 *
 * Must call [super doDisconnect] at some point
 * if ovverriden.
 *
 */
- (void)doDisconnect;


/**
 *
 */
- (void)doShutdown;











////////////////////////////////////////////////////////////////////////////////////////
// Private
///////////

@property (retain) IDScheduler* scheduler;
@property (retain) NSThread* clientThread;
@property (retain) NSOperationQueue* connectionQueue;
@property (retain) IDSecurityAuthService* authService;
@property (retain) NSMutableSet* viewControllers;

@property (retain) NSString* hmiDescriptionName;
@property (retain) NSString* imageDatabaseAllName;
@property (retain) NSString* imageDatabaseBmwName;
@property (retain) NSString* imageDatabaseMiniName;
@property (retain) NSString* textDatabaseAllName;
@property (retain) NSString* textDatabaseBmwName;
@property (retain) NSString* textDatabaseMiniName;


#pragma mark -

#pragma mark -
#pragma mark application api

@property (retain) IDHmiService* hmiService;
@property (retain) IDAudioLine* audioLine;
- (NSString*)documentPath;

@property (retain) NSString* identifier;
@property (retain) id<IDConnection> connection;

/*!
 @group RHMI description
 */

/*!
 @property hmiDescription
 @abstract HMI description data.
 @discussion Returns the XML representation of the HMI description. The data returned by this property will most probably
 be read from the output xml file generated by the HMI Resource Editor.
 This property must not be <code>nil</code>.
 @seealso //apple_ref/occ/instp/IDApplication/imageDatabase imageDatabase
 @seealso //apple_ref/occ/instp/IDApplication/textDatabase textDatabase
 */
@property (retain) NSData* hmiDescription;

/*!
 @property textDatabase
 */
@property (retain) NSArray* textDatabases;

/*!
 @property imageDatabase
 */
@property (retain) NSArray* imageDatabases;
- (void)connectBlockingWithHostname:(NSString*)hostname;
- (void)disconnectBlocking;
@property (readonly) NSData* certificate;
@property (readonly) NSData* keystore;
@property (readonly) IDApplicationState applicationState;
@end
