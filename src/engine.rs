use glfw;
use glfw::{Context, Key, Action};
use std::sync::mpsc::Receiver;
use scene::Scene;
use gl;
use gl::types::*;

pub struct Window {
    glfw: glfw::Glfw,
    window: glfw::Window,
    events: Receiver<(f64, glfw::WindowEvent)>,
}

pub struct Engine {
    window: Window,
    scene: Scene,
}

impl Window {
    pub fn new() -> Window {
        let mut glfw = glfw::init(glfw::FAIL_ON_ERRORS).unwrap();
        let (mut window, events) = glfw.create_window(300, 300, "Yeast", glfw::WindowMode::Windowed).expect("Failed to create GLFW window.");

        window.set_key_polling(true);
        window.make_current();
        glfw.set_swap_interval(1);

        gl::load_with(|s| window.get_proc_address(s) as *const _);

        Window {
            glfw: glfw,
            window: window,
            events: events,
        }
    }

    pub fn handle_window_events(&mut self) {
        self.glfw.poll_events();
        for (_, event) in glfw::flush_messages(&self.events) {
            match event {
                glfw::WindowEvent::Key(Key::Escape, _, Action::Press, _) => {
                    self.window.set_should_close(true)
                }
                _ => {

                }
            }
        }
    }

    pub fn swap_buffers(&mut self) {
        self.window.swap_buffers();
    }

    pub fn should_close(&self) -> bool {
        self.window.should_close()
    }
}

impl Engine {
    pub fn new() -> Engine {
        Engine {
            window: Window::new(),
            scene: Scene::new(),
        }
    }

    pub fn start(&mut self) {
        while !self.window.should_close() {
            //TODO proper game loop
            self.window.handle_window_events();
            self.step_logic();
            self.step_physics();
            self.step_render();
        }
    }

    fn step_logic(&mut self) {

    }

    fn step_physics(&mut self) {

    }

    fn step_render(&mut self) {
        unsafe {
            gl::ClearColor(0.3, 0.3, 0.3, 1.0);
            gl::Clear(gl::COLOR_BUFFER_BIT);
        }
        self.window.swap_buffers();
    }

    pub fn step(&mut self) {

    }
}
