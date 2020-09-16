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
import random
# constants

# how far to look forward before triggering key press
# minimum look distance
LOOK_DISTANCE = 9;
LOOK_MAX_DISTANCE = [40,40,40,40,55,55,55,55]

# camera focus
REGION_W = int(max(LOOK_MAX_DISTANCE)*2)
REGION_H = int(max(LOOK_MAX_DISTANCE)*2)
REGION_X = int(480 - REGION_W/2)
REGION_Y = int(576 - REGION_H/2)

# keboard controls
LEFT = 'a'
RIGHT = 'd'
UP = 'w'
DOWN = 's'

# directions
EAST = 0
NORTH = 1
WEST = 2
SOUTH = 3
NORTHEAST = 4
NORTHWEST = 5
SOUTHWEST = 6
SOUTHEAST = 7
REVERSE = -1

# bot controller codes
ESCAPE_CODE = 40 # character = '\''
START_CODE = 39 # character = ';'

WALL_PRESENT = 1
NO_WALL_PRESENT = 0

# bot states
STATE_PAUSED = 0
STATE_READY = 1
STATE_START = 2

# identification
PIXEL_WALL = [50, 50, 50]       # greater than this identifies walls
PIXEL_WALL_LUMINANCE = 130      # must be greater than this to identify a wall
PIXEL_ENEMY = [250, 250, 250]   # greater than this identifies enemies
PIXEL_ENEMY_LUMINANCE = 250     # greater than this identifies enemies

# randomization
RAND_DIR_CHANCE = 10 # chance of changing direction
RAND_SCALE = 1000 # scale

REVERSE_SLEEP = 0.2 # 0.5 # sleep after reversal
BOT_SLEEP = 0.1 # cooldown for diagonal methods
FRAME_COOLDOWN = 0.0 # cooldown between frames

# variables
botState = STATE_START # bot state
speed = 1 # current speed 
direction = NORTH # current direction
prevDirection = direction # previous direction

# state control variables
esc_triggered = False # whether or not to exit the program
start_triggered = False # whether or not we can start 

# wall status keeps track of where the tracks can go next
# 0 = right, 1 = up, 2 = left, 3 = down
wallStatus = [0,0,0,0,0,0,0,0] # keeps track of available options for moving
wallPix = [0,0,0,0,0,0,0,0] # wall pixels on all sides
dirXMult = [1,0,-1,0,1,-1,-1,1] # x multiplication factors
dirYMult = [0,-1,0,1,-1,-1,1,1] # y multiplication factors 

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

# enacts direction control with keyboard
def enactDirection(curDir, prevDir):
    newDir = curDir
    if(curDir != REVERSE):
        
        if(curDir == EAST):
            if(curDir != prevDir):
                keyboard.press_and_release(RIGHT)
                time.sleep(BOT_SLEEP)
        elif(curDir == NORTH):
            if(curDir != prevDir):
                keyboard.press_and_release(UP)
                time.sleep(BOT_SLEEP)
        elif(curDir == WEST):
            if(curDir != prevDir):
                keyboard.press_and_release(LEFT)
                time.sleep(BOT_SLEEP)
        elif(curDir == SOUTH):
            if(curDir != prevDir):
                keyboard.press_and_release(DOWN)
                time.sleep(BOT_SLEEP)
        
        
        elif(curDir == NORTHEAST):
            keyboard.press_and_release(RIGHT)
            time.sleep(BOT_SLEEP/2)
            keyboard.press_and_release(UP)
            time.sleep(BOT_SLEEP/2)
        elif(curDir == NORTHWEST):
            keyboard.press_and_release(LEFT)
            time.sleep(BOT_SLEEP/2)
            keyboard.press_and_release(UP)
            time.sleep(BOT_SLEEP/2)
        elif(curDir == SOUTHWEST):
            keyboard.press_and_release(LEFT)
            time.sleep(BOT_SLEEP/2)
            keyboard.press_and_release(DOWN)
            time.sleep(BOT_SLEEP/2)
        elif(curDir == SOUTHEAST):
            keyboard.press_and_release(RIGHT)
            time.sleep(BOT_SLEEP/2)
            keyboard.press_and_release(DOWN)
            time.sleep(BOT_SLEEP/2)
        return curDir
    else:
        if(prevDir == EAST):
            keyboard.press_and_release(DOWN)
            time.sleep(BOT_SLEEP/2)
            keyboard.press_and_release(LEFT)
            time.sleep(BOT_SLEEP/2 + REVERSE_SLEEP)
            newDir = WEST
        elif(prevDir == NORTH):
            keyboard.press_and_release(RIGHT)
            time.sleep(BOT_SLEEP/2)
            keyboard.press_and_release(DOWN)
            time.sleep(BOT_SLEEP/2 + REVERSE_SLEEP)
            newDir = SOUTH
        elif(prevDir == WEST):
            keyboard.press_and_release(DOWN)
            time.sleep(BOT_SLEEP/2)
            keyboard.press_and_release(RIGHT)
            time.sleep(BOT_SLEEP/2 + REVERSE_SLEEP)
            newDir = EAST
        elif(prevDir == SOUTH):
            keyboard.press_and_release(RIGHT)
            time.sleep(BOT_SLEEP/2)
            keyboard.press_and_release(UP)
            time.sleep(BOT_SLEEP/2 + REVERSE_SLEEP)
            newDir = NORTH
        elif(prevDir == NORTHEAST):
            keyboard.press_and_release(LEFT)
            time.sleep(BOT_SLEEP/2 + REVERSE_SLEEP)
            keyboard.press_and_release(DOWN)
            time.sleep(BOT_SLEEP/2)
            newDir = SOUTHWEST
        elif(prevDir == NORTHWEST):
            keyboard.press_and_release(RIGHT)
            time.sleep(BOT_SLEEP/2 + REVERSE_SLEEP)
            keyboard.press_and_release(DOWN)
            time.sleep(BOT_SLEEP/2)
            newDir = SOUTHEAST
        elif(prevDir == SOUTHWEST):
            keyboard.press_and_release(RIGHT)
            time.sleep(BOT_SLEEP/2 + REVERSE_SLEEP)
            keyboard.press_and_release(UP)
            time.sleep(BOT_SLEEP/2)
            newDir = NORTHEAST
        elif(prevDir == SOUTHEAST):
            keyboard.press_and_release(LEFT)
            time.sleep(BOT_SLEEP/2 + REVERSE_SLEEP)
            keyboard.press_and_release(UP)
            time.sleep(BOT_SLEEP/2)
            newDir = NORTHWEST
        return newDir

def randomizeDirection( curDir, wallDetection ):
    
    chance = random.randint(0,RAND_SCALE)
    # if there is a wall ahead or we randomly decide to change direction,
    # attempt to change direction
    # make sure current direction is actually a valid index
    if(curDir >= 0):
        if( WALL_PRESENT == wallDetection[curDir] or chance < RAND_DIR_CHANCE ):
            if( wallDetection[curDir] == WALL_PRESENT):
                print("w")
            else:
                print("c")
                
            print(wallDetection)
            
            #return REVERSE
    
            # try to find an empty direction to go
            for i in range(1,20,1):
                r = random.randint(0,7)
                if(wallDetection[r] == NO_WALL_PRESENT and abs(int(wallDetection[r]) - int(r)) != 2):
                    return r
#            for i in range(1,20,1):
#                r = random.randint(4,7)
#                if(wallDetection[r] == NO_WALL_PRESENT and abs(int(wallDetection[r]) - int(r)) != 2):
#                    return r
            # if a good direction was not found, reverse direction as a last resort
            return REVERSE
        else:
            # continue going in the current direction
            return curDir
    else:
        #time.sleep(FRAME_COOLDOWN)
        return curDir

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
        #direction = enactDirection(direction)
        #if(prevDirection == direction):
            # chance to randomize the direction
            # if( random.randint(1,RAND_SCALE) < RAND_DIR_CHANCE ):
            #    direction = randomizeDirection(wallStatus)
            #    keyboard.press_and_release(direction)
            #    prevDirection = direction
            
            
        #print(direction)
        
        # take screenshot
        img = captureScreenshot()
        #img = pyautogui.screenshot(region=(REGION_X,REGION_Y,REGION_W,REGION_H))
        #img.save(r"cap.png")
        
        # check for a wall in a straight line    
        # get the brightest pixel out there
        # get all the pixels down each row and average their luminance
        #print('luminance')
        for directs in range(0, 8, 1):
            wallPix[directs] = 0
            # change length of the looker depending on which direction we are looking
            for pixL in range(LOOK_DISTANCE, LOOK_MAX_DISTANCE[directs], 1):
                newLum = luminance(img.getpixel(( REGION_W/2 + pixL * dirXMult[directs], REGION_H/2 + pixL * dirYMult[directs] )));
                if( wallPix[directs] < newLum ):
                    wallPix[directs] = newLum
            #print(wallPix[directs])
        
        #print('walls')
        # check for the presence of walls by comparing pixel luminance
        for i in range(0, 8, 1):
            #print(luminance(wallPix[i]))
            # if the wall is present, it will have a luminance
            # greater than the threshold. Otherwise a wall is not present.
            if( wallPix[i] > PIXEL_WALL_LUMINANCE and wallPix[i] < PIXEL_ENEMY_LUMINANCE ):
                wallStatus[i] = WALL_PRESENT
            else:
                wallStatus[i] = NO_WALL_PRESENT
        
        #print(wallStatus[i])
    
        # decide the new direction
        #direction = decideDirection( direction, wallStatus )
        direction = randomizeDirection(direction, wallStatus)
        
        if( direction != prevDirection ):
            # enact the new direction
            print('dir = ' + str(direction))
        
        direction = enactDirection(direction, prevDirection)
        prevDirection = direction
        
        #print(wallStatus)
        #time.sleep(FRAME_COOLDOWN)
        
    else:
        time.sleep(0.5)
        

exit()