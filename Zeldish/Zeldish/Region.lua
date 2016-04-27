region = {}

keyW =		22
keyA =		0
keyS =		18
keyD =		3
keySpace =	57
keyEscape =	36

directionDown =		0
directionLeft =		1
directionRight =	2
directionUp =		3
directionNone =		4

function region.Update(deltaTime)
	if Input.IsPressed(keyEscape) == 1 then
		gameState = 0
	end
	if Input.IsPressed(keySpace) == 1 then
		region.LoadTileMaps(2)
	end
	region.HandlePlayerInput()
	
	--Update the player
	region.player:Update(deltaTime);
	--Update the projectiles
	for pIndex = 1, pIndex < region.projectileCnt, 1 do
		
	end

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

	if Input.isDown(keySpace) then
	end

end

function region.LoadCollisionMap()
	region.collisionMap = CollisionMap.New()
	region.collisionMap:Load("testMap")
end

function region.LoadTileMaps(level)

	--Load TileMap
	region.tileMapBackground = TileMap.New()
	region.tileMapForeground = TileMap.New()

	--tiles size in pixels
	tileSizeX = 16
	tileSizeY = 16

	--amount of tiles in the map
	sizeX = 32
	sizeY = 32
	
	if level == 1 then
		map = region.MapOneB()
	elseif level == 2 then
		map = region.MapTwoB()
	end

	region.tileMapBackground:Load("town_tiles.png", tileSizeX, tileSizeY, sizeX, sizeY, map);

	if level == 1 then
		map = region.MapOneF()
	elseif level == 2 then
		map = region.MapTwoF()
	end

	region.tileMapForeground:Load("town_tiles.png", tileSizeX, tileSizeY, sizeX, sizeY, map);

end


function region.Draw()
	--Draw tileMap
	region.tileMapBackground:Draw()
	region.player:Draw()
	region.tileMapForeground:Draw()
end

function region.MapOneB()
	map = {}

	for i = 1, 32 * 32 do
		map[i] = 11	-- all grass
	end
	
	for j = 1, 32 * 16 do
		map[j] = 7	-- all grass
	end

	return map
end

function region.MapTwoB()
	map = {}

	for i = 1, 32 * 32 do
		map[i] = 11	-- all grass
	end

	return map
end


function region.MapOneF()
	map = {}

	for i = 1, 32 * 32 do
		map[i] = -1	-- all grass
	end
	
	map[34] = 13;

	return map
end

function region.MapTwoF()
	map = {}

	for i = 1, 32 * 32 do
		map[i] = -1	-- all grass
	end

	map[534] = 13;

	return map
end

function region.Create()
	region.LoadTileMaps(1)
	region.LoadCollisionMap()
	region.player = Entity.New()
	region.player:Initialize("RacoonCharacter.png")
	region.player:SetPos(64, 64)
	region.player:SetDirection(4)
	region.player:SetSpeed(40)

	region.projectiles = {}
	region.activeProjectiles = {}
	region.projectileCnt = 1
end

return region