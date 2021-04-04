cmake_minimum_required(VERSION 3.10)


add_executable(tests
	runner.c
	test_token.c
)
target_link_libraries(tests
	scanner-token
)