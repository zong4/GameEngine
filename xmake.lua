-- define project
set_project("GameEngine")
set_xmakever("2.9.8")
set_version("1.0.0", {build = "%Y%m%d%H%M"})

-- set common flags
set_languages("cxx20")
set_toolchains("clang")
set_warnings("all")

if is_plat("windows") then
    set_arch("x64") 
    add_defines("PLATFORM_WINDOWS")
elseif is_plat("linux") then
    set_arch("arm64")
    add_defines("PLATFORM_LINUX")
elseif is_plat("macosx") then
    set_arch("arm64")
    add_defines("PLATFORM_MACOSX")
end

-- add rules
add_rules("plugin.compile_commands.autoupdate", {outputdir = ".vscode"})

add_rules("mode.debug") -- todo: add release mode
if is_mode("debug") then
    add_defines("DEBUG")
elseif is_mode("release") then
    add_defines("RELEASE")
end

-- includes sub-projects
includes("Engine")
includes("Editor")