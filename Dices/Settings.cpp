#include "Settings.h"

void Draw_SETTINGSFON(SDL_Renderer*& renderer, SDL_Rect FON, SDL_Texture* texture)
{
	SDL_RenderCopy(renderer, texture, NULL, &FON);
}

void Draw_MainMenuExitButton(SDL_Renderer*& renderer, SDL_Rect MainMenuExitButton, SDL_Texture* texture)
{
	SDL_RenderCopy(renderer, texture, NULL, &MainMenuExitButton);
}

int Is_Tap(int x, int y)
{
    if ((x > 50 && x < 50 + 660) && (y > 50 && y < 50 + 50))
        return 1;
    if ((x > 50 && x < 50 + 660) && (y > 150 && y < 150 + 50))
        return 2;
    if ((x > SCREEN_WIDTH - ButtonsSizeX - 50 && x < SCREEN_WIDTH - 50) && (y > SCREEN_HEIGHT - 50 - ButtonsSizeY && y < SCREEN_HEIGHT - 50))
        return 0;
    return -1;
}

void Settings(SDL_Renderer*& renderer, Mix_Music* MainMenuMusic, Mix_Music* GameMusic, Mix_Chunk* ButtonTapSound, int& MainMenuvolume, int& GameVolume)
{
	SDL_Surface* MainMenuButton = IMG_Load("Buttons/MainMenuButton.bmp");
	SDL_SetColorKey(MainMenuButton, SDL_TRUE, SDL_MapRGB(MainMenuButton->format, 255, 255, 255));
	SDL_Texture* MainMenuButtonTexture = SDL_CreateTextureFromSurface(renderer, MainMenuButton);
	SDL_FreeSurface(MainMenuButton);
	SDL_Rect MainMenuButtonRect = { SCREEN_WIDTH - 50 - ButtonsSizeX,SCREEN_HEIGHT - 50 - ButtonsSizeY,ButtonsSizeX,ButtonsSizeY };

	SDL_Surface* SettingFon = IMG_Load("Fons/MainMenu.bmp");
	SDL_SetColorKey(SettingFon, SDL_TRUE, SDL_MapRGB(SettingFon->format, 255, 255, 255));
	SDL_Texture* SettingFonTexture = SDL_CreateTextureFromSurface(renderer, SettingFon);
	SDL_FreeSurface(SettingFon);
	SDL_Rect SettingFonRect{ 0,0, SCREEN_WIDTH,SCREEN_HEIGHT };

    TTF_Init();

    SDL_Surface* MainMenuMusictextSurface = NULL;
    SDL_Surface* GameMusictextSurface = NULL;
    SDL_Surface* CluetextSurface = NULL;
    TTF_Font* SettingVolumetextfont = TTF_OpenFont("Text/TextSettings.ttf", 100);
    SDL_Color textColor = { 255, 255, 255 };
    GameMusictextSurface = TTF_RenderUTF8_Solid(SettingVolumetextfont, u8"√–ŒÃ Œ—“‹ Ã”«€ » »√–Œ¬Œ… —≈——»»", textColor);
    MainMenuMusictextSurface = TTF_RenderUTF8_Solid(SettingVolumetextfont, u8"√–ŒÃ Œ—“‹ Ã”«€ » √À¿¬ÕŒ√Œ Ã≈Õﬁ", textColor);
    CluetextSurface = TTF_RenderUTF8_Solid(SettingVolumetextfont, u8"À Ã; LEFTARROW(-) RIGHTARROW(+); Q - ¬€’Œƒ »« –≈∆»Ã¿ »«Ã≈Õ≈Õ»ﬂ √–ŒÃ Œ—“»", textColor);
    SDL_Texture* MainMenuMusictextTexture = SDL_CreateTextureFromSurface(renderer, MainMenuMusictextSurface);
    SDL_Texture* GameMusictextTexture = SDL_CreateTextureFromSurface(renderer, GameMusictextSurface);
    SDL_Texture* CluetextTexture = SDL_CreateTextureFromSurface(renderer, CluetextSurface);
    SDL_Rect MainMenuMusictextRect = { 50, 50, 660, 50 };
    SDL_Rect GameMusictextRect = { 50, 150, 660, 50 };
    SDL_Rect CluetextRect = { 50, SCREEN_HEIGHT - 100, 900, 50 };

	SDL_Event event;
	bool quit = false;

    int x, y;
    bool exit = false;

	while (!quit)
	{
		SDL_PollEvent(&event);
		if (event.type == SDL_QUIT)
			quit = true;

		SDL_RenderClear(renderer);
		Draw_SETTINGSFON(renderer, SettingFonRect, SettingFonTexture);
		Draw_MainMenuExitButton(renderer, MainMenuButtonRect, MainMenuButtonTexture);
        SDL_RenderCopy(renderer, MainMenuMusictextTexture, NULL, &MainMenuMusictextRect);
        SDL_RenderCopy(renderer, GameMusictextTexture, NULL, &GameMusictextRect);
        SDL_RenderCopy(renderer, CluetextTexture, NULL, &CluetextRect);
        SDL_RenderPresent(renderer);

        if ((event.type == SDL_MOUSEBUTTONDOWN) && (event.button.button = SDL_BUTTON_LEFT))
        {
            SDL_GetMouseState(&x, &y);
            switch (Is_Tap(x, y))
            {
            case 1:
            {
                exit = false;
                Mix_PlayChannel(-1, ButtonTapSound, 0);
                SDL_Delay(150);
                while (!exit)
                {
                    SDL_PollEvent(&event);
                    if (event.type == SDL_QUIT)
                    {
                        exit = true;
                        quit = true;
                    }

                    if ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_LEFT))
                    {
                        MainMenuvolume -= 10;
                        if (MainMenuvolume < 0)
                        {
                            MainMenuvolume = 0;
                        }
                    }
                    else if ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_RIGHT))
                    {
                        MainMenuvolume += 10;
                        if (MainMenuvolume > MIX_MAX_VOLUME)
                        {
                            MainMenuvolume = MIX_MAX_VOLUME;
                        }
                    }
                    Mix_VolumeMusic(MainMenuvolume);
                    if ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_q)) 
                    {
                        exit = true;
                    }
                }            
            }; break;

            case 2:
            {
                exit = false;
                Mix_PlayChannel(-1, ButtonTapSound, 0);
                SDL_Delay(150);
                Mix_PlayMusic(GameMusic, -1);
                Mix_VolumeMusic(GameVolume);
                while (!exit)
                {
                    SDL_PollEvent(&event);
                    if (event.type == SDL_QUIT)
                    {
                        exit = true;
                        quit = true;
                    }

                    if ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_LEFT))
                    {
                        GameVolume -= 10;
                        if (GameVolume < 0)
                        {
                            GameVolume = 0;
                        }
                    }
                    else if ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_RIGHT))
                    {
                        GameVolume += 10;
                        if (GameVolume > MIX_MAX_VOLUME)
                        {
                            GameVolume = MIX_MAX_VOLUME;
                        }
                    }
                    Mix_VolumeMusic(GameVolume);
                    if ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_q))
                    {
                        Mix_HaltMusic();
                        exit = true;
                        Mix_PlayMusic(MainMenuMusic, -1);
                        Mix_VolumeMusic(MainMenuvolume);
                    }
                }
            }; break;

            case 0:
            {
                Mix_PlayChannel(-1, ButtonTapSound, 0);
                SDL_Delay(150);
                quit = true;
            }; break;

            default:; break;

            }
        }
	}
	SDL_DestroyTexture(MainMenuButtonTexture);
    SDL_DestroyTexture(MainMenuMusictextTexture);
    SDL_DestroyTexture(GameMusictextTexture);
    SDL_DestroyTexture(CluetextTexture);
    SDL_FreeSurface(MainMenuMusictextSurface);
    SDL_FreeSurface(GameMusictextSurface);
    SDL_FreeSurface(CluetextSurface);
    TTF_CloseFont(SettingVolumetextfont);
    TTF_Quit();
}