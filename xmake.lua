-- define project
set_project("GameEngine")
set_xmakever("2.9.8")
set_version("1.0.0", {build = "%Y%m%d%H%M"})

-- set common flags
set_languages("cxx20")

-- add build modes
add_rules("mode.debug", "mode.release")
if is_mode("debug") then
    add_defines("DEBUG")
elseif is_mode("release") then
    add_defines("RELEASE")
end

if is_plat("windows") then
    add_defines("PLATFORM_WINDOWS")
elseif is_plat("linux") then
    add_defines("PLATFORM_LINUX")
elseif is_plat("macosx") then
    add_defines("PLATFORM_MACOS")
end

-- includes sub-projects
includes("Engine")
includes("Editor")