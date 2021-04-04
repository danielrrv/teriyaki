cmake_minimum_required(VERSION 3.10)


add_library(scanner-token
  scanner.c
  token.c
  scanner.h
  token.h
  init.c
  init.h
  token_type.h
)


