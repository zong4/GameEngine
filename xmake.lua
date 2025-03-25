-- Define project
set_project("GameEngine")
set_xmakever("2.9.8")
set_version("1.0.0", {build = "%Y%m%d%H%M"})

-- Add platform informations
if is_plat("windows") then
	add_cxxflags("/utf-8") -- Fix spdlog error

    set_arch("x64")
elseif is_plat("linux") then
    set_arch("x86_64")
elseif is_plat("macosx") then
    set_arch("arm64")
end

-- Add global informations
set_languages("cxx20")
add_rules("plugin.compile_commands.autoupdate", {outputdir = ".vscode"})
add_defines("PROJECT_DIR=\"" .. os.projectdir():gsub("\\", "/") .. "\"")

-- Add mode informations
add_rules("mode.debug", "mode.release")
if is_mode("debug") then
    set_warnings("all", "error")
    add_defines("DEBUG")
elseif is_mode("release") then
    set_warnings("all")
    add_defines("RELEASE")
    set_optimize("fastest")
end

-- Includes sub-projects
includes("Engine")
includes("Editor")