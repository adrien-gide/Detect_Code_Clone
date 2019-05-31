public Position WalkNorth()
{
var player = GetPlayer();
player.Move("N");
return player.NewPosition;
}

public Position WalkSouth()
{
var player = GetPlayer();
player.Move("S");
return player.NewPosition;
}
