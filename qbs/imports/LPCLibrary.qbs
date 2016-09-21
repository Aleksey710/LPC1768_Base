import qbs

LPCProduct {
    type: "staticlibrary"

    destinationDirectory: "./lib"
    buildDirectory: "./build"
    
    cpp.positionIndependentCode: false
    cpp.executableSuffix: ".a"

//    cpp.commonCompilerFlags: [
//        "-mthumb",
//        "-mcpu=cortex-m4",
//        "-mfloat-abi=hard",
//        "-mfpu=fpv4-sp-d16",
//        "-fdata-sections",
//        "-ffunction-sections",
//        "-fno-inline",
//        "-fno-builtin",
////        "-std=c99",
////        "-std=c++11",
//        "-std=gnu99",
////        "-flto"
//    ]

//    cpp.linkerFlags:[
//        "-flto",
//        "-mthumb",
//        "-mcpu=cortex-m4",
//        "-mfloat-abi=hard",
//        "-mfpu=fpv4-sp-d16",
//        "--specs=nano.specs",
////        "--start-group",
//        "-Xlinker",
//        "--gc-sections",
////        "-Wl",
////        "-T",
////        "-lnosys",
////        "-lgcc",
////        "-lc"
//    ]

    Properties {
        condition: qbs.buildVariant === "debug"
        cpp.defines: outer.concat(["DEBUG=1"])
    }
}
