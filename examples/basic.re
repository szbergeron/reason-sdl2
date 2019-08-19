external hello_sdl: unit => unit = "hello_sdl";

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

external resdl_quit: unit => unit = "resdl_quit";

external resdl_wasinit: int => int = "resdl_wasinit";

let run = () => {
  /*let _ = hello_sdl();*/
  let _ = resdl_init(~audio=true, ~video=true, ());

  let _ = resdl_wasinit(0);

  let _ = resdl_quit(());
};
