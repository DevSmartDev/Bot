
add_executable(simple simple.c)
target_link_libraries(simple slope ${DEPENDENCY_LIBRARIES} -lm)

add_executable(plot_stack plot_stack.c)
target_link_libraries(plot_stack slope ${DEPENDENCY_LIBRARIES} -lm)

add_executable(test test.c)
target_link_libraries(test slope ${DEPENDENCY_LIBRARIES} -lm)
