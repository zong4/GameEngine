-- Packages Url
-- https://github.com/xmake-io/xmake-repo/tree/dev/packages/

add_requires("spdlog")
add_requires("glm")
add_requires("tracy")

target("Core")
    set_kind("static")
    add_headerfiles("src/**.hpp")
    add_files("src/**.cpp")
    
    add_includedirs("src")
    add_includedirs("include", {public=true})

    add_packages("spdlog", {public=true})
    add_packages("glm", {public=true})
    
    add_packages("tracy", { public = true })
    add_defines("TRACY_ENABLE")
    if is_plat("windows") then
        add_links("ws2_32") 
    end

