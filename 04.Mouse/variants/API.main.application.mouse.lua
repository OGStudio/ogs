FEATURE api.lua/Impl
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
