--
-- Created by IntelliJ IDEA.
-- User: Citiral
-- Date: 2/07/2016
-- Time: 18:57
--

speed = 500
shoottimer = 0
shoottimermax = 0.01

function printVec(v)
    print("("..v:x()..", "..v:y()..")")
end

function added()
    -- center the sprite
    print(Types[this:renderable()._type])
    this:renderable():centerOrigin()
end

function update()
    -- mouselook
    local diff = engine:window():mousePos() - this:pos()
    this:setRotation(math.atan2(-diff:y(), diff:x()))

    -- movement
    if engine:window():keyIsDown(Keys.D) == true then this:setX(this:x() + speed * deltatime) end
    if engine:window():keyIsDown(Keys.A) == true then this:setX(this:x() - speed * deltatime) end
    if engine:window():keyIsDown(Keys.W) == true then this:setY(this:y() + speed * deltatime) end
    if engine:window():keyIsDown(Keys.S) == true then this:setY(this:y() - speed * deltatime) end

    -- firing
    if engine:window():buttonIsDown(Buttons.mouse1) then
        shoottimer = shoottimer - deltatime
        while shoottimer <= 0 do
            local bullet = Entity("bullet", this:x(), this:y())
            local diff = engine:window():mousePos() - this:pos()
            bullet:getScript("bullet.lua"):lua().init(this:pos(), math.atan2(-diff:y(), diff:x()))
            shoottimer = shoottimer + shoottimermax
        end
    end
end

function destroyed()
    print("rip")
end