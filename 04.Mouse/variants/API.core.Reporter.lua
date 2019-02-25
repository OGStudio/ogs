FEATURE api.lua/Impl
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
