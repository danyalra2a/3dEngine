#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <iostream>
#include <vector>
// include the header file so that we don't need to write out the prototype in this file
#include "other.h"
#define WIDTH 1000
#define HEIGHT 600
#define FPS 60
// #include <SDL2/SDL_timer.h>

int main() {
  SDL_Window *window = nullptr;
  SDL_Renderer *renderer = nullptr;

  Uint64 ticks; // will store the number of ms since SDL init

  vec3d vCamera;
//   vCamera.x, vCamera.y, vCamera.z = 0.0f;

  mesh meshCube;
  mat4x4 matProj;

  float fTheta = 0.5;

  meshCube.tris = {
            // SOUTH
            { 0.0f, 0.0f, 0.0f,    0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 0.0f },
            { 0.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 0.0f, 0.0f },

            // EAST                                                      
            { 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f },
            { 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f, 1.0f },

            // NORTH                                                     
            { 1.0f, 0.0f, 1.0f,    1.0f, 1.0f, 1.0f,    0.0f, 1.0f, 1.0f },
            { 1.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 0.0f, 1.0f },

            // WEST                                                      
            { 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 1.0f, 0.0f },
            { 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 0.0f,    0.0f, 0.0f, 0.0f },

            // TOP                                                       
            { 0.0f, 1.0f, 0.0f,    0.0f, 1.0f, 1.0f,    1.0f, 1.0f, 1.0f },
            { 0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 1.0f, 0.0f },

            // BOTTOM                                                    
            { 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f },
            { 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f },

		};

  // Projection Matrix
  float zNear = 3.0f;
  float zFar = 100.0f;
  float fFov = 90.0f;
  float fAspectRatio = (float) HEIGHT / (float) WIDTH;

  matProj.m[0][0] = fAspectRatio * zNear;
  matProj.m[1][1] = zNear;
  matProj.m[2][2] = 1 / (zFar * zNear);
  matProj.m[2][3] = (-1) / (zFar);
  matProj.m[3][2] = 1.0f;
//   matProj.m[3][3] = 0.0f;

  if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
  {
    // std::cout << "SDL_INit failed with error: " << SDL_GetError() << std::endl;
    printf("error intialising SDL: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  // dynamically allocate memory for window
  window = SDL_CreateWindow("GoogleChrome", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);

  // fail if window doesn't work
  if (!window) 
  {
    printf("error creating window: %s\n", SDL_GetError());
    SDL_Quit();
    return EXIT_FAILURE;
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  // Infinite rendering loop
  bool isRunning = true;
  bool isTriggered = false;

  fTheta = 0.0f;

  // Main application loop
  while(isRunning) {
    SDL_Event event;


    // get time at the start of the loop
    ticks = SDL_GetTicks64();

    // (1) Handle input
    // key data type, event
    while(SDL_PollEvent(&event)) {
    // if(SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_KEYDOWN: {
          isRunning = event.key.keysym.scancode != SDL_SCANCODE_ESCAPE;
          if (event.key.keysym.scancode == SDL_SCANCODE_SPACE) {
            isTriggered = !isTriggered;
            fTheta += 1.0f;           
          }
          break;
        }
        case SDL_QUIT: {
          isRunning = false;
          break;
        }
        default:
          break;
      }
    }

    // (2) Handle Updates

    // Set up rotation matrices
    mat4x4 matRotZ, matRotX;
    // update rotation angle based on FPS - one full rotation every 10 seconds
    fTheta += 2 * 3.14159f / (10 * FPS);
    // fTheta = 1.433f;

    matRotZ.m[0][0] = cosf(fTheta);
    matRotZ.m[0][1] = sinf(fTheta);
    matRotZ.m[1][0] = -sinf(fTheta);
    matRotZ.m[1][1] = cosf(fTheta);
    matRotZ.m[2][2] = 1;
    matRotZ.m[3][3] = 1;

    matRotX.m[0][0] = 1;
    matRotX.m[1][1] = cosf(fTheta * 0.5f);
    matRotX.m[1][2] = sinf(fTheta * 0.5f);
    matRotX.m[2][1] = -sinf(fTheta * 0.5f);
    matRotX.m[2][2] = cosf(fTheta * 0.5f);
    matRotX.m[3][3] = 1;

    // (3) Clear and draw the screen

    // Clear the "canvas", set the colour, then fill the renderer
    SDL_SetRenderDrawColor(renderer,0,0,0,SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    // Actually draw

    // Set draw colour to white
    SDL_SetRenderDrawColor(renderer,255,255,255,SDL_ALPHA_OPAQUE);

    // Draw Triangles
    for (auto tri : meshCube.tris)
    {
        triangle triProjected, triTranslated, triRotatedZ, triRotatedZX;

        // Rotate in Z-Axis
        MultiplyMatrixVector(tri.p[0], triRotatedZ.p[0], matRotZ);
        MultiplyMatrixVector(tri.p[1], triRotatedZ.p[1], matRotZ);
        MultiplyMatrixVector(tri.p[2], triRotatedZ.p[2], matRotZ);

        // Rotate in X-Axis
        MultiplyMatrixVector(triRotatedZ.p[0], triRotatedZX.p[0], matRotX);
        MultiplyMatrixVector(triRotatedZ.p[1], triRotatedZX.p[1], matRotX);
        MultiplyMatrixVector(triRotatedZ.p[2], triRotatedZX.p[2], matRotX);

        // Offset into the screen
        triTranslated = triRotatedZX;
        triTranslated.p[0].z = triRotatedZX.p[0].z + 5.0f;
        triTranslated.p[1].z = triRotatedZX.p[1].z + 5.0f;
        triTranslated.p[2].z = triRotatedZX.p[2].z + 5.0f;

        // Now we calculate the normal, if this has a postive component (dot product) with a line from the camera to
        vec3d normal, line1, line2, camLine;

        line1.x = triTranslated.p[1].x - triTranslated.p[0].x;
        line1.y = triTranslated.p[1].y - triTranslated.p[0].y;
        line1.z = triTranslated.p[1].z - triTranslated.p[0].z;

        line2.x = triTranslated.p[2].x - triTranslated.p[0].x;
        line2.y = triTranslated.p[2].y - triTranslated.p[0].y;
        line2.z = triTranslated.p[2].z - triTranslated.p[0].z;

        // set the normal
        CrossProductNormalised(line1, line2, normal);

        // could choose another point on the plane to taken the line from...
        camLine.x = triTranslated.p[0].x - vCamera.x;
        camLine.y = triTranslated.p[0].y - vCamera.y;
        camLine.z = triTranslated.p[0].z - vCamera.z;

        // this is the dot product part - this assumes that objects have an inside and an outside
        if ( DotProduct(normal, camLine) < 0.0f ) {
        // Project triangles from 3D --> 2D
            MultiplyMatrixVector(triTranslated.p[0], triProjected.p[0], matProj);
            MultiplyMatrixVector(triTranslated.p[1], triProjected.p[1], matProj);
            MultiplyMatrixVector(triTranslated.p[2], triProjected.p[2], matProj);

            // Assume rays of light all come from a single direction
            // -1 z since we assume a triangle is more lit up the more it's normal is aligned with the light direction
            vec3d light_direction = { 0.0f, 0.0f, -1.0f };
            float len = sqrtf(DotProduct(light_direction, light_direction));
            light_direction.x /= len; light_direction.y /= len; light_direction.z /= len;

            float light_amount = DotProduct(normal, light_direction);

            // Scale into window
            triProjected.p[0].x += 1.0f; triProjected.p[0].y += 1.0f;
            triProjected.p[1].x += 1.0f; triProjected.p[1].y += 1.0f;
            triProjected.p[2].x += 1.0f; triProjected.p[2].y += 1.0f;   
            triProjected.p[0].x *= 0.5f * (float)WIDTH;
            triProjected.p[0].y *= 0.5f * (float)HEIGHT;
            triProjected.p[1].x *= 0.5f * (float)WIDTH;
            triProjected.p[1].y *= 0.5f * (float)HEIGHT;
            triProjected.p[2].x *= 0.5f * (float)WIDTH;
            triProjected.p[2].y *= 0.5f * (float)HEIGHT;            

            // Rasterize triangle
            SDL_RenderDrawLine(renderer, triProjected.p[0].x, triProjected.p[0].y, triProjected.p[1].x, triProjected.p[1].y);
            SDL_RenderDrawLine(renderer, triProjected.p[1].x, triProjected.p[1].y, triProjected.p[2].x, triProjected.p[2].y);
            SDL_RenderDrawLine(renderer, triProjected.p[2].x, triProjected.p[2].y, triProjected.p[0].x, triProjected.p[0].y);
        }
    }

    // SDL_SetRenderDrawColor(renderer,255,255,255,SDL_ALPHA_OPAQUE);
    if (isTriggered) {
    SDL_RenderDrawLine(renderer, 50, 50, 400, 300);
    SDL_RenderDrawLine(renderer, 50, 300, 400, 50);
    }

    // Render drawing - I think this moves from frame buffer? See double buffering
    SDL_RenderPresent(renderer);

    // wait until time to render next frame based on FPS

    if ( (float)(SDL_GetTicks64() - ticks) < 1000.0f/FPS ) {
        printf("delay: %d\n", (Uint32)((1000.0f/FPS) - SDL_GetTicks64() + ticks));
        SDL_Delay((Uint32)((1000.0f/FPS) - SDL_GetTicks64() + ticks));
        ticks = SDL_GetTicks64();
    }

  }

//   SDL_Delay(2000);

  // deallocate memory for window and renderer
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  // inverse of SDL_Init, turns off video, audio, etc system we enabled in SDL
  SDL_Quit();

  return EXIT_SUCCESS;
}