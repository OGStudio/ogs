FEATURE api.lua/Methods
-- NOTE This is only a wrapper for a valid node at C++ side.
-- NOTE This does NOT create anything at C++ side.
function scene.createNode(name)
    local instance = {
        __name = name,

FEATURE api.lua/Properties
    }

    local propertiesMT = core.createPropertiesMetatable()
    setmetatable(instance, propertiesMT)

FEATURE api.lua/End
    return instance
end
