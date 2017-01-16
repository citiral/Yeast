--
-- Created by IntelliJ IDEA.
-- User: Citiral
-- Date: 2/07/2016
-- Time: 18:57
--

xspeed = 0
yspeed = 0

xaccel = 800*9
jumpspeed = 1000

xmaxspeed = 700

xdeaccel = 800*4
ydeaccel = -2081

shoottimer = 0
shoottimermax = 0.01

jumped = true

function printVec(v)
    print("("..v:x()..", "..v:y()..")")
end

function onMoveCollideX(e, amount)
    this:setX(this:x() + amount)
    xspeed = 0
end

function onMoveCollideY(e, amount)
    this:setY(this:y() + amount)

    yspeed = 0

    if amount > 0 then
        jumped = false
    end
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
    -- movement
    if engine:window():keyIsDown(Keys.D) == true then
        xspeed = xspeed + xaccel * deltatime
    end

    if engine:window():keyIsDown(Keys.A) == true then
        xspeed = xspeed - xaccel * deltatime
    end

    if math.abs(xspeed) > xmaxspeed then
        if xspeed < 0 then xspeed = -xmaxspeed else xspeed = xmaxspeed end
    end

    if jumped == false and engine:window():keyIsPressed(Keys.W) then
        yspeed = jumpspeed
        jumped = true
    end

    -- deaccel
    if math.abs(xspeed) < xdeaccel * deltatime then
        xspeed = 0
    elseif xspeed > 0 then
        xspeed = xspeed - xdeaccel * deltatime
    else
        xspeed = xspeed + xdeaccel * deltatime
    end

    yspeed = yspeed + ydeaccel * deltatime



    this:move(xspeed * deltatime, yspeed * deltatime)

    --if engine:window():keyIsDown(Keys.W) == true then this:move(0,  speed * deltatime) end
    --if engine:window():keyIsDown(Keys.S) == true then this:move(0, -speed * deltatime) end

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
end