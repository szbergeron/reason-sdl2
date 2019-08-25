module Setup = Sdl_external_functions.Setup;
module Status = Sdl_external_functions.Status;
module Teardown = Sdl_external_functions.Teardown;

module Window = {
    type t;
}

external createWindow: unit => Window.t = "resdl_SDL_createWindow";
external init: unit => int = "resdl_SDL_init";

