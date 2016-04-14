
function InitMenu ()
	--create menu
	menu = Menu.New()
	--Initialize menu
	menu:Initialize()
end

function Update()
	if Input.IsPressed(73) == 1 then
		menu:Select(-1)
	elseif Input.IsPressed(74) == 1 then
		menu:Select(1)
	end

	DrawMenu()
end

function DrawMenu ()
	--Draw menu
	menu:Draw()	
end