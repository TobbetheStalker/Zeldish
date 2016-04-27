region = {}
ai = require("AI")

function region.Update()
	if Input.IsPressed(36) == 1 then
		gameState = 0
	end
	if Input.IsPressed(57) == 1 then
		region.LoadTileMaps(2)
	end

	ai.Update(region.player, region.enemies);

end

function region.LoadCollisionMap()
	region.collisionMap = CollisionMap.New()
	region.collisionMap:Load("testMap")
end

function region.LoadTileMaps(level)
	--Load TileMap
	region.tileMapBackground = TileMap.New()
	region.tileMapForeground = TileMap.New()

	--tiles size in pixels
	tileSizeX = 16
	tileSizeY = 16

	--amount of tiles in the map
	sizeX = 32
	sizeY = 32
	
	if level == 1 then
		map = region.MapOneB()
	elseif level == 2 then
		map = region.MapTwoB()
	end

	region.tileMapBackground:Load("town_tiles.png", tileSizeX, tileSizeY, sizeX, sizeY, map);

	if level == 1 then
		map = region.MapOneF()
	elseif level == 2 then
		map = region.MapTwoF()
	end

	region.tileMapForeground:Load("town_tiles.png", tileSizeX, tileSizeY, sizeX, sizeY, map);

end

function region.Draw()
	--Draw tileMap
	region.tileMapBackground:Draw()
	region.player:Draw()
	region.tileMapForeground:Draw()
end

function region.MapOneB()
	map = {}

	for i = 1, 32 * 32 do
		map[i] = 11	-- all grass
	end
	
	for j = 1, 32 * 16 do
		map[j] = 7	-- all grass
	end

	return map
end

function region.MapTwoB()
	map = {}

	for i = 1, 32 * 32 do
		map[i] = 11	-- all grass
	end

	return map
end


function region.MapOneF()
	map = {}

	for i = 1, 32 * 32 do
		map[i] = -1	-- all grass
	end
	
	map[34] = 13;

	return map
end

function region.MapTwoF()
	map = {}

	for i = 1, 32 * 32 do
		map[i] = -1	-- all grass
	end

	map[534] = 13;

	return map
end

function region.Create()
	region.LoadTileMaps(1)
	region.LoadCollisionMap()
	region.player = Entity.New()
	region.enemy = Entity.New()
	region.enemy:SetPos(100, 100);
	region.enemies = {region.enemy};
	region.player:Initialize()
	region.player:SetPos(64, 64)

end

return region