external hello_sdl: unit => unit = "hello_sdl";
external resdl_init: (~audio: bool=false,
                      ~video: bool=true,
                      ~events: bool=true,
                      ~haptic: bool=false,
                      ~timer: bool=false,
                      ~gamecontroller: bool=false,
                      ~joystick: bool=false,
                      ~everything: bool=false)
        : int => "resdl_init";

external resdl_quit: (~audio: bool=false,
                      ~video: bool=true,
                      ~events: bool=true,
                      ~haptic: bool=false,
                      ~timer: bool=false,
                      ~gamecontroller: bool=false,
                      ~joystick: bool=false,
                      ~everything: bool=false)
        : int => "resdl_quit";

let run = () => {
  /*let _ = hello_sdl();*/
  let _ = resdl_init(~audio=false, ~video=true, ~events=true);
  let _ = resdl_quit(~audio=false, ~video=true, ~events=true);
  //let window = resdl_CreateWindow(
};
