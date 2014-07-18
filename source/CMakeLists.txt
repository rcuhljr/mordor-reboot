link_directories(${GTKMM_LIBRARY_DIRS})

include_directories(${GTKMM_INCLUDE_DIRS})

add_executable(MordorReboot
	test.cpp
	)

target_link_libraries(MordorReboot
	${GTKMM_LIBRARIES} )


