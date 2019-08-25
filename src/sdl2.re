module Window = {
    type t;
}

module OldGl = Gl;
module Gl = {
    external setup: Window.t => unit = "resdl_SDL_GL_Setup";
    external swapWindow: Window.t => unit = "resdl_SDL_GL_SwapWindow";
    include Gl;
};

external createWindow: unit => Window.t = "resdl_SDL_CreateWindow";
external delay: int => unit = "resdl_SDL_Delay";
external init: unit => int = "resdl_SDL_Init";

