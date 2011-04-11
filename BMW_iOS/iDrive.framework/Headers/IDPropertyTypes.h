/*
 *  IDPropertyTypes.h
 *  iDrive
 *
 *  Created by Wolfram Manthey on 11.08.09.
 *  Copyright 2009 BMW Car IT GmbH. All rights reserved.
 *
 *  $Id: IDPropertyTypes.h 50948 2010-11-29 12:20:12Z q188463 $
 */



/*!
 @typedef IDPropertyType
*/
typedef enum IDPropertyTypes
{
    /*!
     @constant kPropertyEnabled
     This property sets the enabled state of a component. A disabled
     component can not be activated
     Parameters
          bool enabled: enabled state
     Applicable for: all components
    */
    kPropertyEnabled = 1,
    
    /*!
     @constant kPropertySelectable
     This property sets the selectable state of a component. A non selectable
     component can not be selected and so not be activated
     Parameters: 
          bool selectable: selectable state
     Applicable for: all components
    */
    kPropertySelectable = 2,
    
    /*!
     @constant kPropertyVisible
     This property sets the visible state of a component. Invisible 
     components do not appear to the user at all
     Parameters: 
          bool visible: visible state
     Applicable for: all components
    */
    kPropertyVisible = 3,
    
    /*!
     @constant kPropertyValid
     This property validates or invalidates a list. An invalidated list
     will try to get new data by a content provider applied to its listmodel.
     Parameters: 
          bool valid: valid state
     Applicable for: list
    */
    kPropertyValid = 4,
    
    /*!
     @constant kPropertyToolbarHmiStatePaging
     This property enables paging on an hmiState with a toolbar. The first and last
     button in the toolbar will be used for page up and down
     Parameters: 
          bool paging: paging enabled state
     Applicable for: toolbarHmiState
    */
    kPropertyToolbarHmiStatePaging = 5,
    
    /*!
     @constant kPropertyListColumnWidth
     This property set the widths for the table columns
     Parameters: 
          sring with a list of int-values: the widths for the columns, in xml separate with commas
     Applicable for: list
    */
    kPropertyListColumnWidth = 6,
    
    /*!
     @constant kPropertyListHasIdColumn
     This property enables an invisible id column of a list. The value of 
     the first column is interpretated as id and is delivered back by the list
     action instead of the column index. The column is not visible to the user.
     Parameters: 
          bool hasIdColumn: hasIdColumn state
     Applicable for: list
    */
    kPropertyListHasIdColumn = 7,
    
    /**
     * This property enables an animation of a button that indicates a 
     * loading process.
     * Parameters: 
     *      bool waitingAnimation: waitingAnimation state
     * Applicable for: label
     */
    kPropertyLabelWaitingAnimation = 8,
    
    /**
     * This property sets the width of a component.
     * Parameters: 
     *      int width: component width
     * Applicable for: image
     */
    kPropertyWidth = 9,
    
    /**
     * This property sets the height of a component.
     * Parameters: 
     *      int height: component height
     * Applicable for: image
     */
    kPropertyHeight = 10,
    
    /**
     * This property sets the video viewport for the terminalUI component.
     * Parameters: 
     *      int x: x position
     *      int y: y position
     *      int width: width of video viewport
     *      int height: height of video viewport
     * Applicable for: terminalUI
     */
    kPropertyTerminalUiVideoViewport = 11,
    
    /**
     * This property sets the screen viewport for the terminalUI component.
     * Parameters: 
     *      int x: x position
     *      int y: y position
     *      int width: width of screen viewport
     *      int height: height of screen viewport
     * Applicable for: terminalUI
     */
    kPropertyTerminalUiScreenViewport = 12,
    
    /**
     * This property sets the fullscreen mode of the terminalUI component.
     * Parameters: 
     *      bool fullscreen: fullscreen state
     * Applicable for: terminalUI
     */
    kPropertyTerminalUiFullScreen = 13,
    
    /**
     * This property requests or disables an audio connection for the terminalUI component.
     *      bool audiomode: request / disable audio
     * Applicable for: terminalUI
     */
    kPropertyTerminalUiAudioMode = 14,
    
    /**
     * This property requests or disables a video connection for the terminalUI component.
     *      bool audiomode: request / disable video
     * Applicable for: terminalUI
     */
    kPropertyTerminalUiVideoMode = 15,
    
    /**
     * This property forces the terminalUI component to close.
     * Applicable for: terminalUI
     */
    kPropertyTerminalUiLeave = 16,
    
    /**
     * This property sets the alignment of a component. 
     * Parameters
     *      int alignment:
     0: Left_Top
     1: Center_Top
     2: Right_Top
     3: Left_Center
     4: Center_Center
     5: Right_Center
     6: Left_Bottom
     7: Center_Bottom
     8: Right_Bottom
     * Applicable for: all components
     */
    kPropertyAlignment = 17,
    
    /**
     * This property sets the x offset of a component.
     * Parameters: 
     *      int height: component height
     * Applicable for: image
     */
    kPropertyOffsetX = 18,
    
    /**
     * This property sets the y offset of a component.
     * Parameters: 
     *      int height: component height
     * Applicable for: image
     */
    kPropertyOffsetY = 19,
    
    /**
     * This property sets the x position of a component.
     * Parameters: 
     *      int x: component x position
     * Applicable for: image
     */
    kPropertyPositionX = 20,
    
    /**
     * This property sets the y position of a component.
     * Parameters: 
     *      int y: component y position
     * Applicable for: image
     */
    kPropertyPositionY = 21,
    
    /**
     * This property sets the bookmarkable state of a component. If a
     * component is bookmarked, is can be activated by the bookmark
     * buttons in the car at any time if the application is available
     * Parameters
     *      bool bookmarkable: bookmarkable state
     * Applicable for: all components
     */
    kPropertyBookmarkable = 22,
    
    /**
     * This property sets the spekable state of a component. If a
     * component is spekable, is can be activated by the speech dialogue 
     * system.
     * Parameters
     *      int speakable: speakable state
     0: not speakable
     1: speakable locally when user is on screen of component
     2: speakable globally in any screen
     * Applicable for: all components
     */
    kPropertySpeakable = 23,
    
    /**
     * This property sets the table type of an hmistate.
     * Parameters
     *      int tabletype: 
     2: normal
     3: wide
     * Applicable for: all components
     */
    kPropertyHmiStateTableType = 24,
    
    /**
     * This property sets the cursor width.
     * Parameters
     *      int cursorwidth
     * Applicable for: all components
     */
    kPropertyCursorWidth = 25,
    
    /**
     * This property sets the table type of an hmistate.
     * Parameters
     *      Int32 layouttype: 
     0: eLayoutType_7Items  = 0
     1: eLayoutType_8Items  = 1
     4: eLayoutType_Paging  = 4
     Int32 begin: begin row to start for layoutmanager
     Int32 end: end row to start for layoutmanager
     * Applicable for: hmistates
     */
    kPropertyHmiStateTableLayout = 26,
    
    /**
     * This property sets the X Axis Min Value in a Chart.
     * Parameters
     *      UINT32 xminvalue
     * Applicable for: chart
     */
    kPropertyChartXAxisMinValue = 27,

    /**
     * This property sets the X Axis Max Value in a Chart.
     * Parameters
     *      UINT32 xmaxvalue
     * Applicable for: chart
     */
    kPropertyChartXAxisMaxValue = 28,

    /**
     * This property sets the X Axis Step in a Chart.
     * Parameters
     *      UINT32 xstep
     * Applicable for: chart
     */
    kPropertyChartXAxisStep = 29,

    /**
     * This property sets the Y Axis Max Value in a Chart.
     * Parameters
     *      UINT32 yminvalue
     * Applicable for: chart
     */
    kPropertyChartYAxisMinValue = 30,

    /**
     * This property sets the Y Axis Max Value in a Chart.
     * Parameters
     *      UINT32 ymaxvalue
     * Applicable for: chart
     */
    kPropertyChartYAxisMaxValue = 31,

    /**
     * This property sets the Y Axis Step in a Chart.
     * Parameters
     *      UINT32 xstep
     * Applicable for: chart
     */
    kPropertyChartYAxisStep = 32,

    /**
     * This property sets the X Axis Label in a Chart.
     * Parameters
     *      String xlabel
     * Applicable for: chart
     */
    kPropertyChartXAxisLabel = 33,

    /**
     * This property sets the X Axis Label in a Chart.
     * Parameters
     *      String ylabel
     * Applicable for: chart
     */
    kPropertyChartYAxisLabel = 34,

    /**
     * This property enables paging on an hmiState with a toolbar. The first and last
     * button in the toolbar will be used for page up and down
     * Parameters: 
     *      bool paging: paging enabled state
     * Applicable for: toolbarHmiState
     */
    kPropertyToolbarhmistatePagingLimited = 35,
    
    /**
     * This property enables a speedlock for components. If the vehicle is driving
     * faster than a defined value the component will no longer be usable /visible
     * Parameters: 
     *      bool speedlock: enable speedlock
     * Applicable for: all components
     */
    kPropertySpeedlock = 36,
    
    /**
     * This property sets the cutting style of a cell. 
     * Parameters
     *      uint32 cuttype:
     0: eCuttingStyle_CutDots,
     1: eCuttingStyle_NoCut,
     2: eCuttingStyle_CutWordsDots, // cut words at spaces and hyphens and add dots if it does not fit
     3: eCuttingStyle_CutBackwardsDots, // cut words as cut words dots but backwards
     4: eCuttingStyle_CutWordsAutoStaticText,
     5: eCuttingStyle_CutWordsAutoDynamicText
     * Applicable for: list
     */
    kPropertyCuttype = 37,
    
    /**
     * This property sets the tab stop offset. 
     * Parameters
     *      uint32 tobstopoffset
     * Applicable for: label, button
     */
    kPropertyTabstopoffset = 38,
    
    /**
     * This property sets the type of background. 
     * Parameters
     *      uint32 background
     * Applicable for: label, button, image
     */
    kPropertyBackground = 39,
    
    /**
     * These properties register/deregister input events for the TerminalUI widget
     * Applicable for: terminalUI
     */
    kPropertyTerminaluiRegisterInputevent = 40,
    kPropertyTerminaluiDeregisterInputevent = 41,
    
    /**
     * This property sets the max row count. 
     * Parameters
     *      int32 row count
     * Applicable for: list
     */
    kPropertyListRichtextMaxRowcount = 42,
    
    /**
     * This property sets replaces content of line[index] with "...". 
     * All lines after line[index] are removed
     * Parameters
     *      int32 row index
     * Applicable for: list
     */
    kPropertyListRichtextLastLineWithThreeDots = 43,
    
    /**
     * These properties set the respective video properties for the TerminalUI video widget
     * Applicable for: terminalUI
     */
    kPropertyTerminaluiSetContrast = 44,
    kPropertyTerminaluiSetBrightness = 45,
    kPropertyTerminaluiSetColor = 46,
    kPropertyTerminaluiSetTint = 47,
    kPropertyTerminaluiStatusbar = 48,
    kPropertyTerminaluiVideovisible = 49,
    kPropertyTerminaluiSetTuimode = 50,
    kPropertyGetValues = 51
} IDPropertyType;
