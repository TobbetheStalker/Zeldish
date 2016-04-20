gameState = 0

function InitMenu ()
	--create menu
	menu = Menu.New()
	--Initialize menu
	menu:Initialize()
	
end

function Update()
	
	if gameState == -1 then
		return 0
	elseif gameState == 0 then
		UpdateMenu()
		DrawMenu()
	elseif gameState == 1 then
		region.Update()
		region.Draw()
	end

	return 1
end

function UpdateMenu ()
	if Input.IsPressed(73) == 1 then
		menu:Select(-1)
	end
	if Input.IsPressed(74) == 1 then
		menu:Select(1)
	end
	if Input.IsPressed(58) == 1 then
		selected = menu:GetSelected()
		if selected == 0 then
			gameState = 1
			region = require("Region")
			region.Create()
		elseif selected == 2 then
			gameState = -1
		end
	end
	if Input.IsPressed(36) == 1 then
		gameState = -1
	end
end

function DrawMenu ()
	--Draw menu
	menu:Draw()	
end