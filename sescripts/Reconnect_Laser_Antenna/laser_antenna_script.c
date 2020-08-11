/*
Laser Antenna Reconnection Script
* Helps you keep your remote ships connected to a base location
* no matter which way the ship is pointing.
* Note: Install laser antennas at the ends of your ship pointing in the
* opposite directions.  This will help increase your coverage.
*
* Also note: you need to paste the host laser antenna (base) coordinates
* into both of your ship's laser antennas before sending it off.
* This way your ship will know what point to connect to in case the
* connection is interrupted.
*
* The base laser antenna must be enabled and under your ownership
* or else the laser antennas from your ship may not connect.

What you need:
1. Programmable block
2. Two laser antennas with the following names:
 - "Laser Antenna"
 - "Laser Antenna 2"
3. A timer block that runs the programmable block and retriggers itself
 - Suggested to keep this around 1-10 seconds, depending on your needs
*/

public void Main(void)
{
       // Grab the first laser antenna
       var ant1 = GridTerminalSystem.GetBlockWithName("Laser Antenna") as IMyLaserAntenna;

       // Grab the second laser antenna
       var ant2 = GridTerminalSystem.GetBlockWithName("Laser Antenna 2") as IMyLaserAntenna;

       // Check connection status of both antennas
       var ant1ConStat = ant1.Status == MyLaserAntennaStatus.Connected;
       var ant2ConStat = ant2.Status == MyLaserAntennaStatus.Connected;

       // If neither antenna is connected, try reinstating the connection
       if(!ant1ConStat && !ant2ConStat)
       {
              ant1.Connect();
              ant2.Connect();
              Echo("connecting...");
       }

       // Otherwise, put the unused antenna into an Idle state
       // If both antennas connected, the first one will be set to Idle
       else {
              // Put the unused antenna into an Idle state
              if(!ant1ConStat)
              {
                     ant1.ApplyAction("Idle");
              } else if(!ant2ConStat)
              {
                     ant2.ApplyAction("Idle");
              }

       Echo("connected");
       }
}
