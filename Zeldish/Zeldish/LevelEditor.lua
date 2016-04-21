this = {}

function Update()
	
end

function CreateEmpty()
	--Create TileMaps
	this.tileMapBackground = TileMap.New()
	this.tileMapForeground = TileMap.New()

	--tiles size in pixels
	tileSizeX = 16
	tileSizeY = 16

	--amount of tiles in the map
	sizeX = 33
	sizeY = 32
	
	map = this.MapGrass()

	this.tileMapBackground:Load("town_tiles.png", tileSizeX, tileSizeY, sizeX, sizeY, map);

	sizeX = 32
	map = this.MapEmpty()

	this.tileMapForeground:Load("town_tiles.png", tileSizeX, tileSizeY, sizeX, sizeY, map);

	this.collisionMap = CollisionMap.New()
	this.collisionMap.Empty()

	--Set some needed state variables
	this.workingLayer = 0 --0: Background, 1: Entities, 2: Foreground
end

function this.MapGrass()
	map = {}

	for i = 1, 33 * 32 do
		map[i] = 11	-- all grass
	end
	for i = 1, 32 do
		map[i * 32 + 1] = i
	end

	return map
end

function this.MapEmpty()
	map = {}

	for i = 1, 32 * 32 do
		map[i] = -1	-- all empty
	end

	return map
end

function Load()

end

function Save()

end

return this