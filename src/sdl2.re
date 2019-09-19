module Image = Image;
module Size = {
  type t = {
    width: int,
    height: int,
  };
};

module Surface = {
  type t;
  external createFromImagePath: string => result(t, string) =
    "resdl_SDL_CreateRGBSurfaceFromImage";
};

module Window = {
  type t;
  external create: (int, int, string) => t = "resdl_SDL_CreateWindow";
  external getId: t => int = "resdl_SDL_GetWindowId";
  external getSize: t => Size.t = "resdl_SDL_GetWindowSize";
  external setIcon: (t, Surface.t) => unit = "resdl_SDL_SetWindowIcon";
  external setPosition: (t, int, int) => unit = "resdl_SDL_SetWindowPosition";

  external hide: t => unit = "resdl_SDL_HideWindow";
  external raise: t => unit = "resdl_SDL_RaiseWindow";
  external show: t => unit = "resdl_SDL_ShowWindow";

  external minimize: t => unit = "resdl_SDL_MinimizeWindow";
  external restore: t => unit = "resdl_SDL_RestoreWindow";
  external maximize: t => unit = "resdl_SDL_MaximizeWindow";
};

module OldGl = Gl;
module Gl = {
  external setup: Window.t => unit = "resdl_SDL_GL_Setup";
  external swapWindow: Window.t => unit = "resdl_SDL_GL_SwapWindow";
  external getDrawableSize: Window.t => Size.t =
    "resdl_SDL_GL_GetDrawableSize";
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

  let show = v =>
    switch (v) {
    | Left => "Left"
    | Middle => "Middle"
    | Right => "Right"
    | X1 => "X1"
    | X2 => "X2"
    };
};

module Scancode = {
  type t = int;

  external getName: t => string = "resdl_SDL_GetScancodeName";

  [@noalloc] external ofInt: int => t = "resdl_PassThrough";
  [@noalloc] external toInt: t => int = "resdl_PassThrough";

  // Incrementally add these as needed from:
  // https://wiki.libsdl.org/SDLScancodeLookup
  let unknown = 0;
};

module Keycode = {
  type t = int;

  external getName: t => string = "resdl_SDL_GetKeyName";

  [@noalloc]
  external ofScancode: Scancode.t => t = "resdl_SDL_GetKeyFromScancode";
  [@noalloc]
  external toScancode: t => Scancode.t = "resdl_SDL_GetScancodeFromKey";

  // Incrementally add these as needed from:
  // https://wiki.libsdl.org/SDLKeycodeLookup
  let unknown = 0;
  let backspace = 8;

  let escape = 27;

  let minus = 45;
  let period = 46;
  let slash = 47;

  let equals = 61;

  let digit0 = 48;
  let digit1 = 49;
  let digit2 = 50;
  let digit3 = 51;
  let digit4 = 52;
  let digit5 = 53;
  let digit6 = 54;
  let digit7 = 55;
  let digit8 = 56;
  let digit9 = 57;

  let c = 99;

  let delete = 127;

  let right = 1073741903;
  let left = 1073741904;
};

module Keymod = {
  type t = int;

  [@noalloc] external isLeftShiftDown: t => bool = "resdl_SDL_ModLeftShift";
  [@noalloc] external isRightShiftDown: t => bool = "resdl_SDL_ModRightShift";

  let isShiftDown = v => isLeftShiftDown(v) || isRightShiftDown(v);

  [@noalloc]
  external isLeftControlDown: t => bool = "resdl_SDL_ModLeftControl";
  [@noalloc]
  external isRightControlDown: t => bool = "resdl_SDL_ModRightControl";

  let isControlDown = v => isLeftControlDown(v) || isRightControlDown(v);

  [@noalloc] external isLeftAltDown: t => bool = "resdl_SDL_ModLeftAlt";
  [@noalloc] external isRightAltDown: t => bool = "resdl_SDL_ModRightAlt";

  let isAltDown = v => isLeftAltDown(v) || isRightAltDown(v);

  [@noalloc] external isLeftGuiDown: t => bool = "resdl_SDL_ModLeftGui";
  [@noalloc] external isRightGuiDown: t => bool = "resdl_SDL_ModRightGui";

  let isGuiDown = v => isLeftGuiDown(v) || isRightGuiDown(v);

  [@noalloc] external isNumLockDown: t => bool = "resdl_SDL_ModNumLockDown";
  [@noalloc] external isCapsLockDown: t => bool = "resdl_SDL_ModCapsLockDown";

  [@noalloc] external isAltGrKeyDown: t => bool = "resdl_SDL_ModAltGrDown";

  let show = (v: t) => {
    let int_of_bool = b => b ? 1 : 0;

    Printf.sprintf(
      "Keymods - LSHIFT: %d RSHIFT: %d LCTRL: %d RCTRL: %d LALT: %d RALT: %d LGUI: %d RGUI: %d NUM: %d CAPS: %d ALTGR: %d",
      int_of_bool(isLeftShiftDown(v)),
      int_of_bool(isRightShiftDown(v)),
      int_of_bool(isLeftControlDown(v)),
      int_of_bool(isRightControlDown(v)),
      int_of_bool(isLeftAltDown(v)),
      int_of_bool(isRightAltDown(v)),
      int_of_bool(isLeftGuiDown(v)),
      int_of_bool(isRightGuiDown(v)),
      int_of_bool(isNumLockDown(v)),
      int_of_bool(isCapsLockDown(v)),
      int_of_bool(isAltGrKeyDown(v)),
    );
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

  type keyboardEvent = {
    windowID: int,
    repeat: bool,
    keymod: Keymod.t,
    scancode: Scancode.t,
    keycode: Keycode.t,
  };

  type t =
    | Quit
    | MouseMotion(mouseMotion)
    | MouseWheel(mouseWheel)
    | MouseButtonDown(mouseButtonEvent)
    | MouseButtonUp(mouseButtonEvent)
    | KeyDown(keyboardEvent)
    | KeyUp(keyboardEvent);

  let show = (v: t) => {
    switch (v) {
    | Quit => "Quit"
    | MouseMotion({windowID, x, y}) =>
      Printf.sprintf("MouseMotion windowId: %d x: %d y: %d", windowID, x, y)
    | MouseWheel({windowID, deltaX, deltaY, isFlipped}) =>
      Printf.sprintf(
        "MouseWheel windowId: %d x: %d y: %d isFlipped: %d",
        windowID,
        deltaX,
        deltaY,
        isFlipped ? 1 : 0,
      )
    | MouseButtonUp({windowID, button, _}) =>
      Printf.sprintf(
        "MouseButtonUp windowId: %d button: %s",
        windowID,
        MouseButton.show(button),
      )
    | MouseButtonDown({windowID, button, _}) =>
      Printf.sprintf(
        "MouseButtonDown windowId: %d button: %s",
        windowID,
        MouseButton.show(button),
      )
    | KeyDown({repeat, keymod, scancode, keycode, _}) =>
      Printf.sprintf(
        "KeyDown repeat %d:\n -- %s\n -- Scancode: %s\n -- Keycode: %s\n",
        repeat ? 1 : 0,
        Keymod.show(keymod),
        Scancode.getName(scancode),
        Keycode.getName(keycode),
      )
    | KeyUp({repeat, keymod, scancode, keycode, _}) =>
      Printf.sprintf(
        "KeyUp repeat %d:\n -- %s\n -- Scancode: %s\n -- Keycode: %s\n",
        repeat ? 1 : 0,
        Keymod.show(keymod),
        Scancode.getName(scancode),
        Keycode.getName(keycode),
      )
    };
  };

  external poll: unit => option(t) = "resdl_SDL_pollEvent";
};

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
