FEATURE api.lua/Impl
function main.application.materials.createMaterial(self, name)
    local key = "application.materials.createMaterial"
    ENV:call(key, {name})
    return render.createMaterial(name)
end
