set(SHADERS_SRC
	"${CMAKE_CURRENT_SOURCE_DIR}/shaders.cpp"
)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_sources(${PROJECT_NAME} PRIVATE ${SHADERS_SRC})
