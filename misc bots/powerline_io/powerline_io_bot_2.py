# -*- coding: utf-8 -*-
"""
Created on Mon Aug 17 18:44:41 2020

@author: IncrediGuy

Plays Powerline.io tron game
Bot version 1
"""

#import pyautogui
from mss import mss
from PIL import Image
import keyboard
import time
# constants

# camera focus
REGION_W = 112
REGION_H = 112
REGION_X = int(480 - REGION_W/2)
REGION_Y = int(576 - REGION_H/2)

# controls
LEFT = 'a'
RIGHT = 'd'
UP = 'w'
DOWN = 's'

ESCAPE_CODE = 40 # character = '\''
START_CODE = 39 # character = ';'
# bot states
STATE_PAUSED = 0
STATE_READY = 1
STATE_START = 2

TRUE = 1
FALSE = 0

# identification
PIXEL_WALL = [50, 50, 50]       # greater than this identifies walls
PIXEL_WALL_LUMINANCE = 130      # must be greater than this to identify a wall
PIXEL_ENEMY = [250, 250, 250]   # greater than this identifies enemies
PIXEL_ENEMY_LUMINANCE = 250     # greater than this identifies enemies

# how far to look forward before triggering key press
# minimum look distance
LOOK_DISTANCE = 20
LOOK_MAX_DISTANCE = 55

# variables
botState = STATE_START # bot state
speed = 1 # current speed 
direction = UP # current direction

esc_triggered = False # whether or not to exit the program
start_triggered = False # whether or not we can start 

# wall status keeps track of where the tracks can go next
# 0 = right, 1 = up, 2 = left, 3 = down
wallStatus = [0, 0, 0, 0] # keeps track of available options for moving
wallPix = [0, 0, 0, 0] # wall pixels on all sides
dirXMult = [1,0,-1,0] # x multiplication factors
dirYMult = [0,-1,0,1] # y multiplication factors 

def captureScreenshot():
    with mss() as sct:
        rect = {"left":REGION_X,"top":REGION_Y,"width":REGION_W,"height":REGION_H}
        #monitor = sct.monitors[1]
        sct_img = sct.grab(rect)
        return Image.frombytes('RGB',sct_img.size, sct_img.bgra, 'raw', 'BGRX')

def luminance(pixel):
    return (pixel[0] * 0.3) + (pixel[1] * 0.59) + (pixel[2] * 0.11)

def lookDistance(speed):
    return LOOK_DISTANCE

# decides which direction to turn based on the current direction
# and the currently detected walls
def decideDirection(curDir, wallDetection):
    newDir = curDir
    if(curDir == RIGHT):
        # only change states if walls are directly ahead
        if(wallDetection[0] == TRUE):
            # check either side to move to
            # check up
            # if no walls detected, go up
            if(wallDetection[1] == FALSE):
                newDir = UP;
            # otherwise go down 
            else:
                newDir = DOWN;
    elif(curDir == UP):
        if(wallDetection[1] == TRUE):
            # check left
            if(wallDetection[2] == FALSE):
                newDir = LEFT;
            else:
                newDir = RIGHT;
    elif(curDir == LEFT):
        if(wallDetection[2] == TRUE):
            # check down
            if(wallDetection[3] == FALSE):
                newDir = DOWN
            else:
                newDir = UP
    elif(curDir == DOWN):
        if(wallDetection[3] == TRUE):
            # check right
            if(wallDetection[0] == FALSE):
                newDir = RIGHT
            else:
                newDir = LEFT
    return newDir

# keyboard event handler
def handle_keyboard_event(e):
    global esc_triggered
    global start_triggered
    global botState
    for code in keyboard._pressed_events:
        #print('code = ' + str(code))
        if( code == ESCAPE_CODE ):
            esc_triggered = True
        if( code == START_CODE ):
            start_triggered = True
            if(botState == STATE_PAUSED):
                print('bot playing')
                botState = STATE_READY
                start_triggered = False
            elif( botState == STATE_READY ):
                print('bot paused')
                botState = STATE_PAUSED
                start_triggered = False
            elif( botState == STATE_START ):
                print('bot playing')
                botState = STATE_READY
                start_triggered = False


# create keyboard handle
keyboard.on_press( handle_keyboard_event )

        
print('bot starting, waiting for \';\'')

while(esc_triggered == False):
    if( botState == STATE_READY ):
        # enact the new direction
        #pyautogui.press(direction)
        keyboard.press_and_release(direction)
        #print(direction)
        
        # take screenshot
        img = captureScreenshot()
        #img = pyautogui.screenshot(region=(REGION_X,REGION_Y,REGION_W,REGION_H))
        #img.save(r"cap.png")
        
        # check for a wall in a straight line    
        # get the brightest pixel out there
        # get all the pixels down each row and average their luminance
        #print('luminance')
        for directs in range(0, 4, 1):
            wallPix[directs] = 0
            for pixL in range(LOOK_DISTANCE, LOOK_MAX_DISTANCE, 1):
                newLum = luminance(img.getpixel(( REGION_W/2 + pixL * dirXMult[directs], REGION_H/2 + pixL * dirYMult[directs] )));
                if( wallPix[directs] < newLum ):
                    wallPix[directs] = newLum
            #print(wallPix[directs])
        
        #print('walls')
        # check for the presence of walls by comparing pixel luminance
        for i in range(0, 4, 1):
            #print(luminance(wallPix[i]))
            # if the wall is present, it will have a luminance
            # greater than the threshold. Otherwise a wall is not present.
            if( wallPix[i] > PIXEL_WALL_LUMINANCE ):
                wallStatus[i] = TRUE
            else:
                wallStatus[i] = FALSE
            
            #print(wallStatus[i])
    
        # decide the new direction
        direction = decideDirection( direction, wallStatus )
        
    else:
        time.sleep(0.5)
        

exit()