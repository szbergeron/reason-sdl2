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

#define Val_none Val_int(0)
static value
Val_some( value v )
{   
    CAMLparam1( v );
    CAMLlocal1( some );
    some = caml_alloc(1, 0);
    Store_field( some, 0, v );
    CAMLreturn( some );
}

static value
Val_ok( value v )
{   
    CAMLparam1( v );
    CAMLlocal1( some );
    some = caml_alloc(1, 0);
    Store_field( some, 0, v );
    CAMLreturn( some );
}

static value
Val_error( value v )
{   
    CAMLparam1( v );
    CAMLlocal1( some );
    some = caml_alloc(1, 1);
    Store_field( some, 0, v );
    CAMLreturn( some );
}

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
        //SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

        SDL_CreateRenderer(
                win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);

         gladLoadGLES2Loader((GLADloadproc) SDL_GL_GetProcAddress);
    }

    CAMLprim value Val_SDL_Event(SDL_Event* event) {
        CAMLparam0();
        CAMLlocal2(ret, v);

        if (event == NULL) {
            ret = Val_none;
        } else {
            switch (event->type) {
            case SDL_QUIT:
               v = Val_int(0);
               ret = Val_some(v);
               break;
            case SDL_MOUSEMOTION:
                v = Val_int(1);
                ret = Val_some(v);
                break;
            default:
               ret = Val_none;
            }
        }

        CAMLreturn(ret);
    };

    CAMLprim value resdl_SDL_pollEvent() {
        CAMLparam0();
        CAMLlocal1(ret);
        SDL_Event e;

        caml_release_runtime_system();
        SDL_PollEvent(&e); 
        caml_acquire_runtime_system();
        ret = Val_SDL_Event(&e); 
        CAMLreturn(ret);
    }
    
    CAMLprim value resdl_SDL_GetWindowSize(value vWindow) {
        CAMLparam1(vWindow);
        CAMLlocal1(ret);
        SDL_Window *win = (SDL_Window *)vWindow;
        int width, height = 0;
        SDL_GetWindowSize(win, &width, &height);
        ret = caml_alloc(2, 0);
        Store_field(ret, 0, Val_int(width));
        Store_field(ret, 1, Val_int(height));
        printf("SDL_GetWindowSize - width: %d height: %d\n", width, height);
        CAMLreturn(ret);
    }
    
    CAMLprim value resdl_SDL_GL_GetDrawableSize(value vWindow) {
        CAMLparam1(vWindow);
        CAMLlocal1(ret);
        SDL_Window *win = (SDL_Window *)vWindow;
        int width, height = 0;
        SDL_GL_GetDrawableSize(win, &width, &height);
        ret = caml_alloc(2, 0);
        Store_field(ret, 0, Val_int(width));
        Store_field(ret, 1, Val_int(height));
        printf("SDL_GL_GetDrawableSize - width: %d height: %d\n", width, height);
        CAMLreturn(ret);
    }
    
    CAMLprim value resdl_SDL_SetWindowIcon(value vWindow, value vIcon) {
        CAMLparam2(vWindow, vIcon);    

        SDL_Window *win = (SDL_Window *)vWindow;
        SDL_Surface *surface = (SDL_Surface *)vIcon;
        SDL_SetWindowIcon(win, surface);

        CAMLreturn(Val_unit);
    };

    CAMLprim value resdl_SDL_CreateRGBSurfaceFromImage(value vPath) {
        CAMLparam1(vPath);
        CAMLlocal1(ret);
        // FROM: 
        // https://wiki.libsdl.org/SDL_CreateRGBSurfaceFrom

        int req_format = STBI_rgb_alpha;
        int width, height, orig_format;
        unsigned char* data = stbi_load(String_val(vPath), &width, &height, &orig_format, req_format);
        if(data == NULL) {
        
          ret = Val_error(caml_copy_string(stbi_failure_reason()));
        } else {

        // Set up the pixel format color masks for RGB(A) byte arrays.
        // Only STBI_rgb (3) and STBI_rgb_alpha (4) are supported here!
        Uint32 rmask, gmask, bmask, amask;
        #if SDL_BYTEORDER == SDL_BIG_ENDIAN
          int shift = (req_format == STBI_rgb) ? 8 : 0;
          rmask = 0xff000000 >> shift;
          gmask = 0x00ff0000 >> shift;
          bmask = 0x0000ff00 >> shift;
          amask = 0x000000ff >> shift;
        #else // little endian, like x86
          rmask = 0x000000ff;
          gmask = 0x0000ff00;
          bmask = 0x00ff0000;
          amask = (req_format == STBI_rgb) ? 0 : 0xff000000;
        #endif

        int depth, pitch;
        if (req_format == STBI_rgb) {
          depth = 24;
          pitch = 3*width; // 3 bytes per pixel * pixels per row
        } else { // STBI_rgb_alpha (RGBA)
          depth = 32;
          pitch = 4*width;
        }

        SDL_Surface* surf = SDL_CreateRGBSurfaceFrom((void*)data, width, height, depth, pitch,
                                                     rmask, gmask, bmask, amask);
        if (surf == NULL) {
            ret = Val_error(caml_copy_string(SDL_GetError()));
            stbi_image_free(data);
        } else {
            ret = Val_ok((value)surf);
        }
        }

        CAMLreturn(ret);
    };

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
                    SDL_Quit();
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
    
    CAMLprim value resdl_SDL_CreateWindow(value vWidth, value vHeight, value vName) {
        CAMLparam3(vWidth, vHeight, vName);

        int width = Int_val(vWidth);
        int height = Int_val(vHeight);
        printf("name: %s\n, WidtH: %d\n height: %d\n", String_val(vName), width, height);

          value vWindow = (value)(SDL_CreateWindow(String_val(vName), 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI));

        CAMLreturn(vWindow);
    }
        
        typedef enum PROCESS_DPI_AWARENESS {
            PROCESS_DPI_UNAWARE = 0,
            PROCESS_SYSTEM_DPI_AWARE = 1,
            PROCESS_PER_MONITOR_DPI_AWARE = 2
        } PROCESS_DPI_AWARENESS;

    CAMLprim value resdl_SDL_Init() {
        CAMLparam0();
        int ret = SDL_Init(SDL_INIT_VIDEO);

        /*printf("SDL_INIT");
        
        void* userDLL;
        BOOL(WINAPI *SetProcessDPIAware)(void); // Vista and later
        void* shcoreDLL;
        HRESULT(WINAPI *SetProcessDpiAwareness)(PROCESS_DPI_AWARENESS dpiAwareness); // Windows 8.1 and later
        INT(WINAPI *GetScaleFactorForDevice)(int deviceType);
        HRESULT(WINAPI *GetScaleFactorForMonitor)(HMONITOR hmon, int *pScale);

        userDLL = SDL_LoadObject("USER32.DLL");
        if (userDLL) {
            printf("Found user DLL!\n");
            SetProcessDPIAware = (BOOL(WINAPI *)(void)) SDL_LoadFunction(userDLL, "SetProcessDPIAware");
        }

        shcoreDLL = SDL_LoadObject("SHCORE.DLL");
        if (shcoreDLL) {
            printf("Found SHCOREd.ll!\n");
            SetProcessDpiAwareness = (HRESULT(WINAPI *)(PROCESS_DPI_AWARENESS)) SDL_LoadFunction(shcoreDLL, "SetProcessDpiAwareness");
            
            GetScaleFactorForDevice = (INT(WINAPI *)(INT)) SDL_LoadFunction(shcoreDLL, "GetScaleFactorForDevice");
            GetScaleFactorForMonitor = (HRESULT(WINAPI *)(HMONITOR, int*)) SDL_LoadFunction(shcoreDLL, "GetScaleFactorForMonitor");
        }

        if (GetScaleFactorForDevice) {
            printf("Found getScaleFactorForDevice!\n");

            int result = GetScaleFactorForDevice(0);
            printf("--RESULT: %d\n", result);
        }

        if (GetScaleFactorForMonitor) {
            printf("Found getScaleFactorForMonitor!!!\n");
        }

        if (SetProcessDpiAwareness) {
            // Try Windows 8.1+ version
            HRESULT result = SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);
            SDL_Log("called SetProcessDpiAwareness: %d", (result == S_OK) ? 1 : 0);
        }
        else if (SetProcessDPIAware) {
            // Try Vista - Windows 8 version.
            // This has a constant scale factor for all monitors.
            BOOL success = SetProcessDPIAware();
            SDL_Log("called SetProcessDPIAware: %d", (int)success);
        }*/
        
        CAMLreturn(Val_int(ret));
    }
  }

