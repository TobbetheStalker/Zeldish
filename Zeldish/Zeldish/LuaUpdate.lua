gameState = 0

function InitMenu ()
	--create menu
	menu = Menu.New()
	--Initialize menu
	menu:Initialize()
	
end

function Update(deltaTime)
	
	if gameState == -1 then
		return 0
	elseif gameState == 0 then
		UpdateMenu()
		menu:Draw()	
	elseif gameState == 1 then
		region.Update(deltaTime)
		region.Draw()
	elseif gameState == 2 then
		editor.Update()
		editor.Draw()
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
	if Input.IsPressed(58) == 1 or Input.IsPressed(57) == 1 then
		selected = menu:GetSelected()
		if selected == 0 then
			gameState = 1
			region = require("Region")
			region.Create()
		elseif selected == 1 then
			gameState = 2
			editor = require("LevelEditor")
			editor.CreateEmpty()
		elseif selected == 2 then
			gameState = -1
		end
	end
	if Input.IsPressed(36) == 1 then
		gameState = -1
	end
end