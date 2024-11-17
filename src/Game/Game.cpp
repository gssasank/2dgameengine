#include "Game.h"
#include "../Logger/Logger.h"
#include "../ECS/ECS.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>
#include <iostream>

Game::Game() {
    isRunning = false;
    Logger::Log("Game constructor called");
}

Game::~Game() {
    Logger::Log("Game destructor called");
}

void Game::Initialize() {

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        Logger::Err("Error initializing SDL2");
        return;
    }

    SDL_DisplayMode displayMode;

    SDL_GetCurrentDisplayMode(0, &displayMode);

    // Config for "fake fullscreen" that can behave differently on monitors of different size.
    // windowWidth = displayMode.w;
    // windowHeight = displayMode.h;

    windowWidth = 800;
    windowHeight = 600;   

    window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        windowWidth,
        windowHeight,
        SDL_WINDOW_BORDERLESS
    );

    if (!window) {
        Logger::Err("Error creating SDL window");
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); // Enabled dedicated GPU acceleration and VSync

    if (!renderer) {
        Logger::Err("Error creating SDL renderer");
    }
    
    // Config for "real fullscreen"
    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

    // if everything has successfully been initialized, then change isRunning to true
    isRunning = true;

}


void Game::ProcessInput() {
    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent)){
        switch (sdlEvent.type)
        {
        case SDL_QUIT:
            isRunning = false;
            break;
        
        case SDL_KEYDOWN:
            if(sdlEvent.key.keysym.sym == SDLK_ESCAPE){
                isRunning = false;
            }
        
        default:
            break;
        }
    }
}


glm::vec2 playerPosition;
glm::vec2 playerVelocity;

void Game::Setup(){
    // One way to intialize the vector
    // playerPosition.x = 10.0;
    // playerPosition.y = 20.0;

    playerPosition = glm::vec2(10.0, 20.0);
    playerVelocity = glm::vec2(150.0, 100.0);

    // Entity tank = registry.CreateEntity();
    // tank.addCompnent<TransformComponent>();
    // tank.addCompnent<BoxColliderComponent>();
    // tank.addCompnent<SpriteComponent>("./assets/images/tank.png");

}

void Game::Update() {
    // Enforcing FPS cap in the update loop - if we are too fast, waste time till MILLISECONDS_PER_FRAME cap is reached
    // while(!SDL_TICKS_PASSED(SDL_GetTicks(), MILLISECONDS_PER_FRAME + millisecondsPreviousFrame)); //This is a very primitive approach
    
    // A more elegant implementation of the above Logic, this also has the added benifit of not holding up the CPU for the entire wait duration.
    // Commenting out/removing the below code would essentially run the game at uncapped framerate.
    int timeToWait = MILLISECONDS_PER_FRAME - (SDL_GetTicks() - millisecondsPreviousFrame);
    if (timeToWait > 0 && timeToWait <= millisecondsPreviousFrame){
        SDL_Delay(timeToWait);
    }
    // SDL_Delay will never work at a finer resolution than what the OS's scheduler offers.


    // Difference in ticks since last frame, conerted into seconds
    double deltaTime = (SDL_GetTicks() - millisecondsPreviousFrame)/1000.0;

    // storing the current frame time
    millisecondsPreviousFrame = SDL_GetTicks();

    playerPosition.x += playerVelocity.x * deltaTime; // basically equivalent to v = D * t; here we have converted the rendering process from per frame to per second.
    playerPosition.y += playerVelocity.y * deltaTime;

    // TODO: 
    // MovementSystem.Update();
    // CollisionSystem.Update();
    // DamageSystem.Update();

}

void Game::Render() {

    // The Render() function is called in a loop, either as part of the game's main loop or a separate rendering loop. 
    // In this case, the back buffer is cleared at the start of each iteration of the loop, before any new objects are drawn. 
    // The player object is then drawn on top of the cleared back buffer.

    SDL_SetRenderDrawColor(renderer, 25, 25, 25, 255);
    SDL_RenderClear(renderer);
    /* This clears the current rendering target (the back buffer) with the currently set draw color. 
    This effectively resets the entire rendering canvas to the specified background color, 
    preparing it for the next rendering operations. */

    // The following code is to render a black rectangle on the screen
    // SDL_SetRenderDrawColor(renderer, 255, 255,255,255);
    // SDL_Rect player = {20, 20, 40, 40};
    // SDL_RenderFillRect(renderer, &player);

    // Rendering an actual image
    SDL_Surface* surface = IMG_Load("./assets/images/tank-tiger-right.png");
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    // Destination Rectanlge to paste our texture
    SDL_Rect dstRect = {
        static_cast<int>(playerPosition.x), 
        static_cast<int>(playerPosition.y), 
        32, 
        32
    };
    SDL_RenderCopy(renderer, texture, NULL, &dstRect);
    // The params are renderer, texture, what part of the texture we want to copy (NULL defaults to the complete texture, the dest rect where we will paste the texture)
    SDL_DestroyTexture(texture);


    SDL_RenderPresent(renderer);
    // SDL uses something called a double-buffered renderer, which basically means that there are 2
    // different buffers at all times - the front buffer and the back buffer. The front buffer is the
    // one that is displayed on the screen and the back buffer is the one where all the sprites and artefacts
    // are populated. Once all of them are populated, the back buffer is swapped with the front buffer
    // and becomes the new front buffer. This is done to prevent any screen-tears, glitching and artefacting that would
    // have been the result of directly populating the front buffer.
}

void Game::Run() {
    Setup();
    while (isRunning) {
        ProcessInput();
        Update();
        Render();
    }
}

void Game::Destroy() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}