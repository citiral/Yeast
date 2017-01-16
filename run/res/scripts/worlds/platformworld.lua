--
-- Created by IntelliJ IDEA.
-- User: Olivier
-- Date: 16/01/17
-- Time: 14:02
-- To change this template use File | Settings | File Templates.
--

function spawnGround(x, y)
    local g = Entity()
    g:setRenderable(Sprite("grassMid_diffuse.png", "grassMid_normal.png"))

    g:setX(x * g:renderable():diffuse():width())
    g:setY(y * g:renderable():diffuse():height())

    local collider = BoxCollider(g:renderable():diffuse():width(), g:renderable():diffuse():height())
    g:setCollider(collider)
end

function begin()
    local l = AmbientLight(Color(1, 1, 1))
    engine:world():addLight(l)

    local background = Entity()
    background:setRenderable(Background("masonry-wall_diffuse.jpg", "masonry-wall_normal.jpg"))
    background:renderable():setScale(0.2)

    local player = Entity("player.lua")

    for x=5,5 do
        spawnGround(x,4)
    end
end

function update()
    if engine:window():keyIsPressed(Keys.R) then
        engine:loadWorld("worlds/platformworld.lua")
    end
end

function destroyed()

end