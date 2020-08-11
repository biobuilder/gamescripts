# -*- coding: utf-8 -*-
"""
Created on Fri Jul 24 12:59:54 2020

# whacks enemies with your fist until they die
# also eats occasionally


@author: damon
"""

import mouse
import keyboard
import time


# constants
WHACKING_SLOT = 6 
EATING_SLOT = 7

NUMBER_OF_WHACKS = 200 # number of whacks before eating

# mouse clicks
MOUSE_EAT_BUTTON = 'right' # mouse button to push to eat
MOUSE_EAT_TIME = 5          # how long to eat
MOUSE_WHACK_BUTTON = 'left' # whacking button
MOUSE_WHACK_COOLDOWN = 1 # number of seconds to wait between successive whacks


# constants
WHACKING_CHAR = ';'
WHACKING_CODE = 39 # character = ';'
ESCAPE_CHAR = '\''
ESCAPE_CODE = 40 # character = '\''

START_STATE = 0
WHACKING_STATE = 1
EATING_STATE = 2
PAUSED_STATE = 3

# global variables
esc_triggered = False    # escape from the program flag
whacking_triggered = False # fishing sequence enabled or not
state = START_STATE # default program state
whack_count = 0 # number of whacks

# keyboard event handler
def handle_keyboard_event(e):
    global esc_triggered
    global whacking_triggered
    for code in keyboard._pressed_events:
        print('code = ' + str(code))
        if( code == ESCAPE_CODE ):
            esc_triggered = True
        if( code == WHACKING_CODE ):
            whacking_triggered = True

# create keyboard handle
keyboard.on_press( handle_keyboard_event )
print('waiting for key press to whack')

# enter main loop
while( esc_triggered == False ):
    if( state == START_STATE ):
        if( whacking_triggered == True ):
            print('whacking')
            keyboard.press_and_release( str( WHACKING_SLOT ) )
            whacking_triggered = False
            state = WHACKING_STATE
            
    elif( state == WHACKING_STATE ):
        if( whacking_triggered == True ):
            print('paused')
            whacking_triggered = False
            state = PAUSED_STATE
        else:
            mouse.click( button = MOUSE_WHACK_BUTTON )
            whack_count += 1
            if( whack_count >= NUMBER_OF_WHACKS ):
                whack_count = 0
                state = EATING_STATE
            else:
                time.sleep( MOUSE_WHACK_COOLDOWN )
            
    elif( state == PAUSED_STATE ):
        if( whacking_triggered == True ):
            keyboard.press_and_release( str( WHACKING_SLOT ) )
            print('whacking')
            whacking_triggered = False
            state = WHACKING_STATE
            
    elif( state == EATING_STATE ):
        #print( 'eating' )
        keyboard.press_and_release( str( EATING_SLOT ) )
        mouse.press( button = MOUSE_EAT_BUTTON )
        time.sleep( MOUSE_EAT_TIME )
        mouse.release( button = MOUSE_EAT_BUTTON )
        keyboard.press_and_release( str( WHACKING_SLOT ) )
        state = WHACKING_STATE
        #print( 'whacking after a good meal' )
        
exit()