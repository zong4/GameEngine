-- Packages Url
-- https://github.com/xmake-io/xmake-repo/tree/dev/packages/

if is_plat("windows") then -- todo: DirectX12
    add_requires("glfw")
    add_requires("glad")
elseif is_plat("linux") then -- OpenGL
    add_requires("glfw")
    add_requires("glad")
elseif is_plat("macosx") then -- todo: Vulkan
    add_requires("glfw")
    add_requires("glad")
end

add_requires("stb")

add_requires("imgui docking", {configs = {glfw_opengl3 = true}})

target("Platform")
    set_kind("static")
    add_headerfiles("src/**.hpp")
    add_files("src/**.cpp")

    add_includedirs("src")
    add_includedirs("include", {public=true})

    add_deps("Core")
    
    if is_plat("windows") then
        add_packages("glfw")
        add_packages("glad")
    elseif is_plat("linux") then
        add_packages("glfw")
        add_packages("glad")
    elseif is_plat("macosx") then
        -- remove_files("**/**/OpenGL/**")

        add_packages("glfw")
        add_packages("glad")
    end

    add_packages("stb")

    add_packages("imgui", {public=true})