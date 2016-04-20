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
		UpdateRegion()
		DrawRegion()
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
			CreateRegion()
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

function UpdateRegion()
	if Input.IsPressed(36) == 1 then
		gameState = 0
	end
	if Input.IsPressed(57) == 1 then
		LoadTileMap(2)
	end
end

function LoadTileMap (level)
	--Load TileMap
	tileMap = TileMap.New();

	--tiles size in pixels
	tileSizeX = 16
	tileSizeY = 16

	--amount of tiles in the map
	sizeX = 32
	sizeY = 32
	
	if level == 1 then
		map = MapOne()
	elseif level == 2 then
		map = MapTwo()
	end

	tileMap:Load("town_tiles.png", tileSizeX, tileSizeY, sizeX, sizeY, map);

end

function DrawRegion ()
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

function MapTwo()
	map = {}

	for i = 1, 32 * 32 do
		map[i] = 7	-- all grass
	end
	
	for j = 1, 32 * 16 do
		map[j] = 11	-- all grass
	end

	map[534] = 13;

	return map
end

function CreateRegion()
	LoadTileMap(1)
end