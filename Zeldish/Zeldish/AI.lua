ai = {}

function ai.Update(player, enemies, regionCnt)
	local foundEnemyCnt = 0
	for key, enemy in pairs(enemies) do
		if foundEnemyCnt > regionCnt - 1 then
			break
		end
		if enemy[2] then
			foundEnemyCnt = foundEnemyCnt + 1
			--print("[LUA] Drawing enemy")
			if not PlayerEnemyCollision(player, enemy[1]) then
				MoveEnemy(player, enemy[1])
			end
		end
	end
end

function MoveEnemy(player, enemy)
	enemyX, enemyY = enemy:GetPos();
	playerX, playerY = player:GetPos()

	difX = enemyX - playerX
	difY = enemyY - playerY
	--print(difX)
	--print(difY)

	if difX == 0 and difY == 0 then
		enemy:SetDirection(4)

	elseif math.abs(difX) > math.abs(difY) then -- If X is dominant
	
		if difX < 0 then	--Right
			enemy:SetDirection(2)
		else				-- Left
			enemy:SetDirection(1)
		end

	else			-- If Y is dominant
		if difY < 0 then
			enemy:SetDirection(0)	-- Down
		else
			enemy:SetDirection(3) --Up
		end

	end

end 

function PlayerEnemyCollision(player, enemy)

	result = false
	enemyX, enemyY = enemy:GetPos();
	playerX, playerY = player:GetPos()

	difX = enemyX - playerX
	difY = enemyY - playerY

	if difX <= 200 and difY <= 200 then

		if enemy:Intersects(player) == true then
			result = true
			if math.abs(difX) <= math.abs(difY) then	--X is smaller
				
				if difX < 0 then
					enemy:SetDirection(2)
				else
					enemy:SetDirection(1)
				end
			else	-- Y is smaller
				if difY < 0 then	
					enemy:SetDirection(0)	-- Down
				else
					enemy:SetDirection(3) --Up
				end
			end
		end		
	end

	return result
end


return ai
