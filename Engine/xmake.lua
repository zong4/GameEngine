-- Packages Url
-- https://github.com/xmake-io/xmake-repo/tree/dev/packages/

-- Core
add_requires("spdlog")
add_requires("glm")
add_requires("stb")

-- Platform
if is_plat("windows") then -- todo: DirectX12
    add_requires("glfw")
    add_requires("glad")
elseif is_plat("linux") then -- OpenGL
    add_requires("glfw")
    add_requires("glad")
elseif is_plat("macosx") or is_plat("iphoneos") then -- Vulkan
    add_requires("glfw")
    add_requires("glad")
end

-- Functions
add_requires("imgui docking", {configs = {glfw_opengl3 = true}})

target("Engine")
    set_kind("static")

    set_pcxxheader("src/EnginePCH.hpp")
    add_headerfiles("src/**.hpp")
    add_files("src/**.cpp")

    add_includedirs("src", {public=true})
    add_includedirs("include", {public=true})

    -- Core
    add_packages("spdlog", {public=true})
    add_packages("glm", {public=true})
    
    -- Platform
    if is_plat("windows") then
        add_packages("glfw", {private=true})
        add_packages("glad", {private=true})
        add_packages("stb", {private=true})
    elseif is_plat("linux") then
        add_packages("glfw", {private=true})
        add_packages("glad", {private=true})
        add_packages("stb", {private=true})
    elseif is_plat("macosx") or is_plat("iphoneos") then
        -- remove_files("**/**/OpenGL/**")

        add_packages("glfw", {private=true})
        add_packages("glad", {private=true})
        add_packages("stb", {private=true})
    end

    -- Functions
    add_packages("imgui", {public=true})