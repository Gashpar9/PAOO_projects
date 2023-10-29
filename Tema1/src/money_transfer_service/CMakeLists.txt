add_library(money_transfer_service money_transfer_service.cpp)

target_link_libraries(money_transfer_service PRIVATE sha256)

target_include_directories(money_transfer_service PUBLIC
                            "${PROJECT_SOURCE_DIR}/sha256"
                            )
