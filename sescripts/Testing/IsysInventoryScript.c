
// Isy's Inventory Manager
// ===================
// Version: 2.3.3
// Date: 2019-03-10

//  =======================================================================================
//                                                                            --- Configuration ---
//  =======================================================================================

// --- Sorting ---
// =======================================================================================

// Define the keyword a cargo container has to contain in order to be recognized as a container of the given type.
const string oreContainerKeyword = "Ores";
const string ingotContainerKeyword = "Ingots";
const string componentContainerKeyword = "Components";
const string toolContainerKeyword = "Tools";
const string ammoContainerKeyword = "Ammo";
const string bottleContainerKeyword = "Bottles";

// Keyword an inventory has to contain to be skipped by the sorting (= no items will be taken out)
const string lockedContainerKeyword = "Locked";

// Keyword for connectors to disable sorting of a grid, that is docked to that connector.
// This also disables the usage of refineries, arc furnaces and assemblers on that grid.
// Special containers, reactors and O2/H2 generators will still be filled.
string noSortingKeyword = "[No Sorting]";

// Balance items between containers of the same type? This will result in an equal amount of all items in all containers of that type.
bool balanceTypeContainers = false;

// Show a fill level in the container's name?
bool showFillLevel = true;

// Auto assign new containers if a type is full or not present?
bool autoAssignContainers = true;

// Auto assign tool, ammo and bottle containers as one?
bool toolsAmmoBottlesInOne = true;

// Fill bottles before storing them in the bottle container?
bool fillBottles = true;


// --- Autocrafting ---
// =======================================================================================

// Enable autocrafting or autodisassembling (disassembling will disassemble everything above the wanted amounts)
// All assemblers will be used. To use one manually, add the manualMachineKeyword to it (by default: "!manual")
bool enableAutocrafting = true;
bool enableAutodisassembling = false;

// A LCD with the keyword "Autocrafting" is required where you can set the wanted amount!
// This has multi LCD support. Just append numbers after the keyword, like: "LCD Autocrafting 1", "LCD Autocrafting 2", ..
string autocraftingKeyword = "Autocrafting";

// Add the header to every screen when using multiple autocrafting LCDs?
bool headerOnEveryScreen = false;

// Margins for assembling or disassembling items in percent based on the wanted amount (default: 0 = exact value).
// Examples:
// assembleMargin = 5 with a wanted amount of 100 items will only produce new items, if less than 95 are available.
// disassembleMargin = 10 with a wanted amount of 1000 items will only disassemble items if more than 1100 are available.
double assembleMargin = 0;
double disassembleMargin = 0;

// To hide certain items from the LCD, simply set their wanted amount to a negative value (e.g.: -1 or -500). These items will be moved
// to the custom data of the first autocrafting LCD. To let them reappear on the LCD again, remove the entry from the custom data.

// Sort the assembler queue based on the most needed components?
bool sortAssemblerQueue = true;

// Autocraft ingots in survival kits if stone is present?
bool enableIngotCrafting = true;


// --- Special Loadout Containers ---
// =======================================================================================

// Keyword an inventory has to contain to be filled with a special loadout (see in it's custom data after you renamed it!)
// Special containers will be filled with your wanted amount of items and never be drained by the auto sorting!
const string specialContainerKeyword = "Special";

// Are special containers allowed to 'steal' items from other special containers with a lower priority?
bool allowSpecialSteal = true;


// --- Ore Balancing ---
// =======================================================================================

// By enabling ore balancing, the script will manage the filling with ores and the queue order of all refinieres.
// To still use a refinery manually, add the manualMachineKeyword to it (by default: "!manual")
bool enableOreBalancing = true;

// Value ore priority
// This will move iron, nickel and cobalt ores to basic refineries if there are more valuable ores, only large refineries can process.
// If the valuable ore is processed, the other ores are spread to all refineries again.
bool enableValueOrePriority = true;

// Process iron, nickel and cobalt ONLY in basic refineries and NOT in large refineries? (this overrides value ore priority mode!)
bool enableBasicOreSpecialization = false;

// If a large refinery contains this keyword, it acts like an basic refinery, is used for the two modes above and will only
// process iron, nickel and coblat.
string actBasicKeyword = "!basic";

// Process stone in refineries?
bool enableStoneProcessing = true;

// Sort the refinery queue based on the most needed ingots?
bool sortRefiningQueue = true;


// --- Ice Balancing ---
// =======================================================================================

// Enable balancing of ice in O2/H2 generators?
// All O2/H2 generators will be used. To use one manually, add the manualMachineKeyword to it (by default: "!manual")
bool enableIceBalancing = true;

// Put ice into O2/H2 generators that are turned off? (default: false)
bool fillOfflineGenerators = false;

// Ice fill level in percent in order to be able to fill bottles? (default: 95)
// Note: O2/H2 generators will pull more ice automatically if value is below 60%
double iceFillLevelPercentage = 95;


// --- Uranium Balancing ---
// =======================================================================================

// Enable balancing of uranium in reactors? (Note: conveyors of reactors are turned off to stop them from pulling more)
// All reactors will be used. To use one manually, add the manualMachineKeyword to it (by default: "!manual")
bool enableUraniumBalancing = true;

// Put uranium into reactors that are turned off? (default: false)
bool fillOfflineReactors = false;

// Amount of uranium in each reactor? (default: 100 for large grid reactors, 25 for small grid reactors)
double uraniumAmountLargeGrid = 100;
double uraniumAmountSmallGrid = 25;


// --- Assembler Cleanup ---
// =======================================================================================

// This cleans up assemblers, if their inventory is too full and puts the contents back into a cargo container.
bool enableAssemblerCleanup = true;

// Set fill level in percent when the assembler should be cleaned up
double assemblerFillLevelPercentage = 50;


// --- Internal item sorting ---
// =======================================================================================

// Sort the items inside all containers?
bool enableInternalSorting = true;

// Internal sorting pattern. Always combine one of each category, e.g.: 'Ad' for descending item amount (from highest to lowest)
// 1. Quantifier:
// A = amount
// N = name
// T = type (alphabetical)
// X = type (number of items)

// 2. Direction:
// a = ascending
// d = descending

string sortingPattern = "Na";

// This can also be set per inventory. Just use '(sort:PATTERN)' in the block's name
// Example: Small Cargo Container 3 (sort:Ad)


// --- LCD panels ---
// =======================================================================================

// To display the main script informations, add the following keyword to any LCD name (default: !IIM).
// You can enable or disable specific informations on the LCD by editing its custom data.
string mainLCDKeyword = "!IIM";

// To display current item amounts of different types, add the following keyword to any LCD name
// and follow the on screen instructions.
string inventoryLCDKeyword = "!inventory";

// To display all current warnings and problems, add the following keyword to any LCD name (default: !warnings).
string warningsLCDKeyword = "!warnings";

// To display the script performance (PB terminal output), add the following keyword to any LCD name (default: !performance).
string performanceLCDKeyword = "!performance";


// --- Settings for enthusiasts ---
// =======================================================================================

// Script cycle time in seconds (default: 7).
double scriptExecutionTime = 7;

// Script mode: "ship", "station" or blank for autodetect
string scriptMode = "";

// Protect type containers when docking to another grid running the script?
bool protectTypeContainers = true;

// If you want to use a machine manually, append the keyword to it.
// This works for assemblers, refineries, arc furances, reactors and O2/H2 generators
string manualMachineKeyword = "!manual";

// Ore yield multiplier based on stone (for sorting the refining queue)
// Basically: to get 1 platinum, 180x the ore (and time) is needed compared to getting 1 stone ingot (aka gravel)
// Result: 1 platinum is worth 180 stone. If you have 1 platinum and 0 gravel and both ore types in the refinery,
// the script will refine stone first until it hits 180 gravel before platinum is queued at the front again
Dictionary<string, double> oreYieldDict = new Dictionary<string, double>()
{
	{ "Stone", 1 },
	{ "Iron", 1.28 },
	{ "Silicon", 1.28 },
	{ "Nickel", 2.25 },
	{ "Cobalt", 3 },
	{ "Silver", 9 },
	{ "Gold", 90 },
	{ "Magnesium", 128.5 },
	{ "Uranium", 128.5 },
	{ "Platinum", 180 }
};

//  =======================================================================================
//                                                                      --- End of Configuration ---
//                                                        Don't change anything beyond this point!
//  =======================================================================================


List<IMyTerminalBlock>ǫ=new List<IMyTerminalBlock>();List<IMyTerminalBlock>Ǭ=new List<IMyTerminalBlock>();List<
IMyTerminalBlock>ǭ=new List<IMyTerminalBlock>();List<IMyTerminalBlock>Ǯ=new List<IMyTerminalBlock>();List<IMyShipConnector>ǯ=new List<
IMyShipConnector>();List<IMyRefinery>ǰ=new List<IMyRefinery>();List<IMyRefinery>Ǳ=new List<IMyRefinery>();List<IMyTerminalBlock>ǲ=new
List<IMyTerminalBlock>();List<IMyTerminalBlock>ǳ=new List<IMyTerminalBlock>();List<IMyAssembler>Ǵ=new List<IMyAssembler>();
List<IMyAssembler>Ƕ=new List<IMyAssembler>();List<IMyAssembler>ǵ=new List<IMyAssembler>();List<IMyGasGenerator>Ƿ=new List<
IMyGasGenerator>();List<IMyReactor>Ș=new List<IMyReactor>();List<IMyTextPanel>ș=new List<IMyTextPanel>();List<string>Ț=new List<string>
();HashSet<IMyCubeGrid>ț=new HashSet<IMyCubeGrid>();List<IMyTerminalBlock>Ȝ=new List<IMyTerminalBlock>();List<
IMyTerminalBlock>ȝ=new List<IMyTerminalBlock>();List<IMyTerminalBlock>Ȟ=new List<IMyTerminalBlock>();List<IMyTerminalBlock>ȟ=new List<
IMyTerminalBlock>();List<IMyTerminalBlock>Ƞ=new List<IMyTerminalBlock>();List<IMyTerminalBlock>ȡ=new List<IMyTerminalBlock>();List<
IMyTerminalBlock>Ȣ=new List<IMyTerminalBlock>();string[]ȣ={oreContainerKeyword,ingotContainerKeyword,componentContainerKeyword,
toolContainerKeyword,ammoContainerKeyword,bottleContainerKeyword};string Ȥ=specialContainerKeyword.ToLower();string ȥ=lockedContainerKeyword
.ToLower();string ȧ="";bool ȴ=false;IMyTerminalBlock Ȩ;int ȩ=0;int Ȫ=0;int ȫ=0;string Ȭ="";string[]ȭ={"/","-","\\","|"};
int Ȯ=0;List<IMyTextPanel>ȯ=new List<IMyTextPanel>();string[]Ȱ={"showContainerStats=true","showManagedBlocks=true",
"showLastAction=true"};string ĥ;HashSet<string>ȱ=new HashSet<string>();HashSet<string>Ȳ=new HashSet<string>();List<IMyTextPanel>ȳ=new List<
IMyTextPanel>();int ȵ=0;int Ȧ=0;int ȗ=1;int Ȇ=0;bool ǹ=true;bool Ǻ=true;bool ǻ=true;string Ǽ="itemID;blueprintID;volume";Dictionary<
string,string>ǽ=new Dictionary<string,string>(){{"oreContainer",oreContainerKeyword},{"ingotContainer",ingotContainerKeyword},
{"componentContainer",componentContainerKeyword},{"toolContainer",toolContainerKeyword},{"ammoContainer",
ammoContainerKeyword},{"bottleContainer",bottleContainerKeyword},{"lockedContainer",lockedContainerKeyword},{"specialContainer",
specialContainerKeyword},{"oreBalancing","true"},{"iceBalancing","true"},{"uraniumBalancing","true"}};string Ǿ="Isy's Autocrafting";string ǿ=
"Remove a line to show this item on the LCD again!";char[]Ȁ={'=','>','<'};List<String>ȁ=new List<string>{"Uranium","Silicon","Silver","Gold","Platinum","Magnesium","Iron",
"Nickel","Cobalt","Scrap"};List<String>Ȃ=new List<string>{"Uranium","Silicon","Silver","Gold","Platinum","Magnesium"};List<
String>ȃ=new List<string>{"Iron","Nickel","Cobalt"};const string Ȅ="MyObjectBuilder_";const string ȅ="Ore";const string ȇ=
"Ingot";const string ȕ="Component";const string Ȉ="AmmoMagazine";const string ȉ="OxygenContainerObject";const string Ȋ=
"GasContainerObject";const string ȋ="PhysicalGunObject";const string Ȍ=Ȅ+"BlueprintDefinition/";SortedSet<MyDefinitionId>ȍ=new SortedSet<
MyDefinitionId>(new Ũ());SortedSet<string>Ȏ=new SortedSet<string>();SortedSet<string>ȏ=new SortedSet<string>();SortedSet<string>Ȑ=new
SortedSet<string>();SortedSet<string>ȑ=new SortedSet<string>();SortedSet<string>Ȓ=new SortedSet<string>();SortedSet<string>ȓ=new
SortedSet<string>();SortedSet<string>Ȕ=new SortedSet<string>();Dictionary<MyDefinitionId,double>Ȗ=new Dictionary<MyDefinitionId,
double>();Dictionary<MyDefinitionId,double>Ǫ=new Dictionary<MyDefinitionId,double>();Dictionary<MyDefinitionId,MyDefinitionId>
ƺ=new Dictionary<MyDefinitionId,MyDefinitionId>();Dictionary<MyDefinitionId,MyDefinitionId>Ƹ=new Dictionary<
MyDefinitionId,MyDefinitionId>();Dictionary<MyDefinitionId,VRage.MyFixedPoint>ƻ=new Dictionary<MyDefinitionId,VRage.MyFixedPoint>();
Dictionary<string,MyDefinitionId>Ƽ=new Dictionary<string,MyDefinitionId>();Dictionary<string,string>ƽ=new Dictionary<string,string
>();bool ƾ=false;string ƿ="station_mode;\n";string ǀ="ship_mode;\n";string ǁ="[PROTECTED] ";string ǂ="";string ǃ="";
string Ǆ="";int ǅ=3;double ǆ=0;string Ǉ="Performance information is generated..";List<IMyTextPanel>ǈ=new List<IMyTextPanel>();
double ǐ,ǉ;int Ǌ=0;List<int>ǋ=new List<int>(new int[100]);List<double>ǌ=new List<double>(new double[100]);Dictionary<string,
int>Ǎ=new Dictionary<string,int>();string[]ǎ={"","Find new items","Get item volume","Create item lists","Assign containers"
,"Learn unknown blueprints","Fill special containers","Sort items","Container balancing","Internal sorting",
"Add fill level to names","Get global item amount","Get assembler queue","Autocrafting","Sort assembler queue","Clean up assemblers",
"Ore balancing","Ice balancing","Uranium balancing"};Program(){Echo("Initializing script..\n");assembleMargin/=100;disassembleMargin/=
100;Ȧ=(int)(scriptExecutionTime*60/18);Runtime.UpdateFrequency=UpdateFrequency.Update100;}void Main(string Ƭ){try{if(ǹ){if(
DateTime.Now.Second%2==0){Echo("Initializing script.\n");}else{Echo("Initializing script..\n");}Echo("Getting base grid..");ź(Me
.CubeGrid);Echo("Getting inventory blocks..");ƶ();Echo("Loading saved items..");if(!ƀ()){Echo("-> No assembler found!");
Echo("-> Can't check saved blueprints..");Echo("Restarting..");return;}Echo("Checking blueprints..");foreach(var Ã in ȍ){Ƥ(Ã
);}Echo("Checking type containers..");Ǥ();Echo("Setting script mode..");if(scriptMode=="station"){ƾ=true;}else if(Ÿ.
IsStatic&&scriptMode!="ship"){ƾ=true;}Me.CustomData=(ƾ?ƿ:ǀ)+Me.CustomData.Replace(ƿ,"").Replace(ǀ,"");ǹ=false;Runtime.
UpdateFrequency=UpdateFrequency.Update1;}if(Ƭ!=""){Ǆ=Ƭ.ToLower();ȗ=1;ǃ="";ǅ=3;}if(ȵ<Ȧ){ȵ++;return;}else{if(Ǻ){ƶ();Ǻ=false;return;}Ȇ++;
if(Ȇ>=5){Ȇ=0;d();return;}if(ǻ){Ğ();ģ();Ħ();ǻ=false;return;}ȵ=0;ǻ=true;Ǻ=true;}if(!ƾ)ư();if(ƹ(Ǆ))return;if(ȗ==1){ž();}if(ȗ
==2){Î();}if(ȗ==3){ƃ();}if(ȗ==4){ǖ();if(autoAssignContainers)ǧ();}if(ȗ==5){Ɣ();}if(ȗ==6){if(Ȣ.Count!=0)ɧ();}if(ȗ==7){Ǚ(ȅ,Ȝ
,oreContainerKeyword);Ǚ(ȇ,ȝ,ingotContainerKeyword);Ǚ(ȕ,Ȟ,componentContainerKeyword);Ǚ(ȋ,ȟ,toolContainerKeyword);Ǚ(Ȉ,Ƞ,
ammoContainerKeyword);Ǚ(ȉ,ȡ,bottleContainerKeyword);Ǚ(Ȋ,ȡ,bottleContainerKeyword);}if(ȗ==8){if(balanceTypeContainers)ɇ();}if(ȗ==9){if(
enableInternalSorting){ɵ();}}if(ȗ==10){ɫ(Ǯ);ɫ(Ȣ);}if(ȗ==11){Ƙ();}if(ȗ==12){if(enableAutocrafting||enableAutodisassembling)ơ();}if(ȗ==13){if(
enableAutocrafting||enableAutodisassembling)ʅ();}if(ȗ==14){if(sortAssemblerQueue)ɗ();}if(ȗ==15){if(enableAssemblerCleanup)ɔ(
assemblerFillLevelPercentage);if(enableIngotCrafting)Ɂ();}if(ȗ==16){if(enableOreBalancing){ƌ("oreBalancing","true");ɒ();}else if(!enableOreBalancing
&&Ɗ("oreBalancing")=="true"){ƌ("oreBalancing","false");foreach(IMyRefinery Ǐ in ǰ){Ǐ.UseConveyorSystem=true;}}}if(ȗ==17){
if(enableIceBalancing){ƌ("iceBalancing","true");ĕ();}else if(!enableIceBalancing&&Ɗ("iceBalancing")=="true"){ƌ(
"iceBalancing","false");foreach(IMyGasGenerator õ in Ƿ){õ.UseConveyorSystem=true;}}}if(ȗ==18){if(enableUraniumBalancing){ƌ(
"uraniumBalancing","true");Ă();}else if(!enableUraniumBalancing&&Ɗ("uraniumBalancing")=="true"){ƌ("uraniumBalancing","false");foreach(
IMyReactor Ĩ in Ș){Ĩ.UseConveyorSystem=true;}}}O();if(ȗ>=18){ȗ=1;ȱ=new HashSet<string>(Ȳ);Ȳ.Clear();if(ȱ.Count==0)ĥ=null;}else{ȗ++
;}Ȯ=Ȯ>=3?0:Ȯ+1;}catch(Exception e){string J=e+" \n\n";J+="The error occured while executing the following script step:\n"
+ǎ[ȗ]+" (ID: "+ȗ+")";Ğ(J);throw new Exception(J);}}bool ƹ(string Ƭ){if(Ƭ.Contains("pauseThisPB")){Echo(
"Script execution paused!\n");var Ʒ=Ƭ.Split(';');if(Ʒ.Length==3){Echo("Found:");Echo("'"+Ʒ[1]+"'");Echo("on grid:");Echo("'"+Ʒ[2]+"'");Echo(
"also running the script.\n");Echo("Type container protection: "+(protectTypeContainers?"ON":"OFF")+"\n");Echo(
"Everything else is managed by the other script.");}return true;}bool ƭ=true;bool Ʈ=true;bool Ư=false;if(Ƭ!="reset"&&Ƭ!="msg"){if(!Ƭ.Contains(" on")&&!Ƭ.Contains(" off")
&&!Ƭ.Contains(" toggle"))return false;if(Ƭ.Contains(" off"))Ʈ=false;if(Ƭ.Contains(" toggle"))Ư=true;}if(Ƭ=="reset"){Ɩ();
return true;}else if(Ƭ=="msg"){}else if(Ƭ.Contains("assigncontainers")){ǂ="Auto container assigment";if(Ư)Ʈ=!
autoAssignContainers;autoAssignContainers=Ʈ;}else if(Ƭ.Contains("fillbottles")){ǂ="Bottle filling";if(Ư)Ʈ=!fillBottles;fillBottles=Ʈ;}else
if(Ƭ.Contains("autocrafting")){ǂ="Autocrafting";if(Ư)Ʈ=!enableAutocrafting;enableAutocrafting=Ʈ;}else if(Ƭ.Contains(
"autodisassembling")){ǂ="Auto disassembling";if(Ư)Ʈ=!enableAutodisassembling;enableAutodisassembling=Ʈ;}else if(Ƭ.Contains(
"sortassemblerqueue")){ǂ="Assembler queue sorting";if(Ư)Ʈ=!sortAssemblerQueue;sortAssemblerQueue=Ʈ;}else if(Ƭ.Contains("assemblercleanup")){
ǂ="Assembler cleanup";if(Ư)Ʈ=!enableAssemblerCleanup;enableAssemblerCleanup=Ʈ;}else if(Ƭ.Contains("orebalancing")){ǂ=
"Ore balancing";if(Ư)Ʈ=!enableOreBalancing;enableOreBalancing=Ʈ;}else if(Ƭ.Contains("arcpriority")){ǂ="Arc priority mode";if(Ư)Ʈ=!
enableValueOrePriority;enableValueOrePriority=Ʈ;}else if(Ƭ.Contains("arcspecialization")){ǂ="Arc specialization mode";if(Ư)Ʈ=!
enableBasicOreSpecialization;enableBasicOreSpecialization=Ʈ;}else if(Ƭ.Contains("stoneprocessing")){ǂ="Stone processing";if(Ư)Ʈ=!
enableStoneProcessing;enableStoneProcessing=Ʈ;}else if(Ƭ.Contains("sortrefiningqueue")){ǂ="Refining queue sorting";if(Ư)Ʈ=!sortRefiningQueue;
sortRefiningQueue=Ʈ;}else if(Ƭ.Contains("icebalancing")){ǂ="Ice balancing";if(Ư)Ʈ=!enableIceBalancing;enableIceBalancing=Ʈ;}else if(Ƭ.
Contains("uraniumbalancing")){ǂ="Uranium balancing";if(Ư)Ʈ=!enableUraniumBalancing;enableUraniumBalancing=Ʈ;}else if(Ƭ.Contains(
"internalsorting")){ǂ="Internal sorting";if(Ư)Ʈ=!enableInternalSorting;enableInternalSorting=Ʈ;}else if(Ƭ.Contains("containerbalancing"))
{ǂ="Container balancing";if(Ư)Ʈ=!balanceTypeContainers;balanceTypeContainers=Ʈ;}else{ƭ=false;}if(ƭ){if(ǃ=="")ǃ=ǂ+
" temporarily "+(Ʈ?"enabled":"disabled")+"!\n";Echo(ǃ);Echo("Continuing in "+ǅ+" seconds..");Ǆ="msg";if(ǅ==0){scriptExecutionTime=ǆ;ǆ=0
;ǂ="";ǃ="";Ǆ="";ǅ=3;}else{if(ǆ==0){ǆ=scriptExecutionTime;scriptExecutionTime=1000;}ǅ-=1;}}return ƭ;}void ư(){List<
IMyProgrammableBlock>Ʊ=new List<IMyProgrammableBlock>();GridTerminalSystem.GetBlocksOfType(Ʊ,ś=>ś!=Me);if(Ǆ=="pauseThisPB"||Ǆ==""){Ǆ="";
foreach(var Ʋ in Ʊ){if(Ʋ.CustomData.Contains(ƿ)||(Ʋ.CustomData.Contains(ǀ)&&Ě(Ʋ)<Ě(Me))){Ǆ="pauseThisPB;"+Ʋ.CustomName+";"+Ʋ.
CubeGrid.CustomName;foreach(var Æ in Ǯ){if(protectTypeContainers&&!Æ.CustomName.Contains(ǁ))Æ.CustomName=ǁ+Æ.CustomName;}return;
}}if(Ǆ==""){foreach(var Æ in Ǯ){Æ.CustomName=Æ.CustomName.Replace(ǁ,"");}}}}void Ƴ(IMyCubeGrid Ŭ,bool Ř=false){ț.Add(Ŭ);
List<IMyShipConnector>ƴ=new List<IMyShipConnector>();List<IMyMotorStator>ū=new List<IMyMotorStator>();List<IMyPistonBase>ř=
new List<IMyPistonBase>();GridTerminalSystem.GetBlocksOfType<IMyShipConnector>(ƴ,Ë=>Ë.CubeGrid==Ŭ&&Ë.Status==
MyShipConnectorStatus.Connected);GridTerminalSystem.GetBlocksOfType<IMyMotorStator>(ū,Ś=>Ś.CubeGrid==Ŭ&&Ś.IsAttached);GridTerminalSystem.
GetBlocksOfType<IMyPistonBase>(ř,ś=>ś.CubeGrid==Ŭ&&ś.IsAttached);foreach(var Ƶ in ƴ){if(!ț.Contains(Ƶ.OtherConnector.CubeGrid)){Ƴ(Ƶ.
OtherConnector.CubeGrid);}}foreach(var Ŝ in ū){if(!ț.Contains(Ŝ.TopGrid)){Ƴ(Ŝ.TopGrid);}}foreach(var ŝ in ř){if(!ț.Contains(ŝ.TopGrid)
){Ƴ(ŝ.TopGrid);}}}void ƶ(){Ž(Ÿ,true);GridTerminalSystem.SearchBlocksOfName(oreContainerKeyword,Ȝ,Ë=>Ë.HasInventory&&Ż.
Contains(Ë.CubeGrid));GridTerminalSystem.SearchBlocksOfName(ingotContainerKeyword,ȝ,Ë=>Ë.HasInventory&&Ż.Contains(Ë.CubeGrid));
GridTerminalSystem.SearchBlocksOfName(componentContainerKeyword,Ȟ,Ë=>Ë.HasInventory&&Ż.Contains(Ë.CubeGrid));GridTerminalSystem.
SearchBlocksOfName(toolContainerKeyword,ȟ,Ë=>Ë.HasInventory&&Ż.Contains(Ë.CubeGrid));GridTerminalSystem.SearchBlocksOfName(
ammoContainerKeyword,Ƞ,Ë=>Ë.HasInventory&&Ż.Contains(Ë.CubeGrid));GridTerminalSystem.SearchBlocksOfName(bottleContainerKeyword,ȡ,Ë=>Ë.
HasInventory&&Ż.Contains(Ë.CubeGrid));foreach(var Æ in Ȣ){if(!Æ.CustomName.ToLower().Contains(Ȥ))Æ.CustomData="";}GridTerminalSystem
.SearchBlocksOfName(specialContainerKeyword,Ȣ,Ë=>Ë.HasInventory);Ǣ(Ȝ);Ǣ(ȝ);Ǣ(Ȟ);Ǣ(ȟ);Ǣ(Ƞ);Ǣ(ȡ);Ǣ(Ȣ);Ǯ.Clear();Ǯ.AddRange(
Ȝ);Ǯ.AddRange(ȝ);Ǯ.AddRange(Ȟ);Ǯ.AddRange(ȟ);Ǯ.AddRange(Ƞ);Ǯ.AddRange(ȡ);ț.Clear();GridTerminalSystem.GetBlocksOfType<
IMyShipConnector>(ǯ,Ë=>Ż.Contains(Ë.CubeGrid)&&Ë.CustomName.Contains(noSortingKeyword));if(ǯ.Count>0){foreach(var Ƶ in ǯ){if(Ƶ.Status!=
MyShipConnectorStatus.Connected)continue;ț.Add(Ƶ.CubeGrid);Ƴ(Ƶ.OtherConnector.CubeGrid);ț.Remove(Ƶ.CubeGrid);}}GridTerminalSystem.
GetBlocksOfType<IMyRefinery>(ǰ,Ś=>!ț.Contains(Ś.CubeGrid)&&!Ś.CustomName.ToLower().Contains(Ȥ)&&!Ś.CustomName.Contains(
manualMachineKeyword)&&Ś.IsWorking);GridTerminalSystem.GetBlocksOfType<IMyRefinery>(Ǳ,Ś=>!ț.Contains(Ś.CubeGrid)&&!Ś.CustomName.ToLower().
Contains(ȥ));ǲ.Clear();ǳ.Clear();foreach(IMyRefinery Ǐ in ǰ){Ǐ.UseConveyorSystem=false;if(Ǐ.BlockDefinition.SubtypeId==
"Blast Furnace"||Ǐ.CustomName.ToLower().Contains(actBasicKeyword.ToLower())){ǳ.Add(Ǐ);}else{ǲ.Add(Ǐ);}}GridTerminalSystem.
GetBlocksOfType<IMyAssembler>(Ǵ,o=>!ț.Contains(o.CubeGrid)&&!o.CustomName.Contains(manualMachineKeyword)&&o.IsWorking);
GridTerminalSystem.GetBlocksOfType<IMyAssembler>(Ƕ,o=>!ț.Contains(o.CubeGrid)&&!o.CustomName.ToLower().Contains(ȥ));GridTerminalSystem.
GetBlocksOfType<IMyAssembler>(ǵ,ǡ=>!ț.Contains(ǡ.CubeGrid)&&ǡ.BlockDefinition.SubtypeId.Contains("Survival")&&!ǡ.CustomName.Contains(
manualMachineKeyword)&&ǡ.IsWorking);GridTerminalSystem.GetBlocksOfType<IMyGasGenerator>(Ƿ,Ë=>!Ë.CustomName.ToLower().Contains(Ȥ)&&!Ë.
CustomName.ToLower().Contains(manualMachineKeyword)&&Ë.IsFunctional);if(!fillOfflineGenerators){Ƿ.RemoveAll(Ë=>!Ë.Enabled);}
GridTerminalSystem.GetBlocksOfType<IMyReactor>(Ș,Ë=>!Ë.CustomName.ToLower().Contains(Ȥ)&&!Ë.CustomName.ToLower().Contains(
manualMachineKeyword)&&Ë.IsFunctional);if(!fillOfflineReactors){Ș.RemoveAll(Ë=>!Ë.Enabled);}GridTerminalSystem.GetBlocksOfType<
IMyTerminalBlock>(ǫ,T=>T.HasInventory&&!ț.Contains(T.CubeGrid)&&!T.CustomName.Contains(ǁ)&&!T.GetType().ToString().Contains("Weapons"));
GridTerminalSystem.GetBlocksOfType<IMyTerminalBlock>(Ǭ,T=>T.HasInventory&&!ț.Contains(T.CubeGrid)&&!T.CustomName.Contains(ǁ)&&T.
InventoryCount==1);GridTerminalSystem.GetBlocksOfType<IMyTerminalBlock>(ǭ,T=>T.HasInventory&&!ț.Contains(T.CubeGrid)&&T.InventoryCount
==1&&!T.CustomName.ToLower().Contains(Ȥ)&&!T.CustomName.ToLower().Contains(ȥ)&&!T.CustomName.Contains(ǁ)&&!T.GetType().
ToString().Contains("Reactor")&&!T.GetType().ToString().Contains("MyCockpit")&&!T.GetType().ToString().Contains("Weapons"));if(
fillBottles){ǭ.Sort((o,q)=>q.BlockDefinition.TypeIdString.Contains("Oxygen").CompareTo(o.BlockDefinition.TypeIdString.Contains(
"Oxygen")));}}void Ǣ(List<IMyTerminalBlock>ǣ){if(ǣ.Count>=2)ǣ.Sort((o,q)=>Ě(o).CompareTo(Ě(q)));}void Ǥ(){bool ǥ=false;if(
oreContainerKeyword!=Ɗ("oreContainer")){ǥ=true;}else if(ingotContainerKeyword!=Ɗ("ingotContainer")){ǥ=true;}else if(
componentContainerKeyword!=Ɗ("componentContainer")){ǥ=true;}else if(toolContainerKeyword!=Ɗ("toolContainer")){ǥ=true;}else if(
ammoContainerKeyword!=Ɗ("ammoContainer")){ǥ=true;}else if(bottleContainerKeyword!=Ɗ("bottleContainer")){ǥ=true;}else if(
lockedContainerKeyword!=Ɗ("lockedContainer")){ǥ=true;}else if(specialContainerKeyword!=Ɗ("specialContainer")){ǥ=true;}if(ǥ){List<
IMyTerminalBlock>Ǧ=new List<IMyTerminalBlock>();GridTerminalSystem.GetBlocks(Ǧ);foreach(var Á in Ǧ){if(Á.CustomName.Contains(Ɗ(
"oreContainer"))){Á.CustomName=Á.CustomName.Replace(Ɗ("oreContainer"),oreContainerKeyword);}if(Á.CustomName.Contains(Ɗ(
"ingotContainer"))){Á.CustomName=Á.CustomName.Replace(Ɗ("ingotContainer"),ingotContainerKeyword);}if(Á.CustomName.Contains(Ɗ(
"componentContainer"))){Á.CustomName=Á.CustomName.Replace(Ɗ("componentContainer"),componentContainerKeyword);}if(Á.CustomName.Contains(Ɗ(
"toolContainer"))){Á.CustomName=Á.CustomName.Replace(Ɗ("toolContainer"),toolContainerKeyword);}if(Á.CustomName.Contains(Ɗ(
"ammoContainer"))){Á.CustomName=Á.CustomName.Replace(Ɗ("ammoContainer"),ammoContainerKeyword);}if(Á.CustomName.Contains(Ɗ(
"bottleContainer"))){Á.CustomName=Á.CustomName.Replace(Ɗ("bottleContainer"),bottleContainerKeyword);}if(Á.CustomName.Contains(Ɗ(
"lockedContainer"))){Á.CustomName=Á.CustomName.Replace(Ɗ("lockedContainer"),lockedContainerKeyword);}if(Á.CustomName.Contains(Ɗ(
"specialContainer"))){Á.CustomName=Á.CustomName.Replace(Ɗ("specialContainer"),specialContainerKeyword);}}ƌ("oreContainer",
oreContainerKeyword);ƌ("ingotContainer",ingotContainerKeyword);ƌ("componentContainer",componentContainerKeyword);ƌ("toolContainer",
toolContainerKeyword);ƌ("ammoContainer",ammoContainerKeyword);ƌ("bottleContainer",bottleContainerKeyword);ƌ("lockedContainer",
lockedContainerKeyword);ƌ("specialContainer",specialContainerKeyword);}}void ǧ(){List<IMyCargoContainer>Ǩ=new List<IMyCargoContainer>();
GridTerminalSystem.GetBlocksOfType<IMyCargoContainer>(Ǩ,Ë=>Ż.Contains(Ë.CubeGrid)&&!Ë.CustomName.ToLower().Contains(Ȥ)&&!Ë.CustomName.
ToLower().Contains(ȥ));IMyCargoContainer ǩ=Ǩ.Find(Ë=>Ë.CustomName.Contains(componentContainerKeyword));if(ǩ!=null){var Ǡ=ǩ.
GetInventory();Ǩ.RemoveAll(Ë=>!Ë.GetInventory().IsConnectedTo(Ǡ));}foreach(var Æ in Ǩ){bool Ǒ=false;foreach(string ǒ in ȣ){if(Æ.
CustomName.Contains(ǒ))Ǒ=true;}if(!Ǒ){bool Ǔ=false;string ǔ=Æ.CustomName;string Ǖ="";if(Ȝ.Count==0||ȧ=="Ore"){Æ.CustomName=Æ.
CustomName+" "+oreContainerKeyword;Ȝ.Add(Æ);Ǖ="Ores";}else if(ȝ.Count==0||ȧ=="Ingot"){Æ.CustomName=Æ.CustomName+" "+
ingotContainerKeyword;ȝ.Add(Æ);Ǖ="Ingots";}else if(Ȟ.Count==0||ȧ=="Component"){Æ.CustomName=Æ.CustomName+" "+componentContainerKeyword;Ȟ.Add(
Æ);Ǖ="Components";}else if(ȟ.Count==0||ȧ=="PhysicalGunObject"){if(toolsAmmoBottlesInOne){Ǔ=true;}else{Æ.CustomName=Æ.
CustomName+" "+toolContainerKeyword;ȟ.Add(Æ);Ǖ="Tools";}}else if(Ƞ.Count==0||ȧ=="AmmoMagazine"){if(toolsAmmoBottlesInOne){Ǔ=true;}
else{Æ.CustomName=Æ.CustomName+" "+ammoContainerKeyword;Ƞ.Add(Æ);Ǖ="Ammo";}}else if(ȡ.Count==0||ȧ=="OxygenContainerObject"||
ȧ=="GasContainerObject"){if(toolsAmmoBottlesInOne){Ǔ=true;}else{Æ.CustomName=Æ.CustomName+" "+bottleContainerKeyword;ȡ.
Add(Æ);Ǖ="Bottles";}}if(Ǔ){Æ.CustomName=Æ.CustomName+" "+toolContainerKeyword+" "+ammoContainerKeyword+" "+
bottleContainerKeyword;ȟ.Add(Æ);Ƞ.Add(Æ);ȡ.Add(Æ);Ǖ="Tools, Ammo and Bottles";}if(Ǖ!=""){Ȭ="Assigned '"+ǔ+"' as a new container for type '"+Ǖ+
"'.";}ȧ="";}}}void ǖ(){foreach(var Æ in ǫ){string j=Æ.CustomName;string Ǘ=j.ToLower();List<string>ǘ=new List<string>();if(Ǘ.
Contains(oreContainerKeyword.ToLower())&&!j.Contains(oreContainerKeyword))ǘ.Add(oreContainerKeyword);if(Ǘ.Contains(
ingotContainerKeyword.ToLower())&&!j.Contains(ingotContainerKeyword))ǘ.Add(ingotContainerKeyword);if(Ǘ.Contains(componentContainerKeyword.
ToLower())&&!j.Contains(componentContainerKeyword))ǘ.Add(componentContainerKeyword);if(Ǘ.Contains(toolContainerKeyword.ToLower(
))&&!j.Contains(toolContainerKeyword))ǘ.Add(toolContainerKeyword);if(Ǘ.Contains(ammoContainerKeyword.ToLower())&&!j.
Contains(ammoContainerKeyword))ǘ.Add(ammoContainerKeyword);if(Ǘ.Contains(bottleContainerKeyword.ToLower())&&!j.Contains(
bottleContainerKeyword))ǘ.Add(bottleContainerKeyword);if(Ǘ.Contains(lockedContainerKeyword.ToLower())&&!j.Contains(lockedContainerKeyword))ǘ.
Add(lockedContainerKeyword);if(Ǘ.Contains(specialContainerKeyword.ToLower())&&!j.Contains(specialContainerKeyword))ǘ.Add(
specialContainerKeyword);if(Ǘ.Contains(noSortingKeyword.ToLower())&&!j.Contains(noSortingKeyword))ǘ.Add(noSortingKeyword);if(Ǘ.Contains(
actBasicKeyword.ToLower())&&!j.Contains(actBasicKeyword))ǘ.Add(actBasicKeyword);if(Ǘ.Contains(manualMachineKeyword.ToLower())&&!j.
Contains(manualMachineKeyword))ǘ.Add(manualMachineKeyword);if(Ǘ.Contains(" p")&&!j.Contains(" P"))ǘ.Add(" P");if(Ǘ.Contains(
" pmax")&&!j.Contains(" PMax"))ǘ.Add(" PMax");if(Ǘ.Contains(" pmin")&&!j.Contains(" PMin"))ǘ.Add(" PMin");foreach(var L in ǘ){Æ
.CustomName=System.Text.RegularExpressions.Regex.Replace(Æ.CustomName,L,L,System.Text.RegularExpressions.RegexOptions.
IgnoreCase);Ȭ="Corrected name\nof: '"+j+"'\nto: '"+Æ.CustomName+"'";}}List<IMyTextPanel>Y=new List<IMyTextPanel>();
GridTerminalSystem.GetBlocksOfType(Y);foreach(var W in Y){string j=W.CustomName;string Ǘ=j.ToLower();List<string>ǘ=new List<string>();if(Ǘ
.Contains(mainLCDKeyword.ToLower())&&!j.Contains(mainLCDKeyword))ǘ.Add(mainLCDKeyword);if(Ǘ.Contains(inventoryLCDKeyword.
ToLower())&&!j.Contains(inventoryLCDKeyword))ǘ.Add(inventoryLCDKeyword);if(Ǘ.Contains(warningsLCDKeyword.ToLower())&&!j.
Contains(warningsLCDKeyword))ǘ.Add(warningsLCDKeyword);foreach(var L in ǘ){W.CustomName=System.Text.RegularExpressions.Regex.
Replace(W.CustomName,L,L,System.Text.RegularExpressions.RegexOptions.IgnoreCase);Ȭ="Corrected name\nof: '"+j+"'\nto: '"+W.
CustomName+"'";}}}void Ǚ(string ǚ,List<IMyTerminalBlock>Ǜ,string ǜ){if(Ǜ.Count==0){Ƣ("There are no containers for type '"+ǜ+
"'!\nBuild new ones or add the tag to existing ones!");ȧ=ǚ;return;}IMyTerminalBlock Ò=null;int ǝ=int.MaxValue;string Ǟ=
"\nhas a different owner/faction!\nCan't move items from there!";foreach(var Æ in Ǜ){if(ǚ==ȉ&&Æ.BlockDefinition.TypeIdString.Contains("OxygenTank")&&Æ.BlockDefinition.SubtypeId.
Contains("Hydrogen")){continue;}else if(ǚ==Ȋ&&Æ.BlockDefinition.TypeIdString.Contains("OxygenTank")&&!Æ.BlockDefinition.
SubtypeId.Contains("Hydrogen")){continue;}var Í=Æ.GetInventory(0);if((float)Í.CurrentVolume<(float)Í.MaxVolume*0.99){int ǟ=Ě(Æ);
if(ǟ<ǝ){ǝ=ǟ;Ò=Æ;}}}if(Ò==null){Ƣ("All containers for type '"+ǜ+"' are full!\nYou should build new cargo containers!");ȧ=ǚ;
return;}IMyTerminalBlock Ǹ=null;if(fillBottles&&(ǚ==ȉ||ǚ==Ȋ)){Ǹ=ɮ(ǚ);}foreach(var Æ in ǭ){if(Æ==Ò||(Æ.CustomName.Contains(ǜ)&&
Ě(Æ)<=ǝ)||(ǚ=="Ore"&&Æ.GetType().ToString().Contains("MyGasGenerator"))){continue;}if(Æ.CustomName.Contains(ǜ)&&
balanceTypeContainers&&!Æ.BlockDefinition.TypeIdString.Contains("OxygenGenerator")&&!Æ.BlockDefinition.TypeIdString.Contains("OxygenTank"))
continue;if(Æ.GetOwnerFactionTag()!=Me.GetOwnerFactionTag()){Ƣ("'"+Æ.CustomName+"'"+Ǟ);continue;}if(Ǹ!=null){if(!Æ.
BlockDefinition.TypeIdString.Contains("Oxygen")){Ú(ǚ,Æ,0,Ǹ,0);continue;}}Ú(ǚ,Æ,0,Ò,0);}foreach(var Ǐ in Ǳ){if(Ǐ==Ò||(Ǐ.CustomName.
Contains(ǜ)&&Ě(Ǐ)<=ǝ)){continue;}if(Ǐ.GetOwnerFactionTag()!=Me.GetOwnerFactionTag()){Ƣ("'"+Ǐ.CustomName+"'"+Ǟ);continue;}Ú(ǚ,Ǐ,1
,Ò,0);}foreach(IMyAssembler Ĉ in Ƕ){if(Ĉ.Mode==MyAssemblerMode.Disassembly||Ĉ==Ò||(Ĉ.CustomName.Contains(ǜ)&&Ě(Ĉ)<=ǝ)){
continue;}if(Ĉ.GetOwnerFactionTag()!=Me.GetOwnerFactionTag()){Ƣ("'"+Ĉ.CustomName+"'"+Ǟ);continue;}if(Ǹ!=null){Ú(ǚ,Ĉ,1,Ǹ,0);
continue;}Ú(ǚ,Ĉ,1,Ò,0);}}IMyTerminalBlock ɮ(string ǚ){List<IMyGasTank>ɯ=new List<IMyGasTank>();GridTerminalSystem.
GetBlocksOfType<IMyGasTank>(ɯ,ɰ=>Ż.Contains(ɰ.CubeGrid)&&!ɰ.CustomName.ToLower().Contains(Ȥ)&&!ɰ.CustomName.ToLower().Contains(ȥ)&&ɰ.
IsWorking);if(ǚ==ȉ)ɯ.RemoveAll(ɰ=>ɰ.BlockDefinition.SubtypeId.Contains("Hydrogen"));if(ǚ==Ȋ)ɯ.RemoveAll(ɰ=>!ɰ.BlockDefinition.
SubtypeId.Contains("Hydrogen"));foreach(var ɱ in ɯ){if(ɱ.FilledRatio>0){ɱ.AutoRefillBottles=true;return ɱ;}}List<IMyGasGenerator>
ɲ=Ƿ;ɲ.RemoveAll(ɳ=>!Ż.Contains(ɳ.CubeGrid)||ɳ.Enabled==false);MyDefinitionId Ę=MyDefinitionId.Parse(Ȅ+ȅ+"/Ice");foreach(
var ɴ in ɲ){if(ì(Ę,ɴ)>0){ɴ.AutoRefill=true;return ɴ;}}return null;}void ɵ(){char ɶ='0';char ɸ='0';char[]ɾ={'A','N','T','X'}
;char[]ɹ={'a','d'};if(sortingPattern.Length==2){ɶ=sortingPattern[0];ɸ=sortingPattern[1];}if(ɶ.ToString().IndexOfAny(ɾ)<0
||ɸ.ToString().IndexOfAny(ɹ)<0){Ƣ("You provided the invalid sorting pattern '"+sortingPattern+
"'!\nCan't sort the inventories!");return;}for(var ɜ=ȩ;ɜ<Ǭ.Count;ɜ++){if(Ɨ(20))return;if(ȩ>=Ǭ.Count-1){ȩ=0;}else{ȩ++;}var Í=Ǭ[ɜ].GetInventory(0);var Ð=
new List<MyInventoryItem>();Í.GetItems(Ð);if(Ð.Count>200)continue;char ɺ=ɶ;char ɻ=ɸ;string ɼ=System.Text.RegularExpressions
.Regex.Match(Ǭ[ɜ].CustomName,@"(\(sort:)(.{2})",System.Text.RegularExpressions.RegexOptions.IgnoreCase).Groups[2].Value;
if(ɼ.Length==2){ɶ=ɼ[0];ɸ=ɼ[1];if(ɶ.ToString().IndexOfAny(ɾ)<0||ɸ.ToString().IndexOfAny(ɹ)<0){Ƣ(
"You provided an invalid sorting pattern in\n'"+Ǭ[ɜ].CustomName+"'!\nUsing global pattern!");ɶ=ɺ;ɸ=ɻ;}}var ɽ=new List<MyInventoryItem>();Í.GetItems(ɽ);if(ɶ=='A'){if(ɸ
=='d'){ɽ.Sort((o,q)=>q.Amount.ToIntSafe().CompareTo(o.Amount.ToIntSafe()));}else{ɽ.Sort((o,q)=>o.Amount.ToIntSafe().
CompareTo(q.Amount.ToIntSafe()));}}else if(ɶ=='N'){if(ɸ=='d'){ɽ.Sort((o,q)=>q.Type.SubtypeId.ToString().CompareTo(o.Type.
SubtypeId.ToString()));}else{ɽ.Sort((o,q)=>o.Type.SubtypeId.ToString().CompareTo(q.Type.SubtypeId.ToString()));}}else if(ɶ=='T'){
if(ɸ=='d'){ɽ.Sort((o,q)=>q.Type.ToString().CompareTo(o.Type.ToString()));}else{ɽ.Sort((o,q)=>o.Type.ToString().CompareTo(q
.Type.ToString()));}}else if(ɶ=='X'){if(ɸ=='d'){ɽ.Sort((o,q)=>(q.Type.TypeId.ToString()+q.Amount.ToIntSafe().ToString(
@"000000000")).CompareTo((o.Type.TypeId.ToString()+o.Amount.ToIntSafe().ToString(@"000000000"))));}else{ɽ.Sort((o,q)=>(o.Type.TypeId
.ToString()+o.Amount.ToIntSafe().ToString(@"000000000")).CompareTo((q.Type.TypeId.ToString()+q.Amount.ToIntSafe().
ToString(@"000000000"))));}}if(ɽ.SequenceEqual(Ð,new Ū()))continue;foreach(var L in ɽ){string ɦ=L.ToString();for(int T=0;T<Ð.
Count;T++){if(Ð[T].ToString()==ɦ){Í.TransferItemTo(Í,T,Ð.Count,false);Ð.Clear();Í.GetItems(Ð);break;}}}ɶ=ɺ;ɸ=ɻ;}}void ɧ(){for
(var ɜ=Ȫ;ɜ<Ȣ.Count;ɜ++){if(Runtime.CurrentInstructionCount>Runtime.MaxInstructionCount*0.75){return;}if(Ȫ>=Ȣ.Count-1){Ȫ=0
;}else{Ȫ++;}Ə(Ȣ[ɜ]);int Ö=0;if(Ȣ[ɜ].BlockDefinition.SubtypeId.Contains("Assembler")){IMyAssembler Ĉ=Ȣ[ɜ]as IMyAssembler;
if(Ĉ.Mode==MyAssemblerMode.Disassembly)Ö=1;}var v=Ȣ[ɜ].CustomData.Split('\n');foreach(var Z in v){if(!Z.Contains("="))
continue;MyDefinitionId Ã;double ɨ=0;var ɩ=Z.Split('=');if(ɩ.Length>=2){if(!MyDefinitionId.TryParse(Ȅ+ɩ[0],out Ã))continue;
double.TryParse(ɩ[1],out ɨ);if(ɩ[1].ToLower().Contains("all")){ɨ=int.MaxValue;Ƈ(Ȣ[ɜ],int.MaxValue);}}else{continue;}double ɪ=ì
(Ã,Ȣ[ɜ],Ö);double ɑ=0;if(ɨ>=0){ɑ=ɨ-ɪ;}else{ɑ=Math.Abs(ɨ)-ɪ;}if(ɑ>=1&&ɨ>=0){IMyTerminalBlock Å=null;if(allowSpecialSteal){
Å=Â(Ã,true,Ȣ[ɜ]);}else{Å=Â(Ã);}if(Å!=null){Ú(Ã.ToString(),Å,0,Ȣ[ɜ],Ö,ɑ,true);}}else if(ɑ<0){IMyTerminalBlock Ò=Ç(Ȣ[ɜ]);if
(Ò!=null)Ú(Ã.ToString(),Ȣ[ɜ],Ö,Ò,0,Math.Abs(ɑ),true);}}}}void ɫ(List<IMyTerminalBlock>Ķ){foreach(var Æ in Ķ){string ɬ=Æ.
CustomName;string ɷ="";var ɭ=System.Text.RegularExpressions.Regex.Match(ɬ,@"\(\d+\.?\d*\%\)").Value;if(ɭ!=""){ɷ=ɬ.Replace(ɭ,"").
TrimEnd(' ');}else{ɷ=ɬ;}var Í=Æ.GetInventory(0);string ļ=((double)Í.CurrentVolume).ť((double)Í.MaxVolume);if(showFillLevel){ɷ+=
" ("+ļ+")";ɷ=ɷ.Replace("  "," ");}if(ɷ!=ɬ)Æ.CustomName=ɷ;}}string ʎ(){if(ș.Count>1){string m=@"("+autocraftingKeyword+
@" *)(\d*)";ș.Sort((o,q)=>System.Text.RegularExpressions.Regex.Match(o.CustomName,m).Groups[2].Value.CompareTo(System.Text.
RegularExpressions.Regex.Match(q.CustomName,m).Groups[2].Value));}string ğ="";if(!ș[0].GetPublicText().Contains("Isy's Autocrafting")){ș[0
].FontSize=0.555f;}foreach(var W in ș){ğ+=W.GetPublicText()+"\n";W.WritePublicTitle(
"Craft item manually once to show up here");W.Font="Monospace";W.FontSize=ș[0].FontSize;W.SetValue<Int64>("alignment",0);W.ShowPublicTextOnScreen();}List<string>í
=ğ.Split('\n').ToList();List<string>v=ș[0].CustomData.Split('\n').ToList();í.RemoveAll(Z=>Z.IndexOfAny(Ȁ)<=0);foreach(var
ã in Ț){bool ʏ=false;foreach(var Z in í){string ʐ=Z.Remove(Z.IndexOf(" "));if(ʐ==ã){ʏ=true;break;}}foreach(var Z in v){if
(Z==ã){ʏ=true;break;}}if(!ʏ){MyDefinitionId Ã=ŕ(ã);double ʑ=Math.Ceiling(ì(Ã));ğ+="\n"+ã+" "+ʑ+" = "+ʑ;}}List<string>ʇ=ğ.
Split('\n').ToList();string µ="";ʇ.RemoveAll(Z=>Z.IndexOfAny(Ȁ)<=0);try{IOrderedEnumerable<string>ʒ;ʒ=ʇ.OrderBy(o=>o.
Substring(0,o.IndexOf(" ")));foreach(var Z in ʒ){bool ʓ=false;string ã=Z.Remove(Z.IndexOf(" "));string ʔ=Z.Replace(ã,"");foreach(
var L in Ț){if(L==ã){ʓ=true;break;}}if(ʓ)µ+=ã+ʔ+"\n";}}catch{}return µ.TrimEnd('\n');}void ʕ(string ğ){if(ğ==""){ğ="Autocrafting error!\n\nNo items for crafting available!\n\nIf you hid all items, check the custom data of the first autocrafting panel and reenable some of them.\n\nOtherwise, store or build new items manually!"
;string í=Ň(ș[0].FontSize,ğ,ș[0]);ș[0].WritePublicText(í);return;}var u=ğ.Split('\n');int w=u.Length;int À=0;int z=(int)
Math.Ceiling(17/ș[0].FontSize);int ľ=26;foreach(var W in ș){ľ=(int)(26/W.FontSize);if(W.BlockDefinition.SubtypeName.Contains
("Wide")){ľ=(int)(52/W.FontSize);}int ª=0;List<string>µ=new List<string>();if(W==ș[0]||headerOnEveryScreen){string ɿ=Ǿ;if
(headerOnEveryScreen&&ș.Count>1){ɿ+=" "+(ș.IndexOf(W)+1)+"/"+ș.Count;try{ɿ+=" ["+u[À][0]+"-#]";}catch{ɿ+=" [Empty]";}}
string ʀ='='.ş(ɿ.Length);µ.Add(ɿ);µ.Add(ʀ+"\n");string ʁ="Component ";string ʂ="Current | Wanted ";string ʃ=' '.ş(ľ-ʁ.Length-ʂ
.Length);µ.Add(ʁ+ʃ+ʂ+"\n");ª=5;}while((À<w&&ª<z)||(W==ș[ș.Count-1]&&À<w)){var Z=u[À].Split(' ');Z[0]+=" ";string ʃ=' '.ş(
ľ-Z[0].Length-Z[1].Length-7);string ʄ=Z[0]+ʃ+Z[1]+Z[2];µ.Add(ʄ.Replace("$"," "));À++;ª++;}if(headerOnEveryScreen&&ș.Count
>1){µ[0]=µ[0].Replace('#',u[À-1][0]);}W.WritePublicText(String.Join("\n",µ));}}void ʅ(){ș.Clear();GridTerminalSystem.
GetBlocksOfType<IMyTextPanel>(ș,W=>Ż.Contains(W.CubeGrid)&&W.CustomName.Contains(autocraftingKeyword));if(ș.Count==0)return;if(Ǵ.Count
==0){Ƣ("No assemblers found!\nBuild assemblers to enable autocrafting!");return;}ė();List<MyDefinitionId>ʆ=new List<
MyDefinitionId>();var ʇ=ʎ().Split('\n');string µ="";foreach(var Z in ʇ){string ã="";try{ã=Z.Substring(0,Z.IndexOf(" "));}catch{
continue;}MyDefinitionId Ã=ŕ(ã);if(Ã==null)continue;double ʈ=Math.Ceiling(ì(Ã));string ʉ=Z.Substring(Z.IndexOfAny(Ȁ)+1);double ʊ
=0;double.TryParse(System.Text.RegularExpressions.Regex.Replace(ʉ,@"\D",""),out ʊ);if(ʉ.Contains("-")){if(!ș[0].
CustomData.Contains(ǿ))ș[0].CustomData=ǿ;ș[0].CustomData+="\n"+ã;continue;}double ʋ=Math.Abs(ʊ-ʈ);bool ʌ;MyDefinitionId Ø=ŋ(Ã,out
ʌ);double ʍ=ŉ(Ø);if(ʈ>=ʊ+ʊ*assembleMargin&&ʍ>0&&!Z.Contains("[D:")){ċ(Ø);ʍ=0;Ȭ="Removed '"+Ã.SubtypeId.ToString()+
"' from the assembling queue.";}if(ʈ<=ʊ-ʊ*disassembleMargin&&ʍ>0&&Z.Contains("[D:")){ċ(Ø);ʍ=0;Ȭ="Removed '"+Ã.SubtypeId.ToString()+
"' from the disassembling queue.";}string Č="";if(ʍ>0||ʋ>0){if(enableAutodisassembling&&ʈ>ʊ+ʊ*disassembleMargin){Č="$[D:";}else if(enableAutocrafting&&ʈ<
ʊ-ʊ*assembleMargin){Č="$[A:";}if(Č!=""){if(ʍ==0){Č+="Wait]";}else{Č+=Math.Round(ʍ)+"]";}}}if(!ʌ)Č="$[NoBP!]";string ƅ="";
if(ʌ&&ʉ.Contains("!")){ʆ.Add(Ø);ƅ="!";}string ɂ="$=$ ";if(ʈ>ʊ)ɂ="$>$ ";if(ʈ<ʊ)ɂ="$<$ ";µ+=ã+" "+ʈ+Č+ɂ+ʊ+ƅ+"\n";if(Č.
Contains("[D:Wait]")){ƫ(Ø,ʋ);}else if(Č.Contains("[A:Wait]")){ɝ(Ø,ʋ);Ȭ="Queued "+ʋ+" '"+Ã.SubtypeId.ToString()+
"' in the assemblers.";}else if(Č.Contains("[NoBP!]")&&ʊ>ʈ){Ƣ("Unsuccessfully attempted to craft\n'"+Ã.SubtypeId.ToString()+"'\nA valid blueprint for this item couldn't be found!\nQueue it up a few times with no other item in queue\nso that the script can learn its blueprint."
);}}Ď();ɚ(ʆ);ʕ(µ.TrimEnd('\n'));}void Ɂ(){MyDefinitionId Ƀ=MyDefinitionId.Parse(Ȅ+ȅ+"/Stone");MyDefinitionId Ø=
MyDefinitionId.Parse(Ȍ+"StoneOreToIngotBasic");double Ʉ=ì(Ƀ);if(Ʉ>0){double Ʌ=Math.Ceiling(Ʉ/500/ǵ.Count);foreach(var Ɇ in ǵ){if(Ɇ.
IsQueueEmpty)Ɇ.AddQueueItem(Ø,Ʌ);}}}void ɇ(){if(ȫ==0)Ɉ(Ȝ,ȅ);if(ȫ==1)Ɉ(ȝ,ȇ);if(ȫ==2)Ɉ(Ȟ,ȕ);if(ȫ==3)Ɉ(ȟ,ȋ);if(ȫ==4)Ɉ(Ƞ,Ȉ);if(ȫ==5)Ɉ(ȡ,
"ContainerObject");ȫ++;if(ȫ>5)ȫ=0;}void Ɉ(List<IMyTerminalBlock>Ķ,string É){Ķ.RemoveAll(Ë=>Ë.InventoryCount==2||Ë.BlockDefinition.
TypeIdString.Contains("OxygenGenerator")||Ë.BlockDefinition.TypeIdString.Contains("OxygenTank"));if(Ķ.Count<=1){ȫ++;return;}
Dictionary<MyDefinitionId,double>ɉ=new Dictionary<MyDefinitionId,double>();foreach(var Æ in Ķ){var Ð=new List<MyInventoryItem>();Æ
.GetInventory(0).GetItems(Ð);foreach(var L in Ð){if(!L.Type.TypeId.ToString().Contains(É))continue;MyDefinitionId Ã=L.
Type;if(ɉ.ContainsKey(Ã)){ɉ[Ã]+=(double)L.Amount;}else{ɉ[Ã]=(double)L.Amount;}}}Dictionary<MyDefinitionId,double>Ɋ=new
Dictionary<MyDefinitionId,double>();foreach(var L in ɉ){Ɋ[L.Key]=L.Value/Ķ.Count;}foreach(var Æ in Ķ){if(Ɨ(75)){ȫ--;return;}var ɋ=
new List<MyInventoryItem>();Æ.GetInventory(0).GetItems(ɋ);Dictionary<MyDefinitionId,double>Ɍ=new Dictionary<MyDefinitionId,
double>();foreach(var L in ɋ){MyDefinitionId Ã=L.Type;if(Ɍ.ContainsKey(Ã)){Ɍ[Ã]+=(double)L.Amount;}else{Ɍ[Ã]=(double)L.Amount;
}}double ɍ=0;foreach(var L in ɉ){Ɍ.TryGetValue(L.Key,out ɍ);double Ɏ=Ɋ[L.Key];if(ɍ>=Ɏ-1)continue;foreach(var ɏ in Ķ){
double ɐ=ì(L.Key,ɏ);if(ɐ<=Ɏ+1)continue;double ɑ=Ɋ[L.Key]-ɍ;if(ɑ>ɐ-Ɏ)ɑ=ɐ-Ɏ;if(ɑ>0){ɍ+=Ú(L.Key.ToString(),ɏ,0,Æ,0,ɑ,true);if(ɍ>=
Ɏ-1&&ɍ<=Ɏ+1)break;}}}}if(!Ɨ(50))ȫ++;}void ɒ(){if(ǰ.Count==0)return;if(ǳ.Count==0)ȴ=false;if(enableStoneProcessing){if(!ȁ.
Contains("Stone")){ȁ.Add("Stone");ȃ.Add("Stone");}}ȁ=ɞ(ȁ);Ȃ=ɞ(Ȃ);ȃ=ɞ(ȃ);if(enableValueOrePriority&&ǳ.Count>0){ȴ=false;foreach(
var L in Ȃ){var Ã=MyDefinitionId.Parse(Ȅ+ȅ+"/"+L);if(ì(Ã)>0){ȴ=true;break;}}}if(ȴ){foreach(var Ǐ in ǲ){IMyTerminalBlock Ò=Ç
(Ǐ,oreContainerKeyword);if(Ò!=null){foreach(var ȶ in ȃ){Ú(ȶ,Ǐ,0,Ò,0);}}}}if(enableBasicOreSpecialization||ȴ){ȼ(ǲ,Ȃ);}else
{ȼ(ǲ,ȁ);}ȼ(ǳ,ȃ);if(enableBasicOreSpecialization||ȴ){ɀ(ǲ,Ȃ);}else{ɀ(ǲ,ȁ);}ɀ(ǳ,ȃ);bool ȷ=false;if(!
enableBasicOreSpecialization&&!ȴ){ȷ=ɟ(ǲ,ǳ,ȃ);}if(!ȷ){ɟ(ǳ,ǲ,ȃ);}ɤ(ǲ);ɤ(ǳ);if(sortRefiningQueue){foreach(IMyRefinery Ǐ in ǰ){var Í=Ǐ.GetInventory(0);
var Ð=new List<MyInventoryItem>();Í.GetItems(Ð);if(Ð.Count<2)continue;bool ȸ=false;int ȹ=0;string Ⱥ="";foreach(var Ȼ in ȁ){
for(int T=0;T<Ð.Count;T++){if(Ð[T].Type.SubtypeId==Ȼ){ȹ=T;Ⱥ=Ȼ;ȸ=true;break;}}if(ȸ)break;}if(ȹ!=0){Í.TransferItemTo(Í,ȹ,0,
true);Ȭ="Sorted the refining queue.\n'"+Ⱥ+"' is now at the front of the queue.";}}}}void ȼ(List<IMyTerminalBlock>Ƚ,List<
string>Ⱦ){MyDefinitionId ȿ=new MyDefinitionId();foreach(var ȶ in Ⱦ){var Ã=MyDefinitionId.Parse(Ȅ+ȅ+"/"+ȶ);if(ì(Ã)>0){ȿ=Ã;break
;}}if(!ȿ.ToString().Contains(ȅ))return;foreach(var Ǐ in Ƚ){var Í=Ǐ.GetInventory(0);if((double)Í.CurrentVolume>(double)Í.
MaxVolume*0.95){var Ð=new List<MyInventoryItem>();Í.GetItems(Ð);foreach(var L in Ð){if((MyDefinitionId)L.Type==ȿ)return;}
IMyTerminalBlock Ò=Ç(Ǐ,oreContainerKeyword);if(Ò!=null){Ú("",Ǐ,0,Ò,0);}}}}void ɀ(List<IMyTerminalBlock>Ƚ,List<string>Ⱦ){var Ķ=new List<
IMyTerminalBlock>();Ķ.AddRange(ǭ);Ķ.AddRange(Ȣ);IMyTerminalBlock Ȩ=null;foreach(var Ǐ in Ƚ){var Í=Ǐ.GetInventory(0);if((double)Í.
CurrentVolume>(double)Í.MaxVolume*0.5)continue;foreach(var L in Ⱦ){if((double)Í.CurrentVolume>(double)Í.MaxVolume*0.95)return;
MyDefinitionId Ã=MyDefinitionId.Parse(Ȅ+ȅ+"/"+L);IMyTerminalBlock Å=null;if(ì(Ã)==0)continue;if(Ȩ!=null){if(Ȩ.GetInventory(0).FindItem
(Ã)!=null){Å=Ȩ;}}if(Å==null){foreach(var Æ in Ķ){if(Æ.GetInventory(0).FindItem(Ã)!=null){Å=Æ;Ȩ=Æ;}}}if(Å==null)continue;Ú
(Ã.ToString(),Å,0,Ǐ,0);}return;}}bool ɟ(List<IMyTerminalBlock>ɠ,List<IMyTerminalBlock>ɡ,List<string>Ⱦ){foreach(var ɢ in ɠ
){if((double)ɢ.GetInventory(0).CurrentVolume>0.05)continue;foreach(var ɣ in ɡ){if((double)ɣ.GetInventory(0).CurrentVolume
>0){foreach(var ȶ in Ⱦ){Ú(ȶ,ɣ,0,ɢ,0,-0.5);}return true;}}}return false;}void ɤ(List<IMyTerminalBlock>ɥ){if(ɥ.Count<2)
return;Dictionary<MyDefinitionId,double>ɉ=new Dictionary<MyDefinitionId,double>();foreach(var Æ in ɥ){var Ð=new List<
MyInventoryItem>();Æ.GetInventory(0).GetItems(Ð);foreach(var L in Ð){MyDefinitionId Ã=L.Type;if(ɉ.ContainsKey(Ã)){ɉ[Ã]+=(double)L.
Amount;}else{ɉ[Ã]=(double)L.Amount;}}}Dictionary<MyDefinitionId,double>Ɋ=new Dictionary<MyDefinitionId,double>();foreach(var L
in ɉ){Ɋ[L.Key]=L.Value/ɥ.Count;}foreach(var Æ in ɥ){if(Ɨ(75)){return;}var ɋ=new List<MyInventoryItem>();Æ.GetInventory(0).
GetItems(ɋ);Dictionary<MyDefinitionId,double>Ɍ=new Dictionary<MyDefinitionId,double>();foreach(var L in ɋ){MyDefinitionId Ã=L.
Type;if(Ɍ.ContainsKey(Ã)){Ɍ[Ã]+=(double)L.Amount;}else{Ɍ[Ã]=(double)L.Amount;}}double ɍ=0;foreach(var L in ɉ){Ɍ.TryGetValue(
L.Key,out ɍ);double Ɏ=Ɋ[L.Key];if(ɍ>=Ɏ-1)continue;foreach(var ɏ in ɥ){double ɐ=ì(L.Key,ɏ);if(ɐ<=Ɏ+1)continue;double ɑ=Ɋ[L
.Key]-ɍ;if(ɑ>ɐ-Ɏ)ɑ=ɐ-Ɏ;if(ɑ>0){ɍ+=Ú(L.Key.ToString(),ɏ,0,Æ,0,ɑ,true);if(ɍ>=Ɏ-1&&ɍ<=Ɏ+1)break;}}}}}List<string>ɞ(List<
string>ɓ){ɓ.Sort((o,q)=>(ì(MyDefinitionId.Parse(Ȅ+ȇ+"/"+o))*Ơ(o)).CompareTo((ì(MyDefinitionId.Parse(Ȅ+ȇ+"/"+q))*Ơ(q))));return
ɓ;}void ɔ(double ɕ){foreach(var Ĉ in Ǵ){if(Ĉ.GetOwnerFactionTag()==Me.GetOwnerFactionTag()){var ɖ=Ĉ.GetInventory(0);if((
float)ɖ.CurrentVolume>=(float)ɖ.MaxVolume*(ɕ/100)||Ĉ.Mode==MyAssemblerMode.Disassembly){IMyTerminalBlock Ò=Ç(Ĉ,
ingotContainerKeyword);if(Ò!=null)Ú("",Ĉ,0,Ò,0);}}}}void ɗ(){foreach(IMyAssembler Ĉ in Ǵ){if(Ĉ.Mode==MyAssemblerMode.Disassembly)continue;if(
Ĉ.CustomData.Contains("skipQueueSorting")){Ĉ.CustomData="";continue;}var Č=new List<MyProductionItem>();Ĉ.GetQueue(Č);if(
Č.Count<2)continue;double ɘ=Double.MaxValue;int ȹ=0;string Ⱥ="";for(int T=0;T<Č.Count;T++){MyDefinitionId Ã=ō(Č[T].
BlueprintId);double ə=ì(Ã);if(ə<ɘ){ɘ=ə;ȹ=T;Ⱥ=Ã.SubtypeId.ToString();}}if(ȹ!=0){Ĉ.MoveQueueItemRequest(Č[ȹ].ItemId,0);Ȭ=
"Sorted the assembling queue.\n'"+Ⱥ+"' is now at the front of the queue.";}}}void ɚ(List<MyDefinitionId>ɛ){if(ɛ.Count==0)return;if(ɛ.Count>1)ɛ.Sort((o,q)
=>ì(ō(o)).CompareTo(ì(ō(q))));foreach(var Ĉ in Ǵ){var Č=new List<MyProductionItem>();Ĉ.GetQueue(Č);if(Č.Count<2)continue;
foreach(var Ø in ɛ){int ɜ=Č.FindIndex(T=>T.BlueprintId==Ø);if(ɜ==-1)continue;if(ɜ==0){Ĉ.CustomData="skipQueueSorting";break;}Ĉ.
MoveQueueItemRequest(Č[ɜ].ItemId,0);Ĉ.CustomData="skipQueueSorting";Ȭ="Sorted the assembler queue by priority.\n'"+ō(Ø).SubtypeId.ToString()
+"' is now at the front of the queue.";break;}}}void ɝ(MyDefinitionId Ø,double N){List<IMyAssembler>ć=new List<
IMyAssembler>();foreach(IMyAssembler Ĉ in Ǵ){if(Ĉ.Mode==MyAssemblerMode.Disassembly&&!Ĉ.IsQueueEmpty)continue;if(Ĉ.Mode==
MyAssemblerMode.Disassembly){Ĉ.Mode=MyAssemblerMode.Assembly;}if(Ĉ.CanUseBlueprint(Ø)){ć.Add(Ĉ);}}ĉ(ć,Ø,N);}void ƫ(MyDefinitionId Ø,
double N){List<IMyAssembler>ć=new List<IMyAssembler>();foreach(IMyAssembler Ĉ in Ǵ){if(Ĉ.Mode==MyAssemblerMode.Assembly&&Ĉ.
IsProducing)continue;if(Ĉ.Mode==MyAssemblerMode.Assembly){Ĉ.ClearQueue();Ĉ.Mode=MyAssemblerMode.Disassembly;}if(Ĉ.Mode==
MyAssemblerMode.Assembly)continue;if(Ĉ.CanUseBlueprint(Ø)){ć.Add(Ĉ);}}ĉ(ć,Ø,N);}void ĉ(List<IMyAssembler>ć,MyDefinitionId Ø,double N){
if(ć.Count==0)return;double Ċ=Math.Ceiling(N/ć.Count);foreach(IMyAssembler Ĉ in ć){if(Ċ>N)Ċ=Math.Ceiling(N);if(N>0){Ĉ.
InsertQueueItem(0,Ø,Ċ);N-=Ċ;}else{break;}}}void ċ(MyDefinitionId Ø){foreach(IMyAssembler Ĉ in Ǵ){var Č=new List<MyProductionItem>();Ĉ.
GetQueue(Č);for(int T=0;T<Č.Count;T++){if(Č[T].BlueprintId==Ø)Ĉ.RemoveQueueItem(T,Č[T].Amount);}}}void ė(){foreach(IMyAssembler
Ĉ in Ǵ){Ĉ.UseConveyorSystem=true;Ĉ.CooperativeMode=false;Ĉ.Repeating=false;if(Ĉ.Mode==MyAssemblerMode.Disassembly&&!Ĉ.
IsProducing){Ĉ.ClearQueue();Ĉ.Mode=MyAssemblerMode.Assembly;}}}void Ď(){List<IMyAssembler>ď=new List<IMyAssembler>(Ǵ);ď.RemoveAll(o
=>o.IsQueueEmpty);if(ď.Count==0)return;List<IMyAssembler>Đ=new List<IMyAssembler>(Ǵ);Đ.RemoveAll(o=>!o.IsQueueEmpty);
foreach(var đ in ď){if(Đ.Count==0)return;var Č=new List<MyProductionItem>();đ.GetQueue(Č);double Ē=(double)Č[0].Amount;if(Ē<50)
continue;double ē=Math.Ceiling(Ē/2);foreach(var Ĕ in Đ){if(!Ĕ.CanUseBlueprint(Č[0].BlueprintId))continue;Ĕ.Mode=đ.Mode;if(Ĕ.Mode
!=đ.Mode)continue;Ĕ.AddQueueItem(Č[0].BlueprintId,ē);đ.RemoveQueueItem(0,ē);Đ.Remove(Ĕ);break;}}}void ĕ(){if(Ƿ.Count==0)
return;double Ė=iceFillLevelPercentage/100;MyDefinitionId Ę=MyDefinitionId.Parse(Ȅ+ȅ+"/Ice");string ą=Ę.ToString();double î=ő(
Ę);if(î==0)î=0.00037;foreach(IMyGasGenerator õ in Ƿ){var Í=õ.GetInventory(0);double ï=ì(Ę,õ);double ð=ï*î;double ñ=(
double)Í.MaxVolume;if(ð>ñ*(Ė+0.001)){IMyTerminalBlock Ò=Ç(õ,oreContainerKeyword);if(Ò!=null){double ò=(ð-ñ*Ė)/î;Ú(ą,õ,0,Ò,0,ò)
;}}else if(ð<ñ*(Ė-0.001)){IMyTerminalBlock Å=Â(Ę,true);if(Å!=null){double ò=(ñ*Ė-ð)/î;Ú(ą,Å,0,õ,0,ò);}}}double ó=0;double
ô=0;foreach(var õ in Ƿ){ó+=ì(Ę,õ);var Í=õ.GetInventory(0);ô+=(double)Í.MaxVolume;}double ö=(ó*î)/ô;foreach(var ø in Ƿ){
var ß=ø.GetInventory(0);double ù=ì(Ę,ø);double ú=ù*î;double û=(double)ß.MaxVolume;if(ú>û*(ö+0.001)){foreach(var ü in Ƿ){if(
ø==ü)continue;var Ó=ü.GetInventory(0);double ý=ì(Ę,ü);double þ=ý*î;double ÿ=(double)Ó.MaxVolume;if(þ<ÿ*(ö-0.001)){double
Ā=((ÿ*ö)-þ)/î;if((ù-Ā)*î>=û*ö&&Ā>5){ù-=Ú(ą,ø,0,ü,0,Ā);continue;}if((ù-Ā)*î<û*ö&&Ā>5){double ā=(ù*î-û*ö)/î;Ú(ą,ø,0,ü,0,ā);
break;}}}}}}void Ă(){if(Ș.Count==0)return;MyDefinitionId ă=MyDefinitionId.Parse(Ȅ+ȇ+"/Uranium");string č=ă.ToString();double
Ą=0;double ę=0;foreach(IMyReactor Ĩ in Ș){Ĩ.UseConveyorSystem=false;double ĩ=ì(ă,Ĩ);double Ī=uraniumAmountLargeGrid;if(Ĩ.
CubeGrid.GridSize==0.5f)Ī=uraniumAmountSmallGrid;ę+=Ī;if(ĩ>Ī+0.05){IMyTerminalBlock Ò=Ç(Ĩ,ingotContainerKeyword);if(Ò!=null){
double ò=ĩ-Ī;Ú(č,Ĩ,0,Ò,0,ò);}}else if(ĩ<Ī-0.05){IMyTerminalBlock Å=Â(ă,true);if(Å!=null){double ò=Ī-ĩ;Ú(č,Å,0,Ĩ,0,ò);}}Ą+=ì(ă,
Ĩ);}double ī=Ą/ę;foreach(var Ĭ in Ș){double ĭ=ì(ă,Ĭ);double Į=ī*uraniumAmountLargeGrid;if(Ĭ.CubeGrid.GridSize==0.5f)Į=ī*
uraniumAmountSmallGrid;if(ĭ>Į+0.05){foreach(var į in Ș){if(Ĭ==į)continue;double İ=ì(ă,į);double ı=ī*uraniumAmountLargeGrid;if(į.CubeGrid.
GridSize==0.5f)ı=ī*uraniumAmountSmallGrid;if(İ<ı-0.05){ĭ=ì(ă,Ĭ);double Ĳ=ı-İ;if(ĭ-Ĳ>=Į){Ú(č,Ĭ,0,į,0,Ĳ);continue;}if(ĭ-Ĳ<Į){Ĳ=ĭ-Į
;Ú(č,Ĭ,0,į,0,Ĳ);break;}}}}}}string ķ(float F=0.65f,int G=26,bool Ġ=true,bool ġ=true,bool Ģ=true){bool K=false;string J=""
;J="Isy's Inventory Manager "+ȭ[Ȯ]+"\n";J+="=========================\n\n";if(ĥ!=null){J+="Warning!\n";J+=ĥ+"\n\n";}if(Ġ)
{J+="Statistics for "+Ǯ.Count+" sorted cargo containers:\n\n";J+=ĵ(F,G,Ȝ,"Ores");J+=ĵ(F,G,ȝ,"Ingots");J+=ĵ(F,G,Ȟ,
"Components");J+=ĵ(F,G,ȟ,"Tools");J+=ĵ(F,G,Ƞ,"Ammo");J+=ĵ(F,G,ȡ,"Bottles");J+="\n";K=true;}if(ġ&&(Ȣ.Count>0||ǰ.Count>0||Ǵ.Count>0||ǵ
.Count>0||Ƿ.Count>0||Ș.Count>0)){J+="Managed blocks by type:\n";int ĳ=0;if(Ȣ.Count>ĳ)ĳ=Ȣ.Count;if(ǰ.Count>ĳ)ĳ=ǰ.Count;if(
Ǵ.Count>ĳ)ĳ=Ǵ.Count;if(Ƿ.Count>ĳ)ĳ=Ƿ.Count;if(Ș.Count>ĳ)ĳ=Ș.Count;int Ĵ=ĳ.ToString().Length;if(Ȣ.Count>0){J+=' '.ş(Ĵ-Ȣ.
Count.ToString().Length)+Ȣ.Count+" Special Containers\n";}if(enableOreBalancing&&ǲ.Count>0){J+=' '.ş(Ĵ-ǲ.Count.ToString().
Length)+ǲ.Count+" Large Refineries: ";J+="Value Ore Priority "+(enableValueOrePriority?"ON":"OFF")+"\n";}if(enableOreBalancing
&&ǳ.Count>0){J+=' '.ş(Ĵ-ǳ.Count.ToString().Length)+ǳ.Count+" Basic Refineries: ";J+="Basic Ore Specialization "+(
enableBasicOreSpecialization?"ON":"OFF")+"\n";}if(Ƿ.Count>0){J+=' '.ş(Ĵ-Ƿ.Count.ToString().Length)+Ƿ.Count+" O2/H2 Generators: ";J+="Ice Balancing "
+(enableIceBalancing?"ON":"OFF")+"\n";}if(Ș.Count>0){J+=' '.ş(Ĵ-Ș.Count.ToString().Length)+Ș.Count+" Reactors: ";J+=
"Uranium Balancing "+(enableUraniumBalancing?"ON":"OFF")+"\n";}if(Ǵ.Count>0){J+=' '.ş(Ĵ-Ǵ.Count.ToString().Length)+Ǵ.Count+" Assemblers: ";J
+="Craft "+(enableAutocrafting?"ON":"OFF")+" | ";J+="Uncraft "+(enableAutodisassembling?"ON":"OFF")+" | ";J+="Cleanup "+(
enableAssemblerCleanup?"ON":"OFF")+"\n";}if(ǵ.Count>0){J+=' '.ş(Ĵ-ǵ.Count.ToString().Length)+ǵ.Count+" Survival Kits: ";J+="Ingot Crafting "+(
enableIngotCrafting?"ON":"OFF")+"\n";}J+="\n";K=true;}if(Ģ&&Ȭ!=""){J+="Last Action:\n"+Ȭ;K=true;}if(!K){J+="-- No informations to show --";
}return J;}string ĵ(double F,int G,List<IMyTerminalBlock>Ķ,string â){double Ñ=0,ħ=0;foreach(var Æ in Ķ){var Í=Æ.
GetInventory(0);Ñ+=(double)Í.CurrentVolume;ħ+=(double)Í.MaxVolume;}string M=Ķ.Count+"x "+â+":";string ě=Ñ.Ţ();string Ĝ=ħ.Ţ();string
ĝ=Ŗ(F,G,M,Ñ,ħ,ě,Ĝ);return ĝ;}void Ğ(string ğ=null){ȯ.Clear();GridTerminalSystem.GetBlocksOfType<IMyTextPanel>(ȯ,e=>e.
CustomName.Contains(mainLCDKeyword));if(ȯ.Count==0)return;foreach(var W in ȯ){bool Ġ=V(W,"showContainerStats");bool ġ=V(W,
"showManagedBlocks");bool Ģ=V(W,"showLastAction");float F=W.FontSize;int G=26;if(W.BlockDefinition.SubtypeName.Contains("Wide"))G=52;string
J="";if(ğ!=null){J=ğ;}else{J=ķ(F,G,Ġ,ġ,Ģ);}string í=Ň(F,J,W);W.WritePublicTitle("Isy's Inventory Manager");W.
WritePublicText(í,false);W.SetValue<Int64>("alignment",0);W.Font="Monospace";W.ShowPublicTextOnScreen();}}void ģ(){ȳ.Clear();
GridTerminalSystem.GetBlocksOfType<IMyTextPanel>(ȳ,e=>e.CustomName.Contains(warningsLCDKeyword));if(ȳ.Count==0)return;foreach(var W in ȳ){
if(W.GetPublicTitle()!="Isy's Inventory Manager Warnings"){W.FontSize=0.5f;}float F=W.FontSize;string J=
"Isy's Inventory Manager Warnings\n";J+="================================\n\n";if(ȱ.Count==0){J+="- No problems detected -";}else{int Ĥ=1;foreach(var ĥ in ȱ
){J+=Ĥ+". "+ĥ.Replace("\n"," ")+"\n";Ĥ++;}}string í=Ň(F,J,W);W.WritePublicTitle("Isy's Inventory Manager Warnings");W.
WritePublicText(í,false);W.SetValue<Int64>("alignment",0);W.Font="Monospace";W.ShowPublicTextOnScreen();}}void Ħ(){ǈ.Clear();
GridTerminalSystem.GetBlocksOfType<IMyTextPanel>(ǈ,e=>e.CustomName.Contains(performanceLCDKeyword));if(ǈ.Count==0)return;foreach(var W in
ǈ){if(W.GetPublicTitle()!="Isy's Inventory Manager Performance"){W.FontSize=0.47f;}float F=W.FontSize;string J=
"Isy's Inventory Manager Performance\n";J+="===================================\n\n";J+=Ǉ.Replace("=\n","").Replace("=","");string í=Ň(F,J,W);W.
WritePublicTitle("Isy's Inventory Manager Performance");W.WritePublicText(í,false);W.SetValue<Int64>("alignment",0);W.Font="Monospace";W
.ShowPublicTextOnScreen();}}void d(){var Y=new List<IMyTextPanel>();GridTerminalSystem.GetBlocksOfType<IMyTextPanel>(Y,e
=>e.CustomName.Contains(inventoryLCDKeyword));if(Y.Count==0)return;HashSet<string>f=new HashSet<string>();foreach(var W in
Y){f.Add(System.Text.RegularExpressions.Regex.Match(W.CustomName,inventoryLCDKeyword+@":\D+").Value);}f.RemoveWhere(h=>h
=="");foreach(var j in f){List<IMyTextPanel>k=new List<IMyTextPanel>();GridTerminalSystem.GetBlocksOfType<IMyTextPanel>(k,
e=>e.CustomName.Contains(j));Y=Y.Except(k).ToList();string m=inventoryLCDKeyword+@":\w+";k.Sort((o,q)=>System.Text.
RegularExpressions.Regex.Match(o.CustomName,m).Value.CompareTo(System.Text.RegularExpressions.Regex.Match(q.CustomName,m).Value));string J
=º(k[0]);float F=k[0].FontSize;if(!k[0].CustomData.ToLower().Contains("noscroll")){J=Ň(F/k.Count,J,k[0],2);}var u=J.Split
('\n');int w=u.Length;int À=0;int z=(int)Math.Ceiling(17/F);foreach(var W in k){W.FontSize=F;W.WritePublicTitle(
"Items for LCD Group: "+j.Replace(inventoryLCDKeyword+":",""));W.SetValue<Int64>("alignment",0);W.Font="Monospace";W.ShowPublicTextOnScreen();
int ª=0;string µ="";while(À<w&&ª<z){µ+=u[À]+"\n";À++;ª++;}W.WritePublicText(µ);}}foreach(var W in Y){string J=º(W);float F=
W.FontSize;if(!W.CustomData.ToLower().Contains("noscroll")){J=Ň(F,J,W,0);}W.WritePublicTitle("Inventory Items");W.
WritePublicText(J,false);W.SetValue<Int64>("alignment",0);W.Font="Monospace";W.ShowPublicTextOnScreen();}}string º(IMyTextPanel W){
float F=W.FontSize;int G=W.BlockDefinition.SubtypeName.Contains("Wide")?52:26;string J="";if(W.CustomData.Length<1){J=
"Put an item or type name in the custom data.\n\n"+"Examples:\nComponent\nIngot\nSteelPlate\nInteriorPlate\n\n"+
"Optionally, add a max amount for the bars as a 2nd parameter.\n\n"+"Example:\nIngot 100000\n\n"+"At last, add any of these modifiers.\n"+"There are 4 modifiers at this point:\n\n"+
"'noHeading' to hide the heading\n"+"'noBar' to hide the bars\n"+"'noScroll' to prevent the text from scrolling\n"+
"'hideEmpty' to hide items that have an amount of 0\n\n"+"Examples:\nComponent 100000 noBar\nSteelPlate noHeading noBar hideEmpty\n\n"+
"To display multiple different items, use a new line for every item!\n\n"+"Hint: One 'noScroll' modifier per screen is enough!\n\n";W.FontSize=0.5f;}else{var v=W.CustomData.Split('\n').ToList()
;v.RemoveAll(e=>e.Length<=1);foreach(var Z in v){var A=Z.Split(' ');double I=100000;bool B=false;bool C=false;bool D=
false;if(A.Length>=2){try{I=Convert.ToDouble(A[1]);}catch{I=100000;}}if(Z.ToLower().Contains("noheading"))B=true;if(Z.ToLower
().Contains("nobar"))C=true;if(Z.ToLower().Contains("hideempty"))D=true;J+=E(F,G,A[0],I,B,C,D);}}return J.TrimStart('\n')
;}string E(float F,int G,string H,double I,bool B=false,bool C=false,bool D=false){string J="";bool K=false;foreach(var L
in ȍ){if(L.ToString().ToLower().Contains(H.ToLower())){if(J==""&&!B){string M="Items containing '"+char.ToUpper(H[0])+H.
Substring(1).ToLower()+"'";J="\n"+' '.ş((int)(G/F)/2-M.Length/2)+M+"\n\n";}double N=ì(L);if(N==0&&D)continue;J+=Ŗ(F,G,L.SubtypeId
.ToString(),N,I,N.Ť(),I.Ť(),C);K=true;}}if(!K){J="\nError!\n\n";J+="No items containing '"+H+
"' found!\nCheck the custom data of this LCD and enter a valid type or item name!\n";}return J;}void O(){if(Ǌ==99){Ǌ=0;}else{Ǌ++;}Echo("Isy's Inventory Manager "+ȭ[Ȯ]+"\n====================\n");if(ĥ!=
null){Echo("Warning!\n"+ĥ+"\n");}if(ȯ.Count==0){Echo("Hint:\nBuild a LCD and add the main LCD\nkeyword '"+mainLCDKeyword+
"' to its name to get\nmore informations about your base\nand the current script actions.\n");}Ǉ="";Ǉ+="Script is running in "+(ƾ?"station":"ship")+" mode\n\n";Ǉ+="Task: "+ǎ[ȗ]+"\n";Ǉ+="Script step: "+ȗ+" / "+(ǎ.
Length-1)+"\n\n";int P=Runtime.CurrentInstructionCount;if(P>ǐ)ǐ=P;ǋ[Ǌ]=P;double Q=ǋ.Sum()/ǋ.Count;Ǉ+="Instructions: "+P+" / "+
Runtime.MaxInstructionCount+"\n";Ǉ+="Max. Instructions: "+ǐ+" / "+Runtime.MaxInstructionCount+"\n";Ǉ+="Avg. Instructions: "+
Math.Floor(Q)+" / "+Runtime.MaxInstructionCount+"\n\n";double R=Runtime.LastRunTimeMs;if(R>ǉ)ǉ=R;ǌ[Ǌ]=R;double S=ǌ.Sum()/ǌ.
Count;Ǉ+="Last runtime "+Math.Round(R,4)+" ms\n";Ǉ+="Max. runtime "+Math.Round(ǉ,4)+" ms\n";Ǉ+="Avg. runtime "+Math.Round(S,4
)+" ms\n\n";Ǉ+="Instructions per Method:\n===================\n\n";Ǎ[ǎ[ȗ]]=P;foreach(var L in Ǎ.OrderByDescending(T=>T.
Value)){Ǉ+="- "+L.Key+": "+L.Value+"\n";}Ǉ+="\n";if(ț.Count>0){Ǉ+="Excluded grids:\n============\n\n";foreach(var U in ț){Ǉ+=
U.CustomName+"\n";}}Echo(Ǉ);}bool V(IMyTextPanel W,string X){à(W);var v=W.CustomData.Replace(" ","").Split('\n');foreach(
var Z in v){if(Z.Contains(X+"=")){try{return Convert.ToBoolean(Z.Replace(X+"=",""));}catch{return true;}}}return true;}void
à(IMyTextPanel W){var v=W.CustomData.Split('\n');if(v.Length!=Ȱ.Length){string Ù="";foreach(var L in Ȱ){Ù+=L+"\n";}W.
CustomData=Ù.TrimEnd('\n');W.FontSize=0.5f;}}double Ú(string Û,IMyTerminalBlock Å,int Ü,IMyTerminalBlock Ò,int Ý,double N=-1,bool
Þ=false){var ß=Å.GetInventory(Ü);var Ð=new List<MyInventoryItem>();ß.GetItems(Ð);if(Ð.Count==0)return 0;var Ó=Ò.
GetInventory(Ý);if((double)Ó.CurrentVolume>(double)Ó.MaxVolume*0.99)return 0;double ë=0;MyDefinitionId Ã=new MyDefinitionId();
MyDefinitionId á=new MyDefinitionId();string â="";string ã="";bool ä=false;string å="";if(N==-0.5)å="halfInventory";if(N==-1)å=
"completeInventory";for(var T=Ð.Count-1;T>=0;T--){Ã=Ð[T].Type;if(Þ?Ã.ToString()==Û:Ã.ToString().Contains(Û)){if(å!=""&&Ã!=á)ë=0;á=Ã;â=Ã.
TypeId.ToString().Replace(Ȅ,"");ã=Ã.SubtypeId.ToString();ä=true;if(!ß.CanTransferItemTo(Ó,Ã)){Ƣ("'"+ã+
"' couldn't be transferred\nfrom '"+Å.CustomName+"'\nto '"+Ò.CustomName+"'\nThere's no conveyor line between them or the conveyor type was too small!");}
double æ=(double)Ð[T].Amount;double ç=0;if(å=="completeInventory"){ß.TransferItemTo(Ó,T,null,true);}else if(å=="halfInventory"
){double è=Math.Ceiling((double)Ð[T].Amount/2);ß.TransferItemTo(Ó,T,null,true,(VRage.MyFixedPoint)è);}else{if(!â.Contains
(ȇ))N=Math.Ceiling(N);ß.TransferItemTo(Ó,T,null,true,(VRage.MyFixedPoint)N);}Ð.Clear();ß.GetItems(Ð);try{if((
MyDefinitionId)Ð[T].Type==Ã){ç=(double)Ð[T].Amount;}}catch{ç=0;}double é=æ-ç;ë+=é;N-=é;if(N<=0&&å=="")break;}}if(!ä)return 0;if(ë>0){
string ê=Math.Round(ë,2)+" "+ã+" "+â;Ȭ="Moved: "+ê+"\nfrom : '"+Å.CustomName+"'\nto   : '"+Ò.CustomName+"'";}else{string ê=
Math.Round(N,2)+" "+Û.Replace(Ȅ,"");if(å=="completeInventory")ê="all items";if(å=="halfInventory")ê="half of the items";Ƣ(
"Couldn't move '"+ê+"'\nfrom '"+Å.CustomName+"'\nto '"+Ò.CustomName+"'\nCheck conveyor connection and owner/faction!");}return ë;}double
ì(MyDefinitionId Ã,IMyTerminalBlock Á,int Ö=0){return(double)Á.GetInventory(Ö).GetItemAmount(Ã);;}IMyTerminalBlock Â(
MyDefinitionId Ã,bool Ä=false,IMyTerminalBlock Å=null){try{if(Ȩ.GetInventory(0).FindItem(Ã)!=null){return Ȩ;}}catch{}foreach(var Æ in
ǭ){if(Ã.SubtypeId.ToString()=="Ice"&&Æ.GetType().ToString().Contains("MyGasGenerator"))continue;if(Æ.GetInventory(0).
FindItem(Ã)!=null){Ȩ=Æ;return Æ;}}if(Ä){foreach(var Æ in Ȣ){if(Å!=null){if(Ě(Æ)<=Ě(Å))continue;}if(Æ.GetInventory(0).FindItem(Ã)
!=null){Ȩ=Æ;return Æ;}}}return null;}IMyTerminalBlock Ç(IMyTerminalBlock È,string É=""){List<IMyCargoContainer>Ê=new List<
IMyCargoContainer>();GridTerminalSystem.GetBlocksOfType<IMyCargoContainer>(Ê,Ë=>Ë.CubeGrid==È.CubeGrid&&!Ë.CustomName.ToLower().Contains(
Ȥ)&&!Ë.CustomName.ToLower().Contains(ȥ)&&!Ë.CustomName.Contains(ǁ));if(É!=""){Ê.RemoveAll(Ë=>!Ë.CustomName.Contains(É));}
if(Ê.Count==0){GridTerminalSystem.GetBlocksOfType<IMyCargoContainer>(Ê,Ë=>!Ë.CustomName.ToLower().Contains(Ȥ)&&!Ë.
CustomName.ToLower().Contains(ȥ)&&!Ë.CustomName.Contains(ǁ));}if(Ê.Count==0){Ƣ("'"+È.CustomName+
"'\nhas no containers to move its items!");return null;}else{IMyTerminalBlock Ì=null;foreach(var Æ in Ê){if(Æ==È)continue;var Í=Æ.GetInventory(0);if((float)Í.
CurrentVolume<(float)Í.MaxVolume*0.99){Ì=Æ;break;}}if(Ì==null){Ƣ("'"+È.CustomName+
"'\nhas no empty containers on its grid!\nCan't move its items!");return null;}else{return Ì;}}}void Î(){foreach(var Í in ǫ){if(Ɨ(75))return;var Ï=Í.GetInventory(0);var Ð=new List<
MyInventoryItem>();Ï.GetItems(Ð);for(int T=0;T<Ð.Count;T++){MyDefinitionId Ã=Ð[T].Type;VRage.MyFixedPoint Ñ=Œ(Ã);if(Ñ>0)continue;if(Ð[T
].Amount<1)continue;IMyTerminalBlock Ò=Ç(Í);if(Ò==null)continue;Ñ=(VRage.MyFixedPoint)0.00037;var Ó=Ò.GetInventory(0);
VRage.MyFixedPoint Ô=Ï.CurrentVolume;Ï.TransferItemTo(Ó,T,null,false,1);VRage.MyFixedPoint Õ=Ï.CurrentVolume;Ï.
TransferItemFrom(Ó,Ó.ItemCount-1,null,true,1);Ñ=Ô-Õ;œ(Ã,Ñ);ƨ(Ã,Ñ);}}}int Ě(IMyTerminalBlock Á){string ƕ=System.Text.RegularExpressions.
Regex.Match(Á.CustomName,@"p\d+|pmax|pmin",System.Text.RegularExpressions.RegexOptions.IgnoreCase).Value.ToLower().Replace(
"p","");int ƅ=0;bool Ɔ=true;if(ƕ=="max"){ƅ=int.MinValue;}else if(ƕ=="min"){ƅ=int.MaxValue;}else{Ɔ=Int32.TryParse(ƕ,out ƅ);}
if(!Ɔ){Int32.TryParse(Á.EntityId.ToString().Substring(0,4),out ƅ);}return ƅ;}void Ƈ(IMyTerminalBlock Á,int ĸ){string ƈ=
System.Text.RegularExpressions.Regex.Match(Á.CustomName,@"p\d+|pmax|pmin",System.Text.RegularExpressions.RegexOptions.
IgnoreCase).Value;string Ɖ="";if(ĸ==int.MaxValue){Ɖ="PMax";}else if(ĸ==int.MinValue){Ɖ="PMin";}else{Ɖ="P"+ĸ;}if(ƈ==Ɖ){return;}else
if(ƈ!=""){Á.CustomName=Á.CustomName.Replace(ƈ,Ɖ);}else{Á.CustomName=Á.CustomName+" "+Ɖ;}}string Ɗ(string X){ƍ();var Ƌ=
Storage.Split('\n');foreach(var Z in Ƌ){if(Z.Contains(X)){return Z.Replace(X+"=","");}}return"";}void ƌ(string X,string ĸ=""){ƍ
();var Ƌ=Storage.Split('\n');string Ǝ="";foreach(var Z in Ƌ){if(Z.Contains(X)){Ǝ+=X+"="+ĸ+"\n";}else{Ǝ+=Z+"\n";}}Storage=
Ǝ.TrimEnd('\n');}void ƍ(){var Ƌ=Storage.Split('\n');if(Ƌ.Length!=ǽ.Count){string Ǝ="";foreach(var L in ǽ){Ǝ+=L.Key+"="+L.
Value+"\n";}Storage=Ǝ.TrimEnd('\n');}}void Ə(IMyTerminalBlock Æ){foreach(var Ɛ in ƽ.Keys.ToList()){ƽ[Ɛ]="0";}List<string>Ƒ=Æ.
CustomData.Replace(" ","").TrimEnd('\n').Split('\n').ToList();Ƒ.RemoveAll(Z=>!Z.Contains("=")||Z.Length<8);bool ƒ=false;foreach(
var Z in Ƒ){var Ɠ=Z.Split('=');if(!ƽ.ContainsKey(Ɠ[0])){MyDefinitionId Ã;if(MyDefinitionId.TryParse(Ȅ+Ɠ[0],out Ã)){ſ(Ã);ƒ=
true;}}ƽ[Ɠ[0]]=Ɠ[1];}if(ƒ)ƀ();List<string>Ƅ=new List<string>{"Special Container modes:","",
"Positive number: stores wanted amount, removes excess (e.g.: 100)","Negative number: doesn't store items, only removes excess (e.g.: -100)",
"Keyword 'all': stores all items of that subtype (like a type container)",""};foreach(var L in ƽ){Ƅ.Add(L.Key+"="+L.Value);}Æ.CustomData=string.Join("\n",Ƅ);}void ƃ(){Ț.Clear();Ț.AddRange(Ȑ);Ț.
AddRange(ȑ);Ț.AddRange(Ȓ);Ț.AddRange(ȓ);Ț.AddRange(Ȕ);ƽ.Clear();foreach(var L in Ȑ){ƽ[ȕ+"/"+L]="0";}foreach(var L in Ȏ){ƽ[ȅ+"/"+
L]="0";}foreach(var L in ȏ){ƽ[ȇ+"/"+L]="0";}foreach(var L in ȑ){ƽ[Ȉ+"/"+L]="0";}foreach(var L in Ȓ){ƽ[ȉ+"/"+L]="0";}
foreach(var L in ȓ){ƽ[Ȋ+"/"+L]="0";}foreach(var L in Ȕ){ƽ[ȋ+"/"+L]="0";}}void ž(){foreach(var Í in ǫ){if(Ɨ(75))return;var Ð=new
List<MyInventoryItem>();Í.GetInventory(0).GetItems(Ð);foreach(var L in Ð){MyDefinitionId Ã=L.Type;if(ȍ.Contains(Ã))continue;
string â=Ã.TypeId.ToString().Replace(Ȅ,"");string ã=Ã.SubtypeId.ToString();Ȭ="Found new item!\n"+ã+" ("+â+")";if(â==ȅ){Ȏ.Add(ã
);ƞ(ã);if(!ã.Contains("Ice")&&!ã.Contains("Stone")){if(ǲ.Count>0){if(ǲ[0].GetInventory(0).CanItemsBeAdded(1,Ã)){if(!ȁ.
Contains(ã))ȁ.Add(ã);if(!Ȃ.Contains(ã)&&!ȃ.Contains(ã))Ȃ.Add(ã);}}}}else if(â==ȇ){ȏ.Add(ã);}else if(â==ȕ){Ȑ.Add(ã);}else if(â==Ȉ
){ȑ.Add(ã);}else if(â==ȉ){Ȓ.Add(ã);}else if(â==Ȋ){ȓ.Add(ã);}else if(â==ȋ){Ȕ.Add(ã);}ſ(Ã);Ƥ(Ã);}}}void ſ(MyDefinitionId Ã)
{à();if(Me.CustomData.Contains(Ã.ToString()))return;var v=Me.CustomData.Split('\n').ToList();v.RemoveAll(Z=>!Z.Contains(
";"));v.Add(Ã+";noBP;0");Me.CustomData=String.Join("\n",v);Ŕ(Ã);}bool ƀ(){à();var v=Me.CustomData.Split('\n');foreach(var Z
in v){var Ɓ=Z.Split(';');if(Z==Ǽ||Ɓ.Length!=3)continue;MyDefinitionId Ã=MyDefinitionId.Parse(Ɓ[0]);string Ƃ=Ɓ[1];VRage.
MyFixedPoint Ñ=VRage.MyFixedPoint.DeserializeString(Ɓ[2]);MyDefinitionId Ø;if(MyDefinitionId.TryParse(Ƃ,out Ø)){if(Ǵ.Count==0)return
false;if(ƣ(Ø)){ŏ(Ã,Ø);}else{Ʃ(Ã);continue;}}string â=Ã.TypeId.ToString().Replace(Ȅ,"");string ã=Ã.SubtypeId.ToString();if(â==
ȅ){Ȏ.Add(ã);ƞ(ã);if(!ã.Contains("Ice")&&!ã.Contains("Stone")){if(ǲ.Count>0){if(ǲ[0].GetInventory(0).CanItemsBeAdded(1,Ã))
{if(!ȁ.Contains(ã))ȁ.Add(ã);if(!Ȃ.Contains(ã)&&!ȃ.Contains(ã))Ȃ.Add(ã);}}}}else if(â==ȇ){ȏ.Add(ã);}else if(â==ȕ){Ȑ.Add(ã)
;}else if(â==Ȉ){ȑ.Add(ã);}else if(â==ȉ){Ȓ.Add(ã);}else if(â==Ȋ){ȓ.Add(ã);}else if(â==ȋ){Ȕ.Add(ã);}Ŕ(Ã);if(Ñ!=0){œ(Ã,Ñ);}}
return true;}void à(){if(!Me.CustomData.Contains(Ǽ)){Me.CustomData=(ƾ?ƿ:ǀ)+Ǽ;}}void Ɣ(){foreach(var Ĉ in Ǵ){var Ð=new List<
MyInventoryItem>();Ĉ.GetInventory(1).GetItems(Ð);var Č=new List<MyProductionItem>();Ĉ.GetQueue(Č);if(Ð.Count==1&&Č.Count==1&&Ĉ.Mode==
MyAssemblerMode.Assembly){if(Ŏ(Č[0].BlueprintId))continue;MyDefinitionId Ã=Ð[0].Type;if(!ȍ.Contains(Ã))continue;Ȭ=
"Learned new Blueprint!\n'"+Č[0].BlueprintId.ToString().Replace(Ȅ,"")+"'\nproduces: '"+Ã.ToString().Replace(Ȅ,"")+"'";ŏ(Ã,Č[0].BlueprintId);ƪ(Ã,Č[0
].BlueprintId.ToString());}}}bool ƣ(MyDefinitionId Ø){try{foreach(var Ĉ in Ǵ){if(Ĉ.CanUseBlueprint(Ø))return true;}}catch
{return false;}return false;}void Ƥ(MyDefinitionId Ã){if(Ǵ.Count==0)return;if(Ã.TypeId.ToString()==Ȅ+ȅ||Ã.TypeId.ToString
()==Ȅ+ȇ)return;MyDefinitionId Ø;bool Ō=ƺ.TryGetValue(Ã,out Ø);if(Ō)Ō=ƣ(Ø);if(!Ō){string[]ƥ={"","Component","Magazine"};
bool Ʀ=false;for(int T=0;T<ƥ.Length;T++){string Ƨ=Ȍ+Ã.SubtypeId.ToString().Replace("Item","")+ƥ[T];MyDefinitionId.TryParse(Ƨ
,out Ø);Ʀ=ƣ(Ø);if(Ʀ){ŏ(Ã,Ø);ƪ(Ã,Ø.ToString());Ō=true;return;}}}}void ƪ(MyDefinitionId Ã,string Ø){à();var v=Me.CustomData
.Split('\n');for(var T=0;T<v.Length;T++){if(!v[T].Contains(Ã.ToString()))continue;var Ɓ=v[T].Split(';');if(Ɓ.Length!=3)
continue;v[T]=Ɓ[0]+";"+Ø+";"+Ɓ[2];Me.CustomData=String.Join("\n",v);return;}}void ƨ(MyDefinitionId Ã,VRage.MyFixedPoint Ñ){à();
var v=Me.CustomData.Split('\n');for(var T=0;T<v.Length;T++){if(!v[T].Contains(Ã.ToString()))continue;var Ɓ=v[T].Split(';');
if(Ɓ.Length!=3)continue;if(Ɓ[2]!="0")return;v[T]=Ɓ[0]+";"+Ɓ[1]+";"+Ñ.SerializeString();Me.CustomData=String.Join("\n",v);
return;}}void Ʃ(MyDefinitionId Ã){à();var v=Me.CustomData.Split('\n').ToList();v.RemoveAll(T=>T.Contains(Ã.ToString()));Me.
CustomData=String.Join("\n",v);}void Ƣ(string ğ){ȱ.Add(ğ);Ȳ.Add(ğ);ĥ=ȱ.ElementAt(0);}void Ɩ(){Me.CustomData="";foreach(var Æ in Ȣ)
{List<string>v=Æ.CustomData.Replace(" ","").TrimEnd('\n').Split('\n').ToList();v.RemoveAll(Z=>!Z.Contains("=")||Z.
Contains("=0"));Æ.CustomData=string.Join("\n",v);}Echo("Stored items deleted!\n");if(Ȣ.Count>0)Echo("Also deleted itemlists of "
+Ȣ.Count+" Special containers!\n");Echo("Please hit 'Recompile'!\n\nScript stopped!");}bool Ɨ(double Ė){return Runtime.
CurrentInstructionCount>Runtime.MaxInstructionCount*(Ė/100);}void Ƙ(){Ȗ.Clear();List<IMyTerminalBlock>ƙ=Ǵ.ToList<IMyTerminalBlock>();List<
IMyTerminalBlock>ƚ=ǰ.ToList<IMyTerminalBlock>();ƛ(ǫ,0);ƛ(ƙ,1);ƛ(ƚ,1);}void ƛ(List<IMyTerminalBlock>Ɯ,int Ö){foreach(var Æ in Ɯ){var Ð=
new List<MyInventoryItem>();Æ.GetInventory(Ö).GetItems(Ð);foreach(var L in Ð){MyDefinitionId Ã=L.Type;if(Ȗ.ContainsKey(Ã)){
Ȗ[Ã]+=(double)L.Amount;}else{Ȗ[Ã]=(double)L.Amount;bool Ɲ;ŋ(Ã,out Ɲ);}}}}double ì(MyDefinitionId Ã){double Ŋ;Ȗ.
TryGetValue(Ã,out Ŋ);return Ŋ;}void ƞ(string Ɵ){if(!oreYieldDict.ContainsKey(Ɵ)){oreYieldDict[Ɵ]=3;}}double Ơ(string Ɵ){double Ŋ;Ɵ=
Ɵ.Replace(Ȅ+ȅ+"/","");oreYieldDict.TryGetValue(Ɵ,out Ŋ);return Ŋ!=0?Ŋ:3;}void ơ(){Ǫ.Clear();foreach(IMyAssembler Ĉ in Ǵ){
var Č=new List<MyProductionItem>();Ĉ.GetQueue(Č);if(Č.Count>0&&!Ĉ.IsProducing){Ƣ("'"+Ĉ.CustomName+
"' has a queue but is currently not producing!");}foreach(var L in Č){MyDefinitionId Ø=L.BlueprintId;if(Ǫ.ContainsKey(Ø)){Ǫ[Ø]+=(double)L.Amount;}else{Ǫ[Ø]=(double)L.
Amount;}}}}double ŉ(MyDefinitionId Ø){double Ŋ;Ǫ.TryGetValue(Ø,out Ŋ);return Ŋ;}MyDefinitionId ŋ(MyDefinitionId Ã,out bool Ō){
MyDefinitionId Ø;Ō=ƺ.TryGetValue(Ã,out Ø);return Ø;}MyDefinitionId ō(MyDefinitionId Ø){MyDefinitionId Ã;Ƹ.TryGetValue(Ø,out Ã);return
Ã;}bool Ŏ(MyDefinitionId Ø){return Ƹ.ContainsKey(Ø);}void ŏ(MyDefinitionId Ã,MyDefinitionId Ø){ƺ[Ã]=Ø;Ƹ[Ø]=Ã;}double ő(
MyDefinitionId Ã){return(double)Œ(Ã);}VRage.MyFixedPoint Œ(MyDefinitionId Ã){VRage.MyFixedPoint Ŋ;ƻ.TryGetValue(Ã,out Ŋ);return Ŋ;}
void œ(MyDefinitionId L,VRage.MyFixedPoint Ñ){ƻ[L]=Ñ;}void Ŕ(MyDefinitionId Ã){ȍ.Add(Ã);Ƽ[Ã.SubtypeId.ToString()]=Ã;}
MyDefinitionId ŕ(string ã){MyDefinitionId Ã=new MyDefinitionId();Ƽ.TryGetValue(ã,out Ã);return Ã;}string Ŗ(double F,int G,string M,
double ĸ,double ň,string Ĺ=null,string ĺ=null,bool C=false,bool Ļ=false){string ě=ĸ.ToString();string Ĝ=ň.ToString();if(Ĺ!=
null){ě=Ĺ;}if(ĺ!=null){Ĝ=ĺ;}string ļ=ĸ.ť(ň);ļ=' '.ş(6-ļ.Length)+ļ;string Ľ=ě+" / "+Ĝ;int ľ=(int)(G/F);double Ŀ=0;if(ň>0)Ŀ=ĸ/
ň>=1?1:ĸ/ň;StringBuilder ŀ=new StringBuilder(M+" ");StringBuilder Ł=new StringBuilder();if(Ļ){if(F<=0.5||(F<=1&&G==52)){ŀ
.Append(' '.ş(9-ě.Length)+ě);ŀ.Append(" / "+Ĝ+' '.ş(9-Ĝ.Length));int ł=ŀ.Length+1;int Ń=ľ-ŀ.Length-ļ.Length-2;int ń=(int)
Math.Ceiling(Ń*Ŀ);ŀ.Append("["+'I'.ş(ń)+'.'.ş(Ń-ń)+"]");ŀ.Append(ļ+"\n");}else{int Ń=ľ-ŀ.Length-ļ.Length-2;int ń=(int)Math.
Ceiling(Ń*Ŀ);ŀ.Append("["+'I'.ş(ń)+'.'.ş(Ń-ń)+"]");ŀ.Append(ļ+"\n");}return ŀ.ToString();}else{if(F<=0.6||(F<=1&&G==52)){ŀ.
Append(' '.ş(ľ/2-(ŀ.Length+ě.Length)));ŀ.Append(ě+" / "+Ĝ);ŀ.Append(' '.ş(ľ-(ŀ.Length+ļ.Length)));ŀ.Append(ļ+"\n");if(!C){int
Ń=ľ-2;int ń=(int)Math.Ceiling(Ń*Ŀ);Ł=new StringBuilder("["+'I'.ş(ń)+'.'.ş(Ń-ń)+"]\n");}}else{ŀ.Append(' '.ş(ľ-(ŀ.Length+Ľ
.Length)));ŀ.Append(Ľ+"\n");if(!C){int Ń=ľ-ļ.Length-2;int ń=(int)Math.Ceiling(Ń*Ŀ);Ł=new StringBuilder("["+'I'.ş(ń)+'.'.ş
(Ń-ń)+"]");Ł.Append(ļ+"\n");}}return ŀ.Append(Ł).ToString();}}DateTime Ņ=DateTime.Now;Dictionary<long,List<int>>ņ=new
Dictionary<long,List<int>>();string Ň(float F,string ğ,IMyTextPanel W,int Ő=3,bool ŗ=true,int Ŷ=1){long ŭ=W.EntityId;if(!ņ.
ContainsKey(ŭ)){ņ[ŭ]=new List<int>{1,3,Ő,0};}int Ů=ņ[ŭ][0];int ů=ņ[ŭ][1];int Ű=ņ[ŭ][2];int ű=ņ[ŭ][3];var Ų=ğ.TrimEnd('\n').Split(
'\n');List<string>u=new List<string>();int ų=(int)Math.Ceiling(17/F*Ŷ);int ľ=(int)(26/F);string í="";if(W.BlockDefinition.
SubtypeName.Contains("Corner")){if(W.CubeGrid.GridSize==0.5){ų=(int)Math.Floor(5/F);}else{ų=(int)Math.Floor(3/F);}}if(W.
BlockDefinition.SubtypeName.Contains("Wide")){ľ=(int)(52/F);}foreach(var Z in Ų){if(Z.Length<=ľ){u.Add(Z);}else{try{string A="";var Ŵ=Z
.Split(' ');string ŵ=System.Text.RegularExpressions.Regex.Match(Z,@".+(\.|\:)\ ").Value;string ŷ=' '.ş(ŵ.Length);foreach(
var ż in Ŵ){if((A+" "+ż).Length>ľ){u.Add(A);A=ŷ+ż+" ";}else{A+=ż+" ";}}u.Add(A);}catch{u.Add(Z);}}}if(ŗ){if(u.Count>ų){if(
DateTime.Now.Second!=ű){ű=DateTime.Now.Second;if(ů>0)ů--;if(ů<=0)Ű+=Ů;if(Ű+ų-Ő>=u.Count&&ů<=0){Ů=-1;ů=3;}if(Ű<=Ő&&ů<=0){Ů=1;ů=3;
}}}else{Ű=Ő;Ů=1;ů=3;}ņ[ŭ][0]=Ů;ņ[ŭ][1]=ů;ņ[ŭ][2]=Ű;ņ[ŭ][3]=ű;}else{Ű=Ő;}for(var Z=0;Z<Ő;Z++){í+=u[Z]+"\n";}for(var Z=Ű;Z<
u.Count;Z++){í+=u[Z]+"\n";}return í;}IMyCubeGrid Ÿ=null;HashSet<IMyCubeGrid>Ź=new HashSet<IMyCubeGrid>();void ź(
IMyCubeGrid Ŭ){Ź.Add(Ŭ);List<IMyMotorStator>ū=new List<IMyMotorStator>();List<IMyPistonBase>ř=new List<IMyPistonBase>();
GridTerminalSystem.GetBlocksOfType<IMyMotorStator>(ū,Ś=>Ś.IsAttached&&Ś.TopGrid==Ŭ&&!Ź.Contains(Ś.CubeGrid));GridTerminalSystem.
GetBlocksOfType<IMyPistonBase>(ř,ś=>ś.IsAttached&&ś.TopGrid==Ŭ&&!Ź.Contains(ś.CubeGrid));if(ū.Count==0&&ř.Count==0){Ÿ=Ŭ;return;}else{
foreach(var Ŝ in ū){ź(Ŝ.CubeGrid);}foreach(var ŝ in ř){ź(ŝ.CubeGrid);}}}HashSet<IMyCubeGrid>Ż=new HashSet<IMyCubeGrid>();void Ž
(IMyCubeGrid Ŭ,bool Ř=false){if(Ř)Ż.Clear();Ż.Add(Ŭ);List<IMyMotorStator>ū=new List<IMyMotorStator>();List<IMyPistonBase>
ř=new List<IMyPistonBase>();GridTerminalSystem.GetBlocksOfType<IMyMotorStator>(ū,Ś=>Ś.CubeGrid==Ŭ&&Ś.IsAttached&&!Ż.
Contains(Ś.TopGrid));GridTerminalSystem.GetBlocksOfType<IMyPistonBase>(ř,ś=>ś.CubeGrid==Ŭ&&ś.IsAttached&&!Ż.Contains(ś.TopGrid))
;foreach(var Ŝ in ū){Ž(Ŝ.TopGrid);}foreach(var ŝ in ř){Ž(ŝ.TopGrid);}}
}static partial class Ş{public static string ş(this char Š,int š){if(š<=0){return"";}return new string(Š,š);}}static
partial class Ş{public static string Ţ(this double ĸ){string ţ="kL";if(ĸ<1){ĸ*=1000;ţ="L";}else if(ĸ>=1000&&ĸ<1000000){ĸ/=1000;
ţ="ML";}else if(ĸ>=1000000&&ĸ<1000000000){ĸ/=1000000;ţ="BL";}else if(ĸ>=1000000000){ĸ/=1000000000;ţ="TL";}return Math.
Round(ĸ,1)+" "+ţ;}}static partial class Ş{public static string Ť(this double ĸ){string ţ="";if(ĸ>=1000&&ĸ<1000000){ĸ/=1000;ţ=
" k";}else if(ĸ>=1000000&&ĸ<1000000000){ĸ/=1000000;ţ=" M";}else if(ĸ>=1000000000){ĸ/=1000000000;ţ=" B";}return Math.Round(ĸ,
1)+ţ;}}static partial class Ş{public static string ť(this double Ŧ,double ŧ){double Ė=Math.Round(Ŧ/ŧ*100,1);if(ŧ==0){
return"0%";}else{return Ė+"%";}}}class Ũ:IComparer<MyDefinitionId>{public int Compare(MyDefinitionId ũ,MyDefinitionId Ć){
return ũ.ToString().CompareTo(Ć.ToString());}}class Ū:IEqualityComparer<MyInventoryItem>{public bool Equals(MyInventoryItem ũ,
MyInventoryItem Ć){return ũ.ToString()==Ć.ToString();}public int GetHashCode(MyInventoryItem L){return L.ToString().GetHashCode();}
