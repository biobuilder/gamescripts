# -*- coding: utf-8 -*-
"""
Created on Wed Jul 15 21:40:31 2020

@author: Damon

Looks at the screen for a bobber
If the bobber is not found, the
script triggers the right mouse button
the button has a cooldown
The script switches poles after a certain number
of uses

"""

import mouse
import keyboard
import pyautogui
import time

from PIL import Image

# constants
FISHING_CHAR = ';'
FISHING_CODE = 39 # character = ';'
SCREENSHOT_CHAR = ']'
SCREENSHOT_CODE = 27 # character = ']'
ESCAPE_CHAR = '\''
ESCAPE_CODE = 40 # character = '\''

POLE_SLOT_START = 6 # starting fishing pole slot (must be greater than 1 and less than 9)
POLE_SLOT_END = 6 # ending fishing pole slot (must be greater than 1 and less than 9)
POLE_MAX_USES = 10000  # how many uses (casts) a pole has before it switches

# program states
SCREENSHOT_STATE = 1
FISHING_STATE = 2
PAUSED_STATE = 3

# mouse clicks
MOUSE_BUTTON = 'right' # mouse button to push
MOUSE_COOLDOWN = 3 # number of seconds to wait between successive clicks
CHECK_COOLDOWN = 0.5 # number of seconds to wait between checking the screen

# red bobber color threshold
RED_THRESHOLD = (130, 100, 100)


# global variables
take_screenshot = False  # take a screenshot flag
esc_triggered = False    # escape from the program flag
fishing_triggered = False # fishing sequence enabled or not
state = SCREENSHOT_STATE # default program state

pole_slot = POLE_SLOT_START # currently selected fishing pole
pole_uses = 0   # keeps track of how many times the selected pole has been used

# keyboard event handler
def handle_keyboard_event(e):
    global esc_triggered
    global take_screenshot
    global fishing_triggered
    for code in keyboard._pressed_events:
        print('code = ' + str(code))
        if( code == ESCAPE_CODE ):
            esc_triggered = True
        if( code == SCREENSHOT_CODE ):
            take_screenshot = True
        if( code == FISHING_CODE ):
            fishing_triggered = True

# take a screenshot of the minecraft screen
def takeScreenshot():
    myScreenshot = pyautogui.screenshot(region=(375,600,200,200))
    myScreenshot.save(r'focus.png')

# create keyboard handle
keyboard.on_press( handle_keyboard_event )

print('Minecraft Fishing System')

# wait for the initiation keyboard key
print('Waiting for key press')
print('Start fishing = ' + FISHING_CHAR)
print('Pause fishing = ' + FISHING_CHAR )
print('Take screenshot = ' + SCREENSHOT_CHAR)
print('Exit = ' + ESCAPE_CHAR)

# take the first screenshot
takeScreenshot()

# search for a pixel that is redder than the
# Red threshold

# enter main loop
while( esc_triggered == False ):
    
    # taking screenshots state
    if( state == SCREENSHOT_STATE ):
        if( take_screenshot == True ):
            takeScreenshot()
            take_screenshot = False # reset flag
            print('Took screenshot')
        elif( fishing_triggered == True ):
            fishing_triggered = False
            state = FISHING_STATE
            print('Fishing')
            # select pole slot using the keyboard
            keyboard.press_and_release(str(pole_slot))
        else:
            time.sleep(CHECK_COOLDOWN)
            
    # main fishing state        
    if( state == FISHING_STATE ):        

        # check to see if the pause button was hit        
        if( fishing_triggered == True):
            fishing_triggered = False
            state = PAUSED_STATE
            print('Paused')
        else:
            # take a screenshot
            takeScreenshot()
            # try and find a valid red value
            img = Image.open('focus.png','r')
            pix_val = list(img.getdata())
            bestPixel = [0,0,0]
            for pixels in pix_val:
                # check for a valid red pixel
                if( (pixels[0] > RED_THRESHOLD[0]) and (pixels[1] < RED_THRESHOLD[1]) and (pixels[2] < RED_THRESHOLD[2])):
                    # store the best one
                    testPixel = pixels
                    if(testPixel[0] > bestPixel[0]):
                        bestPixel = testPixel
            # check to see if we didn't find a valid red pixel
            #print(bestPixel)
            # if so, click the right mouse button
            if( bestPixel[0] == 0 ):
                print('bobber missing - clicked mouse')
                mouse.click(button = MOUSE_BUTTON)                
                time.sleep(MOUSE_COOLDOWN)
                # increment pole use count
                pole_uses += 1
                print('pole use count = ' + str(pole_uses))
                # if the use count reaches the maximum, select the next fishing slot 
                if(pole_uses >= POLE_MAX_USES):
                    # reset the uses variable
                    pole_uses = 0
                    # increment the pole slot
                    pole_slot += 1
                    if(pole_slot > POLE_SLOT_END):
                        pole_slot = POLE_SLOT_END # terminate the sequence
                        pole_slot = POLE_SLOT_START # wrap the pole slot counter
                        state = PAUSED_STATE
                    # select pole slot using the keyboard
                    keyboard.press_and_release(str(pole_slot))
                    print('Selecting pole slot ' + str(pole_slot))
            else:
                # a bobber was detected, so we need to sleep
                #'print('bobber detected')
                time.sleep(CHECK_COOLDOWN)
        
    # paused state     
    if( state == PAUSED_STATE ):
        if( fishing_triggered == True ):
            fishing_triggered = False
            state = FISHING_STATE
            print('Fishing')
        else:
            time.sleep(1)
exit()
