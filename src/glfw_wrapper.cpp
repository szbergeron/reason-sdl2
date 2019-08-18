#include <stdio.h>
#include <stdint.h>

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
    static inline uint32_t priv_bitfield_from_flags(
            value v_audio,
            value v_video,
            value v_events,
            value v_haptic,
            value v_timer,
            value v_gamecontroller,
            value v_joystick,
            value v_everything
        )
    {
        // every passed value should be a bool encoded as a long,
        // so we can check for != 0 to reduce to a bool
        uint32_t i_audio = (v_audio) ? SDL_INIT_AUDIO : 0;
        uint32_t i_video = (v_video) ? SDL_INIT_VIDEO : 0;
        uint32_t i_events = (v_events) ? SDL_INIT_EVENTS : 0;
        uint32_t i_haptic = (v_haptic) ? SDL_INIT_HAPTIC : 0;
        uint32_t i_timer = (v_timer) ? SDL_INIT_TIMER : 0;
        uint32_t i_gamecontroller = (v_gamecontroller) ? SDL_INIT_GAMECONTROLLER : 0;
        uint32_t i_joystick = (v_joystick) ? SDL_INIT_JOYSTICK : 0;
        uint32_t i_everything = (i_everything) ? SDL_INIT_EVERYTHING : 0;

        return i_audio | i_video | i_events | i_haptic | i_timer | i_gamecontroller | i_joystick | i_everything;
    }

    CAMLprim value hello_sdl() {
        printf("hello, world\n");

        SDL_Window *window;
        int init_ret = SDL_Init(SDL_INIT_VIDEO);
        printf("SDL_Init returned %d\n", init_ret);
            // Create an application window with the following settings:

        window = SDL_CreateWindow(
            "An SDL2 window",                  // window title
            20,           // initial x position
            20,           // initial y position
            640,                               // width, in pixels
            480,                               // height, in pixels
            SDL_WINDOW_OPENGL                  // flags - see below
        );

        printf("SDL_CreateWindow returned %p\n", window);
        // Check that the window was successfully created
        if (window == NULL) {
            // In the case that the window could not be made...
            printf("Could not create window: %s\n", SDL_GetError());
            return 1;
        }
        // The window is open: could enter program loop here (see SDL_PollEvent())
        for( int i = 0; i < 50; SDL_Delay(2000), i++ )
        {
            SDL_Surface* window_surface = SDL_GetWindowSurface(window);
            SDL_FillRect(window_surface, NULL, SDL_MapRGB(window_surface->format, (i*1234) % 255, (i*1256) % 255, (i*1356) % 255));
            SDL_UpdateWindowSurface(window);
        }

        // Close and destroy the window
        SDL_DestroyWindow(window);
        
        // Clean up
        SDL_Quit();

        return Val_unit;
    }

    CAMLprim value resdl_init_native(
            value v_audio,
            value v_video,
            value v_events,
            value v_haptic,
            value v_timer,
            value v_gamecontroller,
            value v_joystick,
            value v_everything
        )
    {
        printf("doing sdl setup\n");

        uint32_t flags = priv_bitfield_from_flags( 
            v_audio,
            v_video,
            v_events,
            v_haptic,
            v_timer,
            v_gamecontroller,
            v_joystick,
            v_everything
        );

        // 0 on success, <0 on failure
        int e_code = SDL_InitSubSystem(flags);

        return Val_int(e_code);
    }

    CAMLprim value resdl_init_bytecode(value* argv, int argc)
    {
        return resdl_init_native(
            argv[0],
            argv[1],
            argv[2],
            argv[3],
            argv[4],
            argv[5],
            argv[6],
            argv[7]
        );
    }

    CAMLprim value resdl_quit() {
        SDL_Quit();

        return Val_unit;
    }
}

