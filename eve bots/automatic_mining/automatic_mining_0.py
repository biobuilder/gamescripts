# -*- coding: utf-8 -*-
"""
Created on Wed Sep  2 15:42:45 2020

Tries to automatically mine for me
Better only use this in high-security space


Steps:
    1. Undock
    2. Jump to target system
     - Series of steps to jump
    3. Warp to nearest asteroid belt
    4. Mine Minerals
     - Approach nearest asteroid
     - Wait until they are reached
     - Lock nearest asteroid
     - Wait 5 seconds
     - Begin mining with all lasers
     - Continue mining until the asteroid icon is gone OR
       the inventory bar is full
       - wait 30 seconds if asteroid icon is gone
     - Repeat steps until the inventory bar is full
    5. Jump back to home system
    6. Dock at target base
    7. Transfer item inventory to station
     - Open inventory
     - Grab item and drop into station inventory
     - Check to see if an item is still present in the inventory
     - If an item is still present, repeat
    8. If the client has disconnected, attempt reconnecting after waiting

@author: biobuilder
"""
import pyautogui
import time
import random
#from PIL import Image

# constants
PASS = True
FAIL = False

PAUSE_AMOUNT = 0.5 # how long to wait before making another move
MOUSE_DRAG_DURATION = 0.25 # how long to move the mouse
MOUSE_PRESS_DURATION = 0.25 # how long to press the mouse button

APPROACH_KEY = 'q'
WARP_KEY = 's'
DOCKJUMP_KEY = 'd'
LOCK_KEY = 'ctrl'

# image finding confidence
CONFIDENCE = 0.9

# sequences
stargate_key_location = 'image_keys/stargates/'
destination_stargate_sequence = [#'abudban_key.png'
                                 #'ivar_key.png',
                                 #'trytedald_key.png'
                                 'ameinaka_key.png'
                                 ]

jump_home_stargate_sequence = [#'ivar_key.png',
                               #'ameinaka_key.png',
                               'malukker_key.png'
                               #'rens_key.png'
                               ]

asteroid_key_location = 'image_keys/asteroids/'
target_asteroid_types = [#'veldspar.png',
                         #'omber.png',
                         #'plagioclase.png',
                         'scordite.png']


home_station_location = 'image_keys/home_stations/'
home_station_key = 'malukker_i_republic_university_key.png'


restart_filepath = 'image_keys/game_restart/'


# utility functions
def click_on_icon(img_filepath):
    val = pyautogui.locateCenterOnScreen(img_filepath,confidence=CONFIDENCE)
    if(val != None):
        pyautogui.moveTo(val.x,val.y)
        time.sleep(1)
        pyautogui.click(val.x,val.y)
        time.sleep(1)
        move_mouse_to_safe_spot()
        return PASS
    else:
        return FAIL

def is_icon_present(img_filepath):
    val = pyautogui.locateCenterOnScreen(img_filepath,confidence=CONFIDENCE)
    if( val == None ):
        return False
    else:
        return True


# undocks the ship from the hangar
def undock():
    print('undocking')
    check = click_on_icon('image_keys/undock_key.png')
    #unx = 905
    #uny = 219
    #pyautogui.moveTo(unx,uny)
    #pyautogui.click(unx,uny)
    #move_mouse_to_safe_spot()
    time.sleep(15)
    return check

def jump_to_target_star_system():
    print('jumping to target star system')
    # select the general tab
    click_general_tab()
    
    # find the correct dock gate on the screen
    for keys in destination_stargate_sequence:
        val = pyautogui.locateCenterOnScreen(stargate_key_location + keys, confidence=CONFIDENCE)
        if(val == None):
            return FAIL
        # jump to target gate
        pyautogui.keyDown(DOCKJUMP_KEY)
        pyautogui.moveTo(val.x,val.y)
        pyautogui.click(val.x,val.y)
        pyautogui.keyUp(DOCKJUMP_KEY)
        move_mouse_to_safe_spot()
        print('->'+keys)
        time.sleep(60)
    
    return PASS

def jump_to_home_star_system():
    print('jumping to home star system')
    # select the general tab
    check = click_general_tab()
    # find the correct dock gate on the screen
    for keys in jump_home_stargate_sequence:
        val = pyautogui.locateCenterOnScreen(stargate_key_location + keys, confidence=CONFIDENCE)
        if(val != None):
            # jump to target gate
            pyautogui.keyDown(DOCKJUMP_KEY)
            pyautogui.moveTo(val.x,val.y)
            pyautogui.click(val.x,val.y)
            pyautogui.keyUp(DOCKJUMP_KEY)
            move_mouse_to_safe_spot()
            print('->'+keys)
            time.sleep(60)
            check = PASS
        else:
            check = FAIL
    return check

# docks to the home system
def dock_to_home_station():
    print('docking to home station')
    # select the general tab
    click_general_tab()
    # find the correct dock gate on the screen
    val = pyautogui.locateCenterOnScreen(home_station_location+home_station_key,confidence=CONFIDENCE)
    if(val == None):
        return FAIL
    # jump to target gate
    pyautogui.keyDown(DOCKJUMP_KEY)
    pyautogui.moveTo(val.x,val.y)
    pyautogui.click(val.x,val.y)
    pyautogui.keyUp(DOCKJUMP_KEY)
    move_mouse_to_safe_spot()
    time.sleep(60)
    return PASS

def warp_to_asteroids_old():
    print('warping to asteroid field')
    # click the mining tab
    click_mining_tab()
    
    # find the target asteroid group in the list
    val = pyautogui.locateCenterOnScreen('image_keys/target_asteroid_cluster_key.png', confidence=CONFIDENCE)
    if(val == None):
        return FAIL
    # warp to the asteroid group
    pyautogui.keyDown(WARP_KEY)
    time.sleep(1)
    pyautogui.moveTo(val.x,val.y)
    pyautogui.click(val.x,val.y)
    time.sleep(1)
    pyautogui.keyUp(WARP_KEY)
    move_mouse_to_safe_spot()
    # wait to reach the asteroids
    time.sleep(40)
    
    return PASS

# warps to a random asteroid field
def warp_to_asteroids():
    print('warping to asteroid field')
    # click the mining tab
    click_mining_tab()
    
    # find the target asteroid group in the list
    val = pyautogui.locateAllOnScreen('image_keys/target_asteroid_cluster_key.png', confidence=CONFIDENCE)
    if(val == None):
        return FAIL
    # warp to a random asteroid group
    valList = []
    for val in pyautogui.locateAllOnScreen('image_keys/target_asteroid_cluster_key.png', confidence=CONFIDENCE):
        valList.append(val)
    
    if(len(valList) > 0):
        ind = random.randint(0,len(valList)-1)
        coords = valList[ind]
        x = coords.left+coords.width/2
        y = coords.top+coords.height/2
    else:
       return FAIL
   
    pyautogui.keyDown(WARP_KEY)
    time.sleep(1)
    pyautogui.moveTo(x,y)
    pyautogui.click(x,y)
    time.sleep(1)
    pyautogui.keyUp(WARP_KEY)
    move_mouse_to_safe_spot()
    # wait to reach the asteroids
    time.sleep(40)
    
    return PASS



# clicks the general navigation tab
def click_general_tab():
    # select the general tab
    click_on_icon('image_keys/general_tab_key.png')
    #pyautogui.moveTo(533,200)
    #pyautogui.click(533,200)
    return PASS

# clicks the mining navigation tab
def click_mining_tab():
    # click the mining tab
    click_on_icon('image_keys/mining_tab_key.png')
    #pyautogui.moveTo(580,201)
    #pyautogui.click(580,201)
    return PASS

# moves the mouse off of the screen to keep from opening dialogue boxes
def move_mouse_to_safe_spot():
    pyautogui.moveTo(80,10)
    return PASS

# tries to keep the computer screen from going to sleep
def keepalive():
    pyautogui.moveTo(100,100)
    pyautogui.moveTo(10,10)
    pyautogui.keyDown('a')
    time.sleep(1)
    pyautogui.keyUp('a')
    return PASS

# moves the camera to try and get a better look at the items
def move_camera():
    pyautogui.moveTo(100,685)
    pyautogui.dragTo(200,685,duration=0.25)
    return PASS

# switches the filter icon 
def switch_filter_icon():
    pyautogui.moveTo(520,230)
    pyautogui.click(520,230)
    return PASS

def lock_target():
    print('find and lock on an asteroid')
    # select mining tab
    click_mining_tab()
    
    # switch filter mode to Valuable Asteroids first
    #switch_filter_icon()

    print('approaching target asteroid')    
    # find the best available asteroid in the list and lock onto it
    # select progressively poorer and poorer asteroids until a lock is found
    # if the target asteroids cannot be found give up
    val = None
    for keys in target_asteroid_types:
        val = pyautogui.locateCenterOnScreen(asteroid_key_location+keys)
        if(val != None):
            break
    # lock onto the asteroid (but only if a valid lock was obtained)    
    if(val == None):
        #switch_filter_icon()
        return FAIL

    # approach the asteroid
    pyautogui.keyDown(APPROACH_KEY) # hold down the approach key
    pyautogui.moveTo(val.x,val.y) # move the mouse into position
    time.sleep(0.5)
    pyautogui.click(val.x,val.y) # click the asteroid
    time.sleep(0.5)
    pyautogui.keyUp(APPROACH_KEY) # release the approach key
    move_mouse_to_safe_spot() # move the mouse out of the way
    
    # wait until we get to the asteroid then begin lock
    for i in range(100):
        val = pyautogui.locateCenterOnScreen('image_keys/asteroid_ready_key.png')
        if(val != None):
            break
        time.sleep(1)
    
    #time.sleep(100) # wait until we get there

    print('targeting asteroid')    
    # find the selected asteroid in the list and lock onto it
    val = pyautogui.locateCenterOnScreen('image_keys/asteroid_locked_key.png')
    if(val == None):
        #switch_filter_icon()
        return FAIL
    # lock onto the asteroid
    pyautogui.keyDown(LOCK_KEY) # hold down the target lock key
    pyautogui.moveTo(val.x,val.y) # select the asteroid
    time.sleep(0.5)
    pyautogui.click(val.x,val.y) # click the asteroid and lock it
    time.sleep(0.5)
    pyautogui.keyUp(LOCK_KEY) # release the lock key
    move_mouse_to_safe_spot()
    time.sleep(7) # wait for lock to finish
    
    # switch filter mode back to Asteroid Clusters
    #switch_filter_icon()
    # move mouse out of the way 
    move_mouse_to_safe_spot()
    return PASS
    
def begin_mining():
    print('mining')
    pyautogui.press('f1')
    pyautogui.press('f2')
    #time.sleep(10)
    #pyautogui.press('f1')
    return PASS

def toggle_shield_boosters():
    print('shield boosting')
    pyautogui.keyDown('alt')
    pyautogui.press('f1')
    pyautogui.press('f2')
    pyautogui.keyUp('alt')
    return PASS

def is_hold_full():
    val = pyautogui.locateCenterOnScreen('image_keys/is_hold_full_key.png')
    if(val == None):
        return False
    else:
        return True

def is_target_selected():
    return(is_icon_present('image_keys/is_target_selected_key.png'))

def is_inventory_open():
    return(is_icon_present('image_keys/inventory_tab_key.png'))

def is_ore_present():
    return(is_icon_present('image_keys/ore_top_key.png'))

def toggle_inventory():
    return(click_on_icon('image_keys/inventory_ui_1_key.png'))

def select_ore_hold():
    return(click_on_icon('image_keys/ore_hold_key.png'))    

# transfers inventory into the home system 
def transfer_inventory():
    print('transferring inventory')
    # move mouse to inventory slot
    #invx = 26
    #invy = 271
    #pyautogui.moveTo(invx,invy)
    #pyautogui.click(invx,invy)

    if(is_inventory_open() == False):
        toggle_inventory()
        move_mouse_to_safe_spot()
        time.sleep(5)
    
    # select ore hold
    select_ore_hold()
    time.sleep(2)

    # item hangar location
    deposit = pyautogui.locateCenterOnScreen('image_keys/item_hangar_key.png',confidence=CONFIDENCE)
    
    while(is_ore_present() == True):
        item = pyautogui.locateCenterOnScreen('image_keys/ore_top_key.png',confidence=CONFIDENCE)
        if(item != None and deposit != None):
            pyautogui.moveTo(item.x,item.y+30)
            pyautogui.mouseDown(item.x,item.y+30)
            time.sleep(1)
            pyautogui.moveTo(deposit.x,deposit.y)
            #pyautogui.dragTo(depositx,deposity,duration=0.5)
            time.sleep(1)
            pyautogui.mouseUp(deposit.x,deposit.y)
        else:
            return FAIL
    # close station inventory    
    toggle_inventory()
    move_mouse_to_safe_spot()
    return PASS    
   
    
# reconnect functions
# checks to see if client is disconnected
def is_client_disconnected():
    return( is_icon_present(restart_filepath+'quit_key.png') )

# reconnects the game client
def reconnect_client():
    print('reconnecting')
    #pval = click_on_icon(restart_filepath+'quit_key.png')
    #if(pval == PASS):
    
    # open the launcher window
    click_on_icon(restart_filepath+'eve_launcher_key.png')
    # 
    click_on_icon(restart_filepath+'play_now_key.png')
    time.sleep(40)
    click_on_icon(restart_filepath+'eve_game_key.png')
    # drag the window over to the left side
    val = pyautogui.locateCenterOnScreen(restart_filepath+'eve_window_icon_key.png',confidence=CONFIDENCE)
    pyautogui.moveTo(val.x+60,val.y)
    pyautogui.dragTo(0,40,duration=0.5)
    # click the claim button
    click_on_icon(restart_filepath+'claim.png')
    time.sleep(10)
    # click the close button
    click_on_icon(restart_filepath+'close.png')
    time.sleep(10)
    
    # click on the character
    click_on_icon(restart_filepath+'cad.png')
    time.sleep(30)

    # get rid of the agency window
    click_on_icon(restart_filepath+'agency_icon.png')
    if(is_icon_present(restart_filepath+'the_agency_window_open_key.png')):
        click_on_icon(restart_filepath+'agency_icon.png')
    
    # get rid of the chat window
    # find the people icon then click the minimize key
    val = pyautogui.locateCenterOnScreen(restart_filepath+'startup_chat_window_people_icon.png',confidence=CONFIDENCE)
    pyautogui.moveTo(val.x+22,val.y-22)
    time.sleep(1)
    pyautogui.click(val.x+22,val.y-22)
    
    # make sure ore hold is open
    # if it isn't, get it back open
    if(is_inventory_open() == False):
        toggle_inventory()
        move_mouse_to_safe_spot()
        time.sleep(10)
    select_ore_hold()
    move_mouse_to_safe_spot()
    time.sleep(30)
    
    return PASS

# checks to see if an an enemy is present on screen
def is_enemy_present():
    img = pyautogui.screenshot(region=(10,10,1029,1029))
    for pixel in img.getdata():
        if(pixel[0] > 200 and pixel[1] < 50 and pixel[2] < 50):
            return True
    return False

# - - - - - - - - - - Begin Script - - - - - - - - -


# add delay between actions
pyautogui.PAUSE = PAUSE_AMOUNT

# initiate a run counter
count = 0


# bot script 
while(1==1):

    # undock the vehicle
    check = undock()
    
    if(check == PASS):
        check = jump_to_target_star_system()
                
    if(check == PASS):
        for i in range(6):
            check = warp_to_asteroids()
            if(check == PASS):
                break
            move_camera()
            print('unable to warp to asteroids')

    # we can only begin mining if we were able to warp to an asteroid field
    if(check == PASS):
        toggle_shield_boosters() # protect ourselves
        click_mining_tab()
        switch_filter_icon()
        # perform the hold
        while(is_hold_full() == False and is_client_disconnected() == False):
            
            # check to see if the system is currently locked onto a target
            if(is_target_selected() == False):
                
                # if we aren't currently locked, try to lock onto an asteroid                 
                for i in range(6):
                    check = lock_target()
                    if(check == PASS):
                        break
                    move_camera()
                    print('missed asteroid lock')
                
                # we can only begin mining if the asteroid lock was successful
                if(check == PASS):
                    check = begin_mining()
                else:
                    print('could not lock an asteroid. returning home.')
                    break
            else:
                # jerk the mouse around to keep it awake
                # wait for the mining equipment to do its job
                time.sleep(60)
        # once we're done mining in the field, switch back the filter icon        
        click_mining_tab()
        switch_filter_icon()
        
    
    # once the hold is full, warp back
    for i in range(6):
        move_mouse_to_safe_spot()
        check = jump_to_home_star_system()
        if(check == PASS):
            break
        move_camera() # move the view to try and get a different position
        print('missed jump to home star system')
    
    if(check == PASS):
        # initiate docking procedure
        check = dock_to_home_station()
    
    # transfer inventory
    if(check == PASS):            
        check = transfer_inventory()
        count += 1
        print('Cycle count = ' + str(count))
    else:
        print('could not dock to home station')
    
    # check to see if client is disconnected
    if(is_client_disconnected() == True):
        print('waiting for reconnect window')
        time.sleep(2*3600) # wait up to two hours
        check = click_on_icon(restart_filepath+'quit_key.png')
        if(check != True):
            print('unable to quit and restart')
            while(1==1):
                time.sleep(1)
        else:
            reconnect_client()
            jump_to_home_star_system()
            dock_to_home_station()
            transfer_inventory()

"""
for i in range(0,10,1):
    print(pyautogui.position())
    time.sleep(1)
"""