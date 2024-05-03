project(LibPSSMono)

if(WIN32)
    add_library(LibPSSMono STATIC IMPORTED)    

    if(${CMAKE_BUILD_TYPE} EQUAL "Debug")
        set_target_properties(LibPSSMono PROPERTIES
            IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/lib/Debug/monosgen-2.0.lib
        )
    else()
        set_target_properties(LibPSSMono PROPERTIES
            IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/lib/Release/monosgen-2.0.lib
        )
    endif()

    target_include_directories(LibPSSMono PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)
else()
    set(MAKE_CFLAGS "-DTARGET_PSS -DPSS_USE_CRYPTO -DHAVE_ISINF=1 -include sys/sysmacros.h")

    add_custom_command(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/libmonosgen-static.a ${CMAKE_CURRENT_BINARY_DIR}/libeglib-static.a
        WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/pss-mono
        COMMAND ./configure --with-moonlight=yes --with-moon-gc=sgen --with-sgen=yes --with-gc=sgen --with-mobile=yes --with-monotouch=yes
        COMMAND make -j CFLAGS="${MAKE_CFLAGS}" -C libgc
        COMMAND make -j CFLAGS="${MAKE_CFLAGS}" -C mono/io-layer
        COMMAND make -j CFLAGS="${MAKE_CFLAGS}" -C mono/metadata
        COMMAND make -j CFLAGS="${MAKE_CFLAGS}" -C eglib
        COMMAND make -j CFLAGS="${MAKE_CFLAGS}" -C mono/utils libmonoutils.la
        COMMAND make -j CLFAGS="${MAKE_CFLAGS}" -C mono/mini distdir="mono/mini" distdir
        COMMAND make -j CFLAGS="${MAKE_CFLAGS}" -C mono/mini libmonosgen-static.la
        COMMAND cp ${CMAKE_CURRENT_LIST_DIR}/pss-mono/eglib/src/.libs/libeglib-static.a ${CMAKE_CURRENT_BINARY_DIR}/libeglib-static.a
        COMMAND cp ${CMAKE_CURRENT_LIST_DIR}/pss-mono/mono/mini/.libs/libmonosgen-static.a ${CMAKE_CURRENT_BINARY_DIR}/libmonosgen-static.a
    )

    add_library(libmonosgen STATIC IMPORTED)
    set_target_properties(libmonosgen PROPERTIES
        IMPORTED_LOCATION ${CMAKE_CURRENT_BINARY_DIR}/libmonosgen-static.a
    )

    add_library(eglib STATIC IMPORTED)
    set_target_properties(eglib PROPERTIES
        IMPORTED_LOCATION ${CMAKE_CURRENT_BINARY_DIR}/libeglib-static.a
    )

    add_library(LibPSSMono INTERFACE)

    link_libraries(LibPSSMono libmonosgen eglib c)

    add_custom_target(monosgen DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/libmonosgen-static.a)
    add_dependencies(LibPSSMono monosgen)

    target_include_directories(LibPSSMono INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
endif()
