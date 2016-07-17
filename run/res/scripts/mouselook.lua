--
-- Created by IntelliJ IDEA.
-- User: Citiral
-- Date: 2/07/2016
-- Time: 18:57
--

function printVec(v)
    print("("..v:x()..", "..v:y()..")")
end

function added()
    -- center the sprite
    this:renderable():centerOrigin()
end

function update()
    -- mouselook
    local diff = engine:window():mousePos() - this:pos()
    this:setRotation(math.atan2(-diff:y(), diff:x()))

    -- movement
    if engine:window():keyIsDown(Keys.D) == true then this:setX(this:x() + 10) end
    if engine:window():keyIsDown(Keys.A) == true then this:setX(this:x() - 10) end
    if engine:window():keyIsDown(Keys.W) == true then this:setY(this:y() + 10) end
    if engine:window():keyIsDown(Keys.S) == true then this:setY(this:y() - 10) end

    -- firing
    if engine:window():buttonIsPressed(Buttons.mouse1) then
        print("pang!")
    end
end