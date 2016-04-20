this = {}

function this.Update()
	if Input.IsPressed(36) == 1 then
		gameState = 0
	end
	if Input.IsPressed(57) == 1 then
		this.LoadTileMaps(2)
	end
end

function this.LoadCollisionMap()
	this.collisionMap = CollisionMap.New()
	this.collisionMap:Load("testMap")
end

function this.LoadTileMaps (level)
	--Load TileMap
	this.tileMapBackground = TileMap.New()
	this.tileMapForeground = TileMap.New()

	--tiles size in pixels
	tileSizeX = 16
	tileSizeY = 16

	--amount of tiles in the map
	sizeX = 32
	sizeY = 32
	
	if level == 1 then
		map = this.MapOneB()
	elseif level == 2 then
		map = this.MapTwoB()
	end

	this.tileMapBackground:Load("town_tiles.png", tileSizeX, tileSizeY, sizeX, sizeY, map);

	if level == 1 then
		map = this.MapOneF()
	elseif level == 2 then
		map = this.MapTwoF()
	end

	this.tileMapForeground:Load("town_tiles.png", tileSizeX, tileSizeY, sizeX, sizeY, map);

end

function this.Draw ()
	--Draw tileMap
	this.tileMapBackground:Draw()
	this.tileMapForeground:Draw()
end

function this.MapOneB()
	map = {}

	for i = 1, 32 * 32 do
		map[i] = 11	-- all grass
	end
	
	for j = 1, 32 * 16 do
		map[j] = 7	-- all grass
	end

	return map
end

function this.MapTwoB()
	map = {}

	for i = 1, 32 * 32 do
		map[i] = 11	-- all grass
	end

	return map
end


function this.MapOneF()
	map = {}

	for i = 1, 32 * 32 do
		map[i] = -1	-- all grass
	end
	
	map[34] = 13;

	return map
end

function this.MapTwoF()
	map = {}

	for i = 1, 32 * 32 do
		map[i] = -1	-- all grass
	end

	map[534] = 13;

	return map
end

function this.Create()
	this.LoadTileMaps(1)
	this.LoadCollisionMap()
end

return this