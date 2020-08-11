// See URL for reference:
// https://forum.keenswh.com/threads/guide-accessing-inventory-from-programmable-block.7224691/page-2


void Main()
{
       var block = new List&lt;IMyTerminalBlock>();
       GridTerminalSystem.GetBlocksOfType&lt;IMyRadioAntenna>(block);
       var antenna = block[0];
       double max = 0.0;
       double curr = 0.0;

       var blocks = new List&lt;IMyTerminalBlock>();
       GridTerminalSystem.GetBlocksOfType&lt;IMyCargoContainer>(blocks);

       for(int i =0; i &lt; blocks.Count ; i++)
       {
              var container = blocks[i];

              var inventoryOwner = (IMyInventoryOwner)container;
              var sourceInventory = inventoryOwner.GetInventory(0); // access inventory 0 from this object (refineries have two inventories)
              max += (double)sourceInventory.MaxVolume;
              curr += (double)sourceInventory.CurrentVolume;
        }

       var fill = (double)curr/(double)max;
       int percent = (int)(fill*100);


       if(percent > 0)
       {
              antenna.SetCustomName("Cargo " + percent.ToString() + " percent full");
       }
       else
       {
              antenna.SetCustomName("Container is empty");
       }
}
