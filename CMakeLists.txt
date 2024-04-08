cmake_minimum_required( VERSION 3.5 )

project( UnigradiconLightning CXX )

find_package(ITK REQUIRED)

include( ${ITK_USE_FILE})

find_package(Torch REQUIRED)

add_executable( UnigradiconRegister UnigradiconRegister.cxx)

target_link_libraries( UnigradiconRegister ${TORCH_LIBRARIES} )
set_property(TARGET UnigradiconRegister PROPERTY CXX_STANDARD 17)

add_executable( UnigradiconWarp UnigradiconWarp.cxx )

target_link_libraries( UnigradiconWarp PUBLIC ${ITK_LIBRARIES} )

