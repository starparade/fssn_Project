# Reference: https://github.com/grpc/grpc/blob/v1.41.0/examples/cpp/helloworld/CMakeLists.txt

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

project(hello_grpc C CXX)

include(/home/hyeeun/grpc_install/grpc/examples/cpp/cmake/common.cmake)

# Proto file
get_filename_component(hg_proto "hello_grpc.proto" ABSOLUTE)
get_filename_component(hg_proto_path "${hg_proto}" PATH)

# Generated sources
set(hg_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/hello_grpc.pb.cc")
set(hg_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/hello_grpc.pb.h")
set(hg_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/hello_grpc.grpc.pb.cc")
set(hg_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/hello_grpc.grpc.pb.h")
add_custom_command(
      OUTPUT "${hg_proto_srcs}" "${hg_proto_hdrs}" "${hg_grpc_srcs}" "${hg_grpc_hdrs}"
      COMMAND ${_PROTOBUF_PROTOC}
      ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        -I "${hg_proto_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${hg_proto}"
      DEPENDS "${hg_proto}")

# Include generated *.pb.h files
include_directories("${CMAKE_CURRENT_BINARY_DIR}")

# hg_grpc_proto
add_library(hg_grpc_proto
  ${hg_grpc_srcs}
  ${hg_grpc_hdrs}
  ${hg_proto_srcs}
  ${hg_proto_hdrs})
target_link_libraries(hg_grpc_proto
  ${_REFLECTION}
  ${_GRPC_GRPCPP}
  ${_PROTOBUF_LIBPROTOBUF})

# Targets greeter_[async_](client|server)
foreach(_target
  client server)
  add_executable(${_target} "${_target}.cpp")
  target_link_libraries(${_target}
    hg_grpc_proto
    ${_REFLECTION}
    ${_GRPC_GRPCPP}
    ${_PROTOBUF_LIBPROTOBUF})
endforeach()
