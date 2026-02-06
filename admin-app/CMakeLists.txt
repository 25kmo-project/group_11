cmake_minimum_required(VERSION 3.19)
project(admin-app LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Network)

qt_standard_project_setup()

qt_add_executable(admin-app
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    environment.h environment.cpp

    gui/adminmenu.h gui/adminmenu.cpp gui/adminmenu.ui
    gui/customersmenu.h gui/customersmenu.cpp gui/customersmenu.ui
    gui/addcustomermenu.h gui/addcustomermenu.cpp gui/addcustomermenu.ui
    gui/accountsmenu.h gui/accountsmenu.cpp gui/accountsmenu.ui
    gui/addaccountmenu.h gui/addaccountmenu.cpp gui/addaccountmenu.ui
    gui/cardsmenu.h gui/cardsmenu.cpp gui/cardsmenu.ui

    src/authmanager.h src/authmanager.cpp
    src/account.h src/account.cpp
    src/customer.h src/customer.cpp
    src/card.h src/card.cpp
)

target_include_directories(admin-app PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/gui
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

qt_add_resources(app_resources
    resources/resources.qrc
)

target_sources(admin-app PRIVATE
    ${app_resources}
)

target_link_libraries(admin-app
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Network
)

include(GNUInstallDirs)

install(TARGETS admin-app
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET admin-app
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
