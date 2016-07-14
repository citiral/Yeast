--
-- Created by IntelliJ IDEA.
-- User: Citiral
-- Date: 2/07/2016
-- Time: 18:57
-- To change this template use File | Settings | File Templates.
--



function printVec(v)
    print("("..v:x()..", "..v:y()..")")
end

function added()
    v = Vector2()
    --print(v:x())
    --v2 = v
    v:setX(20)


    --print(v:add(v2):x())

    --print(tvec2:x())
end

function update()

    v2 = Vector2()

    v2:setX(1)
    v2:setY(2)
    v = v:add(v2)

    printVec(v)
end