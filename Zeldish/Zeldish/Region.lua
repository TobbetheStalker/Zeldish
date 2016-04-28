region = {}
ai = require("AI")

directionDown =		0
directionLeft =		1
directionRight =	2
directionUp =		3
directionNone =		4

MAP_SIZE_X = 32
MAP_SIZE_Y = 32

NR_OF_MAPS = 3

function region.Update(deltaTime)
	if Input.IsPressed(keyEscape) == 1 then
		gameState = 0
	end
	if Input.IsPressed(keySpace) == 1 then
		region.currLevel = region.currLevel + 1
		region.currLevel = math.min(region.currLevel, NR_OF_MAPS)
		LoadMap(region.currLevel)
	end

	ai.Update(region.player, region.enemies);

	HandlePlayerInput()
	
	--Update the player
	region.player:Update(deltaTime);
	
	for i = 1, #region.enemies do
		region.enemies[i]:Update(deltaTime)
	end

end

function HandlePlayerInput()
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

function LoadMap(level)
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

	LoadEntityMap(level)
end


function region.Draw()
	--Draw tileMap
	region.tileMapBackground:Draw()
	region.player:Draw()
	
	for i = 1, #region.enemies do
		region.enemies[i]:Draw()
	end

	region.tileMapForeground:Draw()
end

function region.Create()
	region.tileMapBackground = TileMap.New()
	region.tileMapForeground = TileMap.New()
	region.collisionMap = CollisionMap.New()
	region.mapB = {}
	region.mapF = {}
	region.currLevel = 1
	LoadMap(region.currLevel)
	region.player = Entity.New()
	region.player:Initialize("RacoonCharacter.png")
	region.player:SetPos(100, 100)
	region.player:SetSpriteWidth(20)
	region.player:SetSpriteHeight(20)
	region.player:SetWidth(20)
	region.player:SetHeight(20)
	region.player:SetDirection(4)
	region.player:SetSpeed(100)

	region.projectiles = {}
	region.activeProjectiles = {}
	region.projectileCnt = 1

	
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

function LoadEntityMap(level)
	file = assert(io.open("Resources/Maps/level" .. level .. "E.txt", "r"))

	region.enemies = {}

	for i = 1, MAP_SIZE_X * MAP_SIZE_Y do
		local tempValue = file:read("*number")
		if tempValue ~= -1 then
			if tempValue == 0 then
				enemy = Entity.New()
				enemy:Initialize("LinkCharacter.png")
				local x = ((i-1) % MAP_SIZE_X) * 20
				local y = ((i-1) / MAP_SIZE_X) * 20
				enemy:SetPos(x, y);
				enemy:SetSpeed(40)

				table.insert(region.enemies, enemy)
			end
		end
	end

	file:close()
end

return region