FEATURE api.lua/Impl
function main.application.nodes.createNode(self, name)
    local key = "application.nodes.createNode"
    ENV:call(key, {name})
    return scene.createNode(name)
end
