#include "Settings.h"

SDL_Texture* get_Records_text_texture(SDL_Renderer*& renderer, char* text, TTF_Font* StatisticRecordstextfont)
{
    SDL_Surface* textSurface = NULL;
    SDL_Color point_color = { 255,255,255 };
    textSurface = TTF_RenderUTF8_Solid(StatisticRecordstextfont, text, point_color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);
    return texture;
}

void Draw_STATISTICFON(SDL_Renderer*& renderer, SDL_Rect FON, SDL_Texture* texture)
{
    SDL_RenderCopy(renderer, texture, NULL, &FON);
}

void Draw_MainMenuExitStatisticButton(SDL_Renderer*& renderer, SDL_Rect MainMenuExitButton, SDL_Texture* texture)
{
    SDL_RenderCopy(renderer, texture, NULL, &MainMenuExitButton);
}

int Is_MainMenuExit_Tap(int x, int y)
{
    if ((x > SCREEN_WIDTH - ButtonsSizeX - 50 && x < SCREEN_WIDTH - 50) && (y > SCREEN_HEIGHT - 50 - ButtonsSizeY && y < SCREEN_HEIGHT - 50))
        return 0;
    return -1;
}

void draw_Records_int_text(SDL_Renderer*& renderer, SDL_Texture* texture, SDL_Rect rect)
{
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void Statistic(SDL_Renderer*& renderer, Mix_Chunk* ButtonTapSound, int GameCount, int WinsCountInRow, int SmallBackCount, int BigBackCount)
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

    SDL_Surface* NumberOfGamesSinceGameLaunchtextSurface = NULL;
    SDL_Surface* MostWinsInARowSurface = NULL;
    SDL_Surface* TotalNumberBigBacsSurface = NULL;
    SDL_Surface* TotalNumberSmallBacsSurface = NULL;
    TTF_Font* StatisticRecordstextfont = TTF_OpenFont("Text/TextSettings.ttf", 100);
    SDL_Color textColor = { 255, 255, 255 };
    NumberOfGamesSinceGameLaunchtextSurface = TTF_RenderUTF8_Solid(StatisticRecordstextfont, u8"Œ¡Ÿ≈≈  ŒÀ»◊≈—“¬Œ »√–", textColor);
    MostWinsInARowSurface = TTF_RenderUTF8_Solid(StatisticRecordstextfont, u8"Ã¿ —»Ã¿À‹ÕŒ≈ ◊»—ÀŒ œŒ¡≈ƒ œŒƒ–ﬂƒ", textColor);
    TotalNumberBigBacsSurface = TTF_RenderUTF8_Solid(StatisticRecordstextfont, u8"Œ¡Ÿ≈≈ ◊»—ÀŒ ¡ŒÀ‹ÿ»’ ¡¿ Œ¬", textColor);
    TotalNumberSmallBacsSurface = TTF_RenderUTF8_Solid(StatisticRecordstextfont, u8"Œ¡Ÿ≈≈ ◊»—ÀŒ Ã¿À€’ ¡¿ Œ¬", textColor);
    SDL_Texture* NumberOfGamesSinceGameLaunchtextTexture = SDL_CreateTextureFromSurface(renderer, NumberOfGamesSinceGameLaunchtextSurface);
    SDL_Texture* MostWinsInARowTexture = SDL_CreateTextureFromSurface(renderer, MostWinsInARowSurface);
    SDL_Texture* TotalNumberBigBacsTexture = SDL_CreateTextureFromSurface(renderer, TotalNumberBigBacsSurface);
    SDL_Texture* TotalNumberSmallBacsTexture = SDL_CreateTextureFromSurface(renderer, TotalNumberSmallBacsSurface);
    SDL_Texture* GameCount_textTexture;
    SDL_Texture* WinsCountInRow_textTexture;
    SDL_Texture* SmallBackCount_textTexture;
    SDL_Texture* BigBackCount_textTexture;
    SDL_Rect NumberOfGamesSinceGameLaunchtextRect = { 50, 50, 660, 50 };
    SDL_Rect MostWinsInARowRect = { 50, 150, 660, 50 };
    SDL_Rect TotalNumberBigBacsRect = { 50, 250, 660, 50 };
    SDL_Rect TotalNumberSmallBacsRect = { 50, 350, 660, 50 };
    SDL_Rect GameCountRect = { 50 + 760, 50, 50, 50 };
    SDL_Rect WinsCountInRowRect = { 50 + 760, 150, 50, 50 };
    SDL_Rect SmallBackCountRect = { 50 + 760, 250, 50, 50 };
    SDL_Rect BigBackCountRect = { 50 + 760, 350, 50, 50 };

    SDL_Event event;
    bool quit = false;

    int x, y;
    bool exit = false;

    char text[10];
    _itoa_s(GameCount, text, 10);
    GameCount_textTexture = get_Records_text_texture(renderer, text, StatisticRecordstextfont);
    _itoa_s(WinsCountInRow, text, 10);
    WinsCountInRow_textTexture = get_Records_text_texture(renderer, text, StatisticRecordstextfont);
    _itoa_s(BigBackCount, text, 10);
    SmallBackCount_textTexture = get_Records_text_texture(renderer, text, StatisticRecordstextfont);
    _itoa_s(SmallBackCount, text, 10);
    BigBackCount_textTexture = get_Records_text_texture(renderer, text, StatisticRecordstextfont);

    while (!quit)
    {
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT)
            quit = true;

        SDL_RenderClear(renderer);
        Draw_STATISTICFON(renderer, SettingFonRect, SettingFonTexture);
        Draw_MainMenuExitStatisticButton(renderer, MainMenuButtonRect, MainMenuButtonTexture);
        SDL_RenderCopy(renderer, NumberOfGamesSinceGameLaunchtextTexture, NULL, &NumberOfGamesSinceGameLaunchtextRect);
        SDL_RenderCopy(renderer, MostWinsInARowTexture, NULL, &MostWinsInARowRect);
        SDL_RenderCopy(renderer, TotalNumberBigBacsTexture, NULL, &TotalNumberBigBacsRect);
        SDL_RenderCopy(renderer, TotalNumberSmallBacsTexture, NULL, &TotalNumberSmallBacsRect);
        SDL_RenderCopy(renderer, GameCount_textTexture, NULL, &GameCountRect);
        draw_Records_int_text(renderer, WinsCountInRow_textTexture, WinsCountInRowRect);
        draw_Records_int_text(renderer, SmallBackCount_textTexture, SmallBackCountRect);
        draw_Records_int_text(renderer, BigBackCount_textTexture, BigBackCountRect);
        SDL_RenderPresent(renderer);

        if ((event.type == SDL_MOUSEBUTTONDOWN) && (event.button.button = SDL_BUTTON_LEFT))
        {
            SDL_GetMouseState(&x, &y);
            switch (Is_MainMenuExit_Tap(x, y))
            {
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
    SDL_DestroyTexture(NumberOfGamesSinceGameLaunchtextTexture);
    SDL_DestroyTexture(MostWinsInARowTexture);
    SDL_DestroyTexture(TotalNumberBigBacsTexture);
    SDL_DestroyTexture(TotalNumberSmallBacsTexture);
    SDL_DestroyTexture(GameCount_textTexture);
    SDL_DestroyTexture(WinsCountInRow_textTexture);
    SDL_DestroyTexture(SmallBackCount_textTexture);
    SDL_DestroyTexture(BigBackCount_textTexture);
    SDL_FreeSurface(NumberOfGamesSinceGameLaunchtextSurface);
    SDL_FreeSurface(MostWinsInARowSurface);
    SDL_FreeSurface(TotalNumberBigBacsSurface);
    SDL_FreeSurface(TotalNumberSmallBacsSurface);
    TTF_CloseFont(StatisticRecordstextfont);
    TTF_Quit();
}