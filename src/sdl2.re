module Image = Image;
module Size = {
    type t = {
        width: int,
        height: int,
    };
};

module Surface = {
    type t;
    external createFromImagePath: (string) => result(t, string) = "resdl_SDL_CreateRGBSurfaceFromImage";
};

module Window = {
    type t;
    external create: (int, int, string) => t = "resdl_SDL_CreateWindow";
    external getSize: t => Size.t = "resdl_SDL_GetWindowSize";
    external setIcon: (t, Surface.t) => unit = "resdl_SDL_SetWindowIcon";
}

module OldGl = Gl;
module Gl = {
    external setup: Window.t => unit = "resdl_SDL_GL_Setup";
    external swapWindow: Window.t => unit = "resdl_SDL_GL_SwapWindow";
    external getDrawableSize: Window.t => Size.t = "resdl_SDL_GL_GetDrawableSize";
    include Gl;
};

external delay: int => unit = "resdl_SDL_Delay";
external init: unit => int = "resdl_SDL_Init";

module Event = {
    type t =
    | Quit
    | MouseMotion;

    let show = (v: t) => {
        switch (v) {
        | Quit => "Quit";
        | MouseMotion => "MouseMotion";
        }
    };
    
    external poll: unit => option(t) = "resdl_SDL_pollEvent";
};


module Key = {
    type t;
};

module MouseButton = {
    type t;
};
