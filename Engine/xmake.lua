-- Packages Url
-- https://github.com/xmake-io/xmake-repo/tree/dev/packages/

-- Platform
if is_plat("windows") then -- todo: DirectX12
    add_requires("glfw")
    add_requires("glad")
elseif is_plat("linux") then -- OpenGL
    add_requires("glfw")
    add_requires("glad")
elseif is_plat("macosx") then -- Vulkan
    add_requires("glfw")
    add_requires("glad")
end

-- Core
add_requires("spdlog")
add_requires("glm")
add_requires("tracy")

-- Functions
add_requires("stb")
add_requires("imgui docking", {configs = {glfw_opengl3 = true}})

target("Engine")
    set_kind("static")
    set_pcxxheader("src/EnginePCH.hpp")
    add_headerfiles("src/**.hpp")
    add_files("src/**.cpp")
    add_includedirs("src", {public=true})
    add_includedirs("include", {public=true})
    add_includedirs("assets")
    
    -- Platform
    if is_plat("windows") then
        add_packages("glfw", {private=true})
        add_packages("glad", {private=true})
    elseif is_plat("linux") then
        add_packages("glfw", {private=true})
        add_packages("glad", {private=true})
    elseif is_plat("macosx") or is_plat("iphoneos") then
        -- remove_files("**/**/OpenGL/**")

        add_packages("glfw", {private=true})
        add_packages("glad", {private=true})
    end

    -- Core
    add_packages("spdlog", {public=true})
    add_packages("glm", {public=true})
    
    add_packages("tracy", { public = true })
    add_defines("TRACY_ENABLE")
    if is_plat("windows") then
        add_links("ws2_32")
    end

    -- Functions
    add_packages("stb", {private=true})
    add_packages("imgui", {public=true})