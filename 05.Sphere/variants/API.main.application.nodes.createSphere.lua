FEATURE api.lua/Impl
function main.application.nodes.createSphere(self, name, radius)
    local key = "application.nodes.createSphere"
    ENV:call(key, {name, radius})
    return scene.createNode(name)
end
