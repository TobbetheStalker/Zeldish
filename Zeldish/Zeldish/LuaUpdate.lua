
--create menu
local menu

function InitMenu ()
	menu = Menu.New()
	--Initialize menu
	menu.Initialize()
end

function Update()
	DrawMenu()
end

function DrawMenu ()
	--Draw menu
	menu.Draw()	
end