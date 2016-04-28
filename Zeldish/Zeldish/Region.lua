region = {}
ai = require("AI")

--region has [projectileMetatable][bool active]
region.projectiles = {}
region.projectileCnt = 0
region.enemies = {}
region.enemyCnt = 0

keyW =		22
keyA =		0
keyS =		18
keyD =		3
keyM =		12
keySpace =	57
keyEscape =	36
keyFire =	keySpace

directionDown =		0
directionLeft =		1
directionRight =	2
directionUp =		3
directionNone =		4

region.regionWidth = 32 * 20
region.regionHeight = 32 * 20
MAP_SIZE_X = 32
MAP_SIZE_Y = 32

function region.CheckProjectiles()
	local foundProjectileCnt = 0
	for projectileKey, projectile in pairs(region.projectiles) do
		if foundProjectileCnt > region.projectileCnt - 1 then
			break
		end
		if projectile[2] == true then
			foundProjectileCnt = foundProjectileCnt + 1
			--check if we should deactivate them or do something
			--First check is if outside of screen
			--x, y = projectile[1]:GetPos()
			--if x + projectile[1]:GetWidth() < 0 or y + projectile[1]:GetHeight() < 0 or x > region.regionWidth or y > region.regionHeight then
				--projectile[2] = false
				--region.projectileCnt = region.projectileCnt - 1
			--end
			--second check is against the collision map
			result, dX, dY = region.collisionMap:CheckCollision(projectile[1])
			if result == true then
				projectile[2] = false
				region.projectileCnt = region.projectileCnt - 1
			end
			--third check is against the other entities
			local foundEnemyCnt = 0
			for enemyKey, enemy in pairs(region.enemies) do
				if projectile[2] == false or foundEnemyCnt > region.enemyCnt - 1 then
					break;
				end
				--If active enemy
				if enemy[2] then
					foundEnemyCnt = foundEnemyCnt + 1
					if projectile[1]:Intersects(enemy[1]) == true then
						newProjectilHealth = projectile[1]:GetHealth() - enemy[1]:GetDamage()
						projectile[1]:SetHealth(newProjectilHealth)
						newEnemyHealth = enemy[1]:GetHealth() - projectile[1]:GetDamage()
						enemy[1]:SetHealth(newEnemyHealth)
						if newProjectilHealth < 1 then
							projectile[2] = false
							region.projectileCnt = region.projectileCnt - 1
						end
						if newEnemyHealth < 1 then
							enemy[2] = false
							region.enemyCnt = region.enemyCnt - 1;
						end
						print("Enemy [" .. enemyKey .. "] has [" .. newEnemyHealth .. "] health left after taking [" .. projectile[1]:GetDamage() .. "] damage from Projectile[" .. projectileKey .. "]")
					end
				end
			end
		end
	end
end
NR_OF_MAPS = 3

function region.Update(deltaTime)
	if Input.IsPressed(keyEscape) == 1 then
		gameState = 0
	end
	if Input.IsPressed(keyM) == 1 then
		region.currLevel = region.currLevel + 1
		region.currLevel = math.min(region.currLevel, NR_OF_MAPS)
		LoadMap(region.currLevel)
	end


	HandlePlayerInput()

	ai.Update(region.player, region.enemies, region.enemyCnt);
	
	--Check if we should kill / deactivate any particles
	region.CheckProjectiles()

	--Update the player
	result, dX, dY = region.collisionMap:CheckCollision(region.player)
	if result == true then
		region.player:ApplyPos(dX, dY)
	end
	region.player:Update(deltaTime);

	--Update the active enemies
	for key, enemy in pairs(region.enemies) do
		if enemy[2] then
			enemy[1]:Update(deltaTime)
		end
	end

	--Update the active particles
	for key, projectile in pairs(region.projectiles) do
		if projectile[2] then
			projectile[1]:Update(deltaTime)
		end
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

	if Input.IsPressed(keyFire) == 1 then
		--Spawn Projectile
		region.SpawnProjectile(region.player)
	end

end

function region.SpawnProjectile(original)
	foundPos = 0
	for key, projectile in pairs(region.projectiles) do
		if projectile[2] == false then
			foundPos = key
			--The projectile is inactive
			--Push yourself to its place in the list
			x, y = original:GetPos()
			print(x .. " " .. y)
			projectile[1]:Initialize("FireBall.png");
			projectile[1]:SetWidth(10)
			projectile[1]:SetHeight(10)
			projectile[1]:SetSpriteWidth(20)
			projectile[1]:SetSpriteHeight(20)
			projectile[1]:SetPos(x, y)
			projectile[1]:SetHealth(1)
			projectile[1]:SetDamage(original:GetDamage())
			spawnDirection = original:GetDirection();
			if spawnDirection ==  directionNone then
				spawnDirection = original:GetLastDirection()
			end
			projectile[1]:SetDirection(spawnDirection)
			projectile[1]:SetSpeed(80)
			print("[LUA] created projectile[" .. key .. "]")

			projectile[2] = true;
			region.projectileCnt = region.projectileCnt + 1
			print("adding entity")
			break
		end
	end
	if foundPos == 0 then
		print("[LUA] Projectile resource-pool overload")
	end
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
	--projectile, active = region.projectiles[1], region.projectiles[2]
	--print(projectile .. " " .. active)

	for key, enemy in pairs(region.enemies) do
		if enemy[2] then
			--print("[LUA] Drawing enemy")
			enemy[1]:Draw()
		end
	end

	for key, adTemp in pairs(region.projectiles) do
		if adTemp[2] then
			--print("[LUA] Drawing projectile")
			adTemp[1]:Draw()
		end
	end
	
	
	region.tileMapForeground:Draw()
end

function region.Create()

	for pIndex = 1, 300, 1 do
		tempP = Entity:New()
		tempP:Initialize("Fireball.png");
		region.projectiles[pIndex] = {tempP, false}
	end

	for enemyIndex = 1, 50, 1 do
		tempE = Entity:New()
		tempE:Initialize("LinkCharacter.png")
		region.enemies[enemyIndex] = {tempE, false}
	end

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

	for key, temp in pairs(region.projectiles) do
		temp[2] = false
	end
	region.projectileCnt = 0

	file:close()
end

function LoadEntityMap(level)
	file = assert(io.open("Resources/Maps/level" .. level .. "E.txt", "r"))
	
	--Reset all enemies to deactivated to begin with
	for key, enemy in pairs(region.enemies) do
		enemy[2] = false
	end
	region.enemyCnt = 0


	for i = 1, MAP_SIZE_X * MAP_SIZE_Y do
		local tempValue = file:read("*number")
		if tempValue ~= -1 then
			if tempValue == 0 then
				--Go through our enemy resource pool and look for an inactive position
				
				foundPos = 0
				for key, enemy in pairs(region.enemies) do
					if enemy[2] == false then
						foundPos = key
						local x = ((i-1) % MAP_SIZE_X) * 20
						local y = ((i-1) / MAP_SIZE_X) * 20
						--The projectile is inactive
						--Push yourself to its place in the list
						print(x .. " " .. y)
						--enemy[1]:Initialize("LinkCharacter.png")
						enemy[1]:SetPos(x, y)
						--enemy[1]:SetWidth(20)
						--enemy[1]:SetHeight(20)
						--enemy[1]:SetSpriteWidth(20)
						--enemy[1]:SetSpriteHeight(20)
						enemy[1]:SetHealth(20)
						print("Health of enemy = " .. enemy[1]:GetHealth())
						enemy[1]:SetDamage(5)
						enemy[1]:SetDirection(directionNone)
						enemy[1]:SetSpeed(40)
						print("[LUA] created enemy at[" .. key .. "]")
						enemy[2] = true;
						region.enemyCnt = region.enemyCnt + 1;
						break
					end
				end
				if foundPos == 0 then
					print("[LUA] Enemy resource-pool overload")
				end


				--for key, enemy in pairs(region.enemies) do
					--if enemy[2] == false then
						--enemy[1]:SetSpeed(40)
						--enemy[2] = true;
					--end
				--end
			end
		end
	end

	file:close()
end

return region