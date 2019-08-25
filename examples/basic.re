open Sdl2;

external hello_sdl: unit => unit = "hello_sdl";

let run = () => {
  /*let _ = hello_sdl();*/
  let _ = Setup.resdl_init(~audio=true, ~video=true, ());

  //let _ = Status.resdl_wasinit(0);

  //let _ = Teardown.resdl_quit(());
};
