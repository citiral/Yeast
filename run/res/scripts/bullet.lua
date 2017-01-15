--
-- Created by IntelliJ IDEA.
-- User: Citiral
-- Date: 2/07/2016
-- Time: 18:57
--

speed = 50
l = nil
rot = nil

function init(pos, rotation)
    this:setPos(pos)
    rot = rotation
end

function added()
    l = PointLight(Color(1, 0.5, 0)*10, Vector2(this:x(), this:y()), 4, 4, 20)
    engine:world():addLight(l)
end

function update()
    this:setX(this:x() + math.cos(rot) * speed * deltatime)
    this:setY(this:y() - math.sin(rot) * speed * deltatime)

    l:setPos(this:pos())
    checkoob()
end

function destroyed()
    engine:world():removeLight(l)
end

function checkoob()
    if      this:x() < 0 or
            this:y() < 0 or
            this:x() > engine:window():width() or
            this:y() > engine:window():height() then
        this:destroy()
    end
end