--
-- Created by IntelliJ IDEA.
-- User: Olivier
-- Date: 03/11/16
-- Time: 23:17
-- To change this template use File | Settings | File Templates.
--


function begin()
    print("Testworld has been created!")

    local l = AmbientLight(Color(1, 1, 1))
    engine:world():addLight(l)

    local background = Entity()
    background:setRenderable(Background("masonry-wall_diffuse.jpg", "masonry-wall_normal.jpg"))
    background:renderable():setScale(0.2)

    local player = Entity("player.lua")
end

function update()
end