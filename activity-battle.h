#include "activity.h"
#include "engine.h"

namespace gs {

class BattleActivity : public Activity {
public:
	BattleActivity(Engine* engine, SDL_Surface* screen) : Activity(engine, screen)
	{

	}

	virtual ~BattleActivity(void)
	{

	}

	virtual void handle(void)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				stop();

			if (event.type == SDL_MOUSEBUTTONDOWN) {
				if (event.button.button == SDL_BUTTON_LEFT) {
					getEngine()->setCurrent(getEngine()->getMainActivity());
					stop();
				}
			}
		}
	}

	virtual void render(void)
	{
		SDL_Surface* screen = getScreen();
		SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0xff, 0x00, 0x00));
		SDL_Flip(screen);
	}
};

} // namespace gs
