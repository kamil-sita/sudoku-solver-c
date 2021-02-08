cmake_minimum_required(VERSION 3.10)
project(sudokuTxt C)

set(CMAKE_C_STANDARD 11)

include_directories(gui)
include_directories(sudoku)

add_executable(
        sudokuTxt
        main.c
        main.h
        helper.c
        helper.h
        io.c
        io.h
        test.c
        test.h
        gameGui.c
        gameGui.h
        args.c
        args.h
        random.c
        random.h

        sudoku/board.c
        sudoku/board.h
        sudoku/generator.c
        sudoku/generator.h
        sudoku/backTrackingSolver.c
        sudoku/backTrackingSolver.h
        sudoku/solver.c
        sudoku/solver.h
        sudoku/penAndPaperSolver.c
        sudoku/penAndPaperSolver.h
        sudoku/history.c
        sudoku/history.h
)