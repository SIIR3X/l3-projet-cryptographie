@echo off
rem ECB Encrypt : ECB encrypt -k 2b7e151628aed2a6abf7158809cf4f3c -in data/input.txt -out data/output.txt
rem ECB Decrypt : ECB decrypt -k 2b7e151628aed2a6abf7158809cf4f3c -in data/output.txt -out data/decrypted.txt
rem CBC Encrypt : CBC encrypt -k 2b7e151628aed2a6abf7158809cf4f3c -iv 000102030405060708090a0b0c0d0e0f -in data/input.txt -out data/output.txt
rem CBC Decrypt : CBC decrypt -k 2b7e151628aed2a6abf7158809cf4f3c -iv 000102030405060708090a0b0c0d0e0f -in data/output.txt -out data/decrypted.txt
rem CMAC : CMAC -k 2b7e151628aed2a6abf7158809cf4f3c -in data/input.txt -out data/output.txt
bin\aes.exe CMAC -k 2b7e151628aed2a6abf7158809cf4f3c -in data/input.txt -out data/output.txt