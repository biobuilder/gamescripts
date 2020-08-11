# -*- coding: utf-8 -*-
"""
Created on Wed Jul 15 21:40:31 2020

@author: Damon

Looks at the screen for a bobber
If the bobber is not found, the
script triggers the right mouse button
the button has a cooldown

"""

import mouse
import keyboard
import pyautogui
import time

from PIL import Image

# constants
FISHING_CHAR = ';'
FISHING_CODE = 39 # character = ';'
SCREENSHOT_CHAR = 'l'
SCREENSHOT_CODE = 38 # character = 'l'
ESCAPE_CHAR = '\''
ESCAPE_CODE = 40 # character = '\''

# program states
SCREENSHOT_STATE = 1
FISHING_STATE = 2
PAUSED_STATE = 3

# mouse clicks
MOUSE_BUTTON = 'right' # mouse button to push
MOUSE_COOLDOWN = 3 # number of seconds to wait between successive clicks
CHECK_COOLDOWN = 0 # number of seconds to wait between checking the screen

# red bobber color threshold
RED_THRESHOLD = (150, 100, 100)


# global variables
take_screenshot = False  # take a screenshot flag
esc_triggered = False    # escape from the program flag
fishing_triggered = False # fishing sequence enabled or not
state = SCREENSHOT_STATE # default program state

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
    myScreenshot.save(r'myScreenShot.png')

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
        else:
            time.sleep(CHECK_COOLDOWN)
            
    # main fishing state        
    if( state == FISHING_STATE ):
        if( fishing_triggered == True):
            fishing_triggered = False
            state = PAUSED_STATE
            print('Paused')
        else:
            # take a screenshot
            takeScreenshot()
            # try and find a valid red value
            img = Image.open('myScreenShot.png','r')
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
            print(bestPixel)
            # if so, click the right mouse button
            if( bestPixel[0] == 0 ):
                print('clicking mouse')
                mouse.click(button = MOUSE_BUTTON)
                time.sleep(MOUSE_COOLDOWN)
            else:
                print('bobber is still there')
                time.sleep(1)
        
    # paused state     
    if( state == PAUSED_STATE ):
        if( fishing_triggered == True ):
            fishing_triggered = False
            state = FISHING_STATE
            print('Fishing')
        else:
            time.sleep(1)
exit()
