project(${CMAKE_PROJECT_NAME}_lib)

set(HEADER_FILES
        Cell.h
        Geometrics.h
        Initial.h
        Model.h
        Output.h
        Parameters.h
        )
set(SOURCE_FILES
        Cell.cpp
        Geometrics.cpp
        Initial.cpp
        Model.cpp
        Output.cpp
        Input.cpp Input.h consts.h ProgramMorphoTooth.cpp ProgramMorphoTooth.h)


add_library(${CMAKE_PROJECT_NAME}_lib STATIC
        ${SOURCE_FILES}
        ${HEADER_FILES}
        )
