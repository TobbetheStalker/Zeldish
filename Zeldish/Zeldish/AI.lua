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

	-- X movement
	if playerX < enemyX and not player:Intersect(enemy) then
		enemy:SetPos(enemyX - 1, enemyY)
	elseif playerX > enemyX and not player:Intersect(enemy) then
		enemy:SetPos(enemyX + 1, enemyY)
	end

	-- Y movement
	if playerY < enemyY and false ==player:Intersect(enemy) then
		enemy:SetPos(enemyX, enemyY - 1)
	elseif playerY > enemyY and not player:Intersect(enemy) then
		enemy:SetPos(enemyX, enemyY + 1)
	end

end 

return ai
