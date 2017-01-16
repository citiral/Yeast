--
-- Created by IntelliJ IDEA.
-- User: Citiral
-- Date: 2/07/2016
-- Time: 18:57
--

xspeed = 0
yspeed = 0
speed = 500
shoottimer = 0
shoottimermax = 0.01

gravity = -9.81

function printVec(v)
    print("("..v:x()..", "..v:y()..")")
end

function onMoveCollideX(e, amount)
    this:setX(this:x() + amount)
end

function onMoveCollideY(e, amount)
    this:setY(this:y() + amount)
end

function added()
    this:setX(100)
    this:setY(100)
    local b = Sprite("sprite_diffuse.png", "sprite_normal.png")
    this:setRenderable(b)
    -- center the sprite

    this:renderable():centerOrigin()

    local collider = BoxCollider(this:renderable():diffuse():width(), this:renderable():diffuse():height())
    this:setCollider(collider)
    collider:centerOrigin()
end

function update()
    -- mouselook
    local diff = engine:window():mousePos() - this:pos()
    this:setRotation(math.atan2(-diff:y(), diff:x()))

    -- movement
    if engine:window():keyIsDown(Keys.D) == true then this:move( speed * deltatime, 0) end
    if engine:window():keyIsDown(Keys.A) == true then this:move(-speed * deltatime, 0) end
    if engine:window():keyIsDown(Keys.W) == true then this:move(0,  speed * deltatime) end
    if engine:window():keyIsDown(Keys.S) == true then this:move(0, -speed * deltatime) end

    -- firing
    if engine:window():buttonIsPressed(Buttons.mouse1) then
        shoottimer = shoottimer - deltatime
        while shoottimer <= 0 do
            local bullet = Entity("bullet.lua")
            --bullet:setPos(this:x(), this:y())
            local diff = engine:window():mousePos() - this:pos()
            bullet:getScript("bullet.lua"):lua().init(this:pos(), math.atan2(-diff:y(), diff:x()))
            shoottimer = shoottimer + shoottimermax
        end
    end
end

function destroyed()
    print("rip")
end