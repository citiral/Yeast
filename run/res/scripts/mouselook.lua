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
    --engine:world():removeEntity(this)
    --t = Entity()
    v = Vector2()
    --print(v:x())
    --v2 = v
    v:setX(20)


    --print(v:add(v2):x())

    --print(tvec2:x())
end

function update()
    this:setPos(engine:window():mousePos())
    collectgarbage()
    --v2 = Vector2()

    --v2:setX(1)
    --v2:setY(2)
    --v = v:add(v2)

    --printVec(v)
end