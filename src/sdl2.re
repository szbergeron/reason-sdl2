module Window = {
    type t;
}

module Gl = {
    external setup: Window.t => unit = "resdl_SDL_GL_Setup";
};

external createWindow: unit => Window.t = "resdl_SDL_CreateWindow";
external delay: int => unit = "resdl_SDL_Delay";
external init: unit => int = "resdl_SDL_Init";

