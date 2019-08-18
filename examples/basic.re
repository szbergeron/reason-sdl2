external hello_sdl: unit => unit = "hello_sdl";

external resdl_internal_init: (
                  ~audio: bool,
                  ~video: bool,
                  ~events: bool,
                  ~haptic: bool,
                  ~timer: bool,
                  ~gamecontroller: bool,
                  ~joystick: bool,
                  ~everything: bool) => int = "resdl_init";

let resdl_init = (~audio: bool=false,
                  ~video: bool=true,
                  ~events: bool=true,
                  ~haptic: bool=false,
                  ~timer: bool=false,
                  ~gamecontroller: bool=false,
                  ~joystick: bool=false,
                  ~everything: bool=false) : int => {

    let ret:int = resdl_internal_init(audio, video, events, haptic, timer, gamecontroller, joystick, everything);

    ret
}

external resdl_quit: unit => unit = "resdl_quit";

let run = () => {
  /*let _ = hello_sdl();*/
  let _ = resdl_init(~audio=false, ~video=true, ~events=true);
  let _ = resdl_quit(~audio=false, ~video=true, ~events=true);
};
