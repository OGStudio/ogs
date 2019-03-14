FEATURE api.lua/Impl
setShaders = function(self, vertex, fragment)
    local key = "application.materials.material.setShaders"
    ENV:call(
        key,
        {
            self.__name,
            vertex,
            fragment
        }
    )
end,
