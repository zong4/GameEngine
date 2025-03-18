-- Packages Url
-- https://github.com/xmake-io/xmake-repo/tree/dev/packages/

-- Core
add_requires("spdlog")
add_requires("glm")

-- Platform
if is_plat("windows") then
    add_requires("glfw")
    add_requires("vulkansdk")
elseif is_plat("linux") then
    add_requires("glfw")
    add_requires("vulkansdk")
elseif is_plat("macosx") then
    add_requires("glfw")
    add_requires("glad")
end

-- Function
add_requires("imgui")

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
        add_packages("glfw", {public=true})
        add_packages("vulkansdk", {public=true})
    elseif is_plat("linux") then
        add_packages("glfw", {public=true})
        add_packages("vulkansdk", {public=true})
    elseif is_plat("macosx") then
        add_packages("glfw", {public=true})
        add_packages("glad", {public=true})
    end

    -- Function
    add_packages("imgui", {public=true})