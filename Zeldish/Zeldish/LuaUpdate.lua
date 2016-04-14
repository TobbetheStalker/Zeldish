
--create menu
menu = Menu.New()
tileMap = TileMap.New();

function InitMenu ()
	
	--Initialize menu
	menu:Initialize()
	
end

function Update()
	DrawMenu()
	DrawTileMap()
end

function DrawMenu ()
	--Draw menu
	menu:Draw()	
end

function LoadTileMap ()
	--Load TileMap

	--tiles size in pixels
	tileSizeX = 16
	tileSizeY = 16

	--amount of tiles in the map
	sizeX = 60
	sizeY = 60

	mapOne = MapOne()

	tileMap:Load("town_tiles.png", tileSizeX, tileSizeY, sizeX, sizeY, mapOne);

end

function DrawTileMap ()
	--Draw tileMap
	tileMap:Draw()
end

function MapOne()
	map = {}

	for i = 1, 3600 do
		map[i] = 11	-- all grass
	end

	return map
end