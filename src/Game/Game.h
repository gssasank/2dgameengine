#ifndef GAME_H
#define GAME_H
#include <SDL2/SDL.h>

const int FPS = 200;
const int MILLISECONDS_PER_FRAME = 1000 / FPS;

class Game {
    private:
        bool isRunning;
        int millisecondsPreviousFrame = 0;
        SDL_Window* window;
        SDL_Renderer* renderer;

    public:
        Game();  // Constructor
        ~Game(); // Destructor
        void Initialize();
        void Setup();
        void Run();
        void ProcessInput();
        void Update();
        void Render();
        void Destroy();
        int windowWidth;
        int windowHeight;
};

#endif