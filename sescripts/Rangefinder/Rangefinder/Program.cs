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

        string range_command = "range"; // triggers a range
        string toggle_raycast_command = "toggle"; // toggles camera raycast mode
        string change_range_command = "set"; // changes the range to the double specified in set

        double maxRange = 15000; // maximum raycast range in meters

        IMyTextPanel displayPanel;
        IMyCameraBlock camera;

        MyDetectedEntityInfo newTarget;
        string displayText;

        public Program()
        {
            displayPanel = GridTerminalSystem.GetBlockWithName("Text panel r") as IMyTextPanel;
            camera = GridTerminalSystem.GetBlockWithName("Camera r") as IMyCameraBlock;

            // configure both of these blocks

            displayPanel.Enabled = true;
            displayPanel.ContentType = ContentType.TEXT_AND_IMAGE;
            displayPanel.FontSize = 1.25f;

            camera.Enabled = true;
        }

        public void Save()
        {
 
        }

        public void Main(string argument, UpdateType updateSource)
        {

            if(argument.Equals(range_command))
            {
                if (camera.CanScan(maxRange))
                {
                    newTarget = camera.Raycast(maxRange, 0, 0);
                }
            } else if(argument.Equals(toggle_raycast_command))
            {
                camera.EnableRaycast = !camera.EnableRaycast;
            } else if(argument.StartsWith(change_range_command))
            {
                string[] newStrings = argument.Split(' ');
                maxRange = Convert.ToDouble(newStrings[1]);
            }

            // build the string
            displayText = "Range Finder ";

            // display raycasting on/off
            if (camera.EnableRaycast)
            {
                displayText += "On";
            } else
            {
                displayText += "Off";
            }

            // display raycast target distance
            displayText += "\nRanging Distance: " + maxRange.ToString();

            // display raycast distance
            displayText += "\nAvailable Distance: " + camera.AvailableScanRange.ToString();

            
            if (newTarget.EntityId != 0)
            {
                // display target name
                //displayText += "\nName:" + newTarget.Name;

                // display target type
                displayText += "\nTarget Type:" + newTarget.Type.ToString();

                // display target GPS coordinate
                MyWaypointInfo newWaypoint = new MyWaypointInfo(newTarget.Name,newTarget.Position);
                displayText += "\nCoordinates:\n" + newWaypoint.ToString();
            }

            displayPanel.WriteText(displayText);

        }
    }
}
