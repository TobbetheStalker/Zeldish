
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

function LoadTileMap
	--Load tileMap
	tileMap:Load();

function DrawTileMap ()
	--Draw tileMap
	tileMap:Draw()
end