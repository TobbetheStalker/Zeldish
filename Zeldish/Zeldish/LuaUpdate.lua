
function InitMenu ()
	--create menu
	menu = Menu.New()
	--Initialize menu
	menu:Initialize()
	
end

function Update()
	if Input.IsPressed(73) == 1 then
		menu:Select(-1)
	end
	if Input.IsPressed(74) == 1 then
		menu:Select(1)
	end

	selection = menu:GetSelected()

	DrawTileMap()
	DrawMenu()
end

function DrawMenu ()
	--Draw menu
	menu:Draw()	
end

function LoadTileMap ()
	--Load TileMap
	tileMap = TileMap.New();

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

	for j = 1, 1800 do
		map[j] = 7 
	end

	return map
end