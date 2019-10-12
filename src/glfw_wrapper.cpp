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
                SDL_DestroyWindow(reinterpret_cast<SDL_Window*>(win));
                return Val_unit;
            }
            
            CAMLprim value resdl_SDL_CreateWindow(
                value title_v,
                value x_position_v,
                value y_position_v,
                value width_v,
                value height_v,
                value flags_v
            ) {
              // need to design in a way of panicking on bad strings
              if( !caml_string_is_c_safe(title_v) ) {
                // panic somehow? Or just switch to returning an Option
                // also consider returning Option as this call could fail at runtime and just return null
              }
              char * title_c = strdup(String_val(title_v));

              // TODO: properly handle flags rather than hardcoding the sane defaults
              flags_v = Val_int(
                  SDL_WINDOW_OPENGL |
                  SDL_WINDOW_RESIZABLE |
                  SDL_WINDOW_ALLOW_HIGHDPI
                  );

              return (value)(SDL_CreateWindow(
                  title_c,
                  Int_val(x_position_v),
                  Int_val(y_position_v),
                  Int_val(width_v),
                  Int_val(height_v),
                  Int_val(flags_v)
                  ));
            }
            CAMLprim value resdl_SDL_CreateWindow_bytecode(value* argv, int argc) {
                return resdl_SDL_CreateWindow(
                    argv[0],
                    argv[1],
                    argv[2],
                    argv[3],
                    argv[4],
                    argv[5]
                    );
            }
          }

//extern "C" "C" {

    // macro wrapper template
    /*
    namespace resdl_m_MACRONAME {
        std::array<int,ENUM_SIZE> resdl_vtom = {
            ENUM_CONTENTS
        }

        extern "C" CAMLprim value resdl_MACRONAME_vtom(value variant_val) {
            int variant_int = Int_val(variant_val);

            return Val_int(resdl_vtom[variant_int]);
        }

        extern "C" CAMLprim value resdl_MACRONAME_mtov(value macro_val) {
            int macro_int = Int_val(macro_val);

            return Val_int(
                    std::distance(resdl_vtom.begin(),
                        std::find(resdl_vtom.begin(), resdl_vtom.end(), macro_int)
                    )
                );
        }
    }
    */
    //////////MACRO EXPOSURE FUNCTIONS//////////
    namespace resdl_display_and_window_management {
        namespace resdl_f_display_and_window_management {
            CAMLprim value resdl_SDL_CreateWindow(
                value title_v,
                value x_position_v,
                value y_position_v,
                value width_v,
                value height_v,
                value flags_v
            ) {
              // need to design in a way of panicking on bad strings
              if( !caml_string_is_c_safe(title_v) ) {
                // panic somehow? Or just switch to returning an Option
                // also consider returning Option as this call could fail at runtime and just return null
              }
              char * title_c = strdup(String_val(title_v));

              // TODO: properly handle flags rather than hardcoding the sane defaults
              flags_v = Val_int(
                  SDL_WINDOW_OPENGL |
                  SDL_WINDOW_RESIZABLE |
                  SDL_WINDOW_ALLOW_HIGHDPI
                  );

              return reinterpret_cast<value>(SDL_CreateWindow(
                  title_c,
                  Int_val(x_position_v),
                  Int_val(y_position_v),
                  Int_val(width_v),
                  Int_val(height_v),
                  Int_val(flags_v)
                  ));
            }
            CAMLprim value resdl_SDL_CreateWindow_bytecode(value* argv, int argc) {
                return resdl_SDL_CreateWindow(
                    argv[0],
                    argv[1],
                    argv[2],
                    argv[3],
                    argv[4],
                    argv[5]
                    );
            }
        }
        namespace resdl_m_SDL_BlendMode {
            std::array<int,4> resdl_vtom = {
                SDL_BLENDMODE_NONE,
                SDL_BLENDMODE_BLEND,
                SDL_BLENDMODE_ADD,
                SDL_BLENDMODE_MOD
            };

            extern "C" CAMLprim value resdl_SDL_BlendMode_vtom(value variant_val) {
                int variant_int = Int_val(variant_val);

                return Val_int(resdl_vtom[variant_int]);
            }

            extern "C" CAMLprim value resdl_SDL_BlendMode_mtov(value macro_val) {
                // could use a prefetch instruction here, but likely unecessary
                // std::find may also get vectorized, but it's so small it shouldn't matter either way
                int macro_int = Int_val(macro_val);

                return Val_int(
                        std::distance(resdl_vtom.begin(),
                            std::find(resdl_vtom.begin(), resdl_vtom.end(), macro_int)
                        )
                    );
            }
        }

        namespace resdl_m_SDL_GLattr {
            std::array<int,27> resdl_vtom = {
                SDL_GL_RED_SIZE,
                SDL_GL_GREEN_SIZE,
                SDL_GL_BLUE_SIZE,
                SDL_GL_ALPHA_SIZE,
                SDL_GL_BUFFER_SIZE,
                SDL_GL_DOUBLEBUFFER,
                SDL_GL_DEPTH_SIZE,
                SDL_GL_STENCIL_SIZE,
                SDL_GL_ACCUM_RED_SIZE,
                SDL_GL_ACCUM_GREEN_SIZE,
                SDL_GL_ACCUM_BLUE_SIZE,
                SDL_GL_ACCUM_ALPHA_SIZE,
                SDL_GL_STEREO,
                SDL_GL_MULTISAMPLEBUFFERS,
                SDL_GL_MULTISAMPLESAMPLES,
                SDL_GL_ACCELERATED_VISUAL,
                SDL_GL_RETAINED_BACKING,
                SDL_GL_CONTEXT_MAJOR_VERSION,
                SDL_GL_CONTEXT_MINOR_VERSION,
                SDL_GL_CONTEXT_EGL,
                SDL_GL_CONTEXT_FLAGS,
                SDL_GL_CONTEXT_PROFILE_MASK,
                SDL_GL_SHARE_WITH_CURRENT_CONTEXT,
                SDL_GL_FRAMEBUFFER_SRGB_CAPABLE,
                SDL_GL_CONTEXT_RELEASE_BEHAVIOR,
                SDL_GL_CONTEXT_RESET_NOTIFICATION,
                SDL_GL_CONTEXT_NO_ERROR
            };

            extern "C" CAMLprim value resdl_SDL_GLattr_vtom(value variant_val) {
                int variant_int = Int_val(variant_val);

                return Val_int(resdl_vtom[variant_int]);
            }

            extern "C" CAMLprim value resdl_SDL_GLattr_mtov(value macro_val) {
                int macro_int = Int_val(macro_val);

                return Val_int(
                        std::distance(resdl_vtom.begin(),
                            std::find(resdl_vtom.begin(), resdl_vtom.end(), macro_int)
                        )
                    );
            }
        }

        namespace resdl_m_SDL_GLcontextFlag {
            std::array<int,4> resdl_vtom = {
                SDL_GL_CONTEXT_DEBUG_FLAG,
                SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG,
                SDL_GL_CONTEXT_ROBUST_ACCESS_FLAG,
                SDL_GL_CONTEXT_RESET_ISOLATION_FLAG
            };

            extern "C" CAMLprim value resdl_SDL_GLcontextFlag_vtom(value variant_val) {
                int variant_int = Int_val(variant_val);

                return Val_int(resdl_vtom[variant_int]);
            }

            extern "C" CAMLprim value resdl_SDL_GLcontextFlag_mtov(value macro_val) {
                int macro_int = Int_val(macro_val);

                return Val_int(
                        std::distance(resdl_vtom.begin(),
                            std::find(resdl_vtom.begin(), resdl_vtom.end(), macro_int)
                        )
                    );
            }
        }

        namespace resdl_m_SDL_GLprofile {
            std::array<int,3> resdl_vtom = {
                SDL_GL_CONTEXT_PROFILE_CORE,
                SDL_GL_CONTEXT_PROFILE_COMPATIBILITY,
                SDL_GL_CONTEXT_PROFILE_ES
            };

            extern "C" CAMLprim value resdl_SDL_GLprofile_vtom(value variant_val) {
                int variant_int = Int_val(variant_val);

                return Val_int(resdl_vtom[variant_int]);
            }

            extern "C" CAMLprim value resdl_SDL_GLprofile_mtov(value macro_val) {
                int macro_int = Int_val(macro_val);

                return Val_int(
                        std::distance(resdl_vtom.begin(),
                            std::find(resdl_vtom.begin(), resdl_vtom.end(), macro_int)
                        )
                    );
            }
        }

        namespace resdl_m_SDL_HitTestResult {
            std::array<int,10> resdl_vtom = {
                SDL_HITTEST_NORMAL,
                SDL_HITTEST_DRAGGABLE,
                SDL_HITTEST_RESIZE_TOPLEFT,
                SDL_HITTEST_RESIZE_TOP,
                SDL_HITTEST_RESIZE_TOPRIGHT,
                SDL_HITTEST_RESIZE_RIGHT,
                SDL_HITTEST_RESIZE_BOTTOMRIGHT,
                SDL_HITTEST_RESIZE_BOTTOM,
                SDL_HITTEST_RESIZE_BOTTOMLEFT,
                SDL_HITTEST_RESIZE_LEFT
            };

            extern "C" CAMLprim value resdl_SDL_HitTestResult_vtom(value variant_val) {
                int variant_int = Int_val(variant_val);

                return Val_int(resdl_vtom[variant_int]);
            }

            extern "C" CAMLprim value resdl_SDL_HitTestResult_mtov(value macro_val) {
                int macro_int = Int_val(macro_val);

                return Val_int(
                        std::distance(resdl_vtom.begin(),
                            std::find(resdl_vtom.begin(), resdl_vtom.end(), macro_int)
                        )
                    );
            }
        }

        namespace resdl_m_SDL_MessageBoxButtonFlags {
            std::array<int,2> resdl_vtom = {
                SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT,
                SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT
            };

            extern "C" CAMLprim value resdl_SDL_MessageBoxButtonFlags_vtom(value variant_val) {
                int variant_int = Int_val(variant_val);

                return Val_int(resdl_vtom[variant_int]);
            }

            extern "C" CAMLprim value resdl_SDL_MessageBoxButtonFlags_mtov(value macro_val) {
                int macro_int = Int_val(macro_val);

                return Val_int(
                        std::distance(resdl_vtom.begin(),
                            std::find(resdl_vtom.begin(), resdl_vtom.end(), macro_int)
                        )
                    );
            }
        }

        namespace resdl_m_SDL_MessageBoxColorType {
            std::array<int,6> resdl_vtom = {
                SDL_MESSAGEBOX_COLOR_BACKGROUND,
                SDL_MESSAGEBOX_COLOR_TEXT,
                SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
                SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
                SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
                SDL_MESSAGEBOX_COLOR_MAX
            };

            extern "C" CAMLprim value resdl_SDL_MessageBoxColorType_vtom(value variant_val) {
                int variant_int = Int_val(variant_val);

                return Val_int(resdl_vtom[variant_int]);
            }

            extern "C" CAMLprim value resdl_SDL_MessageBoxColorType_mtov(value macro_val) {
                int macro_int = Int_val(macro_val);

                return Val_int(
                        std::distance(resdl_vtom.begin(),
                            std::find(resdl_vtom.begin(), resdl_vtom.end(), macro_int)
                        )
                    );
            }
        }

        namespace resdl_m_SDL_MessageBoxFlags {
            std::array<int,3> resdl_vtom = {
                SDL_MESSAGEBOX_ERROR,
                SDL_MESSAGEBOX_WARNING,
                SDL_MESSAGEBOX_INFORMATION
            };

            extern "C" CAMLprim value resdl_SDL_MessageBoxFlags_vtom(value variant_val) {
                int variant_int = Int_val(variant_val);

                return Val_int(resdl_vtom[variant_int]);
            }

            extern "C" CAMLprim value resdl_SDL_MessageBoxFlags_mtov(value macro_val) {
                int macro_int = Int_val(macro_val);

                return Val_int(
                        std::distance(resdl_vtom.begin(),
                            std::find(resdl_vtom.begin(), resdl_vtom.end(), macro_int)
                        )
                    );
            }
        }

        namespace resdl_m_SDL_WindowEventID {
            std::array<int,17> resdl_vtom = {
                SDL_WINDOWEVENT_NONE,
                SDL_WINDOWEVENT_SHOWN,
                SDL_WINDOWEVENT_HIDDEN,
                SDL_WINDOWEVENT_EXPOSED,
                SDL_WINDOWEVENT_MOVED,
                SDL_WINDOWEVENT_RESIZED,
                SDL_WINDOWEVENT_SIZE_CHANGED,
                SDL_WINDOWEVENT_MINIMIZED,
                SDL_WINDOWEVENT_MAXIMIZED,
                SDL_WINDOWEVENT_RESTORED,
                SDL_WINDOWEVENT_ENTER,
                SDL_WINDOWEVENT_LEAVE,
                SDL_WINDOWEVENT_FOCUS_GAINED,
                SDL_WINDOWEVENT_FOCUS_LOST,
                SDL_WINDOWEVENT_CLOSE,
                SDL_WINDOWEVENT_TAKE_FOCUS,
                SDL_WINDOWEVENT_HIT_TEST
            };

            extern "C" CAMLprim value resdl_SDL_WindowEventID_vtom(value variant_val) {
                int variant_int = Int_val(variant_val);

                return Val_int(resdl_vtom[variant_int]);
            }

            extern "C" CAMLprim value resdl_SDL_WindowEventID_mtov(value macro_val) {
                int macro_int = Int_val(macro_val);

                return Val_int(
                        std::distance(resdl_vtom.begin(),
                            std::find(resdl_vtom.begin(), resdl_vtom.end(), macro_int)
                        )
                    );
            }
        }

        namespace resdl_m_SDL_WindowFlags {
            std::array<int,21> resdl_vtom = {
                SDL_WINDOW_FULLSCREEN,
                SDL_WINDOW_OPENGL,
                SDL_WINDOW_SHOWN,
                SDL_WINDOW_HIDDEN,
                SDL_WINDOW_BORDERLESS,
                SDL_WINDOW_RESIZABLE,
                SDL_WINDOW_MINIMIZED,
                SDL_WINDOW_MAXIMIZED,
                SDL_WINDOW_INPUT_GRABBED,
                SDL_WINDOW_INPUT_FOCUS,
                SDL_WINDOW_MOUSE_FOCUS,
                SDL_WINDOW_FULLSCREEN_DESKTOP,
                SDL_WINDOW_FOREIGN,
                SDL_WINDOW_ALLOW_HIGHDPI,
                SDL_WINDOW_MOUSE_CAPTURE,
                SDL_WINDOW_ALWAYS_ON_TOP,
                SDL_WINDOW_SKIP_TASKBAR,
                SDL_WINDOW_UTILITY,
                SDL_WINDOW_TOOLTIP,
                SDL_WINDOW_POPUP_MENU,
                SDL_WINDOW_VULKAN
            };

            extern "C" CAMLprim value resdl_SDL_WindowFlags_vtom(value variant_val) {
                int variant_int = Int_val(variant_val);

                return Val_int(resdl_vtom[variant_int]);
            }

            extern "C" CAMLprim value resdl_SDL_WindowFlags_mtov(value macro_val) {
                int macro_int = Int_val(macro_val);

                return Val_int(
                        std::distance(resdl_vtom.begin(),
                            std::find(resdl_vtom.begin(), resdl_vtom.end(), macro_int)
                        )
                    );
            }
        }

    namespace resdl_2d_accelerated_drawing {
        namespace resdl_m_SDL_BlendFactor {
            std::array<int,10> resdl_vtom = {
                SDL_BLENDFACTOR_ZERO,
                SDL_BLENDFACTOR_ONE,
                SDL_BLENDFACTOR_SRC_COLOR,
                SDL_BLENDFACTOR_ONE_MINUS_SRC_COLOR,
                SDL_BLENDFACTOR_SRC_ALPHA,
                SDL_BLENDFACTOR_ONE_MINUS_SRC_ALPHA,
                SDL_BLENDFACTOR_DST_COLOR,
                SDL_BLENDFACTOR_ONE_MINUS_DST_COLOR,
                SDL_BLENDFACTOR_DST_ALPHA,
                SDL_BLENDFACTOR_ONE_MINUS_DST_ALPHA
            };

            extern "C" CAMLprim value resdl_SDL_BlendFactor_vtom(value variant_val) {
                int variant_int = Int_val(variant_val);

                return Val_int(resdl_vtom[variant_int]);
            }

            extern "C" CAMLprim value resdl_SDL_BlendFactor_mtov(value macro_val) {
                int macro_int = Int_val(macro_val);

                return Val_int(
                        std::distance(resdl_vtom.begin(),
                            std::find(resdl_vtom.begin(), resdl_vtom.end(), macro_int)
                        )
                    );
            }
        }

        namespace resdl_m_SDL_BlendOperation {
            std::array<int,5> resdl_vtom = {
                SDL_BLENDOPERATION_ADD,
                SDL_BLENDOPERATION_SUBTRACT,
                SDL_BLENDOPERATION_REV_SUBTRACT,
                SDL_BLENDOPERATION_MINIMUM,
                SDL_BLENDOPERATION_MAXIMUM
            };

            extern "C" CAMLprim value resdl_SDL_BlendOperation_vtom(value variant_val) {
                int variant_int = Int_val(variant_val);

                return Val_int(resdl_vtom[variant_int]);
            }

            extern "C" CAMLprim value resdl_SDL_BlendOperation_mtov(value macro_val) {
                int macro_int = Int_val(macro_val);

                return Val_int(
                        std::distance(resdl_vtom.begin(),
                            std::find(resdl_vtom.begin(), resdl_vtom.end(), macro_int)
                        )
                    );
            }
        }

        namespace resdl_m_SDL_RendererFlags {
            std::array<int,4> resdl_vtom = {
                SDL_RENDERER_SOFTWARE,
                SDL_RENDERER_ACCELERATED,
                SDL_RENDERER_PRESENTVSYNC,
                SDL_RENDERER_TARGETTEXTURE
            };

            extern "C" CAMLprim value resdl_SDL_RendererFlags_vtom(value variant_val) {
                int variant_int = Int_val(variant_val);

                return Val_int(resdl_vtom[variant_int]);
            }

            extern "C" CAMLprim value resdl_SDL_RendererFlags_mtov(value macro_val) {
                int macro_int = Int_val(macro_val);

                return Val_int(
                        std::distance(resdl_vtom.begin(),
                            std::find(resdl_vtom.begin(), resdl_vtom.end(), macro_int)
                        )
                    );
            }
        }

        namespace resdl_m_SDL_RendererFlip {
            std::array<int,3> resdl_vtom = {
                SDL_FLIP_NONE,
                SDL_FLIP_HORIZONTAL,
                SDL_FLIP_VERTICAL
            };

            extern "C" CAMLprim value resdl_SDL_RendererFlip_vtom(value variant_val) {
                int variant_int = Int_val(variant_val);

                return Val_int(resdl_vtom[variant_int]);
            }

            extern "C" CAMLprim value resdl_SDL_RendererFlip_mtov(value macro_val) {
                int macro_int = Int_val(macro_val);

                return Val_int(
                        std::distance(resdl_vtom.begin(),
                            std::find(resdl_vtom.begin(), resdl_vtom.end(), macro_int)
                        )
                    );
            }
        }

        namespace resdl_m_SDL_TextureAccess {
            std::array<int,3> resdl_vtom = {
                SDL_TEXTUREACCESS_STATIC,
                SDL_TEXTUREACCESS_STREAMING,
                SDL_TEXTUREACCESS_TARGET
            };
            
            extern "C" CAMLprim value resdl_SDL_TextureAccess_vtom(value variant_val) {
                int variant_int = Int_val(variant_val);
            
                return Val_int(resdl_vtom[variant_int]);
            }
            
            extern "C" CAMLprim value resdl_SDL_TextureAccess_mtov(value macro_val) {
                int macro_int = Int_val(macro_val);
                
                return Val_int(
                        std::distance(resdl_vtom.begin(),
                            std::find(resdl_vtom.begin(), resdl_vtom.end(), macro_int)
                        )
                    );
            }
	    }
    }
}

































    namespace resdl_SDL_f_BlendMode {

        extern "C" CAMLprim value resdl_SDL_GetRenderDrawBlendMode(value v_renderer, value v_blendmode) {
            return Val_int(
                    SDL_GetRenderDrawBlendMode(
                        (SDL_Renderer*)v_renderer,
                        (SDL_BlendMode*)v_blendmode
                    )
                );
        }

        extern "C" CAMLprim value resdl_SDL_GetSurfaceBlendMode(value v_surface, value v_blendmode) {
            return Val_int(
                    SDL_GetSurfaceBlendMode(
                        (SDL_Surface*)v_surface,
                        (SDL_BlendMode*)v_blendmode
                    )
                );
        }

        extern "C" CAMLprim value resdl_SDL_GetTextureBlendMode(value v_texture, value v_blendmode){
            return Val_int(
                    SDL_GetTextureBlendMode(
                        (SDL_Texture*)v_texture,
                        (SDL_BlendMode*)v_blendmode
                    )
                );
        }
    }

    namespace resdl_SDL_Render {

        extern "C" CAMLprim value resdl_SDL_RenderCopy(
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
        extern "C" CAMLprim value resdl_SDL_GetError() {
            return caml_copy_string(SDL_GetError());
        }

        extern "C" CAMLprim value resdl_SDL_ClearError() {
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

    extern "C" CAMLprim value hello_sdl() {
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

    extern "C" CAMLprim value resdl_init_native(
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

    extern "C" CAMLprim value resdl_init_bytecode(value* argv, int argc)
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

    extern "C" CAMLprim value resdl_quit() {
        SDL_Quit();

        return Val_unit;
    }

    extern "C" CAMLprim value resdl_hello() {
        SDL_Init(SDL_INIT_VIDEO);
        SDL_Window* w = SDL_CreateWindow("demo", 0, 0, 500, 500, SDL_WINDOW_OPENGL);
        while(true)
        {
            SDL_Event event;
            printf("waiting on sdl event...\n");
            SDL_WaitEvent(&event);
            printf("got an event:\n");
            if( event.type == SDL_MOUSEWHEEL ) {
                printf("\tit was a mousewheel event\n");
            } else if ( event.type == SDL_FINGERMOTION ) {
                printf("\tit was a fingermotion event\n");
            } else if ( event.type == SDL_FINGERDOWN ) {
                printf("\tit was a fingerdown event\n");
            } else if ( event.type == SDL_QUIT ) {
                printf("\tquitting...\n");
                break;
            }
        }
        SDL_DestroyWindow(w);
        return Val_unit;
    }

    extern "C" CAMLprim value resdl_wasinit(value v_flags)
    {
        int i_flags = Int_val(v_flags);
        printf("flags was 0x%X -- note: UB if negative here, WasInit expects an unsigned int\n", i_flags);

        int r_flags = SDL_WasInit(i_flags);

        printf("returning 0x%X\n", r_flags);

        return Val_int(r_flags);
    }

//}

