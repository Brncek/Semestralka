cmake_minimum_required(VERSION 3.22)

project(
    Semestralka_Pochod
    LANGUAGES C
)

add_executable(klient)
target_sources(klient PRIVATE main.c fileManager.c symulator.c klientIPC.c)
add_executable(server)
target_sources(server PRIVATE server.c fileManager.c symulator.c serverIPC.c)