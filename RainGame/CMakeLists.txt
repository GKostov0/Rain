add_executable(${RAIN_GAME_TARGET_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/include/gameFramework/GameApplication.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gameFramework/GameApplication.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/SpaceShip/SpaceShip.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/SpaceShip/SpaceShip.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/Player/PlayerSpaceShip.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Player/PlayerSpaceShip.cpp
)

target_include_directories(${RAIN_GAME_TARGET_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${RAIN_GAME_TARGET_NAME} PUBLIC ${RAIN_ENGINE_TARGET_NAME})

function(CopyLibDirToTarget LIB_NAME TARGET_NAME)

    add_custom_command(TARGET ${TARGET_NAME} 
        POST_BUILD
        COMMAND 
        ${CMAKE_COMMAND} -E copy_directory
        $<TARGET_FILE_DIR:${LIB_NAME}>
        $<TARGET_FILE_DIR:${TARGET_NAME}>
    )

endfunction()

CopyLibDirToTarget(${RAIN_ENGINE_TARGET_NAME} ${RAIN_GAME_TARGET_NAME})

set(RESOURCES_FOLDER_NAME "assets")
set(RESOURCES_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/${RESOURCES_FOLDER_NAME}")

add_custom_command(
    TARGET ${RAIN_GAME_TARGET_NAME}
    POST_BUILD
    COMMAND
    ${CMAKE_COMMAND} -E copy_directory
    ${RESOURCES_SRC_DIR}
    $<TARGET_FILE_DIR:${RAIN_GAME_TARGET_NAME}>/${RESOURCES_FOLDER_NAME}
)

configure_file(
    "config.h.in"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/config.h" ESCAPE_QUOTES
)