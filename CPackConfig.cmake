include(InstallRequiredSystemLibraries)

set(CPACK_PACKAGE_CONTACT "andrey.tynkov@gmail.com")
set(CPACK_PACKAGE_VERSION "1.0.0.0")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Chain Of Responsibility C++ Design Pattern")

set(CPACK_RESOURCE_FILE_README ${CMAKE_CURRENT_SOURCE_DIR}/README.md)

set(CPACK_DEBIAN_PACKAGE_NAME "chainofresp-dev")
set(CPACK_DEBIAN_PACKAGE_PREDEPENDS "cmake >= 3.10")
set(CPACK_DEBIAN_PACKAGE_RELEASE 1)