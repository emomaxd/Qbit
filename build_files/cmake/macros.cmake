function(qbit_add_lib 
    TARGET_NAME 
    SRC 
    INC 
    INC_SYS
    LIBS
    )

    add_library(${TARGET_NAME} STATIC ${SRC})
    
    target_include_directories(${TARGET_NAME} PUBLIC ${INC})
    target_include_directories(${TARGET_NAME} SYSTEM PUBLIC ${INC_SYS})

    target_link_libraries(${TARGET_NAME} PRIVATE ${LIBS})

endfunction()
