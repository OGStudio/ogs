FEATURE api.lua/Impl
-- Define `application.camera.clearColor`.
do
    local shortKey = "clearColor"
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
