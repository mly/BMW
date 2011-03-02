/*
 *  IDConnection.h
 *  iDrive
 *
 *  Created by Wolfram Manthey on 03.12.09.
 *  Copyright 2009 BMW Car IT GmbH. All rights reserved.
 *
 *  $Id: IDConnection.h 51282 2010-12-06 13:56:07Z q265910 $
 */

#import <Foundation/Foundation.h>

#import "IDResourceIdentifier.h"
#import "IDPropertyTypes.h"
#import "IDLogger.h"
#import "IDAVService.h"

@class IDHmiService;
@class IDVariantMap;
@class IDVariantData;
@class IDTableData;
@class IDCarDataService;
@class IDDiag;
@class IDOTFLogService;
@class IDSecurityAuthService;
@class IDBlockOperation;
@class IDVersionInfo;

@protocol IDConnection <NSObject>

extern NSString* IDConnectionException;
extern NSString* IDSecurityException;

- (void)connectToHost:(NSString*)hostname error:(NSError**)error;
- (void)connectToHost:(NSString*)hostname port:(NSUInteger)port error:(NSError**)error;
- (void)disconnect;


/*!
 @abstract   Determines the version of the communication protocol.
 @discussion This method reads the version of the Remote HMI communication protocol.
 The version number is represented by the major, minor and revision number.
 @result     A dictionary containing the version info to be retrieved by the keys <i>major</i>, <i>minor</i> and <i>revision</i> each of which containing a NSNumber object.
 */
- (IDVersionInfo*)versionInfo;
- (NSDictionary*)systemInfo:(NSString*)component;

- (void)hmiServiceCreate:(IDHmiService*)application;
- (void)deregisterHmiService:(IDHmiService*)application;
- (void)registerCarDataServer:(IDCarDataService*)carDataServer;
- (void)deregisterCarDataServer:(IDCarDataService*)carDataServer;
- (void)registerLogger:(IDOTFLogService*)logger withName:(NSString*)name;
- (void)deregisterLogger:(IDOTFLogService*)logger;
- (void)registerAVService:(IDAVService*)avService;
- (void)deregisterAVService:(IDAVService*)avService;
- (void)registerDiag:(IDDiag*)diag;
- (void)deregisterDiag:(IDDiag*)diag;

// Logger
- (IDBlockOperation*)	loggerLogAsync: (IDOTFLogService*)logger message:(NSString*)message level:(IDLogLevel)level;

// Application

- (void)applicationInitialize:(IDHmiService*)hmiServices;
- (IDBlockOperation*)  applicationInitializeAsync:	    (IDHmiService*)hmiService;
- (IDBlockOperation*)  applicationSetResourceAsync:	    (IDHmiService*)hmiService type:(IDResourceType)type data:(NSData*)data checkBefore:(BOOL)check;
- (IDBlockOperation*)  applicationUpdateDataModelAsync: (IDHmiService*)hmiService modelId:(NSInteger)modelId variantData:(IDVariantData*)data;
- (IDBlockOperation*)  applicationUpdateListModelAsync: (IDHmiService*)hmiService modelId:(NSInteger)modelId tableData:(IDTableData*)data fromRow:(NSUInteger)fromRow rows:(NSUInteger)rows fromColumn:(NSUInteger)fromColumn columns:(NSUInteger)columns totalRows:(NSUInteger)totalRows totalColumns:(NSUInteger)totalColumns;
- (IDBlockOperation*)  applicationUpdatePropertyAsync:  (IDHmiService*)hmiService propertyId:(IDPropertyType)propertyId forComponent:(NSInteger)componentId variantMap:(IDVariantMap*)map;
- (IDBlockOperation*)  applicationTriggerHmiEventAsync: (IDHmiService*)hmiService eventId:(NSUInteger)eventId parameterMap:(IDVariantMap*)params;
- (NSDictionary*)      applicationGetCapabilities:      (IDHmiService*)hmiServices component:(NSString*)component;
- (IDBlockOperation*)  applicationGetCapabilitiesAsync: (IDHmiService*)hmiService component:(NSString*)component;

// Car Data Server
- (IDVersionInfo*)     carDataServerVersionInfo;
- (IDBlockOperation*)  carDataServerBindPropertyAsync:     (IDCarDataService*)carDataService propertyName:(NSString*)propertyName interval:(NSUInteger)interval;
- (IDBlockOperation*)  carDataServerUnbindPropertyAsync:   (IDCarDataService*)carDataService propertyName:(NSString*)propertyName;
- (IDBlockOperation*)  carDataServerAsyncGetPropertyAsync: (IDCarDataService*)carDataService propertyName:(NSString*)propertyName ident:(NSString*)ident;

// AV
- (IDBlockOperation*)  avRequestConnectionAsync:          (IDAVService*)avService connectionType:(AVConnectionType)connectionType;
- (IDBlockOperation*)  avConfirmPlayerStateChangedAsync:  (IDAVService*)avService playerState:(AVPlayerState)playerState connectionType:(AVConnectionType)connectionType;
- (IDBlockOperation*)  avCloseConnectionAsync:			  (IDAVService*)avService connectionType:(AVConnectionType)connectionType;

- (void)securityAuthService:(IDSecurityAuthService*)securityAuthService loginWithCertificate:(NSData*)certificate keyStore:(NSData*)pkcs12 passkey:(NSString*)pkcs12Passphrase;
//- (void)securityAuthService:(IDSecurityAuthService*)securityAuthService login:(NSString*)filePath;
- (void)securityAuthService:(IDSecurityAuthService*)securityAuthService updateCRL:(NSString*)filePath;

// Diag
- (void)	diagPerfStart:	(IDDiag*)diag mode:(int)mode param:(NSDictionary*)param;
- (void)	diagPerfOneway:	(IDDiag*)diag data:(NSData*)data;
- (void)	diagPerfTwoway:	(IDDiag*)diag data:(NSData*)data;
- (int)		diagPerfEnd:	(IDDiag*)diag;

@property (readonly, getter=isConnected) BOOL connected;
@property (nonatomic, copy) NSDictionary* infoDict;
@property(readonly, getter=rhmiVersionInfo) IDVersionInfo* rhmiVersionInfo;


@end

#pragma mark -

@interface IDConnection : NSObject

+ (NSUInteger)defaultPort;
+ (id<IDConnection>)defaultConnection;

@end

