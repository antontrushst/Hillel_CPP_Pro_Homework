cmake_minimum_required(VERSION 3.16)

project(temp_calculator VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(apptemp_calculator
    main.cpp
)

qt_add_qml_module(apptemp_calculator
    URI temp_calculator
    VERSION 1.0
    QML_FILES
        Main.qml
        SOURCES calculatormodel.h calculatormodel.cpp
        SOURCES calculatorcontroller.h calculatorcontroller.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(apptemp_calculator PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.apptemp_calculator
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(apptemp_calculator
    PRIVATE Qt6::Quick
)

target_link_libraries(apptemp_calculator
    PRIVATE Qt6::Widgets
)

include(GNUInstallDirs)
install(TARGETS apptemp_calculator
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
