-- define project
set_project("GameEngine")
set_xmakever("2.9.8")
set_version("1.0.0", {build = "%Y%m%d%H%M"})

-- add global informations
set_languages("cxx20")
add_rules("plugin.compile_commands.autoupdate", {outputdir = ".vscode"})
add_defines("PROJECT_DIR=\"" .. os.projectdir():gsub("\\", "/") .. "\"")

-- add mode informations
add_rules("mode.debug", "mode.release")
if is_mode("debug") then
    -- set_warnings("all", "error")
    set_warnings("all")
    add_defines("DEBUG")
elseif is_mode("release") then
    set_warnings("all")
    add_defines("RELEASE")
    set_optimize("fastest")
end

-- add platform informations
if is_plat("windows") then
    add_cxxflags("/utf-8") -- fix spdlog error

    set_arch("x64")
elseif is_plat("linux") then
    set_arch("x86_64")
elseif is_plat("macosx") then
    set_arch("arm64")
else
    raise("Unsupported platform! Only windows/linux/macosx are supported.")
end

-- includes sub-projects
includes("Engine")
includes("Editor")