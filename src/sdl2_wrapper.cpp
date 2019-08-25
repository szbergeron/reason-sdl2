#include <cstdio>
#include <cstdint>

#include <array>
#include <algorithm>

#include <caml/mlvalues.h>
#include <caml/bigarray.h>
#include <caml/memory.h>
#include <caml/alloc.h>
#include <caml/callback.h>
#include <caml/fail.h>
#include <caml/threads.h>

#include <glad/glad.h>

#include "stb_image.h"

#include <SDL2/SDL.h>

extern "C" {
    CAMLprim value resdl_SDL_SetMainReady() {
        SDL_SetMainReady();

        return Val_unit;
    }
    CAMLprim value resdl_SDL_DestroyWindow(value win) {
            printf("needs implementation!");
    }

    CAMLprim value resdl_SDL_Delay(value delay) {
        CAMLparam1(delay);

        int d = Int_val(delay);
        SDL_Delay(d);
        CAMLreturn(Val_unit);
    }

    CAMLprim value resdl_SDL_GL_Setup(value w) {
        SDL_Window *win = (SDL_Window *)w;
        SDL_GL_CreateContext(win);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

        SDL_GL_SetSwapInterval(0);

        /* Turn on double buffering with a 24bit Z buffer.
         * You may need to change this to 16 or 32 for your system */
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

        SDL_CreateRenderer(
                win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);

         gladLoadGLES2Loader((GLADloadproc) SDL_GL_GetProcAddress);
    }

    CAMLprim value resdl_test_poll() {

    char *text;
    char *composition;
    Sint32 cursor;
    Sint32 selection_len;
int hasStarted = 0;

        while (1) {
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                switch (event.type) {
                case SDL_QUIT:
                    /* Quit */
                    printf("QUIT!");
                    break;
                case SDL_TEXTINPUT:
                    /* Add new text onto the end of our text */
                    printf("text input: %s\n", event.text.text);
    if (hasStarted == 0) {
    SDL_Rect rect1; 
    rect1.x = 50; 
    rect1.y = 50; 
    rect1.w = 200; 
    rect1.h = 32; 
        /*SDL_StartTextInput();
        SDL_SetTextInputRect(&rect1);*/
        hasStarted = 1;
        }
                    break;
                case SDL_TEXTEDITING:
                    /*
                    Update the composition text.
                    Update the cursor position.
                    Update the selection length (if any).
                    */
                    
                    composition = event.edit.text;
                    cursor = event.edit.start;
                    selection_len = event.edit.length;
                    printf("composition! %s|%d|%d", composition, cursor, selection_len);
                    break;
                }
                printf("got an event!\n");
            }
        }
    }

    CAMLprim value resdl_SDL_GL_SwapWindow(value w) {
        SDL_Window *win = (SDL_Window *)w;
        SDL_GL_SwapWindow(win);
    }

    CAMLprim value resdl_test_gl_blue(value w) {
        SDL_Window *win = (SDL_Window *)w;
        glClearColor ( 0.0, 1.0, 0.0, 1.0 );
        glClear ( GL_COLOR_BUFFER_BIT );
        /* Swap our back buffer to the front */
        SDL_GL_SwapWindow(win);
    }
    
    CAMLprim value resdl_test_gl_green(value w) {
        SDL_Window *win = (SDL_Window *)w;
        glClearColor ( 0.0, 0.0, 1.0, 1.0 );
        glClear ( GL_COLOR_BUFFER_BIT );
        /* Swap our back buffer to the front */
        SDL_GL_SwapWindow(win);
    }
    
    CAMLprim value resdl_SDL_CreateWindow() {

      return (value)(SDL_CreateWindow("test", 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN));
    }

    CAMLprim value resdl_SDL_Init() {
        CAMLparam0();
        int ret = SDL_Init(SDL_INIT_VIDEO);
        CAMLreturn(Val_int(ret));
    }
  }

