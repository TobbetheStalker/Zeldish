editor = {}

MAP_SIZE_X = 32
MAP_SIZE_Y = 32

function editor.Update()
	if Input.IsPressed(36) == 1 then --Escape -> menu
		gameState = 0
	end
	if Input.IsPressed(57) == 1 then --Space -> tile picker
		if editor.tileInfo == 1 then
			tilePos = MapPosToTile(Input.GetMousePosX(), Input.GetMousePosY())
			print("[LUA] Mouse tile pos; X: " .. tilePos[1] .. ", Y: " .. tilePos[2])
			if tilePos[2] < 1 then
				editor.activeTile = tilePos[1] + 1
			end
			editor.tileInfo = 0
		elseif editor.tileInfo == 0 and (editor.workingLayer == 0 or editor.workingLayer == 2) then
			editor.tileInfo = 1
		end
	end
	if Input.IsPressed(27) == 1 then --1 -> background layer
		print("[LUA] Changed working layer to background")
		editor.workingLayer = 0
	end
	if Input.IsPressed(28) == 1 then --2 -> entities layer
		print("[LUA] Changed working layer to entities")
		editor.workingLayer = 1
		editor.tileInfo = 0
	end
	if Input.IsPressed(29) == 1 then --3 -> foreground layer
		print("[LUA] Changed working layer to foreground")
		editor.workingLayer = 2
	end
	if Input.IsPressed(30) == 1 then --4 -> collision layer
		print("[LUA] Changed working layer to collision")
		editor.workingLayer = 3
	end

	if Input.IsPressed(18) == 1 then --S -> Save maps
		print("[LUA] Save maps initiated")
		Save()
	end
	if Input.IsPressed(11) == 1 then --L -> Load maps
		print("[LUA] Load maps initiated")
		Load()
		UpdateMaps()
	end

	if Input.IsMousePressed() == 1 then
		tilePos = MapPosToTile(Input.GetMousePosX(), Input.GetMousePosY())
		ChangeTile(tilePos[1], tilePos[2])
		UpdateMap()
	end

	if editor.workingLayer ~= 0 and editor.workingLayer ~= 2 then
		editor.tileInfo = 0
	end
end

function editor.Draw()
	editor.tileMapBackground:Draw()
	editor.tileMapForeground:Draw()
	if editor.tileInfo == 1 then
		editor.tileMapTiles:Draw()
	end
	if editor.workingLayer == 3 then
		editor.tileMapCollision:Draw()
	end
end

function editor.CreateEmpty()
	--Create TileMaps
	editor.tileMapBackground = TileMap.New()
	editor.tileMapForeground = TileMap.New()
	editor.tileMapTiles = TileMap.New()
	editor.tileMapCollision = TileMap.New()

	--tiles size in pixels
	tileSizeX = 16
	tileSizeY = 16
	
	editor.mapB = MapGrass()

	editor.tileMapBackground:Load("town_tiles.png", tileSizeX, tileSizeY, MAP_SIZE_X, MAP_SIZE_Y, editor.mapB)

	editor.mapF = MapEmpty()

	editor.tileMapForeground:Load("town_tiles.png", tileSizeX, tileSizeY, MAP_SIZE_X, MAP_SIZE_Y, editor.mapF)

	map = MapTiles()

	editor.tileMapTiles:Load("town_tiles.png", tileSizeX, tileSizeY, MAP_SIZE_X, MAP_SIZE_Y, map)

	editor.mapC = MapEmpty()

	editor.tileMapCollision:Load("misc_tiles.png", tileSizeX, tileSizeY, MAP_SIZE_X, MAP_SIZE_Y, editor.mapC)

	editor.collisionMap = CollisionMap.New()
	editor.collisionMap:Empty(MAP_SIZE_X, MAP_SIZE_Y)

	--Set some needed state variables
	editor.workingLayer = 0 --0: Background, 1: Entities, 2: Foreground, 3: Collision
	editor.tileInfo = 1
	editor.activeTile = 11
end

function ChangeTile(x, y)
	if editor.workingLayer == 0 then
		editor.mapB[y * MAP_SIZE_X + x + 1] = editor.activeTile;
		print("[LUA] Changed tile in background")
	elseif editor.workingLayer == 2 then
		editor.mapF[y * MAP_SIZE_X + x + 1] = editor.activeTile;
		print("[LUA] Changed tile in foreground")
	elseif editor.workingLayer == 3 then
		if editor.mapC[y * MAP_SIZE_X + x + 1] == -1 then
			editor.mapC[y * MAP_SIZE_X + x + 1] = 2
		else
			editor.mapC[y * MAP_SIZE_X + x + 1] = -1
		end
		print("[LUA] Changed tile in collision")
	end
end

function UpdateMap()
	if editor.workingLayer == 0 then
		editor.tileMapBackground:Load("town_tiles.png", tileSizeX, tileSizeY, MAP_SIZE_X, MAP_SIZE_Y, editor.mapB)
		print("[LUA] Updated tiles in background")
	elseif editor.workingLayer == 2 then
		editor.tileMapForeground:Load("town_tiles.png", tileSizeX, tileSizeY, MAP_SIZE_X, MAP_SIZE_Y, editor.mapF)
		print("[LUA] Updated tiles in foreground")
	elseif editor.workingLayer == 3 then
		editor.tileMapCollision:Load("misc_tiles.png", tileSizeX, tileSizeY, MAP_SIZE_X, MAP_SIZE_Y, editor.mapC)
		print("[LUA] Updated tiles in collision")
	end
end

function UpdateMaps()
	editor.tileMapBackground:Load("town_tiles.png", tileSizeX, tileSizeY, MAP_SIZE_X, MAP_SIZE_Y, editor.mapB)
	print("[LUA] Updated tiles in background")
	editor.tileMapForeground:Load("town_tiles.png", tileSizeX, tileSizeY, MAP_SIZE_X, MAP_SIZE_Y, editor.mapF)
	print("[LUA] Updated tiles in foreground")
	editor.tileMapCollision:Load("misc_tiles.png", tileSizeX, tileSizeY, MAP_SIZE_X, MAP_SIZE_Y, editor.mapC)
	print("[LUA] Updated tiles in collision")
end

function MapGrass()
	map = {}

	for i = 1, MAP_SIZE_X * MAP_SIZE_Y do
		map[i] = 11	-- all grass
	end
	

	return map
end

function MapEmpty()
	map = {}

	for i = 1, MAP_SIZE_X * MAP_SIZE_Y do
		map[i] = -1	-- all empty
	end

	return map
end

function MapTiles()
	map = {}

	for i = 1, MAP_SIZE_X * MAP_SIZE_Y do
		map[i] = -1	-- all empty
	end

	for i = 1, 29 do
		map[i] = i
	end

	return map
end

function Load()
	io.stdout:write("Enter the filename to load maps from: ")
	local filename = io.stdin:read()

	local file = assert(io.open("Resources/Maps/" .. filename .. "B.txt", "r"))
	MAP_SIZE_X = file:read("*number")
	MAP_SIZE_Y = file:read("*number")

	for i = 1, MAP_SIZE_X * MAP_SIZE_Y do
		editor.mapB[i] = file:read("*number")
	end
	file:close()

	file = assert(io.open("Resources/Maps/" .. filename .. "F.txt", "r"))

	for i = 1, MAP_SIZE_X * MAP_SIZE_Y do
		editor.mapF[i] = file:read("*number")
	end
	file:close()

	io.stdout:write("Maps loaded from: " .. filename .. "\n")
end

function Save()
	io.stdout:write("Enter the filename to save maps to: ")
	local filename = io.stdin:read()

	local file = assert(io.open("Resources/Maps/" .. filename .. "B.txt", "w"))
	file:write(MAP_SIZE_X .. " ")
	file:write(MAP_SIZE_Y .. " ")

	for i = 1, MAP_SIZE_X * MAP_SIZE_Y do
		 file:write(editor.mapB[i] .. " ")
	end
	file:close()

	file = assert(io.open("Resources/Maps/" .. filename .. "F.txt", "w"))

	for i = 1, MAP_SIZE_X * MAP_SIZE_Y do
		 file:write(editor.mapF[i] .. " ")
	end
	file:close()

	io.stdout:write("Maps saved as: " .. filename .. "\n")
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