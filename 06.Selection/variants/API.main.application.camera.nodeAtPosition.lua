FEATURE api.lua/Impl
nodeAtPosition = function(self, position, selectionMask)
    local key = "application.camera.nodeAtPosition"
    local values = ENV:call(
        key,
        {
            position[1],
            position[2],
            selectionMask,
        }
    )

    local name = values[1]

    if (name)
    then
        return scene.createNode(name)
    end

    return nil
end,
