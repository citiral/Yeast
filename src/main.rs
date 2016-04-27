#![allow(dead_code)]
extern crate time;
extern crate glfw;

mod engine;
mod math;
mod sprite;
mod scene;
mod gl;

use engine::Engine;

fn main() {
    let mut engine = Engine::new();

    engine.start();
}
