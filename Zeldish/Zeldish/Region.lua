region = {}

directionDown =		0
directionLeft =		1
directionRight =	2
directionUp =		3
directionNone =		4

MAP_SIZE_X = 32
MAP_SIZE_Y = 32

function region.Update(deltaTime)
	if Input.IsPressed(keyEscape) == 1 then
		gameState = 0
	end
	if Input.IsPressed(keySpace) == 1 then
		region.LoadTileMaps(2)
	end
	region.HandlePlayerInput()
	region.player:Update(deltaTime);
end

function region.HandlePlayerInput()
	--extract the input
	down = Input.IsDown(keyS) 
	left = Input.IsDown(keyA) 
	right = Input.IsDown(keyD) 
	up = Input.IsDown(keyW)
	none = down + left + right + up
	newDirection = 0

	--do the input logic
	if none == 0 or none > 1 then
		--no key was pressed or to many keys was pressed
		newDirection = directionNone
	else
		--one single key was pressed
		if down == 1 then
			newDirection = directionDown
			--if Input.IsPressed(keyS) == 1 then
				--region.player:SetDirection(newDirection)
			--end
		end
		if left == 1 then
			newDirection = directionLeft
			--if Input.IsPressed(keyA) == 1 then
				--region.player:SetDirection(newDirection)
			--end
		end
		if right == 1 then
			newDirection = directionRight
			--if Input.IsPressed(keyD) == 1 then
				--region.player:SetDirection(newDirection)
			--end
		end
		if up == 1 then
			newDirection = directionUp
			--if Input.IsPressed(keyW) == 1 then
				--region.player:SetDirection(newDirection)
			--end
		end
	end
	region.player:SetDirection(newDirection)
end

function LoadCollisionMap(map)
	
	region.collisionMap:Load(map)
end

function region.LoadTileMaps(level)
	--tiles size in pixels
	tileSizeX = 16
	tileSizeY = 16

	--amount of tiles in the map
	sizeX = 32
	sizeY = 32
	
	LoadMaps(level)

	region.tileMapBackground:Load("town_tiles2.png", tileSizeX, tileSizeY, MAP_SIZE_X, MAP_SIZE_Y, region.mapB)
	region.tileMapForeground:Load("town_tiles2.png", tileSizeX, tileSizeY, MAP_SIZE_X, MAP_SIZE_Y, region.mapF)

	LoadCollisionMap("level"..level)
end


function region.Draw()
	--Draw tileMap
	region.tileMapBackground:Draw()
	region.player:Draw()
	region.tileMapForeground:Draw()
end

function region.Create()
	region.tileMapBackground = TileMap.New()
	region.tileMapForeground = TileMap.New()
	region.collisionMap = CollisionMap.New()
	region.mapB = {}
	region.mapF = {}
	region.LoadTileMaps(1)
	region.player = Entity.New()
	region.player:Initialize("RacoonCharacter.png")
	region.player:SetPos(64, 64)
	region.player:SetDirection(4)
	region.player:SetSpeed(40)
end

function LoadMaps(level)
	local file = assert(io.open("Resources/Maps/level" .. level .. "B.txt", "r"))

	MAP_SIZE_X = file:read("*number")
	MAP_SIZE_Y = file:read("*number")

	for i = 1, MAP_SIZE_X * MAP_SIZE_Y do
		region.mapB[i] = file:read("*number")
	end
	file:close()

	file = assert(io.open("Resources/Maps/level" .. level .. "F.txt", "r"))

	for i = 1, MAP_SIZE_X * MAP_SIZE_Y do
		region.mapF[i] = file:read("*number")
	end
	file:close()
end

return region