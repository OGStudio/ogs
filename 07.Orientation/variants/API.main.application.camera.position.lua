FEATURE api.lua/Impl
do
    local shortKey = "position"
    local key = "application.camera." .. shortKey
    cameraMT:register(
        shortKey,
        function(self)
            return ENV:call(key, {})
        end,
        function(self, value)
            ENV:call(key, value)
        end
    )
end
