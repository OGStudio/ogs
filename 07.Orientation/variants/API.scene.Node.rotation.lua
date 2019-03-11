FEATURE api.lua/Impl
do
    local shortKey = "rotation"
    local key = "application.nodes.node." .. shortKey
    propertiesMT:register(
        shortKey,
        function(self)
            local node = self.__name
            return ENV:call(key, {node})
        end,
        function(self, rotation)
            local node = self.__name
            ENV:call(
                key,
                {
                    node,
                    rotation[1],
                    rotation[2],
                    rotation[3],
                }
            )
        end
    )
end
