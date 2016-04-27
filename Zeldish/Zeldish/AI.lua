ai = {}

function ai.Create()
	
end

function ai.Update(player, entities)
	
	for i = 1, #entities do
		ai.MoveEnemy(player, entities[i])

	end

end

function ai.MoveEnemy(player, enemy)
	enemyX, enemyY = enemy:GetPos();
	playerX, playerY = player:GetPos()

	difX = enemyX - playerX
	difY = enemyY - playerY
	print (difX)
	print (difY)

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

return ai
