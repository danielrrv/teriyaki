cmake_minimum_required(VERSION 3.10)


add_executable(tests
	runner.c
	test_token.c
)
target_link_libraries(tests
	scanner-token
)

add_custom_command(TARGET tests POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/example.txt 
		$<TARGET_FILE_DIR:tests>
)