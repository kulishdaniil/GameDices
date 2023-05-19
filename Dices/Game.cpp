#include "Game.h"

Mix_Chunk* WinSound = NULL;
Mix_Chunk* LooseSound = NULL;
Mix_Chunk* GameOverSound = NULL;

void Draw_GameFON(SDL_Renderer*& renderer, SDL_Rect FON, SDL_Texture* texture)
{
	SDL_RenderCopy(renderer, texture, NULL, &FON);
}

void Draw_WinFON(SDL_Renderer*& renderer, SDL_Rect FON, SDL_Texture* texture)
{
	SDL_RenderCopy(renderer, texture, NULL, &FON);
}

void Draw_LooseFON(SDL_Renderer*& renderer, SDL_Rect FON, SDL_Texture* texture)
{
	SDL_RenderCopy(renderer, texture, NULL, &FON);
}

void Draw_FirstDiceRollButton(SDL_Renderer*& renderer, SDL_Rect FirstDiceRollButton, SDL_Texture* texture)
{
	SDL_RenderCopy(renderer, texture, NULL, &FirstDiceRollButton);
}

void Draw_MainMenuExitGameButton(SDL_Renderer*& renderer, SDL_Rect MainMenuExitButton, SDL_Texture* texture)
{
	SDL_RenderCopy(renderer, texture, NULL, &MainMenuExitButton);
}

bool IsButtonTap(int x, int y)
{
	if ((x > (SCREEN_WIDTH / 2) - (ButtonsSizeX / 2) && x < (SCREEN_WIDTH / 2) + (ButtonsSizeX / 2)) && (y > SCREEN_HEIGHT - 50 - ButtonsSizeY && y < SCREEN_HEIGHT - 50))
		return true;
	return false;
}

int Is_Main_Menu_or_Restart_Tap(int x, int y)
{
	if ((x > SCREEN_WIDTH - ButtonsSizeX - 50 && x < SCREEN_WIDTH - 50) && (y > SCREEN_HEIGHT - 50 - ButtonsSizeY && y < SCREEN_HEIGHT - 50))
		return 0;
	return -1;
}

void Draw_CubeEdge(SDL_Renderer*& renderer, SDL_Rect DiceEdge, SDL_Texture* edgetexture)
{
	SDL_RenderCopy(renderer, edgetexture, NULL, &DiceEdge);
}

SDL_Texture* get_POINT_text_texture(SDL_Renderer*& renderer, char* text, TTF_Font* Point_Defenitiontext)
{
	SDL_Surface* textSurface = NULL;
	SDL_Color point_color = { 255,255,255 };
	textSurface = TTF_RenderUTF8_Solid(Point_Defenitiontext, text, point_color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_FreeSurface(textSurface);
	return texture;
}

SDL_Texture* get_YOU_SCORE_text_texture(SDL_Renderer*& renderer, char* text, TTF_Font* Point_Defenitiontext)
{
	SDL_Surface* textSurface = NULL;
	SDL_Color point_color = { 255,255,255 };
	textSurface = TTF_RenderUTF8_Solid(Point_Defenitiontext, text, point_color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_FreeSurface(textSurface);
	return texture;
}

SDL_Texture* get_OPPONENT_SCORE_text_texture(SDL_Renderer*& renderer, char* text, TTF_Font* Point_Defenitiontext)
{
	SDL_Surface* textSurface = NULL;
	SDL_Color point_color = { 255,255,255 };
	textSurface = TTF_RenderUTF8_Solid(Point_Defenitiontext, text, point_color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_FreeSurface(textSurface);
	return texture;
}

void draw_POINT_text(SDL_Renderer*& renderer, SDL_Texture* texture)
{
	SDL_Rect POINT_rect = { 0, 40, 70, 70 };
	SDL_RenderCopy(renderer, texture, NULL, &POINT_rect);
}

void draw_YOU_SCORE_text(SDL_Renderer*& renderer, SDL_Texture* texture)
{
	SDL_Rect POINT_rect = { SCREEN_WIDTH - 40, 40, 40, 35 };
	SDL_RenderCopy(renderer, texture, NULL, &POINT_rect);
}

void draw_OPPONENT_1_SCORE_text(SDL_Renderer*& renderer, SDL_Texture* texture)
{
	SDL_Rect POINT_rect = { SCREEN_WIDTH - 40, 75, 40, 35 }; 
	SDL_RenderCopy(renderer, texture, NULL, &POINT_rect);
}

void draw_OPPONENT_2_SCORE_text(SDL_Renderer*& renderer, SDL_Texture* texture)
{
	SDL_Rect POINT_rect = { SCREEN_WIDTH - 40, 110, 40, 35 };
	SDL_RenderCopy(renderer, texture, NULL, &POINT_rect);
}


void Game(SDL_Renderer*& renderer, Mix_Chunk* ButtonTapSound, Mix_Chunk* DiceRollingSound, Mix_Music* GameMusic, int GameVolume, int& GameCount, int& WinsCountInRow, int& SmallBackCount, int& BigBackCount)
{
	SDL_Surface* GameFon = IMG_Load("Fons/GameTable.bmp");
	SDL_SetColorKey(GameFon, SDL_TRUE, SDL_MapRGB(GameFon->format, 255, 255, 255));
	SDL_Texture* GameFonTexture = SDL_CreateTextureFromSurface(renderer, GameFon);
	SDL_FreeSurface(GameFon);
	SDL_Rect GameFonRect{ 0,0, SCREEN_WIDTH,SCREEN_HEIGHT };

	SDL_Surface* WinFon = IMG_Load("Fons/Win.bmp");
	SDL_SetColorKey(WinFon, SDL_TRUE, SDL_MapRGB(WinFon->format, 255, 255, 255));
	SDL_Texture* WinFonTexture = SDL_CreateTextureFromSurface(renderer, WinFon);
	SDL_FreeSurface(WinFon);
	SDL_Rect WinFonRect{ 0,0, SCREEN_WIDTH,SCREEN_HEIGHT };

	SDL_Surface* LooseFon = IMG_Load("Fons/Loose.bmp");
	SDL_SetColorKey(LooseFon, SDL_TRUE, SDL_MapRGB(LooseFon->format, 255, 255, 255));
	SDL_Texture* LooseFonTexture = SDL_CreateTextureFromSurface(renderer, LooseFon);
	SDL_FreeSurface(LooseFon);
	SDL_Rect LooseFonRect{ 0,0, SCREEN_WIDTH,SCREEN_HEIGHT };

	SDL_Surface* FirstDiceRollButton = IMG_Load("Buttons/RollDiceButton.bmp");
	SDL_SetColorKey(FirstDiceRollButton, SDL_TRUE, SDL_MapRGB(FirstDiceRollButton->format, 255, 255, 255));
	SDL_Texture* FirstDiceRollButtonTexture = SDL_CreateTextureFromSurface(renderer, FirstDiceRollButton);
	SDL_FreeSurface(FirstDiceRollButton);
	SDL_Rect FirstDiceRollButtonRect = { (SCREEN_WIDTH / 2) - (ButtonsSizeX / 2), SCREEN_HEIGHT - 50 - ButtonsSizeY, ButtonsSizeX, ButtonsSizeY };

	SDL_Surface* MainMenuButton = IMG_Load("Buttons/MainMenuButton.bmp");
	SDL_SetColorKey(MainMenuButton, SDL_TRUE, SDL_MapRGB(MainMenuButton->format, 255, 255, 255));
	SDL_Texture* MainMenuButtonTexture = SDL_CreateTextureFromSurface(renderer, MainMenuButton);
	SDL_FreeSurface(MainMenuButton);
	SDL_Rect MainMenuButtonRect = { SCREEN_WIDTH - 50 - ButtonsSizeX,SCREEN_HEIGHT - 50 - ButtonsSizeY,ButtonsSizeX,ButtonsSizeY };

	SDL_Surface* Cube_edge_1 = IMG_Load("Edge/edge_1.bmp");
	SDL_SetColorKey(Cube_edge_1, SDL_TRUE, SDL_MapRGB(Cube_edge_1->format, 255, 255, 255));
	SDL_Texture* Cube_edge_1_Texture = SDL_CreateTextureFromSurface(renderer, Cube_edge_1);
	SDL_FreeSurface(Cube_edge_1);
	SDL_Rect Cube_edge_1_LEFT_Rect = { (SCREEN_WIDTH / 2) - (CubeEdgeSizeX * 2) - 10, (SCREEN_HEIGHT / 2) - (CubeEdgeSizeY / 2), CubeEdgeSizeX, CubeEdgeSizeY };
	SDL_Rect Cube_edge_1_MID_Rect = { (SCREEN_WIDTH / 2) - (CubeEdgeSizeX / 2), (SCREEN_HEIGHT / 2) - (CubeEdgeSizeY / 2), CubeEdgeSizeX, CubeEdgeSizeY };
	SDL_Rect Cube_edge_1_RIGHT_Rect = { (SCREEN_WIDTH / 2) + CubeEdgeSizeX + 10, (SCREEN_HEIGHT / 2) - (CubeEdgeSizeY / 2), CubeEdgeSizeX, CubeEdgeSizeY };

	SDL_Surface* Cube_edge_2 = IMG_Load("Edge/edge_2.bmp");
	SDL_SetColorKey(Cube_edge_2, SDL_TRUE, SDL_MapRGB(Cube_edge_2->format, 255, 255, 255));
	SDL_Texture* Cube_edge_2_Texture = SDL_CreateTextureFromSurface(renderer, Cube_edge_2);
	SDL_FreeSurface(Cube_edge_2);
	SDL_Rect Cube_edge_2_LEFT_Rect = { (SCREEN_WIDTH / 2) - (CubeEdgeSizeX * 2) - 10, (SCREEN_HEIGHT / 2) - (CubeEdgeSizeY / 2), CubeEdgeSizeX, CubeEdgeSizeY };
	SDL_Rect Cube_edge_2_MID_Rect = { (SCREEN_WIDTH / 2) - (CubeEdgeSizeX / 2), (SCREEN_HEIGHT / 2) - (CubeEdgeSizeY / 2), CubeEdgeSizeX, CubeEdgeSizeY };
	SDL_Rect Cube_edge_2_RIGHT_Rect = { (SCREEN_WIDTH / 2) + CubeEdgeSizeX + 10, (SCREEN_HEIGHT / 2) - (CubeEdgeSizeY / 2), CubeEdgeSizeX, CubeEdgeSizeY };

	SDL_Surface* Cube_edge_3 = IMG_Load("Edge/edge_3.bmp");
	SDL_SetColorKey(Cube_edge_3, SDL_TRUE, SDL_MapRGB(Cube_edge_3->format, 255, 255, 255));
	SDL_Texture* Cube_edge_3_Texture = SDL_CreateTextureFromSurface(renderer, Cube_edge_3);
	SDL_FreeSurface(Cube_edge_3);
	SDL_Rect Cube_edge_3_LEFT_Rect = { (SCREEN_WIDTH / 2) - (CubeEdgeSizeX * 2) - 10, (SCREEN_HEIGHT / 2) - (CubeEdgeSizeY / 2), CubeEdgeSizeX, CubeEdgeSizeY };
	SDL_Rect Cube_edge_3_MID_Rect = { (SCREEN_WIDTH / 2) - (CubeEdgeSizeX / 2), (SCREEN_HEIGHT / 2) - (CubeEdgeSizeY / 2), CubeEdgeSizeX, CubeEdgeSizeY };
	SDL_Rect Cube_edge_3_RIGHT_Rect = { (SCREEN_WIDTH / 2) + CubeEdgeSizeX + 10, (SCREEN_HEIGHT / 2) - (CubeEdgeSizeY / 2), CubeEdgeSizeX, CubeEdgeSizeY };

	SDL_Surface* Cube_edge_4 = IMG_Load("Edge/edge_4.bmp");
	SDL_SetColorKey(Cube_edge_4, SDL_TRUE, SDL_MapRGB(Cube_edge_4->format, 255, 255, 255));
	SDL_Texture* Cube_edge_4_Texture = SDL_CreateTextureFromSurface(renderer, Cube_edge_4);
	SDL_FreeSurface(Cube_edge_4);
	SDL_Rect Cube_edge_4_LEFT_Rect = { (SCREEN_WIDTH / 2) - (CubeEdgeSizeX * 2) - 10, (SCREEN_HEIGHT / 2) - (CubeEdgeSizeY / 2), CubeEdgeSizeX, CubeEdgeSizeY };
	SDL_Rect Cube_edge_4_MID_Rect = { (SCREEN_WIDTH / 2) - (CubeEdgeSizeX / 2), (SCREEN_HEIGHT / 2) - (CubeEdgeSizeY / 2), CubeEdgeSizeX, CubeEdgeSizeY };
	SDL_Rect Cube_edge_4_RIGHT_Rect = { (SCREEN_WIDTH / 2) + CubeEdgeSizeX + 10, (SCREEN_HEIGHT / 2) - (CubeEdgeSizeY / 2), CubeEdgeSizeX, CubeEdgeSizeY };

	SDL_Surface* Cube_edge_5 = IMG_Load("Edge/edge_5.bmp");
	SDL_SetColorKey(Cube_edge_5, SDL_TRUE, SDL_MapRGB(Cube_edge_5->format, 255, 255, 255));
	SDL_Texture* Cube_edge_5_Texture = SDL_CreateTextureFromSurface(renderer, Cube_edge_5);
	SDL_FreeSurface(Cube_edge_5);
	SDL_Rect Cube_edge_5_LEFT_Rect = { (SCREEN_WIDTH / 2) - (CubeEdgeSizeX * 2) - 10, (SCREEN_HEIGHT / 2) - (CubeEdgeSizeY / 2), CubeEdgeSizeX, CubeEdgeSizeY };
	SDL_Rect Cube_edge_5_MID_Rect = { (SCREEN_WIDTH / 2) - (CubeEdgeSizeX / 2), (SCREEN_HEIGHT / 2) - (CubeEdgeSizeY / 2), CubeEdgeSizeX, CubeEdgeSizeY };
	SDL_Rect Cube_edge_5_RIGHT_Rect = { (SCREEN_WIDTH / 2) + CubeEdgeSizeX + 10, (SCREEN_HEIGHT / 2) - (CubeEdgeSizeY / 2), CubeEdgeSizeX, CubeEdgeSizeY };

	SDL_Surface* Cube_edge_6 = IMG_Load("Edge/edge_6.bmp");
	SDL_SetColorKey(Cube_edge_6, SDL_TRUE, SDL_MapRGB(Cube_edge_6->format, 255, 255, 255));
	SDL_Texture* Cube_edge_6_Texture = SDL_CreateTextureFromSurface(renderer, Cube_edge_6);
	SDL_FreeSurface(Cube_edge_6);
	SDL_Rect Cube_edge_6_LEFT_Rect = { (SCREEN_WIDTH / 2) - (CubeEdgeSizeX * 2) - 10, (SCREEN_HEIGHT / 2) - (CubeEdgeSizeY / 2), CubeEdgeSizeX, CubeEdgeSizeY };
	SDL_Rect Cube_edge_6_MID_Rect = { (SCREEN_WIDTH / 2) - (CubeEdgeSizeX / 2), (SCREEN_HEIGHT / 2) - (CubeEdgeSizeY / 2), CubeEdgeSizeX, CubeEdgeSizeY };
	SDL_Rect Cube_edge_6_RIGHT_Rect = { (SCREEN_WIDTH / 2) + CubeEdgeSizeX - 10, (SCREEN_HEIGHT / 2) - (CubeEdgeSizeY / 2), CubeEdgeSizeX, CubeEdgeSizeY };

	TTF_Init();

	SDL_Surface* Point_DefenitiontextSurface = NULL;
	SDL_Surface* Turn_OrdertextSurface = NULL;
	SDL_Surface* Your_turntextSurface = NULL;
	SDL_Surface* Opponent_turntextSurface = NULL;
	SDL_Surface* POINTtextSurface = NULL;
	SDL_Surface* SCOREtextSurface = NULL;
	SDL_Surface* Text_You_textSurface = NULL;
	SDL_Surface* Text_Opponent_1_textSurface = NULL;
	SDL_Surface* Text_Opponent_2_textSurface = NULL;
	TTF_Font* Point_Defenitiontext = TTF_OpenFont("Text/TextSettings.ttf", 100);
	SDL_Color textColor = { 255, 255, 255 };
	Point_DefenitiontextSurface = TTF_RenderUTF8_Solid(Point_Defenitiontext, u8"ÎÏÐÅÄÅËÅÍÈÅ Î×ÊÀ", textColor);
	Turn_OrdertextSurface = TTF_RenderUTF8_Solid(Point_Defenitiontext, u8"ÏÎÐßÄÎÊ ÕÎÄÀ", textColor);
	Your_turntextSurface = TTF_RenderUTF8_Solid(Point_Defenitiontext, u8"ÂÀØ ÕÎÄ", textColor);
	Opponent_turntextSurface = TTF_RenderUTF8_Solid(Point_Defenitiontext, u8"ÕÎÄ ÑÎÏÅÐÍÈÊÀ", textColor);
	POINTtextSurface = TTF_RenderUTF8_Solid(Point_Defenitiontext, u8"Î×ÊÎ", textColor);
	SCOREtextSurface = TTF_RenderUTF8_Solid(Point_Defenitiontext, u8"Ñ×ÅÒ", textColor);
	Text_You_textSurface = TTF_RenderUTF8_Solid(Point_Defenitiontext, u8"ÂÛ", textColor);
	Text_Opponent_1_textSurface = TTF_RenderUTF8_Solid(Point_Defenitiontext, u8"ÑÎÏÅÐÍÈÊ1", textColor);
	Text_Opponent_2_textSurface = TTF_RenderUTF8_Solid(Point_Defenitiontext, u8"ÑÎÏÅÐÍÈÊ2", textColor);
	SDL_Texture* Point_DefenitiontextTexture = SDL_CreateTextureFromSurface(renderer, Point_DefenitiontextSurface);
	SDL_Texture* Turn_OrdertextTexture = SDL_CreateTextureFromSurface(renderer, Turn_OrdertextSurface);
	SDL_Texture* Your_turntextTexture = SDL_CreateTextureFromSurface(renderer, Your_turntextSurface);
	SDL_Texture* Opponent_turntextTexture = SDL_CreateTextureFromSurface(renderer, Opponent_turntextSurface);
	SDL_Texture* POINTtextTexture = SDL_CreateTextureFromSurface(renderer, POINTtextSurface);
	SDL_Texture* SCOREtextTexture = SDL_CreateTextureFromSurface(renderer, SCOREtextSurface);
	SDL_Texture* Text_You_textTexture = SDL_CreateTextureFromSurface(renderer, Text_You_textSurface);
	SDL_Texture* Text_Opponent_1_textTexture = SDL_CreateTextureFromSurface(renderer, Text_Opponent_1_textSurface);
	SDL_Texture* Text_Opponent_2_textTexture = SDL_CreateTextureFromSurface(renderer, Text_Opponent_2_textSurface);
	SDL_Texture* INT_POINT_textTexture;
	SDL_Texture* You_SCORE_textTexture;
	SDL_Texture* Opponent_1_SCORE_textTexture;
	SDL_Texture* Opponent_2_SCORE_textTexture;
	SDL_Rect Point_DefenitiontextRect = { SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 - 75, 400, 150 };
	SDL_Rect Turn_OrdertextRect = { SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 - 75, 400, 150 };
	SDL_Rect Your_turntextRect = { SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 - 75, 400, 150 };
	SDL_Rect Opponent_turntextRect = { SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 - 75, 400, 150 };
	SDL_Rect POINTtextRect = { 0, 0, 200, 40 };
	SDL_Rect SCOREtextRect = { SCREEN_WIDTH - 200, 0, 200, 40 };
	SDL_Rect Text_You_textRect = { SCREEN_WIDTH - 200, 40, 30, 35 };
	SDL_Rect Text_Opponent_1_textRect = { SCREEN_WIDTH - 200, 75, 95, 35 };
	SDL_Rect Text_Opponent_2_textRect = { SCREEN_WIDTH - 200, 110, 95, 35 };

	SDL_Event event;
	bool quit = false;

	bool FirstChangeQuit = false;
	bool LooseQuit = false;
	bool WinQuit = false;
	bool Point_Definition = true;

	bool YouMove = false;
	bool OpponentMove_1 = false;
	bool OpponentMove_2 = false;

	int TEMP_POINT = 0;
	int YouPoints1 = 0, YouPoints2 = 0, YouPoints3 = 0, YouSumPointsForFirstMove = 0;
	int OpponentPoints1_1 = 0, OpponentPoints2_1 = 0 , OpponentPoints3_1 = 0, OpponentSumPointsForFirstMove_1 = 0;
	int OpponentPoints1_2 = 0, OpponentPoints2_2 = 0, OpponentPoints3_2 = 0, OpponentSumPointsForFirstMove_2 = 0;
	int Loose_Count = 0;
	int x, y;

	int POINT = 0;
	int YouSumPoints = 0;
	int OpponentSumPoints_1 = 0;
	int OpponentSumPoints_2 = 0;
	char text[10];
	_itoa_s(POINT, text, 10);
	_itoa_s(YouSumPoints, text, 10);
	_itoa_s(OpponentSumPoints_1, text, 10);
	_itoa_s(OpponentSumPoints_2, text, 10);
	INT_POINT_textTexture = get_POINT_text_texture(renderer, text, Point_Defenitiontext);
	You_SCORE_textTexture = get_YOU_SCORE_text_texture(renderer, text, Point_Defenitiontext);
	Opponent_1_SCORE_textTexture = get_OPPONENT_SCORE_text_texture(renderer, text, Point_Defenitiontext);
	Opponent_2_SCORE_textTexture = get_OPPONENT_SCORE_text_texture(renderer, text, Point_Defenitiontext);

	WinSound = Mix_LoadWAV("Musics/Win.mp3");
	LooseSound = Mix_LoadWAV("Musics/Loose.mp3");
	GameOverSound = Mix_LoadWAV("Musics/GameOverSound.mp3");

	Mix_PlayMusic(GameMusic, -1);
	Mix_VolumeMusic(GameVolume);

	while (!quit)
	{
		SDL_PollEvent(&event);
		if (event.type == SDL_QUIT)
			quit = true;
		
		if (Point_Definition == true)
		{
			SDL_RenderClear(renderer);
			Draw_GameFON(renderer, GameFonRect, GameFonTexture);
			SDL_RenderCopy(renderer, Turn_OrdertextTexture, NULL, &Turn_OrdertextRect);
			SDL_RenderPresent(renderer);
			SDL_Delay(1000);
			SDL_DestroyTexture(Turn_OrdertextTexture);

			SDL_RenderClear(renderer);
			Draw_GameFON(renderer, GameFonRect, GameFonTexture);
			Draw_FirstDiceRollButton(renderer, FirstDiceRollButtonRect, FirstDiceRollButtonTexture);
			SDL_RenderPresent(renderer);

			while (!FirstChangeQuit)
			{
				SDL_PollEvent(&event);
				if (event.type == SDL_QUIT)
				{
					FirstChangeQuit = true;
					quit = true;
				}

				if ((event.type == SDL_MOUSEBUTTONDOWN) && (event.button.button = SDL_BUTTON_LEFT))
				{
					SDL_GetMouseState(&x, &y);
					if (IsButtonTap(x, y) == true)
					{
						Mix_PlayChannel(-1, ButtonTapSound, 0);
						SDL_Delay(150);
						YouPoints1 = rand() % (6 - 1 + 1) + 1;
						YouPoints2 = rand() % (6 - 1 + 1) + 1;
						YouPoints3 = rand() % (6 - 1 + 1) + 1;
						YouSumPointsForFirstMove = YouPoints1 + YouPoints2 + YouPoints3;

						switch (YouPoints1)
						{
						case 1:
						{
							Mix_PlayChannel(-1, DiceRollingSound, 0);
							Draw_CubeEdge(renderer, Cube_edge_1_LEFT_Rect, Cube_edge_1_Texture);
						}; break;

						case 2:
						{
							Mix_PlayChannel(-1, DiceRollingSound, 0);
							Draw_CubeEdge(renderer, Cube_edge_2_LEFT_Rect, Cube_edge_2_Texture);
						}; break;

						case 3:
						{
							Mix_PlayChannel(-1, DiceRollingSound, 0);
							Draw_CubeEdge(renderer, Cube_edge_3_LEFT_Rect, Cube_edge_3_Texture);
						}; break;

						case 4:
						{
							Mix_PlayChannel(-1, DiceRollingSound, 0);
							Draw_CubeEdge(renderer, Cube_edge_4_LEFT_Rect, Cube_edge_4_Texture);
						}; break;

						case 5:
						{
							Mix_PlayChannel(-1, DiceRollingSound, 0);
							Draw_CubeEdge(renderer, Cube_edge_5_LEFT_Rect, Cube_edge_5_Texture);
						}; break;

						case 6:
						{
							Mix_PlayChannel(-1, DiceRollingSound, 0);
							Draw_CubeEdge(renderer, Cube_edge_6_LEFT_Rect, Cube_edge_6_Texture);
						}; break;
						}

						switch (YouPoints2)
						{
						case 1:
						{
							Mix_PlayChannel(-1, DiceRollingSound, 0);
							Draw_CubeEdge(renderer, Cube_edge_1_MID_Rect, Cube_edge_1_Texture);
						}; break;

						case 2:
						{
							Mix_PlayChannel(-1, DiceRollingSound, 0);
							Draw_CubeEdge(renderer, Cube_edge_2_MID_Rect, Cube_edge_2_Texture);
						}; break;

						case 3:
						{
							Mix_PlayChannel(-1, DiceRollingSound, 0);
							Draw_CubeEdge(renderer, Cube_edge_3_MID_Rect, Cube_edge_3_Texture);
						}; break;

						case 4:
						{
							Mix_PlayChannel(-1, DiceRollingSound, 0);
							Draw_CubeEdge(renderer, Cube_edge_4_MID_Rect, Cube_edge_4_Texture);
						}; break;

						case 5:
						{
							Mix_PlayChannel(-1, DiceRollingSound, 0);
							Draw_CubeEdge(renderer, Cube_edge_6_MID_Rect, Cube_edge_6_Texture);
						}; break;

						case 6:
						{
							Mix_PlayChannel(-1, DiceRollingSound, 0);
							Draw_CubeEdge(renderer, Cube_edge_6_MID_Rect, Cube_edge_6_Texture);
						}; break;
						}

						switch (YouPoints3)
						{
						case 1:
						{
							Mix_PlayChannel(-1, DiceRollingSound, 0);
							Draw_CubeEdge(renderer, Cube_edge_1_RIGHT_Rect, Cube_edge_1_Texture);
						}; break;

						case 2:
						{
							Mix_PlayChannel(-1, DiceRollingSound, 0);
							Draw_CubeEdge(renderer, Cube_edge_2_RIGHT_Rect, Cube_edge_2_Texture);

						}; break;

						case 3:
						{
							Mix_PlayChannel(-1, DiceRollingSound, 0);
							Draw_CubeEdge(renderer, Cube_edge_3_RIGHT_Rect, Cube_edge_3_Texture);
						}; break;

						case 4:
						{
							Mix_PlayChannel(-1, DiceRollingSound, 0);
							Draw_CubeEdge(renderer, Cube_edge_4_RIGHT_Rect, Cube_edge_4_Texture);
						}; break;

						case 5:
						{
							Mix_PlayChannel(-1, DiceRollingSound, 0);
							Draw_CubeEdge(renderer, Cube_edge_5_RIGHT_Rect, Cube_edge_5_Texture);
						}; break;

						case 6:
						{
							Mix_PlayChannel(-1, DiceRollingSound, 0);
							Draw_CubeEdge(renderer, Cube_edge_6_RIGHT_Rect, Cube_edge_6_Texture);
						}; break;
						}

						SDL_RenderPresent(renderer);
						SDL_Delay(2000);
						FirstChangeQuit = true;
					}
				}
			}

			FirstChangeQuit = false;
			SDL_RenderClear(renderer);
			Draw_GameFON(renderer, GameFonRect, GameFonTexture);
			SDL_RenderPresent(renderer);
			SDL_Delay(1000);

			OpponentPoints1_1 = rand() % (6 - 1 + 1) + 1;
			OpponentPoints2_1 = rand() % (6 - 1 + 1) + 1;
			OpponentPoints3_1 = rand() % (6 - 1 + 1) + 1;
			OpponentSumPointsForFirstMove_1 = OpponentPoints1_1 + OpponentPoints2_1 + OpponentPoints3_1;

			switch (OpponentPoints1_1)
			{
			case 1:
			{
				Mix_PlayChannel(-1, DiceRollingSound, 0);
				Draw_CubeEdge(renderer, Cube_edge_1_LEFT_Rect, Cube_edge_1_Texture);
			}; break;

			case 2:
			{
				Mix_PlayChannel(-1, DiceRollingSound, 0);
				Draw_CubeEdge(renderer, Cube_edge_2_LEFT_Rect, Cube_edge_2_Texture);
			}; break;

			case 3:
			{
				Mix_PlayChannel(-1, DiceRollingSound, 0);
				Draw_CubeEdge(renderer, Cube_edge_3_LEFT_Rect, Cube_edge_3_Texture);
			}; break;

			case 4:
			{
				Mix_PlayChannel(-1, DiceRollingSound, 0);
				Draw_CubeEdge(renderer, Cube_edge_4_LEFT_Rect, Cube_edge_4_Texture);
			}; break;

			case 5:
			{
				Mix_PlayChannel(-1, DiceRollingSound, 0);
				Draw_CubeEdge(renderer, Cube_edge_5_LEFT_Rect, Cube_edge_5_Texture);
			}; break;

			case 6:
			{
				Mix_PlayChannel(-1, DiceRollingSound, 0);
				Draw_CubeEdge(renderer, Cube_edge_6_LEFT_Rect, Cube_edge_6_Texture);
			}; break;
			}

			switch (OpponentPoints2_1)
			{
			case 1:
			{
				Mix_PlayChannel(-1, DiceRollingSound, 0);
				Draw_CubeEdge(renderer, Cube_edge_1_MID_Rect, Cube_edge_1_Texture);
			}; break;

			case 2:
			{
				Mix_PlayChannel(-1, DiceRollingSound, 0);
				Draw_CubeEdge(renderer, Cube_edge_2_MID_Rect, Cube_edge_2_Texture);
			}; break;

			case 3:
			{
				Mix_PlayChannel(-1, DiceRollingSound, 0);
				Draw_CubeEdge(renderer, Cube_edge_3_MID_Rect, Cube_edge_3_Texture);
			}; break;

			case 4:
			{
				Mix_PlayChannel(-1, DiceRollingSound, 0);
				Draw_CubeEdge(renderer, Cube_edge_4_MID_Rect, Cube_edge_4_Texture);
			}; break;

			case 5:
			{
				Mix_PlayChannel(-1, DiceRollingSound, 0);
				Draw_CubeEdge(renderer, Cube_edge_6_MID_Rect, Cube_edge_6_Texture);
			}; break;

			case 6:
			{
				Mix_PlayChannel(-1, DiceRollingSound, 0);
				Draw_CubeEdge(renderer, Cube_edge_6_MID_Rect, Cube_edge_6_Texture);
			}; break;
			}

			switch (OpponentPoints3_1)
			{
			case 1:
			{
				Mix_PlayChannel(-1, DiceRollingSound, 0);
				Draw_CubeEdge(renderer, Cube_edge_1_RIGHT_Rect, Cube_edge_1_Texture);
			}; break;

			case 2:
			{
				Mix_PlayChannel(-1, DiceRollingSound, 0);
				Draw_CubeEdge(renderer, Cube_edge_2_RIGHT_Rect, Cube_edge_2_Texture);

			}; break;

			case 3:
			{
				Mix_PlayChannel(-1, DiceRollingSound, 0);
				Draw_CubeEdge(renderer, Cube_edge_3_RIGHT_Rect, Cube_edge_3_Texture);
			}; break;

			case 4:
			{
				Mix_PlayChannel(-1, DiceRollingSound, 0);
				Draw_CubeEdge(renderer, Cube_edge_4_RIGHT_Rect, Cube_edge_4_Texture);
			}; break;

			case 5:
			{
				Mix_PlayChannel(-1, DiceRollingSound, 0);
				Draw_CubeEdge(renderer, Cube_edge_5_RIGHT_Rect, Cube_edge_5_Texture);
			}; break;

			case 6:
			{
				Mix_PlayChannel(-1, DiceRollingSound, 0);
				Draw_CubeEdge(renderer, Cube_edge_6_RIGHT_Rect, Cube_edge_6_Texture);
			}; break;
			}

			SDL_RenderPresent(renderer);
			SDL_Delay(2000);

			SDL_RenderClear(renderer);
			Draw_GameFON(renderer, GameFonRect, GameFonTexture);
			SDL_RenderPresent(renderer);
			SDL_Delay(1000);

			OpponentPoints1_2 = rand() % (6 - 1 + 1) + 1;
			OpponentPoints2_2 = rand() % (6 - 1 + 1) + 1;
			OpponentPoints3_2 = rand() % (6 - 1 + 1) + 1;
			OpponentSumPointsForFirstMove_2 = OpponentPoints1_2 + OpponentPoints2_2 + OpponentPoints3_2;

			switch (OpponentPoints1_2)
			{
			case 1:
			{
				Mix_PlayChannel(-1, DiceRollingSound, 0);
				Draw_CubeEdge(renderer, Cube_edge_1_LEFT_Rect, Cube_edge_1_Texture);
			}; break;

			case 2:
			{
				Mix_PlayChannel(-1, DiceRollingSound, 0);
				Draw_CubeEdge(renderer, Cube_edge_2_LEFT_Rect, Cube_edge_2_Texture);
			}; break;

			case 3:
			{
				Mix_PlayChannel(-1, DiceRollingSound, 0);
				Draw_CubeEdge(renderer, Cube_edge_3_LEFT_Rect, Cube_edge_3_Texture);
			}; break;

			case 4:
			{
				Mix_PlayChannel(-1, DiceRollingSound, 0);
				Draw_CubeEdge(renderer, Cube_edge_4_LEFT_Rect, Cube_edge_4_Texture);
			}; break;

			case 5:
			{
				Mix_PlayChannel(-1, DiceRollingSound, 0);
				Draw_CubeEdge(renderer, Cube_edge_5_LEFT_Rect, Cube_edge_5_Texture);
			}; break;

			case 6:
			{
				Mix_PlayChannel(-1, DiceRollingSound, 0);
				Draw_CubeEdge(renderer, Cube_edge_6_LEFT_Rect, Cube_edge_6_Texture);
			}; break;
			}

			switch (OpponentPoints2_2)
			{
			case 1:
			{
				Mix_PlayChannel(-1, DiceRollingSound, 0);
				Draw_CubeEdge(renderer, Cube_edge_1_MID_Rect, Cube_edge_1_Texture);
			}; break;

			case 2:
			{
				Mix_PlayChannel(-1, DiceRollingSound, 0);
				Draw_CubeEdge(renderer, Cube_edge_2_MID_Rect, Cube_edge_2_Texture);
			}; break;

			case 3:
			{
				Mix_PlayChannel(-1, DiceRollingSound, 0);
				Draw_CubeEdge(renderer, Cube_edge_3_MID_Rect, Cube_edge_3_Texture);
			}; break;

			case 4:
			{
				Mix_PlayChannel(-1, DiceRollingSound, 0);
				Draw_CubeEdge(renderer, Cube_edge_4_MID_Rect, Cube_edge_4_Texture);
			}; break;

			case 5:
			{
				Mix_PlayChannel(-1, DiceRollingSound, 0);
				Draw_CubeEdge(renderer, Cube_edge_6_MID_Rect, Cube_edge_6_Texture);
			}; break;

			case 6:
			{
				Mix_PlayChannel(-1, DiceRollingSound, 0);
				Draw_CubeEdge(renderer, Cube_edge_6_MID_Rect, Cube_edge_6_Texture);
			}; break;
			}

			switch (OpponentPoints3_2)
			{
			case 1:
			{
				Mix_PlayChannel(-1, DiceRollingSound, 0);
				Draw_CubeEdge(renderer, Cube_edge_1_RIGHT_Rect, Cube_edge_1_Texture);
			}; break;

			case 2:
			{
				Mix_PlayChannel(-1, DiceRollingSound, 0);
				Draw_CubeEdge(renderer, Cube_edge_2_RIGHT_Rect, Cube_edge_2_Texture);

			}; break;

			case 3:
			{
				Mix_PlayChannel(-1, DiceRollingSound, 0);
				Draw_CubeEdge(renderer, Cube_edge_3_RIGHT_Rect, Cube_edge_3_Texture);
			}; break;

			case 4:
			{
				Mix_PlayChannel(-1, DiceRollingSound, 0);
				Draw_CubeEdge(renderer, Cube_edge_4_RIGHT_Rect, Cube_edge_4_Texture);
			}; break;

			case 5:
			{
				Mix_PlayChannel(-1, DiceRollingSound, 0);
				Draw_CubeEdge(renderer, Cube_edge_5_RIGHT_Rect, Cube_edge_5_Texture);
			}; break;

			case 6:
			{
				Mix_PlayChannel(-1, DiceRollingSound, 0);
				Draw_CubeEdge(renderer, Cube_edge_6_RIGHT_Rect, Cube_edge_6_Texture);
			}; break;
			}

			SDL_RenderPresent(renderer);
			SDL_Delay(2000);

			SDL_RenderClear(renderer);
			Draw_GameFON(renderer, GameFonRect, GameFonTexture);
			SDL_RenderCopy(renderer, Point_DefenitiontextTexture, NULL, &Point_DefenitiontextRect);
			SDL_RenderPresent(renderer);
			SDL_Delay(1000);
			SDL_DestroyTexture(Point_DefenitiontextTexture);

			SDL_RenderClear(renderer);
			Draw_GameFON(renderer, GameFonRect, GameFonTexture);
			Draw_FirstDiceRollButton(renderer, FirstDiceRollButtonRect, FirstDiceRollButtonTexture);
			SDL_RenderPresent(renderer);

			while (!FirstChangeQuit)
			{
				SDL_PollEvent(&event);
				if (event.type == SDL_QUIT)
				{
					FirstChangeQuit = true;
					quit = true;
				}

				if ((event.type == SDL_MOUSEBUTTONDOWN) && (event.button.button = SDL_BUTTON_LEFT))
				{
					SDL_GetMouseState(&x, &y);
					if (IsButtonTap(x, y) == true)
					{
						Mix_PlayChannel(-1, ButtonTapSound, 0);
						SDL_Delay(150);
						TEMP_POINT = rand() % (6 - 1 + 1) + 1;
						
						POINT = TEMP_POINT;
						_itoa_s(POINT, text, 10);
						SDL_DestroyTexture(INT_POINT_textTexture);
						INT_POINT_textTexture = get_POINT_text_texture(renderer, text, Point_Defenitiontext);

						switch (TEMP_POINT)
						{
						case 1:
						{
							Mix_PlayChannel(-1, DiceRollingSound, 0);
							Draw_CubeEdge(renderer, Cube_edge_1_MID_Rect, Cube_edge_1_Texture);
						}; break;

						case 2:
						{
							Mix_PlayChannel(-1, DiceRollingSound, 0);
							Draw_CubeEdge(renderer, Cube_edge_2_MID_Rect, Cube_edge_2_Texture);
						}; break;

						case 3:
						{
							Mix_PlayChannel(-1, DiceRollingSound, 0);
							Draw_CubeEdge(renderer, Cube_edge_3_MID_Rect, Cube_edge_3_Texture);
						}; break;

						case 4:
						{
							Mix_PlayChannel(-1, DiceRollingSound, 0);
							Draw_CubeEdge(renderer, Cube_edge_4_MID_Rect, Cube_edge_4_Texture);
						}; break;

						case 5:
						{
							Mix_PlayChannel(-1, DiceRollingSound, 0);
							Draw_CubeEdge(renderer, Cube_edge_5_MID_Rect, Cube_edge_5_Texture);
						}; break;

						case 6:
						{
							Mix_PlayChannel(-1, DiceRollingSound, 0);
							Draw_CubeEdge(renderer, Cube_edge_6_MID_Rect, Cube_edge_6_Texture);
						}; break;
						}

						SDL_RenderPresent(renderer);
						SDL_Delay(2000);
						FirstChangeQuit = true;
					}
				}
			}

			if ((YouSumPointsForFirstMove >= OpponentSumPointsForFirstMove_1) && (YouSumPointsForFirstMove >= OpponentSumPointsForFirstMove_2))
			{
				YouMove = true;
				OpponentMove_1 = false;
				OpponentMove_2 = false;
			}
			if ((OpponentSumPointsForFirstMove_1 > YouSumPointsForFirstMove) && (OpponentSumPointsForFirstMove_1 > OpponentSumPointsForFirstMove_2))
			{
				YouMove = false;
				OpponentMove_1 = true;
				OpponentMove_2 = false;
			}
			if ((OpponentSumPointsForFirstMove_2 > YouSumPointsForFirstMove) && (OpponentSumPointsForFirstMove_2 > OpponentSumPointsForFirstMove_1))
			{
				YouMove = false;
				OpponentMove_1 = false;
				OpponentMove_2 = true;
			}

			Point_Definition = false;
		}

		if (YouMove == true)
		{
			if (Loose_Count == 2)
			{
				SDL_RenderClear(renderer);
				Mix_HaltMusic();
				Draw_LooseFON(renderer, LooseFonRect, LooseFonTexture);
				Draw_MainMenuExitGameButton(renderer, MainMenuButtonRect, MainMenuButtonTexture);
				SDL_RenderPresent(renderer);
				Mix_PlayChannel(-1, LooseSound, 0);
				SDL_Delay(250);
				Mix_PlayChannel(-1, GameOverSound, 0);
				SDL_Delay(150);
				WinsCountInRow = 0;

				while (!LooseQuit)
				{
					SDL_PollEvent(&event);
					if (event.type == SDL_QUIT)
						quit = true;

					if ((event.type == SDL_MOUSEBUTTONDOWN) && (event.button.button = SDL_BUTTON_LEFT))
					{
						SDL_GetMouseState(&x, &y);
						switch (Is_Main_Menu_or_Restart_Tap(x, y))
						{
						case 0: 
						{
							LooseQuit = true;
							quit = true;
							break;
						}break;

						default:; break;
						}
					}
				}
				break;
			}

			SDL_RenderClear(renderer);
			Draw_GameFON(renderer, GameFonRect, GameFonTexture);
			SDL_RenderCopy(renderer, Your_turntextTexture, NULL, &Your_turntextRect);
			SDL_RenderPresent(renderer);
			SDL_Delay(1000);

			SDL_RenderClear(renderer);
			Draw_GameFON(renderer, GameFonRect, GameFonTexture);
			SDL_RenderCopy(renderer, POINTtextTexture, NULL, &POINTtextRect);
			draw_POINT_text(renderer, INT_POINT_textTexture);
			draw_YOU_SCORE_text(renderer, You_SCORE_textTexture);
			draw_OPPONENT_1_SCORE_text(renderer, Opponent_1_SCORE_textTexture);
			draw_OPPONENT_2_SCORE_text(renderer, Opponent_2_SCORE_textTexture);
			SDL_RenderCopy(renderer, SCOREtextTexture, NULL, &SCOREtextRect);
			SDL_RenderCopy(renderer, Text_You_textTexture, NULL, &Text_You_textRect);
			SDL_RenderCopy(renderer, Text_Opponent_1_textTexture, NULL, &Text_Opponent_1_textRect);
			SDL_RenderCopy(renderer, Text_Opponent_2_textTexture, NULL, &Text_Opponent_2_textRect);
			Draw_FirstDiceRollButton(renderer, FirstDiceRollButtonRect, FirstDiceRollButtonTexture);
			SDL_Delay(500);
			SDL_RenderPresent(renderer);

			FirstChangeQuit = false;

			while (!FirstChangeQuit)
			{
				SDL_PollEvent(&event);
				if (event.type == SDL_QUIT)
				{
					FirstChangeQuit = true;
					quit = true;
				}

				if ((event.type == SDL_MOUSEBUTTONDOWN) && (event.button.button = SDL_BUTTON_LEFT))
				{
					YouPoints1 = 0;
					YouPoints2 = 0;
					YouPoints3 = 0;

					SDL_GetMouseState(&x, &y);
					if (IsButtonTap(x, y) == true)
					{
						Mix_PlayChannel(-1, ButtonTapSound, 0);
						SDL_Delay(150);
						YouPoints1 = rand() % (6 - 1 + 1) + 1;
						YouPoints2 = rand() % (6 - 1 + 1) + 1;
						YouPoints3 = rand() % (6 - 1 + 1) + 1;

						if (YouPoints1 == POINT)
						{
							YouSumPoints += 1;
						}
						if (YouPoints2 == POINT)
						{
							YouSumPoints += 1;
						}
						if (YouPoints3 == POINT)
						{
							YouSumPoints += 1;
						}
						if ((YouPoints1 == YouPoints2) && (YouPoints2 == YouPoints3))
						{
							YouSumPoints += 5;
							SmallBackCount += 1;
						}
						if ((YouPoints1 == YouPoints2) && (YouPoints2 == YouPoints3) && (YouPoints3 == POINT))
						{
							YouSumPoints += 15;
							BigBackCount += 1;
						}
						if (YouSumPoints >= 15)
							YouSumPoints = 15;

						_itoa_s(YouSumPoints, text, 10);
						SDL_DestroyTexture(You_SCORE_textTexture);
						You_SCORE_textTexture = get_POINT_text_texture(renderer, text, Point_Defenitiontext);
						
						switch (YouPoints1)
						{
						case 1:
						{
							Mix_PlayChannel(-1, DiceRollingSound, 0);
							Draw_CubeEdge(renderer, Cube_edge_1_LEFT_Rect, Cube_edge_1_Texture);
						}; break;

						case 2:
						{
							Mix_PlayChannel(-1, DiceRollingSound, 0);
							Draw_CubeEdge(renderer, Cube_edge_2_LEFT_Rect, Cube_edge_2_Texture);
						}; break;

						case 3:
						{
							Mix_PlayChannel(-1, DiceRollingSound, 0);
							Draw_CubeEdge(renderer, Cube_edge_3_LEFT_Rect, Cube_edge_3_Texture);
						}; break;

						case 4:
						{
							Mix_PlayChannel(-1, DiceRollingSound, 0);
							Draw_CubeEdge(renderer, Cube_edge_4_LEFT_Rect, Cube_edge_4_Texture);
						}; break;

						case 5:
						{
							Mix_PlayChannel(-1, DiceRollingSound, 0);
							Draw_CubeEdge(renderer, Cube_edge_5_LEFT_Rect, Cube_edge_5_Texture);
						}; break;

						case 6:
						{
							Mix_PlayChannel(-1, DiceRollingSound, 0);
							Draw_CubeEdge(renderer, Cube_edge_6_LEFT_Rect, Cube_edge_6_Texture);
						}; break;
						}

						switch (YouPoints2)
						{
						case 1:
						{
							Mix_PlayChannel(-1, DiceRollingSound, 0);
							Draw_CubeEdge(renderer, Cube_edge_1_MID_Rect, Cube_edge_1_Texture);
						}; break;

						case 2:
						{
							Mix_PlayChannel(-1, DiceRollingSound, 0);
							Draw_CubeEdge(renderer, Cube_edge_2_MID_Rect, Cube_edge_2_Texture);
						}; break;

						case 3:
						{
							Mix_PlayChannel(-1, DiceRollingSound, 0);
							Draw_CubeEdge(renderer, Cube_edge_3_MID_Rect, Cube_edge_3_Texture);
						}; break;

						case 4:
						{
							Mix_PlayChannel(-1, DiceRollingSound, 0);
							Draw_CubeEdge(renderer, Cube_edge_4_MID_Rect, Cube_edge_4_Texture);
						}; break;

						case 5:
						{
							Mix_PlayChannel(-1, DiceRollingSound, 0);
							Draw_CubeEdge(renderer, Cube_edge_6_MID_Rect, Cube_edge_6_Texture);
						}; break;

						case 6:
						{
							Mix_PlayChannel(-1, DiceRollingSound, 0);
							Draw_CubeEdge(renderer, Cube_edge_6_MID_Rect, Cube_edge_6_Texture);
						}; break;
						}

						switch (YouPoints3)
						{
						case 1:
						{
							Mix_PlayChannel(-1, DiceRollingSound, 0);
							Draw_CubeEdge(renderer, Cube_edge_1_RIGHT_Rect, Cube_edge_1_Texture);
						}; break;

						case 2:
						{
							Mix_PlayChannel(-1, DiceRollingSound, 0);
							Draw_CubeEdge(renderer, Cube_edge_2_RIGHT_Rect, Cube_edge_2_Texture);

						}; break;

						case 3:
						{
							Mix_PlayChannel(-1, DiceRollingSound, 0);
							Draw_CubeEdge(renderer, Cube_edge_3_RIGHT_Rect, Cube_edge_3_Texture);
						}; break;

						case 4:
						{
							Mix_PlayChannel(-1, DiceRollingSound, 0);
							Draw_CubeEdge(renderer, Cube_edge_4_RIGHT_Rect, Cube_edge_4_Texture);
						}; break;

						case 5:
						{
							Mix_PlayChannel(-1, DiceRollingSound, 0);
							Draw_CubeEdge(renderer, Cube_edge_5_RIGHT_Rect, Cube_edge_5_Texture);
						}; break;

						case 6:
						{
							Mix_PlayChannel(-1, DiceRollingSound, 0);
							Draw_CubeEdge(renderer, Cube_edge_6_RIGHT_Rect, Cube_edge_6_Texture);
						}; break;
						}

						SDL_RenderPresent(renderer);
						SDL_Delay(2000);

						FirstChangeQuit = true;
					}
				}
			}

			if (YouSumPoints == 15)
			{
				SDL_RenderClear(renderer);
				Mix_HaltMusic();
				Draw_WinFON(renderer, WinFonRect, WinFonTexture);
				Draw_MainMenuExitGameButton(renderer, MainMenuButtonRect, MainMenuButtonTexture);
				SDL_RenderPresent(renderer);
				Mix_PlayChannel(-1, WinSound, 0);
				SDL_Delay(150);			
				WinsCountInRow += 1;

				while (!WinQuit)
				{
					SDL_PollEvent(&event);
					if (event.type == SDL_QUIT)
						quit = true;

					if ((event.type == SDL_MOUSEBUTTONDOWN) && (event.button.button = SDL_BUTTON_LEFT))
					{
						SDL_GetMouseState(&x, &y);
						switch (Is_Main_Menu_or_Restart_Tap(x, y))
						{
						case 0:
						{
							Mix_HaltChannel(-1);
							WinQuit = true;
							quit = true;
							break;
						}break;

						default:; break;
						}
					}
				}
				break;
			}

			YouMove = false;
			OpponentMove_1 = true;

			if (OpponentSumPoints_1 == 15)
			{
				OpponentMove_1 = false;
				OpponentMove_2 = true;
				YouMove = false;
			}

			if ((YouPoints1 == YouPoints2) && (YouPoints2 == YouPoints3))
			{
				YouMove = true;
				OpponentMove_1 = false;
				OpponentMove_2 = false;
			}

		}

		if (quit == true)
			break;

		if (OpponentMove_1 == true)
		{
			SDL_RenderClear(renderer);
			Draw_GameFON(renderer, GameFonRect, GameFonTexture);
			SDL_RenderCopy(renderer, Opponent_turntextTexture, NULL, &Your_turntextRect);
			SDL_RenderPresent(renderer);
			SDL_Delay(1000);

			SDL_RenderClear(renderer);
			Draw_GameFON(renderer, GameFonRect, GameFonTexture);
			SDL_RenderCopy(renderer, POINTtextTexture, NULL, &POINTtextRect);
			draw_POINT_text(renderer, INT_POINT_textTexture);
			draw_YOU_SCORE_text(renderer, You_SCORE_textTexture);
			draw_OPPONENT_1_SCORE_text(renderer, Opponent_1_SCORE_textTexture);
			draw_OPPONENT_2_SCORE_text(renderer, Opponent_2_SCORE_textTexture);
			SDL_RenderCopy(renderer, SCOREtextTexture, NULL, &SCOREtextRect);
			SDL_RenderCopy(renderer, Text_You_textTexture, NULL, &Text_You_textRect);
			SDL_RenderCopy(renderer, Text_Opponent_1_textTexture, NULL, &Text_Opponent_1_textRect);
			SDL_RenderCopy(renderer, Text_Opponent_2_textTexture, NULL, &Text_Opponent_2_textRect);
			SDL_RenderPresent(renderer);
			SDL_Delay(1000);

			OpponentPoints1_1 = 0;
			OpponentPoints2_1 = 0;
			OpponentPoints3_1 = 0;

			OpponentPoints1_1 = rand() % (6 - 1 + 1) + 1;
			OpponentPoints2_1 = rand() % (6 - 1 + 1) + 1;
			OpponentPoints3_1 = rand() % (6 - 1 + 1) + 1;

			if (OpponentPoints1_1 == POINT)
			{
				OpponentSumPoints_1 += 1;
			}
			if (OpponentPoints2_1 == POINT)
			{
				OpponentSumPoints_1 += 1;
			}
			if (OpponentPoints3_1 == POINT)
			{
				OpponentSumPoints_1 += 1;
			}
			if ((OpponentPoints1_1 == OpponentPoints2_1) && (OpponentPoints2_1 == OpponentPoints3_1))
			{
				OpponentSumPoints_1 += 5;
			}
			if ((OpponentPoints1_1 == OpponentPoints2_1) && (OpponentPoints2_1 == OpponentPoints3_1) && (OpponentPoints3_1 == POINT))
			{
				OpponentSumPoints_1 += 15;
			}
			if (OpponentSumPoints_1 >= 15)
				OpponentSumPoints_1 = 15;

			OpponentSumPoints_1;
			_itoa_s(OpponentSumPoints_1, text, 10);
			SDL_DestroyTexture(Opponent_1_SCORE_textTexture);
			Opponent_1_SCORE_textTexture = get_POINT_text_texture(renderer, text, Point_Defenitiontext);

			switch (OpponentPoints1_1)
			{
			case 1:
			{
				Mix_PlayChannel(-1, DiceRollingSound, 0);
				Draw_CubeEdge(renderer, Cube_edge_1_LEFT_Rect, Cube_edge_1_Texture);
			}; break;

			case 2:
			{
				Mix_PlayChannel(-1, DiceRollingSound, 0);
				Draw_CubeEdge(renderer, Cube_edge_2_LEFT_Rect, Cube_edge_2_Texture);
			}; break;

			case 3:
			{
				Mix_PlayChannel(-1, DiceRollingSound, 0);
				Draw_CubeEdge(renderer, Cube_edge_3_LEFT_Rect, Cube_edge_3_Texture);
			}; break;

			case 4:
			{
				Mix_PlayChannel(-1, DiceRollingSound, 0);
				Draw_CubeEdge(renderer, Cube_edge_4_LEFT_Rect, Cube_edge_4_Texture);
			}; break;

			case 5:
			{
				Mix_PlayChannel(-1, DiceRollingSound, 0);
				Draw_CubeEdge(renderer, Cube_edge_5_LEFT_Rect, Cube_edge_5_Texture);
			}; break;

			case 6:
			{
				Mix_PlayChannel(-1, DiceRollingSound, 0);
				Draw_CubeEdge(renderer, Cube_edge_6_LEFT_Rect, Cube_edge_6_Texture);
			}; break;
			}

			switch (OpponentPoints2_1)
			{
			case 1:
			{
				Mix_PlayChannel(-1, DiceRollingSound, 0);
				Draw_CubeEdge(renderer, Cube_edge_1_MID_Rect, Cube_edge_1_Texture);
			}; break;

			case 2:
			{
				Mix_PlayChannel(-1, DiceRollingSound, 0);
				Draw_CubeEdge(renderer, Cube_edge_2_MID_Rect, Cube_edge_2_Texture);
			}; break;

			case 3:
			{
				Mix_PlayChannel(-1, DiceRollingSound, 0);
				Draw_CubeEdge(renderer, Cube_edge_3_MID_Rect, Cube_edge_3_Texture);
			}; break;

			case 4:
			{
				Mix_PlayChannel(-1, DiceRollingSound, 0);
				Draw_CubeEdge(renderer, Cube_edge_4_MID_Rect, Cube_edge_4_Texture);
			}; break;

			case 5:
			{
				Mix_PlayChannel(-1, DiceRollingSound, 0);
				Draw_CubeEdge(renderer, Cube_edge_6_MID_Rect, Cube_edge_6_Texture);
			}; break;

			case 6:
			{
				Mix_PlayChannel(-1, DiceRollingSound, 0);
				Draw_CubeEdge(renderer, Cube_edge_6_MID_Rect, Cube_edge_6_Texture);
			}; break;
			}

			switch (OpponentPoints3_1)
			{
			case 1:
			{
				Mix_PlayChannel(-1, DiceRollingSound, 0);
				Draw_CubeEdge(renderer, Cube_edge_1_RIGHT_Rect, Cube_edge_1_Texture);
			}; break;

			case 2:
			{
				Mix_PlayChannel(-1, DiceRollingSound, 0);
				Draw_CubeEdge(renderer, Cube_edge_2_RIGHT_Rect, Cube_edge_2_Texture);

			}; break;

			case 3:
			{
				Mix_PlayChannel(-1, DiceRollingSound, 0);
				Draw_CubeEdge(renderer, Cube_edge_3_RIGHT_Rect, Cube_edge_3_Texture);
			}; break;

			case 4:
			{
				Mix_PlayChannel(-1, DiceRollingSound, 0);
				Draw_CubeEdge(renderer, Cube_edge_4_RIGHT_Rect, Cube_edge_4_Texture);
			}; break;

			case 5:
			{
				Mix_PlayChannel(-1, DiceRollingSound, 0);
				Draw_CubeEdge(renderer, Cube_edge_5_RIGHT_Rect, Cube_edge_5_Texture);
			}; break;

			case 6:
			{
				Mix_PlayChannel(-1, DiceRollingSound, 0);
				Draw_CubeEdge(renderer, Cube_edge_6_RIGHT_Rect, Cube_edge_6_Texture);
			}; break;
			}

			SDL_RenderPresent(renderer);
			SDL_Delay(2000);

			if (OpponentSumPoints_1 == 15)
			{
				Loose_Count += 1;
			}
				
			OpponentMove_1 = false;
			OpponentMove_2 = true;

			if (OpponentSumPoints_2 == 15)
			{
				OpponentMove_1 = false;
				OpponentMove_2 = false;
				YouMove = true;
			}

			if ((OpponentPoints1_1 == OpponentPoints2_1) && (OpponentPoints2_1 == OpponentPoints3_1))
			{
				YouMove = false;
				OpponentMove_1 = true;
				OpponentMove_2 = false;
			}
		}

		if (quit == true)
			break;

		if (OpponentMove_2 == true)
		{
			SDL_RenderClear(renderer);
			Draw_GameFON(renderer, GameFonRect, GameFonTexture);
			SDL_RenderCopy(renderer, Opponent_turntextTexture, NULL, &Your_turntextRect);
			SDL_RenderPresent(renderer);
			SDL_Delay(1000);

			SDL_RenderClear(renderer);
			Draw_GameFON(renderer, GameFonRect, GameFonTexture);
			SDL_RenderCopy(renderer, POINTtextTexture, NULL, &POINTtextRect);
			draw_POINT_text(renderer, INT_POINT_textTexture);
			draw_YOU_SCORE_text(renderer, You_SCORE_textTexture);
			draw_OPPONENT_1_SCORE_text(renderer, Opponent_1_SCORE_textTexture);
			draw_OPPONENT_2_SCORE_text(renderer, Opponent_2_SCORE_textTexture);
			SDL_RenderCopy(renderer, SCOREtextTexture, NULL, &SCOREtextRect);
			SDL_RenderCopy(renderer, Text_You_textTexture, NULL, &Text_You_textRect);
			SDL_RenderCopy(renderer, Text_Opponent_1_textTexture, NULL, &Text_Opponent_1_textRect);
			SDL_RenderCopy(renderer, Text_Opponent_2_textTexture, NULL, &Text_Opponent_2_textRect);
			SDL_RenderPresent(renderer);
			SDL_Delay(1000);

			OpponentPoints1_2 = 0;
			OpponentPoints2_2 = 0;
			OpponentPoints3_2 = 0;

			OpponentPoints1_2 = rand() % (6 - 1 + 1) + 1;
			OpponentPoints2_2 = rand() % (6 - 1 + 1) + 1;
			OpponentPoints3_2 = rand() % (6 - 1 + 1) + 1;

			if (OpponentPoints1_2 == POINT)
			{
				OpponentSumPoints_2 += 1;
			}
			if (OpponentPoints2_2 == POINT)
			{
				OpponentSumPoints_2 += 1;
			}
			if (OpponentPoints3_2 == POINT)
			{
				OpponentSumPoints_2 += 1;
			}
			if ((OpponentPoints1_2 == OpponentPoints2_2) && (OpponentPoints2_2 == OpponentPoints3_2))
			{
				OpponentSumPoints_2 += 5;
			}
			if ((OpponentPoints1_2 == OpponentPoints2_2) && (OpponentPoints2_2 == OpponentPoints3_2) && (OpponentPoints3_2 == POINT))
			{
				OpponentSumPoints_2 += 15;
			}
			if (OpponentSumPoints_2 >= 15)
				OpponentSumPoints_2 = 15;

			OpponentSumPoints_2;
			_itoa_s(OpponentSumPoints_2, text, 10);
			SDL_DestroyTexture(Opponent_2_SCORE_textTexture);
			Opponent_2_SCORE_textTexture = get_POINT_text_texture(renderer, text, Point_Defenitiontext);

			switch (OpponentPoints1_2)
			{
			case 1:
			{
				Mix_PlayChannel(-1, DiceRollingSound, 0);
				Draw_CubeEdge(renderer, Cube_edge_1_LEFT_Rect, Cube_edge_1_Texture);
			}; break;

			case 2:
			{
				Mix_PlayChannel(-1, DiceRollingSound, 0);
				Draw_CubeEdge(renderer, Cube_edge_2_LEFT_Rect, Cube_edge_2_Texture);
			}; break;

			case 3:
			{
				Mix_PlayChannel(-1, DiceRollingSound, 0);
				Draw_CubeEdge(renderer, Cube_edge_3_LEFT_Rect, Cube_edge_3_Texture);
			}; break;

			case 4:
			{
				Mix_PlayChannel(-1, DiceRollingSound, 0);
				Draw_CubeEdge(renderer, Cube_edge_4_LEFT_Rect, Cube_edge_4_Texture);
			}; break;

			case 5:
			{
				Mix_PlayChannel(-1, DiceRollingSound, 0);
				Draw_CubeEdge(renderer, Cube_edge_5_LEFT_Rect, Cube_edge_5_Texture);
			}; break;

			case 6:
			{
				Mix_PlayChannel(-1, DiceRollingSound, 0);
				Draw_CubeEdge(renderer, Cube_edge_6_LEFT_Rect, Cube_edge_6_Texture);
			}; break;
			}

			switch (OpponentPoints2_2)
			{
			case 1:
			{
				Mix_PlayChannel(-1, DiceRollingSound, 0);
				Draw_CubeEdge(renderer, Cube_edge_1_MID_Rect, Cube_edge_1_Texture);
			}; break;

			case 2:
			{
				Mix_PlayChannel(-1, DiceRollingSound, 0);
				Draw_CubeEdge(renderer, Cube_edge_2_MID_Rect, Cube_edge_2_Texture);
			}; break;

			case 3:
			{
				Mix_PlayChannel(-1, DiceRollingSound, 0);
				Draw_CubeEdge(renderer, Cube_edge_3_MID_Rect, Cube_edge_3_Texture);
			}; break;

			case 4:
			{
				Mix_PlayChannel(-1, DiceRollingSound, 0);
				Draw_CubeEdge(renderer, Cube_edge_4_MID_Rect, Cube_edge_4_Texture);
			}; break;

			case 5:
			{
				Mix_PlayChannel(-1, DiceRollingSound, 0);
				Draw_CubeEdge(renderer, Cube_edge_6_MID_Rect, Cube_edge_6_Texture);
			}; break;

			case 6:
			{
				Mix_PlayChannel(-1, DiceRollingSound, 0);
				Draw_CubeEdge(renderer, Cube_edge_6_MID_Rect, Cube_edge_6_Texture);
			}; break;
			}

			switch (OpponentPoints3_2)
			{
			case 1:
			{
				Mix_PlayChannel(-1, DiceRollingSound, 0);
				Draw_CubeEdge(renderer, Cube_edge_1_RIGHT_Rect, Cube_edge_1_Texture);
			}; break;

			case 2:
			{
				Mix_PlayChannel(-1, DiceRollingSound, 0);
				Draw_CubeEdge(renderer, Cube_edge_2_RIGHT_Rect, Cube_edge_2_Texture);

			}; break;

			case 3:
			{
				Mix_PlayChannel(-1, DiceRollingSound, 0);
				Draw_CubeEdge(renderer, Cube_edge_3_RIGHT_Rect, Cube_edge_3_Texture);
			}; break;

			case 4:
			{
				Mix_PlayChannel(-1, DiceRollingSound, 0);
				Draw_CubeEdge(renderer, Cube_edge_4_RIGHT_Rect, Cube_edge_4_Texture);
			}; break;

			case 5:
			{
				Mix_PlayChannel(-1, DiceRollingSound, 0);
				Draw_CubeEdge(renderer, Cube_edge_5_RIGHT_Rect, Cube_edge_5_Texture);
			}; break;

			case 6:
			{
				Mix_PlayChannel(-1, DiceRollingSound, 0);
				Draw_CubeEdge(renderer, Cube_edge_6_RIGHT_Rect, Cube_edge_6_Texture);
			}; break;
			}

			SDL_RenderPresent(renderer);
			SDL_Delay(2000);

			if (OpponentSumPoints_2 == 15)
			{
				Loose_Count += 1;
			}

			OpponentMove_2 = false;
			YouMove = true;

			if ((OpponentPoints1_2 == OpponentPoints2_2) && (OpponentPoints2_2 == OpponentPoints3_2))
			{
				YouMove = false;
				OpponentMove_1 = false;
				OpponentMove_2 = true;
			}
		}
		
	}
	SDL_DestroyTexture(GameFonTexture);
	SDL_DestroyTexture(WinFonTexture);
	SDL_DestroyTexture(LooseFonTexture);
	SDL_DestroyTexture(FirstDiceRollButtonTexture);
	SDL_DestroyTexture(MainMenuButtonTexture);
	SDL_DestroyTexture(Turn_OrdertextTexture);
	SDL_DestroyTexture(Point_DefenitiontextTexture);
	SDL_DestroyTexture(Your_turntextTexture);
	SDL_DestroyTexture(Opponent_turntextTexture);
	SDL_DestroyTexture(POINTtextTexture);
	SDL_DestroyTexture(SCOREtextTexture);
	SDL_DestroyTexture(Text_You_textTexture);
	SDL_DestroyTexture(Text_Opponent_1_textTexture);
	SDL_DestroyTexture(Text_Opponent_2_textTexture);
	SDL_DestroyTexture(INT_POINT_textTexture);
	SDL_DestroyTexture(You_SCORE_textTexture);
	SDL_DestroyTexture(Opponent_1_SCORE_textTexture);
	SDL_DestroyTexture(Opponent_2_SCORE_textTexture);
	SDL_DestroyTexture(Cube_edge_1_Texture);
	SDL_DestroyTexture(Cube_edge_2_Texture);
	SDL_DestroyTexture(Cube_edge_3_Texture);
	SDL_DestroyTexture(Cube_edge_4_Texture);
	SDL_DestroyTexture(Cube_edge_5_Texture);
	SDL_DestroyTexture(Cube_edge_6_Texture);
	SDL_FreeSurface(Point_DefenitiontextSurface);
	SDL_FreeSurface(Turn_OrdertextSurface);
	SDL_FreeSurface(Your_turntextSurface);
	SDL_FreeSurface(Opponent_turntextSurface);
	SDL_FreeSurface(POINTtextSurface);
	SDL_FreeSurface(SCOREtextSurface);
	SDL_FreeSurface(Text_You_textSurface);
	SDL_FreeSurface(Text_Opponent_1_textSurface);
	SDL_FreeSurface(Text_Opponent_2_textSurface);
	TTF_CloseFont(Point_Defenitiontext);
	TTF_Quit();
}