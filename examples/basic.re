external pollEvent: unit => unit = "resdl_test_poll";

let run = () => {

  let _ = Sdl2.init()
  let w = Sdl2.Window.create(640, 480, "example");
  let _ = Sdl2.Gl.setup(w);

  let { width, height }: Sdl2.Size.t = Sdl2.Window.getSize(w);
  Printf.printf("Width: %d height: %d\n", width, height);
  
  let { width, height }: Sdl2.Size.t = Sdl2.Gl.getDrawableSize(w);
  Printf.printf("Width: %d height: %d\n", width, height);

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
