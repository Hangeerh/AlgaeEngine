function(compile_swift_sources TARGET)
    if(NOT APPLE)
        message(FATAL_ERROR "compile_swift_sources() requires Apple/macOS. Swift is not available on this platform.")
    endif()

    cmake_parse_arguments(ARGS
        ""
        "MODULE_NAME"
        "SOURCES;COMPILE_FLAGS;LINK_FLAGS"
        ${ARGN}
    )

    if(NOT ARGS_SOURCES)
        set(ARGS_SOURCES ${ARGN})
    endif()

    if(NOT ARGS_MODULE_NAME)
        set(ARGS_MODULE_NAME ${TARGET}Swift)
    endif()

    set(SWIFT_SOURCES "")
    foreach(SRC IN LISTS ARGS_SOURCES)
        get_filename_component(ABS_SRC ${SRC} ABSOLUTE)
        list(APPEND SWIFT_SOURCES ${ABS_SRC})
    endforeach()

    set(SWIFT_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/swift)
    file(MAKE_DIRECTORY ${SWIFT_OUTPUT_DIR})

    set(SWIFT_OBJS "")
    set(SWIFT_MODULE_FILE ${SWIFT_OUTPUT_DIR}/${ARGS_MODULE_NAME}.swiftmodule)
    set(SWIFT_MODULE_BC ${SWIFT_OUTPUT_DIR}/${ARGS_MODULE_NAME}.swiftinterface)

    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(SWIFT_BUILD_FLAGS -Onone -g)
    else()
        set(SWIFT_BUILD_FLAGS -O)
    endif()

    set(SWIFT_COMMON_FLAGS
        -module-name ${ARGS_MODULE_NAME}
        -parse-as-library
        -wmo
        ${SWIFT_BUILD_FLAGS}
        -Xcc -fmodules
        ${ARGS_COMPILE_FLAGS}
    )

    list(LENGTH SWIFT_SOURCES NUM_SOURCES)
    if(${NUM_SOURCES} EQUAL 1)
        list(GET SWIFT_SOURCES 0 SOURCE_FILE)
        get_filename_component(SRC_BASENAME ${SOURCE_FILE} NAME_WE)
        set(SWIFT_OBJ ${SWIFT_OUTPUT_DIR}/${SRC_BASENAME}.o)
        
        add_custom_command(
            OUTPUT ${SWIFT_OBJ} ${SWIFT_MODULE_FILE} ${SWIFT_MODULE_BC}
            COMMAND xcrun -sdk macosx swiftc
                -c ${SOURCE_FILE}
                -o ${SWIFT_OBJ}
                ${SWIFT_COMMON_FLAGS}
                -emit-module
                -module-link-name ${ARGS_MODULE_NAME}
                -emit-module-path ${SWIFT_MODULE_FILE}
            DEPENDS ${SOURCE_FILE}
            COMMENT "Compiling Swift source: ${SOURCE_FILE}"
            VERBATIM
        )
        list(APPEND SWIFT_OBJS ${SWIFT_OBJ})
    else()
        set(SWIFT_OBJ ${SWIFT_OUTPUT_DIR}/${ARGS_MODULE_NAME}.o)

        add_custom_command(
            OUTPUT ${SWIFT_OBJ} ${SWIFT_MODULE_FILE} ${SWIFT_MODULE_BC}
            COMMAND xcrun -sdk macosx swiftc
                -c ${SWIFT_SOURCES}
                -o ${SWIFT_OBJ}
                ${SWIFT_COMMON_FLAGS}
                -emit-module
                -module-link-name ${ARGS_MODULE_NAME}
                -emit-module-path ${SWIFT_MODULE_FILE}
            DEPENDS ${SWIFT_SOURCES}
            COMMENT "Compiling Swift sources: ${ARGS_MODULE_NAME}"
            VERBATIM
        )
        list(APPEND SWIFT_OBJS ${SWIFT_OBJ})
    endif()

    add_custom_target(${TARGET}_Swift ALL
        DEPENDS ${SWIFT_OBJS} ${SWIFT_MODULE_FILE} ${SWIFT_MODULE_BC}
    )

    target_sources(${TARGET} PRIVATE ${SWIFT_OBJS})

    add_dependencies(${TARGET} ${TARGET}_Swift)

    set_target_properties(${TARGET} PROPERTIES
        INTERFACE_SWIFT_INCLUDE_DIRECTORIES ${SWIFT_OUTPUT_DIR}
    )

    target_link_options(${TARGET} PRIVATE
        "-Wl,-force_load,${SWIFT_OUTPUT_DIR}"
        ${ARGS_LINK_FLAGS}
    )
endfunction()

function(target_link_swift_libraries TARGET)
    if(NOT APPLE)
        message(FATAL_ERROR "target_link_swift_libraries() requires Apple/macOS.")
    endif()

    target_link_libraries(${TARGET} PRIVATE
        "-framework Foundation"
        "-framework Metal"
        "-framework MetalKit"
        "-framework QuartzCore"
        "-framework AppKit"
        ${ARGN}
    )
endfunction()