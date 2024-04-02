cmake_minimum_required( VERSION 3.5 )

project( UnigradiconLightning CXX )

find_package(ITK REQUIRED)

#find_package(ITK COMPONENTS
#	ITKIOImageBase
#	ITKImageFilterBase
#   ITKCommon
#   ITKTransform
#)
include( ${ITK_USE_FILE})

add_executable( UnigradiconWarp UnigradiconWarp.cxx )

target_link_libraries( UnigradiconWarp PUBLIC ${ITK_LIBRARIES} )

