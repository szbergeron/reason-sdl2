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

namespace bind_tools {
    
}

extern "C" {
    //////////MACRO EXPOSURE FUNCTIONS//////////
    namespace resdl_SDL_BlendMode {
        std::array<int,4> resdl_vtom = {
            SDL_BLENDMODE_NONE,
            SDL_BLENDMODE_BLEND,
            SDL_BLENDMODE_ADD,
            SDL_BLENDMODE_MOD
        };

        CAMLprim value resdl_SDL_BlendMode_vtom(value variant_val) {
            int variant_int = Int_val(variant_val);

            return Val_int(resdl_vtom[variant_int]);
        }

        CAMLprim value resdl_SDL_BlendMode_mtov(value macro_val) {
            // could use a prefetch instruction here, but likely unecessary
            // std::find may also get vectorized, but it's so small it shouldn't matter either way
            int macro_int = Int_val(macro_val);

            return Val_int(
                    std::distance(resdl_vtom.begin(),
                        std::find(resdl_vtom.begin(), resdl_vtom.end(), macro_int)
                    )
                );
        }

        CAMLprim value resdl_SDL_GetRenderDrawBlendMode(value v_renderer, value v_blendmode) {
            return Val_int(
                    SDL_GetRenderDrawBlendMode(
                        (SDL_Renderer*)v_renderer,
                        (SDL_BlendMode*)v_blendmode
                    )
                );
        }

        CAMLprim value resdl_SDL_GetSurfaceBlendMode(value v_surface, value v_blendmode) {
            return Val_int(
                    SDL_GetSurfaceBlendMode(
                        (SDL_Surface*)v_surface,
                        (SDL_BlendMode*)v_blendmode
                    )
                );
        }

        CAMLprim value resdl_SDL_GetTextureBlendMode(value v_texture, value v_blendmode){
            return Val_int(
                    SDL_GetTextureBlendMode(
                        (SDL_Texture*)v_texture,
                        (SDL_BlendMode*)v_blendmode
                    )
                );
        }

    }

    namespace resdl_SDL_GLattr {
        CAMLprim value resdl_m_SDL_GL_RED_SIZE() {
            return Val_int(SDL_GL_RED_SIZE);
        }

        CAMLprim value resdl_m_SDL_GL_GREEN_SIZE() {
            return Val_int(SDL_GL_GREEN_SIZE);
        }

        CAMLprim value resdl_m_SDL_GL_BLUE_SIZE() {
            return Val_int(SDL_GL_BLUE_SIZE);
        }

        CAMLprim value resdl_m_SDL_GL_ALPHA_SIZE() {
            return Val_int(SDL_GL_ALPHA_SIZE);
        }

        CAMLprim value resdl_m_SDL_GL_BUFFER_SIZE() {
            return Val_int(SDL_GL_BUFFER_SIZE);
        }

        CAMLprim value resdl_m_SDL_GL_DOUBLEBUFFER() {
            return Val_int(SDL_GL_DOUBLEBUFFER);
        }

        CAMLprim value resdl_m_SDL_GL_DEPTH_SIZE() {
            return Val_int(SDL_GL_DEPTH_SIZE);
        }

        CAMLprim value resdl_m_SDL_GL_STENCIL_SIZE() {
            return Val_int(SDL_GL_STENCIL_SIZE);
        }

        CAMLprim value resdl_m_SDL_GL_ACCUM_RED_SIZE() {
            return Val_int(SDL_GL_ACCUM_RED_SIZE);
        }

        CAMLprim value resdl_m_SDL_GL_ACCUM_GREEN_SIZE() {
            return Val_int(SDL_GL_ACCUM_GREEN_SIZE);
        }

        CAMLprim value resdl_m_SDL_GL_ACCUM_BLUE_SIZE() {
            return Val_int(SDL_GL_ACCUM_BLUE_SIZE);
        }

        CAMLprim value resdl_m_SDL_GL_ACCUM_ALPHA_SIZE() {
            return Val_int(SDL_GL_ACCUM_ALPHA_SIZE);
        }

        CAMLprim value resdl_m_SDL_GL_STEREO() {
            return Val_int(SDL_GL_STEREO);
        }

        CAMLprim value resdl_m_SDL_GL_MULTISAMPLEBUFFERS() {
            return Val_int(SDL_GL_MULTISAMPLEBUFFERS);
        }

        CAMLprim value resdl_m_SDL_GL_MULTISAMPLESAMPLES() {
            return Val_int(SDL_GL_MULTISAMPLESAMPLES);
        }

        CAMLprim value resdl_m_SDL_GL_ACCELERATED_VISUAL() {
            return Val_int(SDL_GL_ACCELERATED_VISUAL);
        }

        CAMLprim value resdl_m_SDL_GL_CONTEXT_MAJOR_VERSION() {
            return Val_int(SDL_GL_CONTEXT_MAJOR_VERSION);
        }

        CAMLprim value resdl_m_SDL_GL_CONTEXT_MINOR_VERSION() {
            return Val_int(SDL_GL_CONTEXT_MINOR_VERSION);
        }

        CAMLprim value resdl_m_SDL_GL_CONTEXT_FLAGS() {
            return Val_int(SDL_GL_CONTEXT_FLAGS);
        }

        CAMLprim value resdl_m_SDL_GL_CONTEXT_PROFILE_MASK() {
            return Val_int(SDL_GL_CONTEXT_PROFILE_MASK);
        }

        CAMLprim value resdl_m_SDL_GL_SHARE_WITH_CURRENT_CONTEXT() {
            return Val_int(SDL_GL_SHARE_WITH_CURRENT_CONTEXT);
        }

        // WARN: for this macro, we should inspect the behavior on intel cards
        // from memory, although they advertize this the i915 driver on linux
        // does not actually support this and what results is an uncorrected
        // linear framebuffer is presented instead
        CAMLprim value resdl_m_SDL_GL_FRAMEBUFFER_SRGB_CAPABLE() {
            return Val_int(SDL_GL_FRAMEBUFFER_SRGB_CAPABLE);
        }

        CAMLprim value resdl_m_SDL_GL_CONTEXT_RELEASE_BEHAVIOR() {
            return Val_int(SDL_GL_CONTEXT_RELEASE_BEHAVIOR);
        }
    }

    namespace resdl_SDL_GLcontextFlag {
        CAMLprim value resdl_m_SDL_GL_CONTEXT_DEBUG_FLAG() {
            return Val_int(SDL_GL_CONTEXT_DEBUG_FLAG);
        }

        CAMLprim value resdl_m_SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG() {
            return Val_int(SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
        }

        CAMLprim value resdl_m_SDL_GL_CONTEXT_ROBUST_ACCESS_FLAG() {
            return Val_int(SDL_GL_CONTEXT_ROBUST_ACCESS_FLAG);
        }

        CAMLprim value resdl_m_SDL_GL_CONTEXT_RESET_ISOLATION_FLAG() {
            return Val_int(SDL_GL_CONTEXT_RESET_ISOLATION_FLAG);
        }
    }

    namespace resdl_SDL_GLprofile {

        CAMLprim value resdl_m_SDL_GL_CONTEXT_PROFILE_CORE() {
            return Val_int(SDL_GL_CONTEXT_PROFILE_CORE);
        }

        CAMLprim value resdl_m_SDL_GL_CONTEXT_PROFILE_COMPATIBILITY() {
            return Val_int(SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
        }

        CAMLprim value resdl_m_SDL_GL_CONTEXT_PROFILE_ES() {
            return Val_int(SDL_GL_CONTEXT_PROFILE_ES);
        }
    }

    namespace resdl_SDL_HitTestResult {
        CAMLprim value resdl_m_SDL_HITTEST_NORMAL() {
            return Val_int(SDL_HITTEST_NORMAL);
        }

        CAMLprim value resdl_m_SDL_HITTEST_DRAGGABLE() {
            return Val_int(SDL_HITTEST_DRAGGABLE);
        }

        CAMLprim value resdl_m_SDL_HITTEST_RESIZE_TOPLEFT() {
            return Val_int(SDL_HITTEST_RESIZE_TOPLEFT);
        }

        CAMLprim value resdl_m_SDL_HITTEST_RESIZE_TOP() {
            return Val_int(SDL_HITTEST_RESIZE_TOP);
        }

        CAMLprim value resdl_m_SDL_HITTEST_RESIZE_TOPRIGHT() {
            return Val_int(SDL_HITTEST_RESIZE_TOPRIGHT);
        }

        CAMLprim value resdl_m_SDL_HITTEST_RESIZE_RIGHT() {
            return Val_int(SDL_HITTEST_RESIZE_RIGHT);
        }

        CAMLprim value resdl_m_SDL_HITTEST_RESIZE_BOTTOMRIGHT() {
            return Val_int(SDL_HITTEST_RESIZE_BOTTOMRIGHT);
        }

        CAMLprim value resdl_m_SDL_HITTEST_RESIZE_BOTTOM() {
            return Val_int(SDL_HITTEST_RESIZE_BOTTOM);
        }

        CAMLprim value resdl_m_SDL_HITTEST_RESIZE_BOTTOMLEFT() {
            return Val_int(SDL_HITTEST_RESIZE_BOTTOMLEFT);
        }

        CAMLprim value resdl_m_SDL_HITTEST_RESIZE_LEFT() {
            return Val_int(SDL_HITTEST_RESIZE_LEFT);
        }
    }

    namespace resdl_SDL_MessageBoxButtonFlags {
        CAMLprim value resdl_m_SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT() {
            return Val_int(SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT);
        }

        CAMLprim value resdl_m_SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT() {
            return Val_int(SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT);
        }
    }

    namespace resdl_SDL_MessageBoxColorType {
        CAMLprim value resdl_m_SDL_MESSAGEBOX_COLOR_BACKGROUND() {
            return Val_int(SDL_MESSAGEBOX_COLOR_BACKGROUND);
        }

        CAMLprim value resdl_m_SDL_MESSAGEBOX_COLOR_TEXT() {
            return Val_int(SDL_MESSAGEBOX_COLOR_TEXT);
        }

        CAMLprim value resdl_m_SDL_MESSAGEBOX_COLOR_BUTTON_BORDER() {
            return Val_int(SDL_MESSAGEBOX_COLOR_BUTTON_BORDER);
        }

        CAMLprim value resdl_m_SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND() {
            return Val_int(SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND);
        }

        CAMLprim value resdl_m_SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED() {
            return Val_int(SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED);
        }

        CAMLprim value resdl_m_SDL_MESSAGEBOX_COLOR_MAX() {
            return Val_int(SDL_MESSAGEBOX_COLOR_MAX);
        }
    }

    namespace resdl_SDL_MessageBoxFlags {
        CAMLprim value resdl_m_SDL_MESSAGEBOX_ERROR() {
            return Val_int(SDL_MESSAGEBOX_ERROR);
        }

        CAMLprim value resdl_m_SDL_MESSAGEBOX_WARNING() {
            return Val_int(SDL_MESSAGEBOX_WARNING);
        }

        CAMLprim value resdl_m_SDL_MESSAGEBOX_INFORMATION() {
            return Val_int(SDL_MESSAGEBOX_INFORMATION);
        }
    }

    namespace resdl_SDL_WindowEventID {
        CAMLprim value resdl_m_SDL_WINDOWEVENT_SHOWN() {
            return Val_int(SDL_WINDOWEVENT_SHOWN);
        }

        CAMLprim value resdl_m_SDL_WINDOWEVENT_HIDDEN() {
            return Val_int(SDL_WINDOWEVENT_HIDDEN);
        }

        CAMLprim value resdl_m_SDL_WINDOWEVENT_EXPOSED() {
            return Val_int(SDL_WINDOWEVENT_EXPOSED);
        }

        CAMLprim value resdl_m_SDL_WINDOWEVENT_MOVED() {
            return Val_int(SDL_WINDOWEVENT_MOVED);
        }

        CAMLprim value resdl_m_SDL_WINDOWEVENT_RESIZED() {
            return Val_int(SDL_WINDOWEVENT_RESIZED);
        }

        CAMLprim value resdl_m_SDL_WINDOWEVENT_SIZE_CHANGED() {
            return Val_int(SDL_WINDOWEVENT_SIZE_CHANGED);
        }

        CAMLprim value resdl_m_SDL_WINDOWEVENT_MINIMIZED() {
            return Val_int(SDL_WINDOWEVENT_MINIMIZED);
        }

        CAMLprim value resdl_m_SDL_WINDOWEVENT_MAXIMIZED() {
            return Val_int(SDL_WINDOWEVENT_MAXIMIZED);
        }

        CAMLprim value resdl_m_SDL_WINDOWEVENT_RESTORED() {
            return Val_int(SDL_WINDOWEVENT_RESTORED);
        }

        CAMLprim value resdl_m_SDL_WINDOWEVENT_ENTER() {
            return Val_int(SDL_WINDOWEVENT_ENTER);
        }

        CAMLprim value resdl_m_SDL_WINDOWEVENT_LEAVE() {
            return Val_int(SDL_WINDOWEVENT_LEAVE);
        }

        CAMLprim value resdl_m_SDL_WINDOWEVENT_FOCUS_GAINED() {
            return Val_int(SDL_WINDOWEVENT_FOCUS_GAINED);
        }

        CAMLprim value resdl_m_SDL_WINDOWEVENT_FOCUS_LOST() {
            return Val_int(SDL_WINDOWEVENT_FOCUS_LOST);
        }

        CAMLprim value resdl_m_SDL_WINDOWEVENT_CLOSE() {
            return Val_int(SDL_WINDOWEVENT_CLOSE);
        }

        CAMLprim value resdl_m_SDL_WINDOWEVENT_TAKE_FOCUS() {
            return Val_int(SDL_WINDOWEVENT_TAKE_FOCUS);
        }

        CAMLprim value resdl_m_SDL_WINDOWEVENT_HIT_TEST() {
            return Val_int(SDL_WINDOWEVENT_HIT_TEST);
        }
    }

    namespace resdl_SDL_WindowFlags {
        CAMLprim value resdl_m_SDL_WINDOW_FULLSCREEN() {
            return Val_int(SDL_WINDOW_FULLSCREEN);
        }

        CAMLprim value resdl_m_SDL_WINDOW_FULLSCREEN_DESKTOP() {
            return Val_int(SDL_WINDOW_FULLSCREEN_DESKTOP);
        }

        CAMLprim value resdl_m_SDL_WINDOW_OPENGL() {
            return Val_int(SDL_WINDOW_OPENGL);
        }

        CAMLprim value resdl_m_SDL_WINDOW_SHOWN() {
            return Val_int(SDL_WINDOW_SHOWN);
        }

        CAMLprim value resdl_m_SDL_WINDOW_HIDDEN() {
            return Val_int(SDL_WINDOW_HIDDEN);
        }

        CAMLprim value resdl_m_SDL_WINDOW_BORDERLESS() {
            return Val_int(SDL_WINDOW_BORDERLESS);
        }

        CAMLprim value resdl_m_SDL_WINDOW_RESIZABLE() {
            return Val_int(SDL_WINDOW_RESIZABLE);
        }

        CAMLprim value resdl_m_SDL_WINDOW_MINIMIZED() {
            return Val_int(SDL_WINDOW_MINIMIZED);
        }

        CAMLprim value resdl_m_SDL_WINDOW_MAXIMIZED() {
            return Val_int(SDL_WINDOW_MAXIMIZED);
        }

        CAMLprim value resdl_m_SDL_WINDOW_INPUT_GRABBED() {
            return Val_int(SDL_WINDOW_INPUT_GRABBED);
        }

        CAMLprim value resdl_m_SDL_WINDOW_INPUT_FOCUS() {
            return Val_int(SDL_WINDOW_INPUT_FOCUS);
        }

        CAMLprim value resdl_m_SDL_WINDOW_FOREIGN() {
            return Val_int(SDL_WINDOW_FOREIGN);
        }

        CAMLprim value resdl_m_SDL_WINDOW_ALLOW_HIGHDPI() {
            return Val_int(SDL_WINDOW_ALLOW_HIGHDPI);
        }

        CAMLprim value resdl_m_SDL_WINDOW_MOUSE_CAPTURE() {
            return Val_int(SDL_WINDOW_MOUSE_CAPTURE);
        }

        CAMLprim value resdl_m_SDL_WINDOW_ALWAYS_ON_TOP() {
            return Val_int(SDL_WINDOW_ALWAYS_ON_TOP);
        }

        CAMLprim value resdl_m_SDL_WINDOW_SKIP_TASKBAR() {
            return Val_int(SDL_WINDOW_SKIP_TASKBAR);
        }

        CAMLprim value resdl_m_SDL_WINDOW_UTILITY() {
            return Val_int(SDL_WINDOW_UTILITY);
        }

        CAMLprim value resdl_m_SDL_WINDOW_TOOLTIP() {
            return Val_int(SDL_WINDOW_TOOLTIP);
        }

        CAMLprim value resdl_m_SDL_WINDOW_POPUP_MENU() {
            return Val_int(SDL_WINDOW_POPUP_MENU);
        }
    }

    namespace resdl_SDL_Render {

        CAMLprim value resdl_SDL_RenderCopy(
                value v_renderer,
                value v_texture,
                value v_srcrect,
                value v_dstrect
        ) {
            return Val_int(
                    SDL_RenderCopy(
                        (SDL_Renderer*)v_renderer,
                        (SDL_Texture*)v_texture,
                        (SDL_Rect*)v_srcrect,
                        (SDL_Rect*)v_dstrect
                    )
                );
        }
    }

    namespace resdl_category_handling {
        CAMLprim value resdl_SDL_GetError() {
            return caml_copy_string(SDL_GetError());
        }

        CAMLprim value resdl_SDL_ClearError() {
            SDL_ClearError();
            return Val_unit;
        }

        // TODO: implement handling for [int SDL_SetError(const char* fmt, ...)]
        //   Need to account for variadics in OCaml, is it possible? Or is an alternative solution necessary?
    }

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
        uint32_t i_audio = (Val_bool(v_audio)) ? SDL_INIT_AUDIO : 0;
        uint32_t i_video = (Val_bool(v_video)) ? SDL_INIT_VIDEO : 0;
        uint32_t i_events = (Val_bool(v_events)) ? SDL_INIT_EVENTS : 0;
        uint32_t i_haptic = (Val_bool(v_haptic)) ? SDL_INIT_HAPTIC : 0;
        uint32_t i_timer = (Val_bool(v_timer)) ? SDL_INIT_TIMER : 0;
        uint32_t i_gamecontroller = (Val_bool(v_gamecontroller)) ? SDL_INIT_GAMECONTROLLER : 0;
        uint32_t i_joystick = (Val_bool(v_joystick)) ? SDL_INIT_JOYSTICK : 0;
        uint32_t i_everything = (Val_bool(i_everything)) ? SDL_INIT_EVERYTHING : 0;

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
        printf("Hello from SDL, "
                "revision: %s\n",
                SDL_GetRevision()
                );

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

        printf("init returned %d\n", e_code);

        printf("Hints:\n");
        printf("End hints\n");

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

    CAMLprim value resdl_wasinit(value v_flags)
    {
        int i_flags = Int_val(v_flags);
        printf("flags was 0x%X -- note: UB if negative here, WasInit expects an unsigned int\n", i_flags);

        int r_flags = SDL_WasInit(i_flags);

        printf("returning 0x%X\n", r_flags);

        return Val_int(r_flags);
    }

}

