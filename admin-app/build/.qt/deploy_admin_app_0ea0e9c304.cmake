include(C:/GIT_Repositoryt/group_11/admin-app/build/.qt/QtDeploySupport.cmake)
include("${CMAKE_CURRENT_LIST_DIR}/admin-app-plugins.cmake" OPTIONAL)
set(__QT_DEPLOY_I18N_CATALOGS "qtbase")

qt6_deploy_runtime_dependencies(
    EXECUTABLE C:/GIT_Repositoryt/group_11/admin-app/build/admin-app.exe
    GENERATE_QT_CONF
)
