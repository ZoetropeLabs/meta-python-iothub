DESCRIPTION = "Azure iot hub package" 
SECTION = "core" 
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${WORKDIR}/git/LICENSE;md5=4283671594edec4c13aeb073c219237a"

DEPENDS = " git-native util-linux curl boost "
RDEPENDS_${PN} = " curl boost "

SRCREV = "1e8f6fdf2890dec7e603b417aa07151a8660f213"
SRC_URI = "gitsm://git@github.com/Azure/azure-iot-sdks.git;protocol=https \
           file://0002-Clear-rpath-from-build.patch"

S = "${WORKDIR}/git"

inherit pkgconfig cmake python-dir

FILES_${PN} += "${PYTHON_SITEPACKAGES_DIR}/iothub_client.so"

do_configure() {
    cmake \
        --debug \
        -DBOOST_ROOT:string=${PKG_CONFIG_SYSROOT_DIR}/usr/ \
        -DPYTHON_INCLUDE_DIR=${PKG_CONFIG_SYSROOT_DIR}/usr/include/${PYTHON_DIR}${PYTHON_ABI} \
        -DPYTHON_LIBRARY=${PKG_CONFIG_SYSROOT_DIR}/usr/lib/lib${PYTHON_DIR}${PYTHON_ABI}.so \
        -Drun_valgrind:BOOL=false \
        -Drun_e2e_tests:BOOL=false \
        -Drun_longhaul_tests=false \
        -Duse_amqp:BOOL=true \
        -Duse_http:BOOL=true \
        -Duse_mqtt:BOOL=true \
        -Duse_wsio:BOOL=false \
        -Dskip_unittests:BOOL=true \
        -Dbuild_python:STRING="${PYTHON_BASEVERSION}"\
        -Dbuild_javawrapper:BOOL=false \
        ${S}/c
}

do_compile() {
    oe_runmake
}
    
do_install() {
    install -d ${D}/${PYTHON_SITEPACKAGES_DIR}/
    install -m 0644 ${S}/../build/python/src/iothub_client.so ${D}/${PYTHON_SITEPACKAGES_DIR}/
}
