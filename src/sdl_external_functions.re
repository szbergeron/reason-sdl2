
open Sdl_types;

module Windowing = {
  // TODO: figure out how we want to handle flags here.
  // note: doing a bitwise or on a [value] and then converting to
  // an int should be identical to the bitwise or on the C/++ uint32 type for this case
  external resdl_SDL_CreateWindow: (
    ~window_title: string,
    ~x_window_position: int,
    ~y_window_position: int,
    ~window_width: int,
    ~window_height: int,
    ~windowFlags: int
  ) => Resdl_t_windowing.window = "resdl_SDL_CreateWindow_bytecode"
                                  "resdl_SDL_CreateWindow";

  external resdl_SDL_DestroyWindow: Resdl_t_windowing.window => unit = "resdl_SDL_DestroyWindow";
}

