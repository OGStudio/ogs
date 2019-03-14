FEATURE api.lua/Impl
setMaterial = function(self, material)
    local key = "application.nodes.node.setMaterial"
    local node = self.__name
    local params = {node}
    -- If material does not exist, it's a nil material.
    if (material)
    then
        table.insert(params, material.__name)
    end
    ENV:call(key, params)
end,
