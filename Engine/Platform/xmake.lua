-- Packages Url
-- https://github.com/xmake-io/xmake-repo/tree/dev/packages/

if is_plat("windows") then -- todo: DirectX12
    add_requires("glfw")
    add_requires("glad")
elseif is_plat("linux") then
    add_requires("glfw")
    add_requires("glad")
elseif is_plat("macosx") then
    add_requires("glfw")
    add_requires("glad")
    add_requires("vulkansdk")
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

    before_build("macosx", function (target)
        print("Running setup_vulkan.sh before build Platform on macOS")
        os.runv("zsh", {"./scripts/setup_vulkan.sh"})
    end)
    
    if is_plat("windows") then
        remove_files("**/**/Vulkan/**")

        add_packages("glfw")
        add_packages("glad")
    elseif is_plat("linux") then
        add_packages("glfw")
        add_packages("glad")
    elseif is_plat("macosx") then
        -- remove_files("**/**/OpenGL/**")

        add_packages("glfw")
        add_packages("glad")
        add_packages("vulkansdk")
    end

    add_packages("stb")

    add_packages("imgui", {public=true})