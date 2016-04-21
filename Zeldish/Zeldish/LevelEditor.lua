editor = {}

function editor.Update()
	if Input.IsPressed(36) == 1 then
		gameState = 0
	end
	if Input.IsPressed(57) == 1 then
		if editor.tileInfo == 1 then
			print("[LUA] Mouse pos; X: " .. Input.GetMousePosX() .. ", Y: " .. Input.GetMousePosY())
			editor.tileInfo = 0
		else
			editor.tileInfo = 1
		end
	end
end

function editor.Draw()
	editor.tileMapBackground:Draw()
	editor.tileMapForeground:Draw()
	if editor.tileInfo == 1 then
		editor.tileMapTiles:Draw()
	end
end

function editor.CreateEmpty()
	--Create TileMaps
	editor.tileMapBackground = TileMap.New()
	editor.tileMapForeground = TileMap.New()
	editor.tileMapTiles = TileMap.New()

	--tiles size in pixels
	tileSizeX = 16
	tileSizeY = 16

	--amount of tiles in the map
	sizeX = 32
	sizeY = 32
	
	map = editor.MapGrass()

	editor.tileMapBackground:Load("town_tiles.png", tileSizeX, tileSizeY, sizeX, sizeY, map);

	map = editor.MapEmpty()

	editor.tileMapForeground:Load("town_tiles.png", tileSizeX, tileSizeY, sizeX, sizeY, map);

	map = editor.MapTiles()

	editor.tileMapTiles:Load("town_tiles.png", tileSizeX, tileSizeY, sizeX, sizeY, map);

	editor.collisionMap = CollisionMap.New()
	editor.collisionMap:Empty(32, 32)

	--Set some needed state variables
	editor.workingLayer = 0 --0: Background, 1: Entities, 2: Foreground
	editor.tileInfo = 1
end

function editor.MapGrass()
	map = {}

	for i = 1, 32 * 32 do
		map[i] = 11	-- all grass
	end
	

	return map
end

function editor.MapEmpty()
	map = {}

	for i = 1, 32 * 32 do
		map[i] = -1	-- all empty
	end

	return map
end

function editor.MapTiles()
	map = {}

	for i = 1, 32 * 32 do
		map[i] = -1	-- all empty
	end

	for i = 1, 29 do
		map[i] = i
	end

	return map
end

function editor.Load()

end

function editor.Save()

end

return editor