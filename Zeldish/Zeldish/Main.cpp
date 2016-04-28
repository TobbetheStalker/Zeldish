#include "System.h"
#include "WindowLib.h"

//The Icon
#pragma region
static const struct {
	unsigned int 	 width;
	unsigned int 	 height;
	unsigned int 	 bytes_per_pixel; /* 2:RGB16, 3:RGB, 4:RGBA */
	unsigned char	 pixel_data[32 * 32 * 4 + 1];
} game_icon = {
	32, 32, 4,
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\25\25\25\377\25\25\25\377\25\25\25\377\25"
	"\25\25\377\25\25\25\377\25\25\25\377\25\25\25\377\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\25\25\25\377++!\377++!\377++!\377"
	"++!\377\0\0\0\0\25\25\25\377>>>\377>>>\377HHH\377HHH\377HHH\377HHH\377HH"
	"H\377>>>\377>>>\377\25\25\25\377\0\0\0\0++!\377++!\377++!\377++!\377\25\25"
	"\25\377\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0++!\377>>>\377HHH\377HHH\377HHH\377>>>\377++!\377HHH\377XXX\377XXX"
	"\377XXX\377XXX\377XXX\377XXX\377XXX\377HHH\377++!\377>>>\377HHH\377HHH\377"
	"HHH\377>>>\377++!\377\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0>>>\377HHH\377>>>\377++!\377>>>\377HHH\377HHH\377>>>"
	"\377XXX\377XXX\377XXX\377XXX\377XXX\377XXX\377XXX\377>>>\377HHH\377HHH\377"
	">>>\377++!\377>>>\377HHH\377>>>\377\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0>>>\377HHH\377|\203\203\377\243\253\257"
	"\377++!\377++!\377>>>\377>>>\377XXX\377XXX\377XXX\377XXX\377XXX\377XXX\377"
	"XXX\377>>>\377>>>\377++!\377++!\377\243\253\257\377|\203\203\377HHH\377>"
	">>\377\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\25\25\25\377>>>\377++!\377|\203\203\377\243\253\257\377++!\377++!"
	"\377>>>\377XXX\377XXX\377XXX\377XXX\377XXX\377XXX\377XXX\377>>>\377++!\377"
	"++!\377\243\253\257\377|\203\203\377++!\377>>>\377\25\25\25\377\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\25\25\25\377"
	">>>\377|\203\203\377\333\346\353\377\333\346\353\377\243\253\257\377|\203"
	"\203\377XXX\377XXX\377XXX\377XXX\377XXX\377XXX\377XXX\377XXX\377XXX\377|"
	"\203\203\377\243\253\257\377\333\346\353\377\333\346\353\377|\203\203\377"
	">>>\377\25\25\25\377\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\25\25\25\377++!\377>>>\377|\203\203\377\243\253\257"
	"\377\333\346\353\377XXX\377XXX\377XXX\377XXX\377XXX\377XXX\377XXX\377XXX"
	"\377XXX\377XXX\377XXX\377\333\346\353\377\243\253\257\377|\203\203\377>>"
	">\377++!\377\25\25\25\377\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\25\25\25\377>>>\377\243\253\257\377\333"
	"\346\353\377XXX\377XXX\377XXX\377XXX\377XXX\377XXX\377XXX\377XXX\377XXX\377"
	"XXX\377XXX\377XXX\377XXX\377\333\346\353\377\243\253\257\377>>>\377\25\25"
	"\25\377\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\25\25\25\377++!\377\25\25\25\377\333\345\353\377\333"
	"\345\353\377\333\345\353\377\333\345\353\377\333\345\353\377\333\345\353"
	"\377XXX\377XXX\377XXX\377\333\345\353\377\333\345\353\377\333\345\353\377"
	"\333\345\353\377\333\345\353\377\333\345\353\377\25\25\25\377++!\377\25\25"
	"\25\377\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\25\25\25\377}\203\204\377\243\252\257\377"
	"\333\345\353\377\333\345\353\377\333\345\353\377\333\345\353\377\333\345"
	"\353\377\333\345\353\377\333\345\353\377\333\345\353\377\333\345\353\377"
	"\333\345\353\377\333\345\353\377\333\345\353\377\333\345\353\377\243\252"
	"\257\377}\203\204\377\25\25\25\377\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\377}\203\204\377HHH\377>>>\377\25\25\25\377\25\25\25\377\25\25\25\377\333"
	"\345\353\377\333\345\353\377\333\345\353\377\333\345\353\377\333\345\353"
	"\377\25\25\25\377\25\25\25\377\25\25\25\377>>>\377HHH\377}\203\204\377\0"
	"\0\0\377\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\377HHH\377>>>\377"
	"\224\224\224\377\0\0\0\377\0\0\0\377>>>\377>>>\377>>>\377>>>\377>>>\377\0"
	"\0\0\377\0\0\0\377\224\224\224\377>>>\377HHH\377\0\0\0\377\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\377>>>\377HHH\377\323\323\323\377"
	"\0\0\0\377\0\0\0\377>>>\377>>>\377>>>\377>>>\377>>>\377\0\0\0\377\0\0\0\377"
	"\323\323\323\377HHH\377>>>\377\0\0\0\377\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\377>>>\377HHH\377\323\323\323\377(=l\377(=l\377>>"
	">\377>>>\377>>>\377>>>\377>>>\377(=l\377(=l\377\323\323\323\377HHH\377>>"
	">\377\0\0\0\377\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\377"
	"\25\25\25\377HHH\377\323\323\323\377(=l\377(=l\377*+!\377\333\345\353\377"
	"\333\345\353\377\333\345\353\377*+!\377(=l\377(=l\377\323\323\323\377HHH"
	"\377\25\25\25\377\0\0\0\377\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\377\0\0\0\377>>>\377HHH\377*+!\377*+!\377\333\345\353\377*+!\377"
	"*+!\377*+!\377\333\345\353\377*+!\377*+!\377HHH\377>>>\377\0\0\0\377\0\0"
	"\0\377\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\25\25\25\377\25\25\25\377>>>\377>"
	">>\377*+!\377}\203\204\377\243\252\257\377\333\345\353\377\333\345\353\377"
	"\333\345\353\377*+!\377\333\345\353\377\333\345\353\377\333\345\353\377\243"
	"\252\257\377}\203\204\377*+!\377>>>\377>>>\377\25\25\25\377\25\25\25\377"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\25\25\25\377>>>\377HHH\377XXX\377HHH\377>>>\377*+!\377*+!\377}\203"
	"\204\377}\203\204\377\243\252\257\377\243\252\257\377\243\252\257\377}\203"
	"\204\377}\203\204\377*+!\377*+!\377>>>\377HHH\377XXX\377HHH\377>>>\377\25"
	"\25\25\377\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\25\25\25\377>>>\377XXX\377XXX\377HHH\377>>>\377\25\25\25\377}\203\204"
	"\377\243\252\257\377}\203\204\377*+!\377*+!\377*+!\377*+!\377*+!\377}\203"
	"\204\377\243\252\257\377}\203\204\377\25\25\25\377>>>\377HHH\377XXX\377X"
	"XX\377>>>\377\25\25\25\377\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\25\25\25\377HHH\377XXX\377HHH\377>>>\377\25\25\25\377\0\0\0\377"
	"\243\252\257\377\333\345\353\377\333\345\353\377\243\252\257\377}\203\204"
	"\377}\203\204\377}\203\204\377\243\252\257\377\333\345\353\377\333\345\353"
	"\377\243\252\257\377\0\0\0\377\25\25\25\377>>>\377HHH\377XXX\377HHH\377\25"
	"\25\25\377\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\25\25\25\377>"
	">>\377HHH\377HHH\377\25\25\25\377\25\25\25\377\25\25\25\377\0\0\0\377\243"
	"\252\257\377\333\345\353\377\333\345\353\377\333\345\353\377\333\345\353"
	"\377\333\345\353\377\333\345\353\377\333\345\353\377\333\345\353\377\333"
	"\345\353\377\243\252\257\377\0\0\0\377\25\25\25\377\25\25\25\377\25\25\25"
	"\377HHH\377HHH\377>>>\377\25\25\25\377\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\25\25\25\377>>>\377HHH\377>>>\377>>>\377\25\25\25\377\0\0\0\377\0"
	"\0\0\377}\203\204\377\333\345\353\377\333\345\353\377\333\345\353\377\243"
	"\252\257\377\243\252\257\377\243\252\257\377\333\345\353\377\333\345\353"
	"\377\333\345\353\377}\203\204\377\0\0\0\377\0\0\0\377\25\25\25\377>>>\377"
	">>>\377HHH\377>>>\377\25\25\25\377\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\377>>>\377XXX\377XXX\377>>>\377\25\25\25\377\0\0\0\377}"
	"\203\204\377\243\252\257\377\243\252\257\377\243\252\257\377\333\345\353"
	"\377\333\345\353\377\333\345\353\377\243\252\257\377\243\252\257\377\243"
	"\252\257\377}\203\204\377\0\0\0\377\25\25\25\377>>>\377XXX\377XXX\377>>>"
	"\377\0\0\0\377\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\377>>>\377XXX\377XXX\377>>>\377\25\25\25\377\37(i\377\37(i\377}\203"
	"\204\377}\203\204\377\243\252\257\377\333\345\353\377\333\345\353\377\333"
	"\345\353\377\243\252\257\377}\203\204\377}\203\204\377\37(i\377\37(i\377"
	"\25\25\25\377>>>\377XXX\377XXX\377>>>\377\0\0\0\377\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\377HHH\377HHH\377>>>\377"
	"\0\0\0\377\37(i\377G_\217\377G_\217\377\37(i\377\37(i\377\37(i\377\37(i\377"
	"\37(i\377\37(i\377\37(i\377G_\217\377G_\217\377\37(i\377\0\0\0\377>>>\377"
	"HHH\377HHH\377\0\0\0\377\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\377\0\0\0\377\0\0\0\377\0\0\0\0\37"
	"(i\377G_\217\377\202\246\324\377\202\246\324\377G_\217\377G_\217\377G_\217"
	"\377G_\217\377G_\217\377\202\246\324\377\202\246\324\377G_\217\377\37(i\377"
	"\0\0\0\0\0\0\0\377\0\0\0\377\0\0\0\377\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\37(i\377G_\217\377\202\246\324\377\202\246\324\377G_\217\377"
	"\37(i\377\0\0\0\377\37(i\377G_\217\377\202\246\324\377\202\246\324\377G_"
	"\217\377\37(i\377\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\377>>>\377>>>\377HHH\377>>>\377>>>\377\0\0"
	"\0\377>>>\377>>>\377HHH\377>>>\377>>>\377\0\0\0\377\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\377>>>\377"
	"HHH\377HHH\377HHH\377>>>\377\0\0\0\377>>>\377HHH\377HHH\377HHH\377>>>\377"
	"\0\0\0\377\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\377XXX\377XXX\377XXX\377\0\0\0\377\0\0\0"
	"\0\0\0\0\377XXX\377XXX\377XXX\377\0\0\0\377\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\377>>>\377HHH\377>>>\377\0\0\0\377\0\0\0\0\0\0\0\377>>>\377HHH\377>>>\377"
	"\0\0\0\377\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0",
};
#pragma endregion icon


int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	sf::RenderWindow tWindow(sf::VideoMode(640, 640), "SFML works!", sf::Style::None);
	tWindow.setIcon(game_icon.width, game_icon.height, game_icon.pixel_data);
	window = &tWindow;

	sf::Clock gameTimer;


	System zeldish;
	int result = zeldish.Initialize();
	if (result == -1) {
		window->close();
	}

	while (window->isOpen())
	{
		InputChecker::Instance().UpdateInput();
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
			if (event.type == sf::Event::KeyPressed) {
				InputChecker::Instance().SetKeyPressed(event.key.code);
			}
			if (event.type == sf::Event::KeyReleased) {
				InputChecker::Instance().SetKeyReleased(event.key.code);
			}
			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Button::Left) {
					InputChecker::Instance().SetLeftMousePressed();
				} 
				else if (event.mouseButton.button == sf::Mouse::Button::Right) {
					InputChecker::Instance().SetRightMousePressed();
				}
			}
			if (event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Button::Left) {
					InputChecker::Instance().SetLeftMouseReleased();
				}
				else if (event.mouseButton.button == sf::Mouse::Button::Right) {
					InputChecker::Instance().SetRightMouseReleased();
				}
			}
		}
		
		window->clear();
		zeldish.HandleInput();
		result = zeldish.Update(gameTimer.restart().asSeconds());
		if (result == 0) {
			window->close();
		}
		window->display();
	}

	delete &InputChecker::Instance();
	window = nullptr;
	system("pause");
	return 0;
}