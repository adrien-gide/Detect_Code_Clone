public Position WalkEast()
{
var player = GetPlayer();
player.Move("E");
return player.NewPosition;
}

public Position WalkWest()
{
var player = GetPlayer();
player.Move("W");
return player.NewPosition;
}
