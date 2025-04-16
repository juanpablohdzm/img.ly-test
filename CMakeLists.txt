cmake_minimum_required(VERSION 3.30)
project(img_ly_test)

set(CMAKE_CXX_STANDARD 20)

add_executable(img_ly_test main.cpp
        src/ComputePipeline.cpp
        src/ComputePipeline.h
        src/utils/Option.h
        src/actions/ActionResult.h
        src/actions/Load/FileLoad.h
        src/actions/Load/UrlLoad.h
        src/actions/Load/BundleLoad.h
        src/actions/ImageDecoding.h
        src/actions/Load/LoadResult.h
        src/actions/DataDecompressor.h
        src/actions/JsonUnserializer.h
        src/actions/Load/LoadFactory.h)
