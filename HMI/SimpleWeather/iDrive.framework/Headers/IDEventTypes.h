/*
 *  IDEventTypes.h
 *  iDrive
 *
 *  Created by Wolfram Manthey on 11.08.09.
 *  Copyright 2009 BMW Car IT GmbH. All rights reserved.
 *
 *  $Id: IDEventTypes.h 50948 2010-11-29 12:20:12Z q188463 $
 */



/*!
 @typedef IDPropertyType
 */
typedef enum IDEventTypes
{
    /*!
     * @constant kEventFocus
     * This event is fired when a component gets focussed or unfocussed.
     * Parameters: 
     *      bool focus
     */
    kEventFocus = 1,
    
    /*!
     * @constant kEventRequestData
     * This event is fired when an invalidated list request new data.
     * Parameters: 
     *      bool from: list index from which data is needed
     *      bool to: list index to which data is needed
     */
    kEventRequestData = 2,
    
    /*!
     * @constant kEventApplicationInit
     * This event is fired when the remote application was 
     * successfully integrated and can initialize its components.
     */
    kEventApplicationInit = 3,
    
    /*!
     * @constant kEventIntegrationError
     * This event is fired when something went wrong, e.g. when an invalid
     * description was sent.
     * Parameters: 
     *      uint32 errorcode
     *      string errorinfo
     */
    kEventIntegrationError = 4,
    
    /*!
     * @constant kEventAudioChannel
     * This event is fired when the audio channel status changes
     * Parameters: 
     *      uint32 channelstatus
     */
    kEventAudioChannel = 5,
    
    /*!
     * @constant kEventVideoChannel
     * This event is fired when the video channel status changes
     * Parameters: 
     *      uint32 channelstatus
     */
    kEventVideoChannel = 6,
    
    /*!
     * @constant kEventSplitscreen
     * This event is fired when splitscreen is enabled or disabled. This is done
     * only for the terminalUI component.
     * Parameters: 
     *      bool splitscreen: splitscreen state
     */
    kEventSplitscreen = 7,
    
    /*!
     * @constant kEventApplicationRelease
     * This event is fired when the remote application is released from
     * the HMI side (e.g. if it does not respond for a long time)
     */
    kEventApplicationRelease = 8,
    
    /*!
     * @constant kEventKeyCode
     * This event is not fired for all key events in the car but for very special 
     * global ones like the skip buttons on the steering wheel, when a multimedia 
     * connection was initiated by the remote application.
     * Parameters: 
     *      uint32 keyCode (see PropertyTypes.h)
     */
    kEventKeyCode = 9,
    
    /*!
     * @constant kEventInternetConnection
     * This event is fired when the status of the internet connection
     * of the headunit changes.
     * Parameters:
     *      uint32 internetconnectionstatus
     */
    kEventInternetConnection = 10,
    
    /*!
     * @constant kEventVisible
     * This event is fired when a component gets visible or invisible.
     * Parameters: 
     *      bool visible
     */
    kEventVisible = 11,
    
    /*!
     * @constant kEventRestoreHMI
     * This event is fired when this application was the last visible application and
     * shall restore its last hmi state.
     * Parameters: 
     *      int32 last state
     */
    kEventRestoreHMI = 12,
    
    /*!
     * @constant kEventRestoreAudio
     * This event is fired when this application was the last visible application and
     * shall restore its audio source.
     */
    kEventRestoreAudio = 13
} IDEventTypes;



/*!
 @typedef IDIntegrationErrorCodes
 */
typedef enum IDIntegrationErrorCodes
{
    /*!
     * @constant kErrorDescriptionInvalid
     */
    kErrorDescriptionInvalid = 1,
    
    /*!
     * @constant kErrorDataNotSet
     */
    kErrorDataNotSet = 2,
    
    /*!
     * @constant kErrorWrongVersion
     */
    kErrorWrongVersion = 3,
    
    /*!
     * @constant kErrorNotRegisteredBefore
     */
    kErrorNotRegisteredBefore = 4,
    
    /*!
     * @constant kErrorNotEnoughMemoryAvailable
     */
    kErrorNotEnoughMemoryAvailable = 5,
    
    /*!
     * @constant kErrorApplicationAlreadyLoaded
     */
    kErrorApplicationAlreadyLoaded = 6,
    
    /*!
     * @constant kErrorDescriptionSizeInvalid
     */
    kErrorDescriptionSizeInvalid = 7,
    
    /*!
     * @constant kErrorNoHMICommAdapter
     */
    kErrorNoHMICommAdapter = 8
} IDIntegrationErrorCodes;



/*!
 @typedef IDChannelStatus
 */
typedef enum IDChannelStatus
{
    /*!
     * @constant kChannelNotAvailable
     */
    kChannelNotAvailable,
    
    /*!
     * @constant kChannelAvailable
     */
    kChannelAvailable,
    
    /*!
     * @constant kChannelGranted
     */
    kChannelGranted,
    
    /*!
     * @constant kChannelRemoved
     */
    kChannelRemoved
} IDChannelStatus;



/*!
 @typedef IDSplitscreenStatus
 */
typedef enum IDSplitscreenStatus
{
    /*!
     * @constant kSplitscreenEnabled
     */
    kSplitscreenEnabled,
    
    /*!
     * @constant kSplitscreenDisabled
     */
    kSplitscreenDisabled
} IDSplitscreenStatus;

/*!
 @typedef IDInternetConnectionStatus
 */
typedef enum IDInternetConnectionStatus
{
    /*!
     * @constant kInternetNotAvailable
     */
    kInternetNotAvailable,
    
    /*!
     * @constant kInternetAvailable
     */
    kInternetAvailable,
    
    /*!
     * @constant kInternetConnecting
     */
    kInternetConnecting,
    
    /*!
     * @constant kInternetConnected
     */
    kInternetConnected,
    
    /*!
     * @constant kInternetDisconnected
     */
    kInternetDisconnected,
    
    /*!
     * @constant kInternetConnectionError
     */
    kInternetConnectionError
} IDInternetConnectionStatus;
