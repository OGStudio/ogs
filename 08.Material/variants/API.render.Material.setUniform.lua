FEATURE api.lua/Impl
setUniform = function(self, name, rawValue)
    local key = "application.materials.material.setUniform"
    local params = {self.__name, name}
    -- Array.
    if (type(rawValue) == "table")
    then
        for _, value in pairs(rawValue)
        do
            table.insert(params, value)
        end
    -- Single value.
    else
        table.insert(params, rawValue)
    end

    ENV:call(key, params)
end,
