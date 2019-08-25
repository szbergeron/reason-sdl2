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

#define GLFW_INCLUDE_NONE

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
    
    CAMLprim value resdl_SDL_CreateWindow() {

      return (value)(SDL_CreateWindow("test", 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN));
    }

    CAMLprim value resdl_SDL_init() {
        CAMLparam0();
        int ret = SDL_Init(SDL_INIT_VIDEO);
        CAMLreturn(Val_int(ret));
    }
  }

