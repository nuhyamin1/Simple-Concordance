cmake_minimum_required(VERSION 3.10)
project(concordance_tool)

# Since we don't have pre-built wxWidgets libraries, let's build without wxWidgets for now
# and focus on the command-line version

# Command-line version
add_executable(concordance_tool 
    main.cpp 
    concordance.cpp
)

# Comment out the GUI version until wxWidgets is properly installed
# GUI version
# add_executable(concordance_gui
#     gui_main.cpp
#     concordance.cpp
# )

# Link wxWidgets libraries to GUI version
# target_link_libraries(concordance_gui ${wxWidgets_LIBRARIES})

message(STATUS "Building command-line version only. GUI version disabled until wxWidgets is properly installed.")