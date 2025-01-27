cmake_minimum_required(VERSION 3.5)

project(histogram VERSION 1)

# Указываем, что используем C++11 или выше
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_FLAGS -Wall)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Подключаем модули Qt
find_package(Qt5 REQUIRED COMPONENTS Widgets)

# Указываем исходные файлы
add_executable(${PROJECT_NAME}_Executable 
    main.cpp
    MainWindow.cpp
    MainWindow.h
    Comparators.cpp
    PrintHistogram.cpp
)

# Подключаем библиотеки Qt к проекту
target_link_libraries(${PROJECT_NAME}_Executable PRIVATE Qt5::Widgets)

# Указываем директорию с заголовочными файлами
target_include_directories(${PROJECT_NAME}_Executable PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
