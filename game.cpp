#include <iostream>
#include <SDL.h>



#define WIDTH 500
#define HEIGHT 500
#define BUFFER 3000
#define BALL_SIZE 15
#define BALL_SPEED 5

#define PADDLE_HEIGHT 70
#define PADDLE_WIDTH 10
#define PADDLE_SPEED 10


int window() {
    SDL_Window *window_var = NULL;
    SDL_Event event;
    SDL_Renderer *renderer = NULL;
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL failed to initialise: %s\n", SDL_GetError());
        return 1;
    }
    

    window_var = SDL_CreateWindow(
        "Ping Pong", 
    SDL_WINDOWPOS_UNDEFINED, 
    SDL_WINDOWPOS_UNDEFINED,
    WIDTH,
    HEIGHT,
    0
    );
    if (window_var == NULL) {
        fprintf(stderr, "SDL window failed to initialise: %s\n", SDL_GetError());
        return 1;
    }

    renderer = SDL_CreateRenderer(window_var, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        fprintf(stderr, "SDL renderer failed to initialise: %s\n", SDL_GetError());
        return 1;
    }

    bool run = true;

    int ballHorizontal = WIDTH / 2;
    int ballVertical = HEIGHT / 2;
    int ballSpeedHorizontal = BALL_SPEED;
    int ballSpeedVertical = BALL_SPEED;
    
    SDL_Rect ballRect = {WIDTH / 2 - BALL_SIZE / 2, HEIGHT / 2 - BALL_SIZE / 2,  BALL_SIZE, BALL_SIZE};
    SDL_Rect autoPaddleRect = {50, HEIGHT / 2 - BALL_SIZE / 2 + 10, PADDLE_WIDTH, PADDLE_HEIGHT};
    SDL_Rect userPaddleRect = {450, HEIGHT / 2 - BALL_SIZE / 2 + 10, PADDLE_WIDTH, PADDLE_HEIGHT};

    int autoPaddleSpeedHorizontal = PADDLE_SPEED;
    int autoPaddleSpeedVertical =  PADDLE_SPEED;
    int userPaddleSpeedHorizontal = PADDLE_SPEED;
    int userPaddleSpeedVertical = PADDLE_SPEED;

    while (run) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                run = false;
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                        userPaddleRect.y -= userPaddleSpeedVertical;
                        break;
                    case SDLK_DOWN:
                        userPaddleRect.y += userPaddleSpeedVertical;
                    case SDLK_LEFT:
                        userPaddleRect.x -= userPaddleSpeedHorizontal;
                    case SDLK_RIGHT:
                        userPaddleRect.x += userPaddleSpeedHorizontal;
                }
            }
        }
        

        ballRect.x += ballSpeedHorizontal;
        ballRect.y += ballSpeedVertical;

        //paddleRect.x += autoPaddleSpeedHorizontal;
        autoPaddleRect.y += ballSpeedVertical;


        if (ballRect.x < 0 || ballRect.x + ballRect.w > WIDTH - 1) {
            ballSpeedHorizontal = -ballSpeedHorizontal;
        }
        if (ballRect.y < 0 || ballRect.y + ballRect.h  > HEIGHT-1) {
            ballSpeedVertical = -ballSpeedVertical;
        }

        /*if (ballRect.x == paddleRect.x && ballRect.y == paddleRect.y) {
            ballSpeedHorizontal = -ballSpeedHorizontal;
            ballSpeedVertical = -ballSpeedVertical;
        }*/

        /*if (paddleRect.x < 0 || paddleRect.x + paddleRect.w > WIDTH - 1) {
            autoPaddleSpeedHorizontal = -autoPaddleSpeedHorizontal;
        }*/
        if (autoPaddleRect.y < 0 || autoPaddleRect.y + autoPaddleRect.h  > HEIGHT-1) {
            autoPaddleSpeedVertical = -ballSpeedVertical;
        }

        //collision with auto paddle
        if (ballRect.x <= autoPaddleRect.x + autoPaddleRect.w &&
        ballRect.x + ballRect.w >= autoPaddleRect.x &&
        ballRect.y <= autoPaddleRect.y + autoPaddleRect.h &&
        ballRect.y + ballRect.h >= autoPaddleRect.y
        ) {
            ballSpeedHorizontal = -ballSpeedHorizontal;
            ballSpeedVertical = -ballSpeedVertical;
        }

        // collision with user paddle
        if (ballRect.x <= userPaddleRect.x + userPaddleRect.w &&
        ballRect.x + ballRect.w >= userPaddleRect.x &&
        ballRect.y <= userPaddleRect.y + userPaddleRect.h &&
        ballRect.y + ballRect.h >= userPaddleRect.y
        ) {
            ballSpeedHorizontal = -ballSpeedHorizontal;
            ballSpeedVertical = -ballSpeedVertical;
        }



        // user paddle within window range
        if (userPaddleRect.y < 0) {
            userPaddleRect.y = 0;
        } else if (userPaddleRect.y + userPaddleRect.h > HEIGHT) {
            userPaddleRect.y = HEIGHT - userPaddleRect.h;
        }



        //window black background
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);


        //draw ball
        SDL_SetRenderDrawColor(renderer, 255, 128, 128, 255);
        SDL_RenderFillRect(renderer, &ballRect);



        //draw auto paddle
        SDL_SetRenderDrawColor(renderer, 122, 240, 173, 255);
        SDL_RenderFillRect(renderer, &autoPaddleRect);


        //draw user paddle
        SDL_SetRenderDrawColor(renderer, 255, 169, 71, 255);
        SDL_RenderFillRect(renderer, &userPaddleRect);

        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }
    //SDL_Delay(BUFFER);
    SDL_DestroyWindow(window_var);
    SDL_Quit();
    return 0;
}
int main() {
    //std::cout << "Hello, World!" << std::endl;
    window();
    return 0;
}

