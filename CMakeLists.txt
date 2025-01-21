set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include ../CMlib/include ../DBlib/include ../RGlib/include ../MFlib/include)

foreach(loop_var netCells2Grid)
	add_executable(${loop_var} src/CMD${loop_var}.C)
	if(${CMAKE_HOST_APPLE})
		target_link_libraries(${loop_var} LINK_PUBLIC RG22 DB22 MF10 CM10 -lnetcdf -ludunits2 -lm)
	else(${CMAKE_HOST_APPLE})
		target_link_libraries(${loop_var} LINK_PUBLIC RG22 DB22 MF10 CM10 -lnetcdf -ludunits2 -lm -pthread)
	endif(${CMAKE_HOST_APPLE})
	install (TARGETS ${loop_var} RUNTIME DESTINATION ghaas/bin)
endforeach(loop_var)
