gameState = 0

function InitMenu ()
	--create menu
	menu = Menu.New()
	--Initialize menu
	menu:Initialize()
	
end

function Update()
	
	if gameState == -1 then
		return 0
	elseif gameState == 0 then
		UpdateMenu()
		DrawMenu()
	elseif gameState == 1 then
		UpdateTilemap()
		DrawTileMap()
	end

	return 1
end

function UpdateMenu ()
	if Input.IsPressed(73) == 1 then
		menu:Select(-1)
	end
	if Input.IsPressed(74) == 1 then
		menu:Select(1)
	end
	if Input.IsPressed(58) == 1 then
		selected = menu:GetSelected()
		if selected == 0 then
			gameState = 1
		elseif selected == 2 then
			gameState = -1
		end
	end
	if Input.IsPressed(36) == 1 then
		gameState = -1
	end
end

function DrawMenu ()
	--Draw menu
	menu:Draw()	
end

function UpdateTilemap()
	if Input.IsPressed(36) == 1 then
		gameState = 0
	end
end

function LoadTileMap ()
	--Load TileMap
	tileMap = TileMap.New()

	--tiles size in pixels
	tileSizeX = 16
	tileSizeY = 16

	--amount of tiles in the map
	sizeX = 32
	sizeY = 32

	mapOne = MapOne()

	tileMap:Load("town_tiles.png", tileSizeX, tileSizeY, sizeX, sizeY, mapOne);

end

function DrawTileMap ()
	--Draw tileMap
	tileMap:Draw()
end

function MapOne()
	map = {}

	for i = 1, 32 * 32 do
		map[i] = 11	-- all grass
	end
	
	for j = 1, 32 * 16 do
		map[j] = 7	-- all grass
	end

	map[34] = 13;

	return map
end