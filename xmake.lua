add_rules("mode.debug", "mode.release")

target("env")
    on_build(function (target)
        cur_env = "unknown"
        if is_arch("arm.*") then
            cur_env = "arm"
        elseif is_arch("x86_64", "i386") then
            cur_env = "x86"
        end
        io.writefile("cur.env", cur_env)
    end)
 
target("freq_test")
    set_optimize("none")
    set_kind("binary")

    if is_arch("arm.*") then
        add_files("src/freq/*arm.cpp")
    elseif is_arch("x86_64", "i386") then
        add_files("src/freq/*x86.cpp")
    end

target("pipewidth_test")
    set_optimize("none")
    set_kind("binary")

    if is_arch("arm.*") then
        add_files("src/pipewidth/pipewidth_arm.cpp")
    elseif is_arch("x86_64", "i386") then
        add_files("src/pipewidth/*x86.cpp")
    end

-- target("fetchwidth_test")
--     set_optimize("none")
--     set_kind("binary")

--     if is_arch("arm.*") then
--         add_files("src/pipewidth/fetchwidth_arm.cpp")
--     elseif is_arch("x86_64", "i386") then
--         add_files("src/fetchwidth/*x86.cpp")
--     end

target("movelimination_test")
    set_optimize("none")
    set_kind("binary")

    if is_arch("arm.*") then
        add_files("src/movelimination/*arm.cpp")
    elseif is_arch("x86_64", "i386") then
        add_files("src/movelimination/*x86.cpp")
    end

target("instlatency_test")
    set_optimize("none")
    set_kind("binary")

    if is_arch("arm.*") then
        add_files("src/instlatency/*arm.cpp")
    elseif is_arch("x86_64", "i386") then
        add_files("src/instlatency/*x86.cpp")
    end

target("ptchase_test")
    set_optimize("none")
    set_kind("binary")

    if is_arch("arm.*") then
        add_files("src/ptchase/*arm.cpp")
    elseif is_arch("x86_64", "i386") then
        add_files("src/ptchase/*x86.cpp")
    end

target("btb_test")
    set_optimize("fast")
    set_kind("binary")
    set_default(false)

    add_files("src/btb/test.c")

target("cachelatency_test")
    set_optimize("none")
    set_kind("binary")

    add_files("src/cachelatency/*.c")


target("membandwidth_test")
    set_optimize("faster")
    set_kind("binary")
    -- add_packages("openmp")
    -- add_defines("STREAM_ARRAY_SIZE=2000000000")
    add_defines("NTIMES=100")
    -- add_cflags("-mcmodel=large","-fno-PIC",{force=true})

    add_files("src/membandwidth/*.c")

target("ldstforward_test")
    set_optimize("faster")
    set_kind("binary")

    if is_arch("arm.*") then
        add_files("src/ldstforward/*_arm.cpp")
    elseif is_arch("x86_64", "i386") then
        add_files("src/ldstforward/*_x86.cpp")
    end

target("ldstorder_test")
    set_optimize("faster")
    set_kind("binary")
    set_default(false)

    add_files("src/ldstorder/test.c")

target("bp_test")
    set_optimize("faster")
    set_kind("binary")
    set_default(false)

    add_files("src/bp/test.c")

target("ras_test")
    set_optimize("fast") -- Don't use any level upper fast(O1)
    set_kind("binary")

    add_files("src/ras/test.c")

target("ras_dist_test")
    set_optimize("fast") -- Don't use any level upper fast(O1)
    set_kind("binary")
    set_default(false)

    add_files("src/ras_dist/test.c")

target("c2clatency_test")
    set_optimize("none") -- Don't use any level upper none(O0)
    set_kind("binary")

    add_files("src/c2clatency/c2clatency.c")
    add_ldflags("-lpthread")

    if is_plat("macosx") then
       set_default(false)
    -- elseif is_arch("x86_64", "i386") then
    --     add_files("src/ldstorder/*_x86.cpp")
    end

target("mlp_test")
    set_optimize("none")
    set_kind("binary")

    add_files("src/mlp/*.c")


--
-- If you want to known more usage about xmake, please see https://xmake.io
--
-- ## FAQ
--
-- You can enter the project directory firstly before building project.
--
--   $ cd projectdir
--
-- 1. How to build project?
--
--   $ xmake
--
-- 2. How to configure project?
--
--   $ xmake f -p [macosx|linux|iphoneos ..] -a [x86_64|i386|arm64 ..] -m [debug|release]
--
-- 3. Where is the build output directory?
--
--   The default output directory is `./build` and you can configure the output directory.
--
--   $ xmake f -o outputdir
--   $ xmake
--
-- 4. How to run and debug target after building project?
--
--   $ xmake run [targetname]
--   $ xmake run -d [targetname]
--
-- 5. How to install target to the system directory or other output directory?
--
--   $ xmake install
--   $ xmake install -o installdir
--
-- 6. Add some frequently-used compilation flags in xmake.lua
--
-- @code
--    -- add debug and release modes
--    add_rules("mode.debug", "mode.release")
--
--    -- add macro defination
--    add_defines("NDEBUG", "_GNU_SOURCE=1")
--
--    -- set warning all as error
--    set_warnings("all", "error")
--
--    -- set language: c99, c++11
--    set_languages("c99", "c++11")
--
--    -- set optimization: none, faster, fastest, smallest
--    set_optimize("fastest")
--
--    -- add include search directories
--    add_includedirs("/usr/include", "/usr/local/include")
--
--    -- add link libraries and search directories
--    add_links("tbox")
--    add_linkdirs("/usr/local/lib", "/usr/lib")
--
--    -- add system link libraries
--    add_syslinks("z", "pthread")
--
--    -- add compilation and link flags
--    add_cxflags("-stdnolib", "-fno-strict-aliasing")
--    add_ldflags("-L/usr/local/lib", "-lpthread", {force = true})
--
-- @endcode
--

