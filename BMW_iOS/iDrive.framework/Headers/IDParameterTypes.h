/*
 *  IDParameterTypes.h
 *  iDrive
 *
 *  Created by Wolfram Manthey on 28.09.09.
 *  Copyright 2009 BMW Car IT GmbH. All rights reserved.
 *
 *  $Id: IDParameterTypes.h 50948 2010-11-29 12:20:12Z q188463 $
 */

/*!
 @typedef IDPropertyType
 */
typedef enum IDParameterTypes
{
    kParamInvalid = 255,
    kEventParamValue = 0,
    kActionParamListIndex = 1,
    kActionParamSelectedValue = 2,
    kActionParamChecked = 3,
    kEventParamFocus = 4,
    kEventParamRequestdataFrom = 5,
    kEventParamRequestdataSize = 6,
    kEventParamSplitscreen = 7,
    kActionParamSpellerInput = 8,
    kActionParamKeycode = 20,
    kEventParamKeycode = 20,
    kEventParamChannelStatus = 21,
    kEventParamConnectionStatus = 22,
    kEventParamVisible = 23,
    kActionLocationInput = 40,
    kEventParamListIndex = 41,
    kActionParamSelectionText = 42,
    kActionParamInvokedBy = 43
} IDParameterTypes;
