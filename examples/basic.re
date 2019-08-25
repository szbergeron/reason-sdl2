external pollEvent: unit => unit = "resdl_test_poll";

let run = () => {

  //let _ = Sdl2.init()
  let w = Sdl2.createWindow();
  let _ = Sdl2.Gl.setup(w);

  print_endline ("red")

 /* Sdl2.Gl.glClearColor(1.0, 0.0, 0.0, 1.0);
  Sdl2.Gl.swapWindow(w);

  Sdl2.delay(2000);
  Sdl2.Gl.glClearColor(0.0, 1.0, 0.0, 1.0);
  Sdl2.Gl.swapWindow(w);

  Sdl2.delay(2000);*/
  
  Sdl2.Gl.glClearColor(0.0, 0.0, 1.0, 1.0);
  Sdl2.Gl.swapWindow(w);

  pollEvent();
  
  
  Sdl2.delay(2000);

  print_endline ("DONE");

  //let _ = Status.resdl_wasinit(0);

  //let _ = Teardown.resdl_quit(());
};
