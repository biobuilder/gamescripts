using Sandbox.Game.EntityComponents;
using Sandbox.ModAPI.Ingame;
using Sandbox.ModAPI.Interfaces;
using SpaceEngineers.Game.ModAPI.Ingame;
using System.Collections.Generic;
using System.Collections;
using System.Linq;
using System.Text;
using System;
using VRage.Collections;
using VRage.Game.Components;
using VRage.Game.GUI.TextPanel;
using VRage.Game.ModAPI.Ingame.Utilities;
using VRage.Game.ModAPI.Ingame;
using VRage.Game.ObjectBuilders.Definitions;
using VRage.Game;
using VRage;
using VRageMath;

namespace IngameScript
{
    partial class Program : MyGridProgram
    {
        /*
         * Finds other players using an NPC-assigned remote control
         * Make sure the timer block is set to run the programmable block with the "find" argument
         * Make sure the remote control is called Remote Control NPC and is assigned to the pirate faction
         */


        IMyRemoteControl seekerRemote;
        IMyTextPanel outputPanel;
        IMyTimerBlock timer;

        string listOfWaypoints;
        List<Vector3D> playerCoords;

        // commands
        string find_nearest_player = "find";

        // settings
        double max_overlap_range = 5000; // maximum overlap range between subsequent checks

        int uniqueCount = 0; // unique player counts

        public Program()
        {
            seekerRemote = GridTerminalSystem.GetBlockWithName("Remote Control NPC") as IMyRemoteControl;
            outputPanel = GridTerminalSystem.GetBlockWithName("Text panel") as IMyTextPanel;
            timer = GridTerminalSystem.GetBlockWithName("Timer Block") as IMyTimerBlock;
            playerCoords = new List<Vector3D>();

            timer.Enabled = true;
            timer.StopCountdown();
            timer.TriggerDelay = 10; // delay in seconds between triggers

            outputPanel.Enabled = true;
            outputPanel.ContentType = ContentType.TEXT_AND_IMAGE; // configure the LCD panel
        }

        public void Save()
        {

        }

        public void Main(string argument, UpdateType updateSource)
        {
            if (argument.Equals(find_nearest_player))
            {
                // find the player's position
                Vector3D playerPosition;
                seekerRemote.GetNearestPlayer(out playerPosition);

                // check to see if the waypoint should be added to the list
                bool isUnique = true;
                foreach (Vector3D waypoint in playerCoords)
                {
                    if (Vector3D.Distance(waypoint, playerPosition) < max_overlap_range)
                    {
                        isUnique = false;
                        break;
                    }
                }
                if (isUnique)
                {
                    // add the player's position to the player coordinate list
                    playerCoords.Add(playerPosition);

                    // send the string to the LCD screen so that players can retrieve the list of GPS coordinates
                    MyWaypointInfo newWaypoint = new MyWaypointInfo(uniqueCount.ToString(), playerPosition);
                    listOfWaypoints += newWaypoint.ToString() + "\n\r";
                }

            }

            // display the results on the screen
            outputPanel.WriteText(listOfWaypoints);

            // retrigger the timer block
            timer.StartCountdown();
        }
    }
}
