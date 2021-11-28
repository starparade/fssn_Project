# Reference: https://github.com/grpc/grpc/blob/v1.41.0/examples/cpp/route_guide/CMakeLists.txt

# Copyright 2018 gRPC authors.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.


cmake_minimum_required(VERSION 3.5.1)

project(Bidirectional C CXX)

include(/home/hyeeun/grpc_install/grpc/examples/cpp/cmake/common.cmake)

# Proto file
get_filename_component(bs_proto "Bidirectional.proto" ABSOLUTE)
get_filename_component(bs_proto_path "${bs_proto}" PATH)

# Generated sources
set(bs_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/Bidirectional.pb.cc")
set(bs_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/Bidirectional.pb.h")
set(bs_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/Bidirectional.grpc.pb.cc")
set(bs_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/Bidirectional.grpc.pb.h")
add_custom_command(
      OUTPUT "${bs_proto_srcs}" "${bs_proto_hdrs}" "${bs_grpc_srcs}" "${bs_grpc_hdrs}"
      COMMAND ${_PROTOBUF_PROTOC}
      ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        -I "${bs_proto_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${bs_proto}"
      DEPENDS "${bs_proto}")

# Include generated *.pb.h files
include_directories("${CMAKE_CURRENT_BINARY_DIR}")

# bs_grpc_proto
add_library(bs_grpc_proto
  ${bs_grpc_srcs}
  ${bs_grpc_hdrs}
  ${bs_proto_srcs}
  ${bs_proto_hdrs})
target_link_libraries(bs_grpc_proto
  ${_REFLECTION}
  ${_GRPC_GRPCPP}
  ${_PROTOBUF_LIBPROTOBUF})

# Targets route_guide_(client|server)
foreach(_target
  client server)
  add_executable(${_target} "${_target}.cpp")
  target_link_libraries(${_target}
    bs_grpc_proto
    ${_REFLECTION}
    ${_GRPC_GRPCPP}
    ${_PROTOBUF_LIBPROTOBUF})
endforeach()