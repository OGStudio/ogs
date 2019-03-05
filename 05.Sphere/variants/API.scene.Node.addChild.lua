FEATURE api.lua/Impl
addChild = function(self, node)
    local key = "application.nodes.node.addChild"
    local parent = self.__name
    local child = node.__name
    ENV:call(key, {parent, child})
end,
