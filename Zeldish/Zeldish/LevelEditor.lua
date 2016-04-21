editor = {}

function editor.Update()
	if Input.IsPressed(36) == 1 then --Escape -> menu
		gameState = 0
	end
	if Input.IsPressed(57) == 1 then
		if editor.tileInfo == 1 then
			tilePos = MapPosToTile(Input.GetMousePosX(), Input.GetMousePosY())
			print("[LUA] Mouse tile pos; X: " .. tilePos[1] .. ", Y: " .. tilePos[2])
			editor.activeTile = tilePos[1] + 1
			editor.tileInfo = 0
		else
			editor.tileInfo = 1
		end
	end
	if Input.IsMousePressed() == 1 then
		tilePos = MapPosToTile(Input.GetMousePosX(), Input.GetMousePosY())
		ChangeTile(tilePos[1], tilePos[2])
		UpdateMaps()
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
	
	editor.mapB = MapGrass()

	editor.tileMapBackground:Load("town_tiles.png", tileSizeX, tileSizeY, sizeX, sizeY, editor.mapB)

	editor.mapF = MapEmpty()

	editor.tileMapForeground:Load("town_tiles.png", tileSizeX, tileSizeY, sizeX, sizeY, editor.mapF)

	map = MapTiles()

	editor.tileMapTiles:Load("town_tiles.png", tileSizeX, tileSizeY, sizeX, sizeY, map)

	editor.collisionMap = CollisionMap.New()
	editor.collisionMap:Empty(32, 32)

	--Set some needed state variables
	editor.workingLayer = 0 --0: Background, 1: Entities, 2: Foreground
	editor.tileInfo = 1
	editor.activeTile = 0
end

function ChangeTile(x, y)
	if editor.workingLayer == 0 then
		editor.mapB[y * 32 + x + 1] = editor.activeTile;
	elseif editor.workingLayer == 2 then
		editor.mapF[y * 32 + x + 1] = editor.activeTile;
	end
end

function UpdateMaps()
	if editor.workingLayer == 0 then
		editor.tileMapBackground:Load("town_tiles.png", tileSizeX, tileSizeY, sizeX, sizeY, editor.mapB)
	elseif editor.workingLayer == 1 then
		editor.tileMapForeground:Load("town_tiles.png", tileSizeX, tileSizeY, sizeX, sizeY, editor.mapF)
	end
end

function MapGrass()
	map = {}

	for i = 1, 32 * 32 do
		map[i] = 11	-- all grass
	end
	

	return map
end

function MapEmpty()
	map = {}

	for i = 1, 32 * 32 do
		map[i] = -1	-- all empty
	end

	return map
end

function MapTiles()
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

function MapPosToTile(x, y)
	result = {}

	tileX = x / 20
	tileY = y / 20

	result[1] = math.floor(tileX)
	result[2] = math.floor(tileY)

	return result
end

return editor