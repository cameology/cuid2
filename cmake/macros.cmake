function(addExecutable name path)
    add_executable(${name} ${path})

    if(ARGN)
        target_link_libraries(${name} PRIVATE ${ARGN})
    endif()
endfunction()


function(addLibrary name)
    cmake_parse_arguments(ARG "" "VERSION;SOVERSION;INCLUDE" "SOURCES" ${ARGN})

    add_library(${name} SHARED
        ${ARG_SOURCES}
    )

    target_include_directories(${name} PUBLIC ${ARG_INCLUDE})
    set_target_properties(cuid2 PROPERTIES
        VERSION ${ARG_VERSION}
        SOVERSION ${ARG_SOVERSION}
    )
endfunction()
