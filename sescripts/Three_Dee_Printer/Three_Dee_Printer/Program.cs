/*
3D Printer script
Damon Printz
10/11/2019

Uses an autopilot, source connector and a single row of welders to build a ship projection
Can run on any size ship

Actions
1. Undock and Weld
2. Automatically redock
3. Monitor internal inventory (later version)
4. Display internal inventory items on external LCD


Configuration
1. Docking
 - ship-side connector must be in front of the remote control block
 - remote control block must be facing forward in the same direction as the welders and ship-side connector
 - automatically determine position of remote control block relative to the ship-side connector
 - projection is x meters above the base-side connector
 - base-side connector must have a specific name
 - 
Initialization
1. Get connector GPS coordinate and orientation, use as origin
2. Generate docking coordinates
*/

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
        // arguments (constants)
        string command_print = "print";
        string command_pause = "pause";
        string command_resume = "resume";
        string command_set_build_volume = "set";
        string command_check_inventory = "check";

        // build state enums
        enum BuildState
        {
            // build states
            begin_weld,
            undock,
            wait_for_z_undock,
            align_x_pass,
            wait_for_x_alignment,
            make_y_pass,
            wait_for_y_pass,
            change_x_pass,
            wait_for_x_pass,
            increment_z_pass,
            wait_for_z_pass,
            return_to_dock_x,
            wait_for_return_to_dock_x,
            return_to_dock_y,
            wait_for_return_to_dock_y,
            return_to_dock_z,
            wait_for_return_to_dock_z,
            reconnect,

            // other states
            pause_print,
            resume_weld

        };

        public class BuildVariables
        {
            Program _program;
            public BuildVariables(Program program)
            {
                _program = program;
            }

            // 3D printer constants
            public double PrintSpeed { get; set; } // printing speed
            public double TraverseSpeed { get; set; } // maximum travel speed
            public double Tolerance { get; set; } // target tolerance for waypoint detection
            public double DockingDepth { get; set; } // docking depth
            public double PassWidth { get; set; } // pass width of welder array (m)
            public double ZStepSize { get; set; } // height of each step in z axis (m)
            public Vector3D BuildOffset { get; set; } // build offsets from origin
            public Vector3D AutopilotOffset { get; set; } // autopilot offset from its connector
            public double BlockSize { get; set; } // 2.5 meters for large blocks, 0.5 meters for small blocks

            // world orientation and position
            public Vector3D BuildXaxis { get; set; } // +x build axis (all normalized)
            public Vector3D BuildYaxis { get; set; } // +y build axis
            public Vector3D BuildZaxis { get; set; } // -z axis
            public Vector3D BaseConnectorOrigin { get; set; } // base connector origin

            // orientation definitions for the autopilot
            public Base6Directions.Direction PlusXDir;
            public Base6Directions.Direction MinusXDir;
            public Base6Directions.Direction PlusYDir;
            public Base6Directions.Direction MinusYDir;
            public Base6Directions.Direction PlusZDir;
            public Base6Directions.Direction MinusZDir;

            // construction variables
            public int WorkState { get; set; } // build state machine
            public int OverallState { get; set; } // overall state machine
            public Vector3D CurrentWaypoint { get; set; } // current GPS waypoint
            public Vector3D DockingEndpoint { get; set; } // docking endpoint
            public Vector3D BuildOrigin { get; set; } // build origin + offsets included
            public Vector3D BuildVolume { get; set; } // build volume (x, y, and z in meters)

            // working variables
            public int XPassMaxCount { get; set; }
            public int ZPassMaxCount { get; set; }
            public bool YPassDir { get; set; }
            public bool XPassDir { get; set; }
            public int XCount { get; set; }
            public int ZCount { get; set; }


            // methods

            // reset all working variable counts
            public void ResetCounts()
            {
                YPassDir = false;
                XCount = 0;
                ZCount = 0;
                XPassDir = true;
            }
            // calculate the max build counts for the new build
            public void CalculateMaxCounts()
            {
                // calculate the maximum number of Z passes
                ZPassMaxCount = (int)Math.Ceiling(BuildVolume.Z / ZStepSize);
                // calculate the maximum number of x passes
                XPassMaxCount = (int)Math.Ceiling(BuildVolume.X / PassWidth);
            }
        }

        // ship-specific identities
        IMyTimerBlock timer; // main ship timer
        IMyShipConnector shipConnector; // ship-side connector
        IMyShipConnector baseConnector; // docking port connector
        IMyTextPanel panel; // lcd panel for displaying items
        IMyRemoteControl remoteControl;
        List<IMyShipWelder> welders;
        List<IMyCargoContainer> cargo;

        // build variables class
        BuildVariables myBuildVars;

        // output to screen
        string lcdText = "";

        public Program()
        {
            // try to get the base connector
            try
            {
                baseConnector = GridTerminalSystem.GetBlockWithName("Connector WB") as IMyShipConnector;
            } catch(Exception e)
            {
                Echo("Please connect to a valid base station");
                Echo($"Error: {e}");
                //lcdText = "connect to the base";
                //panel.WriteText(lcdText);
                throw;
            }
            //shipConnector = GridTerminalSystem.GetBlockWithName("Connector W") as IMyShipConnector;
            var connectors = new List<IMyShipConnector>();
            GridTerminalSystem.GetBlocksOfType(connectors, block => block.IsSameConstructAs(Me));
            shipConnector = connectors[0];
            //remoteControl = GridTerminalSystem.GetBlockWithName("Remote Control W") as IMyRemoteControl;
            var remotes = new List<IMyRemoteControl>();
            GridTerminalSystem.GetBlocksOfType(remotes, block => block.IsSameConstructAs(Me));
            remoteControl = remotes[0];
            //timer = GridTerminalSystem.GetBlockWithName("Timer W") as IMyTimerBlock;
            var timers = new List<IMyTimerBlock>();
            GridTerminalSystem.GetBlocksOfType(timers, block => block.IsSameConstructAs(Me));
            timer = timers[0];
            //panel = GridTerminalSystem.GetBlockWithName("LCD Panel W") as IMyTextPanel;
            var panels = new List<IMyTextPanel>();
            GridTerminalSystem.GetBlocksOfType(panels, block => block.IsSameConstructAs(Me));
            panel = panels[0];

            // welders
            welders = new List<IMyShipWelder>();
            GridTerminalSystem.GetBlocksOfType(welders, block => block.IsSameConstructAs(Me));

            // cargo containers
            cargo = new List<IMyCargoContainer>();
            GridTerminalSystem.GetBlocksOfType(cargo, block => block.IsSameConstructAs(Me));

            // pre-configure all the blocks
            remoteControl.FlightMode = FlightMode.OneWay; // flight direction
            remoteControl.SetDockingMode(true); // precision flight mode
            panel.ContentType = ContentType.TEXT_AND_IMAGE; // display stuff on the screen

            timer.StopCountdown();
            timer.TriggerDelay = 1; // trigger delay for countdown

            // set printer constants
            myBuildVars = new BuildVariables(this)
            {
                PrintSpeed = 2, // printing speed (m/s)
                TraverseSpeed = 10, // traverse speed (m/s)
                Tolerance = 0.25, // must be within 1/4 a meter to count
                DockingDepth = 10, // 10 meter default docking depth
                PassWidth = 7*2.5, // pass width of the welders in meters
                ZStepSize = 2.5, // step size along z axis in meters
                BuildOffset = new Vector3D(5, 10, 2.5+2), // build offsets from origin (x, y, z)
                BlockSize = 2.5, // block size (2.5 m for large blocks, 0.5 m for small blocks)
                AutopilotOffset = new Vector3D(0, 0, 3 * 2.5), // position of autopilot relative to connector

                // get world orientation and direction of base connector
                // get build x axis
                BuildXaxis = Vector3D.Normalize(baseConnector.WorldMatrix.Right),
                // get build y axis
                BuildYaxis = Vector3D.Normalize(baseConnector.WorldMatrix.Down),
                // get build z axis
                BuildZaxis = Vector3D.Normalize(baseConnector.WorldMatrix.Forward),
                // get base connector origin
                BaseConnectorOrigin = baseConnector.GetPosition(),


                // configure autopilot directions
                PlusXDir = Base6Directions.Direction.Right,
                MinusXDir = Base6Directions.Direction.Left,
                PlusYDir = Base6Directions.Direction.Up,
                MinusYDir = Base6Directions.Direction.Down,
                PlusZDir = Base6Directions.Direction.Forward,
                MinusZDir = Base6Directions.Direction.Backward
            };

            // calculate entry points, etc.
            calculateDockingPoint(myBuildVars);
            lcdText = ("docking endpoint:\n\r" + myBuildVars.DockingEndpoint.ToString());
            panel.WriteText(lcdText, false);
        }

        public void Save()
        {
        }

        public void Main(string argument, UpdateType updateSource)
        {
            try
            {
                // resume printing command
                if (argument.Equals(command_resume))
                {
                    lcdText = ("Resume printing");
                    panel.WriteText(lcdText, false);

                    // reset build states
                    myBuildVars.OverallState = (int)BuildState.resume_weld;

                    // resume autopilot
                    remoteControl.SetAutoPilotEnabled(true);
                    // resume welders
                    controlWelders(welders, true);

                }
                // pause printing command
                else if (argument.Equals(command_pause))
                {
                    lcdText = ("Pause printing");
                    panel.WriteText(lcdText, false);

                    myBuildVars.OverallState = (int)BuildState.pause_print;

                    // disable autopilot
                    remoteControl.SetAutoPilotEnabled(false);
                    // disable welders
                    controlWelders(welders, false);

                }
                // start printing command
                else if (argument.Equals(command_print))
                {
                    lcdText = ("Begin printing");
                    panel.WriteText(lcdText, false);

                    myBuildVars.ResetCounts();
                    myBuildVars.OverallState = (int)BuildState.resume_weld;
                    myBuildVars.WorkState = (int)BuildState.begin_weld;

                    remoteControl.SetAutoPilotEnabled(false);
                }
                // set build volume command
                // start with the command string followed by X, Y, Z separated by commas
                else if (argument.StartsWith(command_set_build_volume))
                {
                    // break the string down by ' ' and ',' delimiters
                    string[] elements = argument.Split(' ');
                    Vector3D volume;
                    volume.X = double.Parse(elements[1]);
                    volume.Y = double.Parse(elements[2]);
                    volume.Z = double.Parse(elements[3]);

                    myBuildVars.BuildVolume = volume;

                    myBuildVars.CalculateMaxCounts();

                    lcdText = "Set build volume to:\n\rX: " + volume.X.ToString() + "\n\rY: " + volume.Y.ToString() + "\n\rZ: " + volume.Z.ToString();
                    lcdText += "\n\rMax Counts:\n\rZc: " + myBuildVars.ZPassMaxCount.ToString() + "\n\rXc: " + myBuildVars.XPassMaxCount.ToString() + "\n\r";
                    panel.WriteText(lcdText);
                }
                // check the cargo container inventory
                else if(argument.Equals(command_check_inventory))
                {
                    lcdText = "Inventory\n";
                    panel.WriteText(lcdText);

                }
            }
            catch(Exception e)
            {
                Echo($"Error: {e}");
                throw;
            }

            try
            {
                if (myBuildVars.OverallState == (int)BuildState.resume_weld)
                {
                    // enter the massive state machine
                    switch (myBuildVars.WorkState)
                    {
                        case (int)BuildState.begin_weld:
                            {
                                // calculate build origin
                                calculateBuildOrigin(myBuildVars);

                                // turn on the welders
                                controlWelders(welders, true);

                                // set autopilot speed to transit speed
                                remoteControl.SpeedLimit = (float)myBuildVars.TraverseSpeed;

                                // clear remote control waypoints
                                remoteControl.ClearWaypoints();

                                lcdText = ("beginning weld, build origin:\n");
                                lcdText += myBuildVars.BuildOrigin.ToString();
                                panel.WriteText(lcdText, false);

                                myBuildVars.WorkState = (int)BuildState.undock;
                                break;
                            }
                        case (int)BuildState.undock:
                            {
                                lcdText = ("undocking");
                                panel.WriteText(lcdText, false);
                                shipConnector.Disconnect(); // disconnect the ship connector

                                // calculate the first step translation vector from the connector
                                Vector3D translationVect = Vector3D.Multiply(myBuildVars.BuildZaxis, myBuildVars.BuildOffset.Z);
                                // add this vector to the docking endpoint to get the first exit waypoint
                                myBuildVars.CurrentWaypoint = Vector3D.Add(myBuildVars.DockingEndpoint, translationVect);
                                // go to the new waypoint
                                setTargetWaypoint(remoteControl, myBuildVars.CurrentWaypoint, myBuildVars.MinusZDir);

                                remoteControl.SetAutoPilotEnabled(true); // enable the autopilot

                                myBuildVars.WorkState = (int)BuildState.wait_for_z_undock;
                                break;
                            }
                        case (int)BuildState.wait_for_z_undock:
                            {
                                lcdText = ("waiting for z axis undock to:\n");
                                lcdText += remoteControl.CurrentWaypoint.ToString();
                                panel.WriteText(lcdText, false);
                                if (isAtDestination(remoteControl))
                                {
                                    myBuildVars.WorkState = (int)BuildState.align_x_pass;
                                }
                                break;
                            }
                        case (int)BuildState.align_x_pass:
                            {

                                // calculate new x coordinate direction
                                // calculate the first step translation vector from the connector
                                Vector3D translationVect = Vector3D.Multiply(myBuildVars.BuildXaxis, myBuildVars.BuildOffset.X);
                                // add this vector to the docking endpoint to get the first exit waypoint
                                myBuildVars.CurrentWaypoint = Vector3D.Add(myBuildVars.CurrentWaypoint, translationVect);
                                // assign the new waypoint
                                setTargetWaypoint(remoteControl, myBuildVars.CurrentWaypoint, myBuildVars.PlusXDir);

                                lcdText = ("aligning to initial x position");
                                panel.WriteText(lcdText, false);

                                myBuildVars.WorkState = (int)BuildState.wait_for_x_alignment;
                                break;
                            }
                        case (int)BuildState.wait_for_x_alignment:
                            {
                                lcdText = ("waiting for x alignment\n");
                                lcdText += myBuildVars.CurrentWaypoint.ToString();
                                panel.WriteText(lcdText, false);

                                if (isAtDestination(remoteControl)) // Vector3D.Subtract(remoteControl.GetPosition(), myBuildVars.CurrentWaypoint).Normalize() < myBuildVars.Tolerance)
                                {
                                    // reset speed to print speed
                                    remoteControl.SpeedLimit = (float)myBuildVars.PrintSpeed;
                                    // change state
                                    myBuildVars.WorkState = (int)BuildState.make_y_pass;
                                }
                                break;
                            }
                        case (int)BuildState.make_y_pass:
                            {
                                lcdText = ("making a y pass");
                                panel.WriteText(lcdText, false);

                                
                                // flip flop the y pass direction
                                myBuildVars.YPassDir = !myBuildVars.YPassDir;

                                // calculate the next waypoint
                                calculateNewWaypoint(myBuildVars);
                                
                                if(myBuildVars.YPassDir)
                                {
                                    setTargetWaypoint(remoteControl, myBuildVars.CurrentWaypoint, myBuildVars.PlusYDir);
                                } else
                                {
                                    setTargetWaypoint(remoteControl, myBuildVars.CurrentWaypoint, myBuildVars.MinusYDir);
                                }
                                myBuildVars.WorkState = (int)BuildState.wait_for_y_pass;
                                break;
                            }
                        case (int)BuildState.wait_for_y_pass:
                            {
                                lcdText = ("waiting for y pass\n");
                                lcdText += remoteControl.CurrentWaypoint.ToString();
                                panel.WriteText(lcdText, false);
                                if (isAtDestination(remoteControl))
                                {
                                    myBuildVars.WorkState = (int)BuildState.change_x_pass;
                                }
                                break;
                            }
                        case (int)BuildState.change_x_pass:
                            {
                                lcdText = ("changing x pass");
                                panel.WriteText(lcdText, false);


                                // if counting up x passes
                                if(myBuildVars.XPassDir == true)
                                {
                                    // if we haven't reached the max x pass count, make an x pass change
                                    if(myBuildVars.XCount < myBuildVars.XPassMaxCount - 1)
                                    {
                                        myBuildVars.XCount++;
                                        calculateNewWaypoint(myBuildVars);
                                        setTargetWaypoint(remoteControl, myBuildVars.CurrentWaypoint, myBuildVars.PlusXDir);
                                        myBuildVars.WorkState = (int)BuildState.wait_for_x_pass;
                                    }
                                    // otherwise, initiate a z pass change
                                    else
                                    {
                                        myBuildVars.XPassDir = !myBuildVars.XPassDir;
                                        myBuildVars.WorkState = (int)BuildState.increment_z_pass;
                                    }
                                } 
                                // if counting down x passes
                                else
                                {
                                    // if we haven't reached the origin yet, initiate an x pass
                                    if(myBuildVars.XCount > 0)
                                    {
                                        myBuildVars.XCount--;
                                        calculateNewWaypoint(myBuildVars);
                                        setTargetWaypoint(remoteControl, myBuildVars.CurrentWaypoint, myBuildVars.MinusXDir);
                                        myBuildVars.WorkState = (int)BuildState.wait_for_x_pass;
                                    }
                                    // otherwise, initiate a z pass
                                    else
                                    {
                                        myBuildVars.XPassDir = !myBuildVars.XPassDir;
                                        myBuildVars.WorkState = (int)BuildState.increment_z_pass;
                                    }
                                }
                                break;
                            }
                        case (int)BuildState.wait_for_x_pass:
                            {
                                lcdText = ("waiting for x pass\n");
                                lcdText += myBuildVars.CurrentWaypoint.ToString();
                                panel.WriteText(lcdText, false);

                                if(isAtDestination(remoteControl))
                                {
                                    myBuildVars.WorkState = (int)BuildState.make_y_pass;
                                }

                                break;
                            }
                        case (int)BuildState.increment_z_pass:
                            {
                                lcdText = ("incrementing z pass");
                                panel.WriteText(lcdText, false);

                                // if we haven't reached the top yet
                                if(myBuildVars.ZCount < myBuildVars.ZPassMaxCount)
                                {
                                    myBuildVars.ZCount++;
                                    calculateNewWaypoint(myBuildVars);
                                    setTargetWaypoint(remoteControl, myBuildVars.CurrentWaypoint, myBuildVars.MinusZDir);
                                    myBuildVars.WorkState = (int)BuildState.wait_for_z_pass;
                                } else
                                {
                                    myBuildVars.WorkState = (int)BuildState.return_to_dock_x;
                                }
                                break;
                            }
                        case (int)BuildState.wait_for_z_pass:
                            {
                                lcdText = ("waiting for z pass");
                                lcdText += myBuildVars.CurrentWaypoint.ToString();
                                panel.WriteText(lcdText, false);

                                if(isAtDestination(remoteControl))
                                {
                                    myBuildVars.WorkState = (int)BuildState.make_y_pass;
                                }
                                break;
                            }
                        case (int)BuildState.return_to_dock_x:
                            {
                                lcdText = ("return to x dock coordinate");
                                panel.WriteText(lcdText, false);

                                // increase speed to traverse speed
                                remoteControl.SpeedLimit = (float)myBuildVars.TraverseSpeed;

                                // set the x count to zero
                                myBuildVars.XCount = 0;
                                calculateNewWaypoint(myBuildVars);

                                // offset toward the docking point plane
                                myBuildVars.CurrentWaypoint = Vector3D.Subtract(myBuildVars.CurrentWaypoint, Vector3D.Multiply(myBuildVars.BuildXaxis, myBuildVars.BuildOffset.X));

                                // store the docking endpoint
                                setTargetWaypoint(remoteControl, myBuildVars.CurrentWaypoint, myBuildVars.MinusXDir);

                                myBuildVars.WorkState = (int)BuildState.wait_for_return_to_dock_x;
                                break;
                            }
                        case (int)BuildState.wait_for_return_to_dock_x:
                            {
                                lcdText = ("waiting for x return");
                                lcdText += myBuildVars.CurrentWaypoint.ToString();
                                panel.WriteText(lcdText, false);
                                if(isAtDestination(remoteControl))
                                {
                                    myBuildVars.WorkState = (int)BuildState.return_to_dock_y;
                                }
                                break;
                            }
                        case (int)BuildState.return_to_dock_y:
                            {
                                lcdText = ("return to y dock coordinate");
                                panel.WriteText(lcdText, false);

                                // set the y direction to false (close to origin)
                                myBuildVars.YPassDir = false;
                                calculateNewWaypoint(myBuildVars);

                                // offset toward the docking point plane
                                myBuildVars.CurrentWaypoint = Vector3D.Subtract(myBuildVars.CurrentWaypoint, Vector3D.Multiply(myBuildVars.BuildYaxis, myBuildVars.BuildOffset.Y));
                                myBuildVars.CurrentWaypoint = Vector3D.Subtract(myBuildVars.CurrentWaypoint, Vector3D.Multiply(myBuildVars.BuildXaxis, myBuildVars.BuildOffset.X));

                                // store the docking endpoint
                                setTargetWaypoint(remoteControl, myBuildVars.CurrentWaypoint, myBuildVars.MinusYDir);

                                myBuildVars.WorkState = (int)BuildState.wait_for_return_to_dock_y;
                                break;
                            }
                        case (int)BuildState.wait_for_return_to_dock_y:
                            {
                                lcdText = ("waiting for y return");
                                lcdText += myBuildVars.CurrentWaypoint.ToString();
                                panel.WriteText(lcdText, false);
                                if (isAtDestination(remoteControl))
                                {
                                    myBuildVars.WorkState = (int)BuildState.return_to_dock_z;
                                }
                                break;
                            }
                        case (int)BuildState.return_to_dock_z:
                            {
                                lcdText = ("return to docking z coordinate");
                                panel.WriteText(lcdText, false);

                                myBuildVars.CurrentWaypoint = myBuildVars.DockingEndpoint;

                                setTargetWaypoint(remoteControl, myBuildVars.CurrentWaypoint, myBuildVars.PlusZDir);

                                myBuildVars.WorkState = (int)BuildState.wait_for_return_to_dock_z;
                                break;
                            }
                        case (int)BuildState.wait_for_return_to_dock_z:
                            {
                                lcdText = ("waiting for z return");
                                panel.WriteText(lcdText, false);
                                if(isAtDestination(remoteControl))
                                {
                                    myBuildVars.WorkState = (int)BuildState.reconnect;
                                }
                                break;
                            }
                        case (int)BuildState.reconnect:
                            {
                                lcdText = ("reconnecting");
                                panel.WriteText(lcdText, false);
                                shipConnector.Connect();
                                break;
                            }
                        default: break;
                    }

                    // retrigger the timer block
                    timer.StartCountdown();
                }
            }
            catch (Exception e)
            {
                Echo($"Error: {e}\n");
                throw;
            }

        }


        // checks to see if an autopilot has reached its destination
        public bool isAtDestination(IMyRemoteControl myRemote)
        {
            Vector3D curPos = myRemote.GetPosition(); // current position of autopilot
            Vector3D destination = myRemote.CurrentWaypoint.Coords; // destination of autopilot
            double distance = Vector3D.Subtract(curPos, destination).Length();
            
            return (distance < myBuildVars.Tolerance);
        }

        // controls any list of welders, true = on, false = off
        public void controlWelders(List<IMyShipWelder> welderList, bool enable)
        {
            foreach (var welder in welderList)
            {
                welder.Enabled = enable;
            }
        }

        // causes the autopilot to go to the target waypoints
        // myRemote is the remote control block to control
        // targetWaypoint is the target waypoint of interest as a Vector3D
        // direction is the desired direction
        public void setTargetWaypoint(IMyRemoteControl myRemote, Vector3D targetWaypoint, Base6Directions.Direction dir)
        {
            //myRemote.SetAutoPilotEnabled(false);
            //while (myRemote.IsAutoPilotEnabled) ;
            remoteControl.ClearWaypoints();
            myRemote.Direction = dir;
            myRemote.AddWaypoint(new MyWaypointInfo("w",targetWaypoint)); // add the next waypoint
            myRemote.SetAutoPilotEnabled(true);
        }

        // calculates a new waypoint based on the current presets in the build variables
        public void calculateNewWaypoint(BuildVariables vars)
        {
            double xDis = vars.XCount * vars.PassWidth;
            double zDis = vars.ZCount * vars.ZStepSize;
            double yDis;

            if(myBuildVars.YPassDir == true)
            {
                yDis = vars.BuildVolume.Y;
            } else
            {
                yDis = 0;
            }

            Vector3D translation = Vector3D.Multiply(myBuildVars.BuildXaxis, xDis);
            translation = Vector3D.Add(Vector3D.Multiply(myBuildVars.BuildYaxis, yDis), translation);
            translation = Vector3D.Add(Vector3D.Multiply(myBuildVars.BuildZaxis, zDis), translation);

            vars.CurrentWaypoint = Vector3D.Add(myBuildVars.BuildOrigin, translation);
        }

        // calculate the build origin (i.e. docking point)
        public void calculateDockingPoint(BuildVariables vars)
        { 
            //Vector3D translation = Vector3D.Multiply(myBuildVars.BuildZaxis, myBuildVars.AutopilotOffset.Z);
            Vector3D newSpot = Vector3D.Add(vars.BaseConnectorOrigin, vars.AutopilotOffset);
            vars.DockingEndpoint = newSpot;
        }

        // calculates the build origin
        public void calculateBuildOrigin(BuildVariables vars)
        {
            Vector3D translate = Vector3D.Multiply(vars.BuildXaxis, vars.BuildOffset.X);
            translate = Vector3D.Add(Vector3D.Multiply(vars.BuildYaxis, vars.BuildOffset.Y), translate);
            translate = Vector3D.Add(Vector3D.Multiply(vars.BuildZaxis, vars.BuildOffset.Z), translate);
            vars.BuildOrigin = Vector3D.Add(vars.DockingEndpoint, translate);
        }

        // checks available inventory in the listed cargo containers and stores it in myText string

        public void checkInventory(List<IMyCargoContainer> cargoContainers, string myOutputText)
        {
            IMyInventory myInventory;
            foreach(IMyCargoContainer container in cargoContainers)
            {
                // get inventory

            }

            // compute inventory totals

            // add it to the text string
            myOutputText += "\n";
        }
    }
}
