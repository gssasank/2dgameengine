#include <iostream>
#include "./Logger/Logger.h"
#include "./Game/Game.h"

int main(int argc, char* argv[]) {
    
    Logger::Log("Started execution of the main file");

    Game game; // Since the "new" keyword is not being used here, C++ stores the object in the stack and destroys it when the scope ends.

    game.Initialize();
    game.Run();
    game.Destroy();

    return 0;
}
