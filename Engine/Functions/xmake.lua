-- Packages Url
-- https://github.com/xmake-io/xmake-repo/tree/dev/packages/

target("Functions")
    set_kind("static")
    add_headerfiles("src/**.hpp")
    add_files("src/**.cpp")

    add_includedirs("src")
    add_includedirs("include", {public=true})

    add_deps("Core")
    add_deps("Platform")