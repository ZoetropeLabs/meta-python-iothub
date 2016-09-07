# meta-python-iothub

This layer provides a way to use the Python implementation of the Microsoft Azure iot client SDK: https://github.com/Azure/azure-iot-sdks

It should be enough to just add this layer into your bblayers.conf and add a RDEPENDS to `python(3)-iothub`.

This does not have many dependencies (just boost and curl), but to make sure boost is there, you need to add this to your local.conf file:


```
PACKAGECONFIG_pn-boost = "python"
```

This will build the `liboost-python${PYTHON_BASEVERSION}.so` (includes the ABI) so that the iothub package can link aginst it.

Note that this has only been tested to work with Yocto 2.1 (Krogoth).
