module setup = {
  external resdl_internal_init: (
                    bool,
                    bool,
                    bool,
                    bool,
                    bool,
                    bool,
                    bool,
                    bool) => int = "resdl_init_bytecode"
                                   "resdl_init_native";

  let resdl_init = (~audio: bool=false,
                    ~video: bool=true,
                    ~events: bool=true,
                    ~haptic: bool=false,
                    ~timer: bool=false,
                    ~gamecontroller: bool=false,
                    ~joystick: bool=false,
                    ~everything: bool=false,
                    ()) : int => {

      let ret:int = resdl_internal_init(audio, video, events, haptic, timer, gamecontroller, joystick, everything);

      ret
  }

  external resdl_setMainReady: unit => unit = "resdl_SDL_SetMainReady();
}

module teardown = {
  external resdl_quit: unit => unit = "resdl_quit";
}

module status = {
  external resdl_wasinit: int => int = "resdl_wasinit";
}

module windowing = {
  external resdl_SDL_CreateWindow: (
                    ~window_title: String,
                    ~x_window_position: int,
                    ~y_window_position: int,
                    ~window_width: int,
                    ~window_height: int,
                    ~SDL_WindowFlags: int
                    ) : SDL_Window
}

