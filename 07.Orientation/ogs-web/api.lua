
--[[
This file is part of OGS: https://github.com/ogstudio/ogs

Copyright (C) 2019 Opensource Game Studio

This software is provided 'as-is', without any express or implied
warranty.  In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
--]]

core = {}

-- PropertiesMetatable allows to register property getters/setters dynamically.
function core.createPropertiesMetatable()
    local instance = {
        -- Register properties with callbacks.
        __callbacks = {},
        register = function(mtself, key, getter, setter)
            local callback = {}
            callback.getter = getter
            callback.setter = setter
            mtself.__callbacks[key] = callback
        end,

        -- Getter.
        __index = function(self, key)
            local mtself = getmetatable(self)
            local callback = mtself.__callbacks[key]
            if 
                callback and
                callback.getter
            then
                return callback.getter(self)
            end
            return nil
        end,

        -- Setter.
        __newindex = function(self, key, value)
            local mtself = getmetatable(self)
            local callback = mtself.__callbacks[key]
            if 
                callback and
                callback.setter
            then
                callback.setter(self, value)
            end
        end,
    }
    return instance
end
-- NOTE This is a core::Reporter (C++) implementation in Lua.
function core.createReporter()
    local instance = {
        -- Internal list of callbacks.
        __callbacks = {},

        -- Add a new callback.
        addCallback = function(self, callback, name)
            -- Work around callback reactivation happenning
            -- before `report()` call.
            if (self:__reactivateInactiveCallback(name))
            then
                return
            end
            local item = {
                callback = callback,
                name = name
            }
            table.insert(self.__callbacks, item)
        end,

        -- Internal list of one-time callbacks.
        __oneTimeCallbacks = {},

        -- Add a callback that is only executed once.
        addOneTimeCallback = function(self, callback)
            table.insert(self.__oneTimeCallbacks, callback)
        end,

        -- Internal list of callback names to remove later.
        __inactiveCallbackNames = {},

        removeCallback = function(self, name)
            -- This call only deactivates a callback for
            -- later removal that happens during next report() call.
            for _, callback in pairs(self.__callbacks)
            do
                if 
                    callback.name and
                    (callback.name == name)
                then
                    table.insert(self.__inactiveCallbackNames, name)
                end
            end
        end,

        report = function(self)
            self:__removeInactiveCallbacks()
            
            -- Call normal callbacks.
            for _, callback in pairs(self.__callbacks)
            do
                callback.callback()
            end

            -- Create a copy of the list of one-time callbacks.
            local oneTimeCallbacks = {table.unpack(self.__oneTimeCallbacks)}
            -- Remove one-time callbacks.
            self.__oneTimeCallbacks = {}
            -- Call one-time callbacks.
            for _, callback in pairs(oneTimeCallbacks)
            do
                callback()
            end
        end,

        __reactivateInactiveCallback = function(self, name)
            for id, callbackName in pairs(self.__inactiveCallbackNames)
            do
                if (callbackName == name)
                then
                    self.__inactiveCallbackNames[id] = nil
                    return true
                end
            end
            return false
        end,

        __removeInactiveCallbacks = function(self)
            -- Loop through the names of inactive callbacks.
            for _, name in pairs(self.__inactiveCallbackNames)
            do
                -- Loop through callbacks to find matching name.
                for id, callback in pairs(self.__callbacks)
                do
                    if 
                        callback.name and
                        (callback.name == name)
                    then
                        -- Remove matching callback.
                        self.__callbacks[id] = nil
                        break
                    end
                end
            end
            -- Clear the list of the names of inactive callbacks.
            self.__inactiveCallbackNames = {}
        end,
    }
    return instance
end

scene = {}

-- NOTE This is only a wrapper for a valid node at C++ side.
-- NOTE This does NOT create anything at C++ side.
function scene.createNode(name)
    local instance = {
        __name = name,

        addChild = function(self, node)
            local key = "application.nodes.node.addChild"
            local parent = self.__name
            local child = node.__name
            ENV:call(key, {parent, child})
        end,
        setMask = function(self, mask)
            local key = "application.nodes.node.setMask"
            local node = self.__name
            ENV:call(key, {node, mask})
        end,
    }

    local propertiesMT = core.createPropertiesMetatable()
    setmetatable(instance, propertiesMT)

do
    local shortKey = "position"
    local key = "application.nodes.node." .. shortKey
    propertiesMT:register(
        shortKey,
        function(self)
            local node = self.__name
            return ENV:call(key, {node})
        end,
        function(self, position)
            local node = self.__name
            ENV:call(
                key,
                {
                    node,
                    position[1],
                    position[2],
                    position[3],
                }
            )
        end
    )
end
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
    return instance
end

main = {}
main.application = {}

main.application.camera = {

    nodeAtPosition = function(self, position, selectionMask)
        local key = "application.camera.nodeAtPosition"
        local values = ENV:call(
            key,
            {
                position[1],
                position[2],
                selectionMask,
            }
        )
    
        local name = values[1]
    
        if (name)
        then
            return scene.createNode(name)
        end
    
        return nil
    end,
}

local cameraMT = core.createPropertiesMetatable()
setmetatable(main.application.camera, cameraMT)
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
do
    local shortKey = "rotation"
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

-- Create mouse.
main.application.mouse = {
    position = {},
    positionChanged = core.createReporter(),

    pressedButtons = {},
    pressedButtonsChanged = core.createReporter(),
}

-- Configure mouse.
do
    local mouse = main.application.mouse
    -- Create environment client.
    local client = EnvironmentClient.new()
    -- Define keys.
    local buttonsKey = "application.mouse.pressedButtons"
    local positionKey = "application.mouse.position"
    -- Define callback.
    client.call = function(key, values)
        if (key == buttonsKey)
        then
            mouse.pressedButtons = values
            mouse.pressedButtonsChanged:report()
        elseif (key == positionKey)
        then
            mouse.position = values
            mouse.positionChanged:report()
        end

        return {}
    end
    -- Register client.
    mouse.client = client
    ENV:addClient(
        mouse.client,
        {
            buttonsKey,
            positionKey
        }
    );
end

main.application.nodes = {}

function main.application.nodes.createSphere(self, name, radius)
    local key = "application.nodes.createSphere"
    ENV:call(key, {name, radius})
    return scene.createNode(name)
end
function main.application.nodes.node(self, name)
    local key = "application.nodes.node.exists"
    -- Find out if node exists in C++.
    local result = ENV:call(key, {name})
    -- Return nothing if node does not exist.
    if (not result[1]) then
        return nil
    end
    -- Return Lua node representation otherwise.
    return scene.createNode(name)
end

