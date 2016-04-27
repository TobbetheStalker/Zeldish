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
	if playerX < enemyX then
		enemy:SetPos(enemyX - 10, enemyY)
	elseif playerX > enemyX then
		enemy:SetPos(enemyX + 10, enemyY)
	end

	-- Y movement
	if playerY < enemyY then
		enemy:SetPos(enemyX, enemyY - 10)
	elseif playerY > enemyY then
		enemy:SetPos(enemyX, enemyY + 10)
	end

end 

return ai
