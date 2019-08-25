external test_red : Sdl2.Window.t => unit = "resdl_test_gl_red";
external test_green : Sdl2.Window.t => unit = "resdl_test_gl_green";
external test_blue : Sdl2.Window.t => unit = "resdl_test_gl_blue";
let run = () => {

  //let _ = Sdl2.init()
  let w = Sdl2.createWindow();
  let _ = Sdl2.Gl.setup(w);

  print_endline ("red")

  test_red(w);

  Sdl2.delay(2000);
  test_green(w);

  Sdl2.delay(2000);
  test_blue(w);
  
  Sdl2.delay(2000);

  print_endline ("DONE");

  //let _ = Status.resdl_wasinit(0);

  //let _ = Teardown.resdl_quit(());
};
