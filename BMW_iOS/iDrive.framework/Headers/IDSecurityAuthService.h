/*
 *  IDSecurityAuthService.h
 *  iDrive
 *
 *  Created by Vladimir Glavtchev Feb. 2, 2010
 *  Copyright 2009 BMW Car IT GmbH. All rights reserved.
 *
 *  $Id: IDSecurityAuthService.h 50948 2010-11-29 12:20:12Z q188463 $
 */

#import <Foundation/Foundation.h>
#import <CommonCrypto/CommonDigest.h>

#import "IDService.h"


@interface IDSecurityAuthService : IDService
{
    bool isLoggedIn;
}

// SAS will not support login without certificate - car data server does for now
- (void)loginWithCertificate:(NSData*)certificate keyStore:(NSData*)pkcs12 passkey:(NSString*)pkcs12Passphrase;
- (NSString*)getPermission:(NSString*)key;
- (void)updateCRL:(NSString*)filePath;
- (NSData*)encryptChallenge:(NSData*)challenge forPKCS12:(NSData*)pkcs12 andPassphrase:(NSString*)passphrase;

@end
