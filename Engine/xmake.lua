-- Packages Url
-- https://github.com/xmake-io/xmake-repo/tree/dev/packages/

includes("Core")
includes("Platform")

target("Engine")
    set_kind("static")
    add_headerfiles("src/**.hpp")
    add_files("src/**.cpp")

    add_includedirs("src", {public=true})
    add_includedirs("include", {public=true})
    add_includedirs("assets")

    add_deps("Core")
    add_deps("Platform")