-- Core
add_requires("spdlog")
add_requires("glfw")

-- -- Renderer
-- if is_plat("windows") then
--     add_requires("vulkan")
-- elseif is_plat("linux") then
--     add_requires("vulkan")
-- elseif is_plat("macosx") then
--     add_requires("vulkan")
-- end

target("Engine")
    set_kind("shared")
    add_files("src/**.cpp")
    add_headerfiles("src/**.hpp")

    add_includedirs("include", {public=true})

    -- Core
    add_packages("spdlog", {public=true})
    add_packages("glfw", {public=true})

    -- Renderer
    if is_plat("windows") then
        add_defines("PLATFORM_WINDOWS")
        -- add_packages("vulkan", {public=true})
    elseif is_plat("linux") then
        add_defines("PLATFORM_LINUX")
        -- add_packages("vulkan", {public=true})
    elseif is_plat("macosx") then
        add_defines("PLATFORM_MACOSX")
        -- add_packages("vulkan", {public=true})
    end
