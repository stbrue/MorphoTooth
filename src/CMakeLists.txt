project(${CMAKE_PROJECT_NAME}_lib)

set(HEADER_FILES
        Cell.h
        Geometrics.h
        Grid.h
        Initial.h
        Model.h
        Output.h
        Parameters.h
        )
set(SOURCE_FILES
        Cell.cpp
        Geometrics.cpp
        Grid.cpp
        Initial.cpp
        Model.cpp
        Output.cpp
        Parameters.cpp
        Input.cpp Input.h)


add_library(${CMAKE_PROJECT_NAME}_lib STATIC
        ${SOURCE_FILES}
        ${HEADER_FILES}
        )
