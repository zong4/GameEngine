-- Packages Url
-- https://github.com/xmake-io/xmake-repo/tree/dev/packages/

if is_plat("windows") then
    add_requires("glfw")
    add_requires("glad")
    add_requires("stb")
elseif is_plat("linux") then
    add_requires("glfw")
    add_requires("glad")
    add_requires("stb")
elseif is_plat("macosx") then
    add_requires("glfw")
    add_requires("glad")
    add_requires("stb")
    add_requires("bgfx")
end

add_requires("imgui docking", {configs = {glfw_opengl3 = true}})

target("Platform")
    set_kind("static")
    add_headerfiles("src/**.hpp")
    add_files("src/**.cpp")

    add_includedirs("src")
    add_includedirs("include", {public=true})

    add_deps("Core")
    
    if is_plat("windows") then
        remove_files("**/Vulkan/**.cpp")
        remove_files("**/BGFX/**.cpp")

        add_packages("glfw")
        add_packages("glad")
        add_packages("stb")
    elseif is_plat("linux") then
        remove_files("**/BGFX/**.cpp")

        add_packages("glfw")
        add_packages("glad")
        add_packages("stb")
    elseif is_plat("macosx") then
        remove_files("**/Vulkan/**.cpp")

        add_packages("glfw")
        add_packages("glad")
        add_packages("stb")

        add_packages("bgfx")
    end

    add_packages("imgui", {public=true})