#include "Shered.h"
#include "Game.h"
#include "Settings.h"
#include "Statistic.h"

Mix_Music* MainMenuMusic = NULL;
Mix_Music* GameMusic = NULL;
Mix_Chunk* ButtonTapSound = NULL;
Mix_Chunk* DiceRollingSound = NULL;

void Draw_FON(SDL_Renderer*& renderer, SDL_Rect FON, SDL_Texture* texture)
{
    SDL_RenderCopy(renderer, texture, NULL, &FON);
}

void Draw_GameRules(SDL_Renderer*& renderer, SDL_Rect FON, SDL_Texture* texture)
{
    SDL_RenderCopy(renderer, texture, NULL, &FON);
}

void Draw_StartGameButton(SDL_Renderer*& renderer, SDL_Rect StartGameButton, SDL_Texture* texture)
{
    SDL_RenderCopy(renderer, texture, NULL, &StartGameButton);
}

void Draw_SettingsButton(SDL_Renderer*& renderer, SDL_Rect SettingsButton, SDL_Texture* texture)
{
    SDL_RenderCopy(renderer, texture, NULL, &SettingsButton);
}

void Draw_StatisticsButton(SDL_Renderer*& renderer, SDL_Rect StatisticsButton, SDL_Texture* texture)
{
    SDL_RenderCopy(renderer, texture, NULL, &StatisticsButton);
}

void Draw_GameExitButton(SDL_Renderer*& renderer, SDL_Rect GameExitButton, SDL_Texture* texture)
{
    SDL_RenderCopy(renderer, texture, NULL, &GameExitButton);
}

void Draw_GameRulesButton(SDL_Renderer*& renderer, SDL_Rect GameExitButton, SDL_Texture* texture)
{
    SDL_RenderCopy(renderer, texture, NULL, &GameExitButton);
}

int Is_Button_Tap(int x, int y)
{
    if ((x > 50 && x < 50 + ButtonsSizeX) && (y > 50 && y < 50 + ButtonsSizeY))
        return 1;
    if ((x > 50 && x < 50 + ButtonsSizeX) && (y > 150 && y < 150 + ButtonsSizeY))
        return 2;
    if ((x > 50 && x < 50 + ButtonsSizeX) && (y > 250 && y < 250 + ButtonsSizeY))
        return 3;
    if ((x > 50 && x < 50 + ButtonsSizeX) && (y > 350 && y < 350 + ButtonsSizeY))
        return 4;
    if ((x > SCREEN_WIDTH - ButtonsSizeX - 50 && x < SCREEN_WIDTH - 50) && (y > SCREEN_HEIGHT - 50 - ButtonsSizeY && y < SCREEN_HEIGHT - 50))
        return 0;
    return -1;
}

bool Is_ButtonRules_Tap(int x, int y)
{
    if ((x > SCREEN_WIDTH - ButtonsSizeX - 50 && x < SCREEN_WIDTH - 50) && (y > SCREEN_HEIGHT - 10 - ButtonsSizeY && y < SCREEN_HEIGHT - 25))
        return true;
    return false;
}

int main(int argc, char** argv)
{
    setlocale(LC_ALL, "rus");
    srand(time(NULL));

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow("Back Dice", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_Surface* Fon = IMG_Load("Fons/MainMenu.bmp");
    SDL_SetColorKey(Fon, SDL_TRUE, SDL_MapRGB(Fon->format, 255, 255, 255));
    SDL_Texture* FonTexture = SDL_CreateTextureFromSurface(renderer, Fon);
    SDL_FreeSurface(Fon);
    SDL_Rect FonRect{ 0,0, SCREEN_WIDTH,SCREEN_HEIGHT };

    SDL_Surface* StartGameButton = IMG_Load("Buttons/StartGameButton.bmp");
    SDL_SetColorKey(StartGameButton, SDL_TRUE, SDL_MapRGB(StartGameButton->format, 255, 255, 255));
    SDL_Texture* StartGameButtonTexture = SDL_CreateTextureFromSurface(renderer, StartGameButton);
    SDL_FreeSurface(StartGameButton);
    SDL_Rect StartGameButtonRect = { 50,50,ButtonsSizeX,ButtonsSizeY };

    SDL_Surface* SettingsButton = IMG_Load("Buttons/SettingsButton.bmp");
    SDL_SetColorKey(SettingsButton, SDL_TRUE, SDL_MapRGB(SettingsButton->format, 255, 255, 255));
    SDL_Texture* SettingsButtonTexture = SDL_CreateTextureFromSurface(renderer, SettingsButton);
    SDL_FreeSurface(SettingsButton);
    SDL_Rect SettingsButtonRect = { 50,150,ButtonsSizeX,ButtonsSizeY };

    SDL_Surface* StatisticsButton = IMG_Load("Buttons/StatisticsButton.bmp");
    SDL_SetColorKey(StatisticsButton, SDL_TRUE, SDL_MapRGB(StatisticsButton->format, 255, 255, 255));
    SDL_Texture* StatisticsButtonTexture = SDL_CreateTextureFromSurface(renderer, StatisticsButton);
    SDL_FreeSurface(StatisticsButton);
    SDL_Rect StatisticsButtonRect = { 50,250,ButtonsSizeX,ButtonsSizeY };

    SDL_Surface* GameRulesButton = IMG_Load("Buttons/GameRulesButton.bmp");
    SDL_SetColorKey(GameRulesButton, SDL_TRUE, SDL_MapRGB(GameRulesButton->format, 255, 255, 255));
    SDL_Texture* GameRulesButtonTexture = SDL_CreateTextureFromSurface(renderer, GameRulesButton);
    SDL_FreeSurface(GameRulesButton);
    SDL_Rect GameRulesButtonRect = { 50,350,ButtonsSizeX,ButtonsSizeY };

    SDL_Surface* GameExitButton = IMG_Load("Buttons/GameExitButton.bmp");
    SDL_SetColorKey(GameExitButton, SDL_TRUE, SDL_MapRGB(GameExitButton->format, 255, 255, 255));
    SDL_Texture* GameExitButtonTexture = SDL_CreateTextureFromSurface(renderer, GameExitButton);
    SDL_FreeSurface(GameExitButton);
    SDL_Rect GameExitButtonRect = { SCREEN_WIDTH - 50 - ButtonsSizeX, SCREEN_HEIGHT - 50 - ButtonsSizeY, ButtonsSizeX, ButtonsSizeY };

    SDL_Surface* GameRulesFon = IMG_Load("Fons/GameRules.bmp");
    SDL_SetColorKey(GameRulesFon, SDL_TRUE, SDL_MapRGB(GameRulesFon->format, 0, 0, 0));
    SDL_Texture* GameRulesFonTexture = SDL_CreateTextureFromSurface(renderer, GameRulesFon);
    SDL_FreeSurface(GameRulesFon);
    SDL_Rect GameRulesFonRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

    SDL_Surface* MainMenuExitRulesButton = IMG_Load("Buttons/MainMenuButton.bmp");
    SDL_SetColorKey(MainMenuExitRulesButton, SDL_TRUE, SDL_MapRGB(MainMenuExitRulesButton->format, 255, 255, 255));
    SDL_Texture* MainMenuExitRulesButtonTexture = SDL_CreateTextureFromSurface(renderer, MainMenuExitRulesButton);
    SDL_FreeSurface(MainMenuExitRulesButton);
    SDL_Rect MainMenuExitRulesButtonRect = { SCREEN_WIDTH - 50 - ButtonsSizeX, SCREEN_HEIGHT - 10 - ButtonsSizeY, ButtonsSizeX, ButtonsSizeY };
    

    int MainMenuvolume = MIX_MAX_VOLUME;
    int GameVolume = MIX_MAX_VOLUME / 2 + 30;

    Mix_Init(0);
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024);
    MainMenuMusic = Mix_LoadMUS("Musics/MainMenuTheme.mp3");
    GameMusic = Mix_LoadMUS("Musics/GameMusic.mp3");
    ButtonTapSound = Mix_LoadWAV("Musics/ButtonTapSound.mp3");
    DiceRollingSound = Mix_LoadWAV("Musics/DiceRollingSound.mp3");
    Mix_PlayMusic(MainMenuMusic, -1);

    SDL_Event event;
    bool quit = false;

    bool CloseRules = false;

    int GameCount, WinsCountInRow, SmallBackCount, BigBackCount;

    int x, y;

    while (!quit)
    {
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT)
            quit = true;

        SDL_RenderClear(renderer);
        Draw_FON(renderer, FonRect, FonTexture);
        Draw_StartGameButton(renderer, StartGameButtonRect, StartGameButtonTexture);
        Draw_SettingsButton(renderer, SettingsButtonRect, SettingsButtonTexture);
        Draw_StatisticsButton(renderer, StatisticsButtonRect, StatisticsButtonTexture);
        Draw_GameExitButton(renderer, GameExitButtonRect, GameExitButtonTexture);
        Draw_GameRulesButton(renderer, GameRulesButtonRect, GameRulesButtonTexture);
        SDL_RenderPresent(renderer);

        ifstream f("Records.txt");
        if (f.is_open())
            while (!f.eof())
            {
                f >> GameCount;
                f >> WinsCountInRow;
                f >> SmallBackCount;
                f >> BigBackCount;
            }
        else
            cout << "File not found\n";
        f.close();

        if ((event.type == SDL_MOUSEBUTTONDOWN) && (event.button.button = SDL_BUTTON_LEFT))
        {
            SDL_GetMouseState(&x, &y);
            switch (Is_Button_Tap(x, y))
            {
            case 1:
            {
                Mix_PlayChannel(-1, ButtonTapSound, 0);
                SDL_Delay(150);
                Game(renderer, ButtonTapSound, DiceRollingSound, GameMusic, GameVolume, GameCount, WinsCountInRow, SmallBackCount, BigBackCount);
                GameCount += 1;

                ofstream f("Records.txt");
                f.seekp(0);
                f << GameCount << " " << WinsCountInRow << " " << SmallBackCount << " " << BigBackCount;
                f.close();

                Mix_PlayMusic(MainMenuMusic, -1);
                Mix_VolumeMusic(MainMenuvolume);
            }; break;

            case 2:
            {
                Mix_PlayChannel(-1, ButtonTapSound, 0);
                SDL_Delay(150);
                Settings(renderer, MainMenuMusic, GameMusic, ButtonTapSound, MainMenuvolume, GameVolume);
            }; break;

            case 3:
            { 
                Mix_PlayChannel(-1, ButtonTapSound, 0);
                SDL_Delay(150);
                Statistic(renderer, ButtonTapSound, GameCount, WinsCountInRow, SmallBackCount, BigBackCount);
            }; break;

            case 4:
            {
                CloseRules = false;
                Mix_PlayChannel(-1, ButtonTapSound, 0);
                SDL_Delay(150);
                SDL_RenderClear(renderer);
                Draw_GameRules(renderer, GameRulesFonRect, GameRulesFonTexture);
                SDL_RenderCopy(renderer, MainMenuExitRulesButtonTexture, NULL, &MainMenuExitRulesButtonRect);
                SDL_RenderPresent(renderer);
                while (!CloseRules)
                {
                    SDL_PollEvent(&event);
                    if (event.type == SDL_QUIT)
                        CloseRules = true;

                    if ((event.type == SDL_MOUSEBUTTONDOWN) && (event.button.button = SDL_BUTTON_LEFT))
                    {
                        SDL_GetMouseState(&x, &y);
                        if (Is_ButtonRules_Tap(x, y) == true)
                        {
                            Mix_PlayChannel(-1, ButtonTapSound, 0);
                            SDL_Delay(150);
                            CloseRules = true;
                        }
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
    SDL_DestroyTexture(StartGameButtonTexture);
    SDL_DestroyTexture(SettingsButtonTexture);
    SDL_DestroyTexture(StatisticsButtonTexture);
    SDL_DestroyTexture(GameExitButtonTexture);
    SDL_DestroyTexture(GameRulesButtonTexture);
    SDL_DestroyTexture(GameRulesFonTexture);
    SDL_DestroyTexture(MainMenuExitRulesButtonTexture);
    Mix_CloseAudio();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}