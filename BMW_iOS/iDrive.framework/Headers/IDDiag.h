/*
 *  IDDiag.h
 *  iDrive
 *
 *  Created by Andreas Hildisch on 3/16/10.
 *  Copyright 2010 BMW Car IT GmbH. All rights reserved.
 *
 *  $Id: IDDiag.h 50948 2010-11-29 12:20:12Z q188463 $
 */

#import <Foundation/Foundation.h>

#import "IDEventHandler.h"

@protocol IDConnection;

@interface IDDiag : NSObject <IDEventHandler> {
    id<IDConnection> _connection;
	
}

- (id)initWithConnection:(id<IDConnection>)connection;

@end
