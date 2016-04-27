use sprite::Sprite;

pub struct Scene {
        sprites: Vec<Sprite>,
}

impl Scene {
    pub fn new() -> Scene {
        Scene {
            sprites: Vec::new(),
        }
    }
}
