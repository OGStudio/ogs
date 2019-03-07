FEATURE api.lua/Impl
setMask = function(self, mask)
    local key = "application.nodes.node.setMask"
    local node = self.__name
    ENV:call(key, {node, mask})
end,
