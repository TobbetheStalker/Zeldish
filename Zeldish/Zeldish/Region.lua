region = {}

--region has [projectileMetatable][bool active]
region.projectiles = {}

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

region.regionWidth = 32 * 20
region.regionHeight = 32 * 20

function region.CheckParticles()
	for key, projectile in pairs(region.projectiles) do
		if projectile[2] == true then
			--check if we should deactivate them or do something
			--First check is if outside of screen
			x, y = projectile[1]:GetPos()
			if x + projectile[1]:GetWidth() < 0 or y + projectile[1]:GetHeight() < 0 or x > region.regionWidth or y > region.regionHeight then
				projectile[2] = false
			end
			--second check is against the collision map
			--third check is against the other entities
		end
	end
end

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

	--Check if we should kill / deactivate any particles
	region.CheckParticles()

	--Update the active particles
	for key, projectile in pairs(region.projectiles) do
		if projectile[2] then
			projectile[1]:Update(deltaTime)
		end
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

	if Input.IsLeftMousePressed() == 1 then
		--Spawn Projectile
		region.SpawnProjectile(region.player)
	end

end

function region.SpawnProjectile(original)
	for key, projectile in pairs(region.projectiles) do
		if projectile[2] == false then
			foundPos = key
			--The projectile is inactive
			--Push yourself to its place in the list
			x, y = original:GetPos()
			print(x .. " " .. y)
			projectile[1]:Initialize("FireBall.png");
			projectile[1]:SetPos(x, y)
			projectile[1]:SetWidth(20)
			projectile[1]:SetHeight(20)
			projectile[1]:SetSpriteWidth(20)
			projectile[1]:SetSpriteHeight(20)
			spawnDirection = original:GetDirection();
			if spawnDirection ==  directionNone then
				spawnDirection = original:GetLastDirection()
			end
			projectile[1]:SetDirection(spawnDirection)
			projectile[1]:SetSpeed(60)
			print("[LUA] created projectile[1]")

			projectile[2] = true;
			print("adding entity")
			break
		end
	end
	if foundPos == 0 then
		print("[LUA] Resourcepool overload")
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
	--projectile, active = region.projectiles[1], region.projectiles[2]
	--print(projectile .. " " .. active)
	for key, adTemp in pairs(region.projectiles) do
		if adTemp[2] then
			--print("[LUA] Drawing projectile")
			adTemp[1]:Draw()
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
	region.player:SetSpeed(60)

	for pIndex = 1, 100, 1 do
		tempP = Entity:New()
		tempP:Initialize("Fireball.png");
		region.projectiles[pIndex] = {tempP, false}
	end

end

return region