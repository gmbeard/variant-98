add_executable(
    StorageTestProg
    storage_tests.cpp
)

add_executable(
    VisitorTestProg
    visitor_tests.cpp
)

add_definitions(
    -Wall -Werror -Wextra -pedantic
)

add_test(
    StorageTests
    StorageTestProg
)

add_test(
    VisitorTests
    VisitorTestProg
)
