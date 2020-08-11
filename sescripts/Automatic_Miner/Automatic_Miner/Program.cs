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
        // block names for each critical component
        string mainRotorName = "rotor main";
        string elbowRotorName = "rotor elbow";
        string drillRotorName = "rotor drill";
        string timerName = "timer computer";
        string drillGroupName = "drills";

        // set up rotor clockwise direction as viewed from the top of the drill platform
        int mainRotorDir = 1;
        int elbowRotorDir = 1;
        int drillRotorDir = 1;

        // set up rotor offsets (in rad)
        float mainRotorOffset = 0f;
        float elbowRotorOffset = 0f;
        float drillRotorOffset = 0f;

        // rotor torques
        float mainRotorTorque = 1000000f;
        float elbowRotorTorque = 1000000f;
        float drillRotorTorque = 1000000f;
        float brakingTorque = 1000000f;

        // rotor speeds (rad/s)
        float elbowRotorSpeed = (float)(90 * Math.PI / 180);
        float drillRotorSpeed = (float)(90 * Math.PI / 180);

        // configure arm lengths (m)
        const int len1 = 20; // between main base and elbow
        const int len2 = 20; // between elbow and drill head

        // max drill velocity (m/s)
        float drillVel = 0.5f; // meters per second

        // drill penetration angle (rad)
        float drillAng = (float)(45 * Math.PI / 180);

        // drill pass depth (m / cycle)
        float drillPassDepth = 2; // depth of each drill pass

        // maximum extension length
        float maxRadius = len1 + len2; // maximum mining radius
                                       // number of drill passes required
        float numPasses = 0;    // number of passes
        int curPass = 0; // current pass depth
        bool changePass = false; // whether or not to perform a pass cut
        float preAng = 0; // previous angle (used to determine changePass)

        // Initialize a list to store all the drill blocks connected to the ship
        List<IMyShipDrill> drills = new List<IMyShipDrill>();

        // rotor blocks
        IMyMotorAdvancedStator mainRotor;
        IMyMotorAdvancedStator elbowRotor;
        IMyMotorAdvancedStator drillRotor;

        // computer timer block
        IMyTimerBlock timer;

        void Program()
        {
            numPasses = maxRadius / drillPassDepth;


            //Runtime.UpdateFrequency = UpdateFrequency.Update100; // once every 1.7 seconds

            // fill the list with all drills in the assigned block group
            //GridTerminalSystem.GetBlocksOfType(drills);
            var drillGroup = GridTerminalSystem.GetBlockGroupWithName(drillGroupName);
            drillGroup.GetBlocksOfType(drills); // grab the drills out of the block group

            // get rotors
            mainRotor = GridTerminalSystem.GetBlockWithName(mainRotorName) as IMyMotorAdvancedStator;
            elbowRotor = GridTerminalSystem.GetBlockWithName(elbowRotorName) as IMyMotorAdvancedStator;
            drillRotor = GridTerminalSystem.GetBlockWithName(drillRotorName) as IMyMotorAdvancedStator;

            // get the computer timer block
            timer = GridTerminalSystem.GetBlockWithName(timerName) as IMyTimerBlock;

            // configure the drills, rotors and the timer block
            // all rotors and drills off

            setDrills(false);
            mainRotor.Enabled = false;
            mainRotor.Torque = mainRotorTorque;
            mainRotor.BrakingTorque = brakingTorque;
            mainRotor.LowerLimitRad = float.MinValue; // unlimited turning
            mainRotor.UpperLimitRad = float.MaxValue;
            elbowRotor.Enabled = false;
            elbowRotor.Torque = elbowRotorTorque;
            elbowRotor.BrakingTorque = brakingTorque;
            drillRotor.Enabled = false;
            drillRotor.Torque = drillRotorTorque;
            drillRotor.BrakingTorque = brakingTorque;
            timer.Enabled = true; // enable the timer
            timer.TriggerDelay = 1; // set trigger delay time to 1 second

        }

        void Main(string argument, UpdateType updateType)
        {
            // check argument type
            if (string.Equals(argument, "extend"))
            {
                // fully extend the carriage head
                extendTo(maxRadius);

                // turn off the drills
                setDrills(false);

                // reset the drill pass count
                curPass = 0;
            }

            else if (string.Equals(argument, "retract"))
            {
                // fully retract the carriage head
                retractTo(0);

                // turn off the drills
                setDrills(false);

                // reset the drill pass count
                curPass = 0;
            }


            // continues drilling
            else if (string.Equals(argument, "drill"))
            {
                // turn on the drills
                setDrills(true);

                // get current rotor angle
                float angle = mainRotor.Angle;

                // set changePass flag
                changePass = mainRotorDir * (angle - preAng) < 0;

                // check to see if a change pass is required
                if (changePass)
                {
                    curPass++;
                    retractTo(maxRadius - curPass * drillPassDepth);

                    // set the main driving rotor speed
                    var curRad = calcCurRadius(elbowRotor.Angle, len1, len2); // current drill radius (m)
                    var rotVel = mainRotorDir * calcMainVel(curRad, drillVel);  // desired main rotor rotational velocity (rad/s)
                    mainRotor.TargetVelocityRad = rotVel; // set the main rotor velocity (rad/s)
                    changePass = false;
                }

                // store old angle
                preAng = angle;

                // trigger the timer block
                timer.StartCountdown();
            }

            // pauses progress
            else if (string.Equals(argument, "pause"))
            {
                // shut down the rotors
                mainRotor.Enabled = false;
                elbowRotor.Enabled = false;
                drillRotor.Enabled = false;

                // shut down the drills
                setDrills(false);

                // do not retrigger the timer block
                timer.StopCountdown();
            }
        }

        // extends the arm to the given length
        void extendTo(float radius)
        {
            // get desired rotor angle
            float angle = calcElbowAng(radius, len1, len2);

            // set target rotor speed
            elbowRotor.TargetVelocityRad = elbowRotorSpeed * elbowRotorDir;

            if (elbowRotorDir < 0)
            {
                elbowRotor.LowerLimitRad = float.MinValue; // unlimited
                elbowRotor.UpperLimitRad = angle;
            }
            else
            {
                elbowRotor.LowerLimitRad = angle;
                elbowRotor.UpperLimitRad = float.MaxValue; // unlimited
            }

        }

        // retracts the arm to the given length
        void retractTo(float radius)
        {
            // get desired rotor angle
            float angle = calcElbowAng(radius, len1, len2);

            // set target rotor speed
            elbowRotor.TargetVelocityRad = elbowRotorSpeed * -elbowRotorDir;

            if (elbowRotorDir > 0)
            {
                elbowRotor.LowerLimitRad = float.MinValue; // unlimited
                elbowRotor.UpperLimitRad = angle;
            }
            else
            {
                elbowRotor.LowerLimitRad = angle;
                elbowRotor.UpperLimitRad = float.MaxValue; // unlimited
            }
        }

        // sets the drill to the correct angle
        // elbAng is the current elbow angle
        void setDrillAngle(float elbAng)
        {
            // calculate the required drill angle
            // make sure the unit circle has plenty of radians onboard
            float reqAng = calcDrillAng(drillAng, elbAng, len1, len2);

            // calculate difference between the current angle and the desired angle
            float diffAng = reqAng - drillRotor.Angle;

            // adjust for shortest path to reach destination
            if (diffAng > (float)Math.PI)
            {
                diffAng = diffAng - (float)(Math.PI * 2);
            }
            else if (diffAng < (float)(-Math.PI))
            {
                diffAng = diffAng + (float)(Math.PI * 2);
            }

            // decide which direction to rotate
            // the sign denotes which way to rotate
            if (diffAng < 0)
            {
                drillRotor.TargetVelocityRad = drillRotorSpeed;
            }
            else
            {
                drillRotor.TargetVelocityRad = -drillRotorSpeed;
            }

            // set rotor limits
            drillRotor.LowerLimitRad = reqAng;
            drillRotor.UpperLimitRad = reqAng;

        }

        // calculates the desired elbow angle
        // r is the desired radius in units
        // l1 is the base to elbow length in units
        // l2 is the elbow to endpoint length in units
        float calcElbowAng(float r, float l1, float l2)
        {
            return ((float)(Math.Acos((l1 * l1 + l2 * l2 - r * r) / (-2 * l1 * l2))));
        }

        // calculates the desired drill rotor angle based on the elbow angle
        // dang is the desired drill penetration angle
        // elbang is the current elbow angle
        // l1 is the length between base and elbow in units
        // r is the current drill radius
        float calcDrillAng(float dang, float elbang, float l1, float r)
        {
            return ((float)(Math.PI / 2 - Math.Asin(l1 * Math.Sin(elbang) / r) - dang));
        }

        // calculates the current extension length of the arm based on the rotor values
        // ang is elbow rotor angle in radians
        // l1 is the length between base and elbow
        // l2 is the length between elbow and drill head
        float calcCurRadius(float ang, float l1, float l2)
        {
            return ((float)(Math.Sqrt(l1 * l1 + l2 * l2 - 2 * l1 * l2 * Math.Cos(ang))));
        }

        // calculates the required rad/s of the main rotor to achieve the desired cut rate
        // drillRadius is the current drilling radius in units
        // desiredVel is the desired cutting velocity in units / second
        float calcMainVel(float drillRadius, float desiredVel)
        {
            return (desiredVel / drillRadius);
        }

        // sets the drills to either "on" = 1 or "off" = 0
        void setDrills(bool s)
        {
            for (int i = 0; i < drills.Count; i++)
            {
                IMyShipDrill drill = drills[i];
                drill.Enabled = s;
            }
        }

        // causes the given advanced rotor to go to the specified angle
        // stator is the stator reference
        // angle is the desired angle
        void rotateAdvancedStatorTo(IMyMotorAdvancedStator stator, double angle)
        {
            float curAng = stator.Angle; // get current angle
                        
            // calculate difference between the current angle and the desired angle
            float diffAng = angle - curAng;

            // spin to the desired angle with the shortest distance
            if (diffAng > (float)Math.PI)
            {
                diffAng = diffAng - (float)(Math.PI * 2);
            }
            else if (diffAng < (float)(-Math.PI))
            {
                diffAng = diffAng + (float)(Math.PI * 2);
            }

            // decide which direction to rotate
            // the sign denotes which way to rotate
            if (diffAng < 0)
            {
                stator.TargetVelocityRad = drillRotorSpeed;
            }

            else
            {
                stator.TargetVelocityRad = -drillRotorSpeed;
            }

            // set rotor limits
            stator.LowerLimitRad = angle;
            stator.UpperLimitRad = angle;
        }
        

    }
}



