external hello_sdl: unit => unit = "hello_sdl";

let run = () => {
  /*let _ = hello_sdl();*/
  let _ = resdl_init(~audio=true, ~video=true, ());

  let _ = resdl_wasinit(0);

  let _ = resdl_quit(());
};
