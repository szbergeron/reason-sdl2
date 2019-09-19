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
    external getId: t => int = "resdl_SDL_GetWindowId";
    external getSize: t => Size.t = "resdl_SDL_GetWindowSize";
    external setIcon: (t, Surface.t) => unit = "resdl_SDL_SetWindowIcon";
    external setPosition: (t, int, int) => unit = "resdl_SDL_SetWindowPosition";

    external hide: (t) => unit = "resdl_SDL_HideWindow";
    external raise: (t) => unit = "resdl_SDL_RaiseWindow";
    external show: (t) => unit = "resdl_SDL_ShowWindow";

    external minimize: (t) => unit = "resdl_SDL_MinimizeWindow";
    external restore: (t) => unit = "resdl_SDL_RestoreWindow";
    external maximize: (t) => unit = "resdl_SDL_MaximizeWindow";
}

module OldGl = Gl;
module Gl = {
    external setup: Window.t => unit = "resdl_SDL_GL_Setup";
    external swapWindow: Window.t => unit = "resdl_SDL_GL_SwapWindow";
    external getDrawableSize: Window.t => Size.t = "resdl_SDL_GL_GetDrawableSize";
    include OldGl;
};

external delay: int => unit = "resdl_SDL_Delay";
external init: unit => int = "resdl_SDL_Init";

module MouseButton = {
    type t =
    | Left
    | Middle
    | Right
    | X1
    | X2;

    let show = (v) => switch (v) {
    | Left => "Left"
    | Middle => "Middle"
    | Right => "Right"
    | X1 => "X1"
    | X2 => "X2"
    };
};


module Event = {

    type mouseMotion = {
        windowID: int,
        x: int,
        y: int,
    };

    type mouseWheel = {
        windowID: int,
        deltaX: int,
        deltaY: int,
        isFlipped: bool,
    };

    type mouseButtonEvent = {
        windowID: int,
        button: MouseButton.t,
        clicks: int,
        x: int,
        y: int,
    };

    type t =
    | Quit
    | MouseMotion(mouseMotion)
    | MouseWheel(mouseWheel)
    | MouseButtonDown(mouseButtonEvent)
    | MouseButtonUp(mouseButtonEvent);

    let show = (v: t) => {
        switch (v) {
        | Quit => "Quit";
        | MouseMotion({windowID, x, y}) => Printf.sprintf("MouseMotion windowId: %d x: %d y: %d", windowID, x, y);
        | MouseWheel({windowID, deltaX, deltaY, isFlipped}) => Printf.sprintf("MouseWheel windowId: %d x: %d y: %d isFlipped: %d", windowID, deltaX, deltaY, isFlipped ? 1 : 0);
        | MouseButtonUp({windowID, button, _}) =>
            Printf.sprintf("MouseButtonUp windowId: %d button: %s", windowID, MouseButton.show(button));
        | MouseButtonDown({windowID, button, _}) =>
            Printf.sprintf("MouseButtonDown windowId: %d button: %s", windowID, MouseButton.show(button));
        }
    };
    
    external poll: unit => option(t) = "resdl_SDL_pollEvent";
};

Printexc.record_backtrace(true);

module Cursor = {

    type systemCursor = 
    | Arrow
    | IBeam
    | Wait
    | Crosshair
    | WaitArrow
    | SizeNWSE
    | SizeNESW
    | SizeWE
    | SizeNS
    | SizeAll
    | No
    | Hand;

    type t;

    external createSystem: systemCursor => t = "resdl_SDL_CreateSystemCursor";
    external setCursor: t => unit = "resdl_SDL_SetCursor";
};

module Key = {
    type t;
};
