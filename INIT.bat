md SRC
md LIB
md Modules

cd SRC
    type nul > main.ino
cd ..

cd LIB
    type nul > STD_TYPES.h
cd..

cd Modules
    md Navigation
    md shooting
    md Bluetooth

    cd Navigation
        type nul > NAV_private.h
        type nul > NAV_interface.h
        type nul > NAV_configure.h
        type nul > NAV_program.c
    cd ..    

    cd shooting
        type nul > SHOT_private.h
        type nul > SHOT_interface.h
        type nul > SHOT_configure.h
        type nul > SHOT_program.c
    cd ..   

      cd Bluetooth
        type nul > BLUE_private.h
        type nul > BLUE_interface.h
        type nul > BLUE_configure.h
        type nul > BLUE_program.c
    cd ..   