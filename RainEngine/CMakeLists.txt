add_library(${RAIN_ENGINE_TARGET_NAME} STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/framework/Application.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/framework/Application.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/framework/World.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/framework/World.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/framework/Actor.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/framework/Actor.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/framework/Object.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/framework/Object.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/EntryPoint.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/EntryPoint.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/framework/Core.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/framework/Core.cpp
)

target_include_directories(${RAIN_ENGINE_TARGET_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${RAIN_ENGINE_TARGET_NAME} PUBLIC sfml-graphics)
target_link_libraries(${RAIN_ENGINE_TARGET_NAME} PUBLIC sfml-window)
target_link_libraries(${RAIN_ENGINE_TARGET_NAME} PUBLIC sfml-system)
target_link_libraries(${RAIN_ENGINE_TARGET_NAME} PUBLIC sfml-audio)

function(CopyLibToTarget LIB_NAME TARGET_NAME)

    add_custom_command(TARGET ${TARGET_NAME} 
        POST_BUILD
        COMMAND 
        ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:${LIB_NAME}>
        $<TARGET_FILE_DIR:${TARGET_NAME}>
    )

endfunction()

CopyLibToTarget(sfml-graphics ${RAIN_ENGINE_TARGET_NAME})
CopyLibToTarget(sfml-window ${RAIN_ENGINE_TARGET_NAME})
CopyLibToTarget(sfml-system ${RAIN_ENGINE_TARGET_NAME})
CopyLibToTarget(sfml-audio ${RAIN_ENGINE_TARGET_NAME})