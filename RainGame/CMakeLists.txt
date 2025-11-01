add_executable(${RAIN_GAME_TARGET_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/include/gameFramework/GameApplication.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gameFramework/GameApplication.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/Spaceship/Spaceship.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Spaceship/Spaceship.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/Player/PlayerspaceShip.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Player/PlayerspaceShip.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/Weapon/Shooter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Weapon/Shooter.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/Weapon/BulletShooter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Weapon/BulletShooter.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/Weapon/Bullet.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Weapon/Bullet.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/gameplay/HealthComponent.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gameplay/HealthComponent.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/VFX/Explosion.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/VFX/Explosion.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/Enemy/EnemySpaceship.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Enemy/EnemySpaceship.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/Enemy/Vanguard.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Enemy/Vanguard.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/Level/GameLevelOne.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Level/GameLevelOne.cpp
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