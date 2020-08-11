List<MyDetectedEntityInfo> entity_list = new List<MyDetectedEntityInfo>();
public Program()
{
    Runtime.UpdateFrequency = UpdateFrequency.Update10;
    //This makes the program automatically run every 10 ticks.
}
public void Main()
{
    var door_sensor = GridTerminalSystem.GetBlockWithName("Door Sensor 1") as IMySensorBlock;
    door_sensor.DetectedEntities (entity_list);
    if (entity_list.Count == 0)
    {
        var door = GridTerminalSystem.GetBlockWithName("Door 1") as IMyDoor;
        door.ApplyAction ("Open_Off");
    }
}
