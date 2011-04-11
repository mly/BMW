/*
 *  IDLogger.h
 *  iDrive
 *
 *  Created by Wolfram Manthey on 03.12.09.
 *  Copyright 2009 BMW Car IT GmbH. All rights reserved.
 *
 *  $Id: IDLogger.h 50948 2010-11-29 12:20:12Z q188463 $
 */

#import <Foundation/Foundation.h>

#define IDLOGEXCEPTION(e) \
IDLog(IDLogLevelError, @"%@ Exception in %s[%d]: %@", e.name, __FUNCTION__, __LINE__, e.reason);


typedef enum IDLogLevel
{
    IDLogLevelTrace,
    IDLogLevelDebug,
    IDLogLevelInfo,
    IDLogLevelWarn,
    IDLogLevelError,
    IDLogLevelAll = IDLogLevelTrace
} IDLogLevel;

#pragma mark -

void IDLogSetGlobalLogLevel(IDLogLevel newLevel);
void IDLog(IDLogLevel level, NSString* format, ...);
void IDLogWithCategory(IDLogLevel level, NSString* category, NSString* format, ...);

#pragma mark -

@interface NSString (IDLogger)
+ (NSString*)stringWithLogLevel:(IDLogLevel)level;
@end

#pragma mark -

@interface IDLogAppender : NSObject
{
    IDLogLevel   logLevel;
}

- (void)logMessage:(NSDictionary*)infoDict;
- (NSString*)formatMessage:(NSDictionary*)infoDict;

@property (assign) IDLogLevel logLevel;

@end

#pragma mark -

#define IDFLog(level, fmt, ...) \
IDLogWithCategory(level, @"iDrive", (@"%s [Line %d] " fmt), __FUNCTION__, __LINE__, ##__VA_ARGS__);
/*
#pragma mark -

@protocol IDConnection;

@interface IDLogger : NSObject
{
    id<IDConnection>  _connection;
    
    NSString*   _name;
    IDLogLevel  logLevel;
}

- (id)initWithConnection:(id<IDConnection>)connection name:(NSString*)name;
- (void)log:(IDLogLevel)level message:(NSString*)message;

@property (readonly) id<IDConnection> connection;
@property (readonly) NSString* name;
@property (assign) IDLogLevel logLevel;

@end
*/
