/*
ATT - Automatic Trade Teller/Terminal
Purpose: Allows players to trade minerals in exchange for other resources

Available trades are listed in the LCD above the trade terminal
Player selects an available trade by pushing a button
Player inputs the required amount of resources into a public container
Player pushes a button
The automatic terminal grabs the minerals and then dumps the trade amount
into the public container
The player removes their resources



Button commands
"Trade" - attempts to perform a trade
"Switch" - selects a new trade

When the player runs the programmable block with the "Trade" argument,
the trade terminal does the following:
1. Check the container for the amount of input trade resource
2. Calculate the maximum exchange amount from the input amount
3. Check to see how much inventory is available
4. Calculate the maximum exchange amount from the available quantity
5. Store the max transaction number using whichever amount is limiting
 - Grab the input resources and store them in the inventory container
 - Dump the inventory resources into the public container


Next step: Public Interface
1. Initialize a public trade index selection variable at compilation
2. Display all of the available trades in the Trade LCD panel
 - Only display as many trades as will fit on the LCD panel
3. If the "Switch" argument is sent to the programmable block,
 - display the selected trade on the selection LCD panel

* Check out the Final Frontier coding references
http://thefinalfrontier.se/category/scripts/inventory/
*/


// LCD Panel Selections for this trade terminal
const string SELECTION_LCD = "ATT LCD Select";
const string TRADE_LCD = "ATT LCD Trade";

// Cargo Container Names for this trade terminal
const string PUBLIC_CARGO = "Trade Container";
const string INVENTORY_CARGO = "ATT Cargo Storage";

// argument references
const string TRADE = "Trade";   // initiate a trade (based on selection)
const string SWITCHUP = "SwitchUp"; // swap to a different trade
const string SWITCHDN = "SwitchDown";


// Item Names Reference
const string TYPE_PREFIX = "MyObjectBuilder_";

string[] ITEM_TYPE = {
                     "Ore",
                     "Ingot",
                     "Component",
                     "PhysicalGunObject"
                     };

string[] COMPONENT = {
                     "Construction",
                     "MetalGrid",
                     "InteriorPlate",
                     "SteelPlate",
                     "SmallTube",
                     "LargeTube",
                     "BulletproofGlass",
                     "Reactor",
                     "Thrust",
                     "GravityGenerator",
                     "Medical",
                     "RadioCommunication",
                     "Detector",
                     "SolarCell",
                     "PowerCell"
                     };


string[] TOOL =      {
                     "AutomaticRifleItem",
                     "WelderItem",
                     "AngleGrinderItem",
                     "HandDrillItem",
                     "AutomaticRifle2Item",
                     "Welder2Item",
                     "AngleGrinder2Item",
                     "HandDrill2Item"
                     };

string[] MATERIAL = {
                     "Stone",
                     "Iron",
                     "Nickel",
                     "Cobalt",
                     "Magnesium",
                     "Silicon",
                     "Silver",
                     "Gold",
                     "Platinum",
                     "Uranium",
                     "Ice"
                     };

// Variables
int tradeSelection = 0; // current trade selection

// trade class (defines what type of item to trade and the exchange amount)
public class Trade
{
       // input and output trade resource reference (index of resource string)
       public string inputItemType; // actual component or item
       public string outputItemType;
       public string inputItem; // actual component or item name
       public string outputItem;
       // input amount for a given output amount
       public float inputAmnt;
       public float outputAmnt;

       public Trade(string nT, string n, float ia, string oT, string o, float io)
       {
              inputItemType = nT;
              outputItemType = oT;
              inputItem = n;
              outputItem = o;
              inputAmnt = ia;
              outputAmnt = io;
       }
}


// List of available trades
List <Trade> myTrade = new List<Trade>();

public Program()
{
       // Add in the current trades
       myTrade.Add(new Trade("Ingot","Gold",1,"Ingot","Uranium",2)); // trade 1 kg Gold for 2 kg Uranium
       myTrade.Add(new Trade("Ingot","Gold",1,"Ingot","Magnesium",2)); // trade 1 kg Gold for 2 kg Magnesium
       myTrade.Add(new Trade("Ingot","Platinum",1,"Ingot","Uranium",2)); // 1 kg Platinum for 4 kg Uranium
       myTrade.Add(new Trade("Ingot","Platinum",1,"Ingot","Magnesium",2)); // trade 1 kg Platinum for 3 kg Magnesium
}

public void Main(string argument, UpdateType updateSource)
{
       // get inventory and lcd blocks
       IMyCargoContainer thePublicContainer = GridTerminalSystem.GetBlockWithName(PUBLIC_CARGO) as IMyCargoContainer;
       //IMyInventory publicContainer = GridTerminalSystem.GetBlockWithName(PUBLIC_CARGO) as IMyInventory;
       // get trading inventory
       IMyCargoContainer theAttContainer = GridTerminalSystem.GetBlockWithName(INVENTORY_CARGO) as IMyCargoContainer;
       //IMyInventory attContainer = GridTerminalSystem.GetBlockWithName(INVENTORY_CARGO) as IMyInventory;
       // get trade selection lcd
       IMyTextPanel selectionLCD = GridTerminalSystem.GetBlockWithName(SELECTION_LCD) as IMyTextPanel; // get selection LCD
       // get trade display lcd
       IMyTextPanel tradeLCD = GridTerminalSystem.GetBlockWithName(TRADE_LCD) as IMyTextPanel;

       // grab the inventories out of the containers
       IMyInventory publicContainer = thePublicContainer.GetInventory(0);
       IMyInventory attContainer = theAttContainer.GetInventory(0);

       // get a list of public items
       List<MyInventoryItem> publicItems = new List<MyInventoryItem>();
       publicContainer.GetItems(publicItems);

       // get a list of ATT stored items
       List<MyInventoryItem> attItems = new List<MyInventoryItem>();
       attContainer.GetItems(attItems);


       string itemsText = "Items\n";
       // display the list to the screen
       for(int i = 0; i < publicItems.Count; i++)
       {
              itemsText += publicItems[i].Type.TypeId + ", ";
              itemsText += publicItems[i].Type.SubtypeId + ", ";
              itemsText += publicItems[i].Amount + "\n";
              Echo(itemsText);
       }
       //selectionLCD.WritePublicText(itemsText);
       //selectionLCD.ShowPublicTextOnScreen();



       // Display the current available trades
       string tradesText = " - - - Available Trades - - - \n";
       for(int i = 0; i < myTrade.Count; i++)
       {
              tradesText += myTrade[i].inputAmnt + "x ";
              tradesText += myTrade[i].inputItem + " ";
              tradesText += myTrade[i].inputItemType + " -> ";
              tradesText += myTrade[i].outputAmnt + "x ";
              tradesText += myTrade[i].outputItem + " ";
              tradesText += myTrade[i].outputItemType + "\n";
       }

       tradeLCD.WritePublicText(tradesText);
       tradeLCD.ShowPublicTextOnScreen();

       // Perform a trade
       if(string.Equals(argument, TRADE))
       {

              // calculated maximum number of trades at the given rate possible
              // from either the att inventory or the public (input) inventory
              float maxOutputTrades = 0;
              float maxInputTrades = 0;

              int publicItemIndex = 0;
              int attItemIndex = 0; // item transfer indices

              //float inputToOutputRatio = myTrade[tradeSelection].inputAmnt / myTrade[tradeSelection].outputAmnt;

              // find the number of public items matching the input amounts for the selected trade
              for(int i = 0; i < publicItems.Count; i++)
              {
                     if(string.Equals(publicItems[i].Type.TypeId,
                            TYPE_PREFIX + myTrade[tradeSelection].inputItemType) &&
                            string.Equals(publicItems[i].Type.SubtypeId,
                            myTrade[tradeSelection].inputItem))
                     {
                            publicItemIndex = i;
                            // acquire total number of this item available
                            float amnt = (float)publicItems[i].Amount;
                            // calculate the maximum possible number of trades
                            maxInputTrades = amnt / myTrade[tradeSelection].inputAmnt;

                            Echo("Max # input trades = " + maxInputTrades);
                     }
              }


              // find the number of att items matching the input amounts for the selected trade
              for(int i = 0; i < attItems.Count; i++)
              {
                     if(string.Equals(attItems[i].Type.TypeId,
                            TYPE_PREFIX + myTrade[tradeSelection].outputItemType) &&
                            string.Equals(attItems[i].Type.SubtypeId,
                            myTrade[tradeSelection].outputItem))
                     {
                            attItemIndex = i;
                            // acquire total number of this item available
                            float amnt = (float)attItems[i].Amount;
                            // calculate the maximum possible number of trades
                            maxOutputTrades = amnt / myTrade[tradeSelection].outputAmnt;

                            Echo("Max # output trades = " + maxOutputTrades);
                     }
              }

              // Take the lesser of the two maximum trade amounts
              // and perform a trade accordingly
              float tradeAmnt = 0;
              if(maxOutputTrades > 0 && maxOutputTrades <= maxInputTrades)
              {
                     tradeAmnt = maxOutputTrades;
              } else if(maxInputTrades > 0 && maxInputTrades <= maxOutputTrades)
              {
                     tradeAmnt = maxInputTrades;
              }

              Echo("Trading " + tradeAmnt + " times");


              // Perform the inventory transfer
              // transfer from public cargo container to the att storage
              publicContainer.TransferItemTo(attContainer, publicItemIndex, attItems.Count + 1, true, (VRage.MyFixedPoint)tradeAmnt*myTrade[tradeSelection].inputAmnt);
              // transfer from att cargo container to the public storage
              attContainer.TransferItemTo(publicContainer, attItemIndex, publicItems.Count + 1, true, (VRage.MyFixedPoint)tradeAmnt*myTrade[tradeSelection].outputAmnt);
       }
       // Otherwise, consider updating the current Trade Selection
       else
       {
              if(string.Equals(argument, SWITCHUP))
              {
                     if(tradeSelection < myTrade.Count - 1)
                     {
                            tradeSelection++;
                     }
              }
              else if(string.Equals(argument, SWITCHDN))
              {
                     if(tradeSelection > 0)
                     {
                            tradeSelection--;
                     }
              }

              // display current trade selection on the screen
              string selectionText = "Current Selected \nTrade:\n\n";
              selectionText += myTrade[tradeSelection].inputAmnt + "x ";
              selectionText += myTrade[tradeSelection].inputItem + " ";
              selectionText += myTrade[tradeSelection].inputItemType + "\nFor: \n";
              selectionText += myTrade[tradeSelection].outputAmnt + "x ";
              selectionText += myTrade[tradeSelection].outputItem + " ";
              selectionText += myTrade[tradeSelection].outputItemType + "\n";

              selectionLCD.WritePublicText(selectionText);
              selectionLCD.ShowPublicTextOnScreen();
       }


}




/*



public void Save()
{

    // Called when the program needs to save its state. Use
    // this method to save your state to the Storage field
    // or some other means.
    //
    // This method is optional and can be removed if not
    // needed.

}

*/
