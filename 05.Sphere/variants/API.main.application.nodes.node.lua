FEATURE api.lua/Impl
function main.application.nodes.node(self, name)
    local key = "application.nodes.node.exists"
    -- Find out if node exists in C++.
    local result = ENV:call(key, {name})
    -- Return nothing if node does not exist.
    if (not result[1]) then
        return nil
    end
    -- Return Lua node representation otherwise.
    return scene.createNode(name)
end
