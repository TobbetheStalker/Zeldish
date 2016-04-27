region = {}

--region has [projectileMetatable][bool active]
region.projectiles = {}
region.projectileCnt = 0

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
	print(region.projectiles[1])
	--for key, projectile in (region.projectiles) do
		--if projectile[2] then
			--projectile[1]:Update(deltaTime)
		--end
		--print(key .. " " .. projectile)
	--end
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

	if Input.IsLeftMousePressed() == 1 then
		--Spawn Projectile
		region.SpawnProjectile(region.player)
	end

end

function region.InsertProjectile(toAdd)
foundPos = 0
print("[LUA] Finding position for projectile")
	for key, projectile in (region.projectiles) do
		if projectile[2] == false then
			foundPos = key
			--The projectile is inactive
			--Push yourself to its place in the list
			projectile = toAdd
			print("adding entity")
			break
		end
	end
	if foundPos == 0 then
		print("[LUA] Resourcepool overload")
	end
end

function region.SpawnProjectile(original)
	x, y = original:GetPos()
	print(x .. " " .. y)
	projectile = Entity:New()
	projectile:Initialize("FireBall.png");
	projectile:SetPos(x, y)
	projectile:SetWidth(20)
	projectile:SetHeight(20)
	projectile:SetSpriteWidth(20)
	projectile:SetSpriteHeight(20)
	projectile:SetDirection(original:GetDirection())
	projectile:SetSpeed(10)
	print("[LUA] created projectile")
	region.InsertProjectile(projectile)
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

	for projectile, active in (region.projectiles) do
		if ative then
			--print("[LUA] Drawing projectile")
			projectile:Draw()
		end
	end

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
	region.player:SetPos(100, 100)
	region.player:SetSpriteWidth(20)
	region.player:SetSpriteHeight(20)
	region.player:SetWidth(20)
	region.player:SetHeight(20)
	region.player:SetDirection(4)
	region.player:SetSpeed(40)

	for pIndex = 1, pIndex < 100, 1 do
		tempP = Entity:New()
		tempP:Initialize("Fireball.png");
		region.projectiles[pIndex] = {tempP, false}
	end

end

return region