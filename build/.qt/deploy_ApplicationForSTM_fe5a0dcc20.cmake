include("C:/Users/a.faizullin/Documents/ApplicationForSTM/build/.qt/QtDeploySupport.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/ApplicationForSTM-plugins.cmake" OPTIONAL)
set(__QT_DEPLOY_I18N_CATALOGS "qtbase;qtserialport")

qt6_deploy_runtime_dependencies(
    EXECUTABLE "C:/Users/a.faizullin/Documents/ApplicationForSTM/build/ApplicationForSTM.exe"
    GENERATE_QT_CONF
)
