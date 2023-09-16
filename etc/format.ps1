write-host "== Formatting Code =="
clang-format.exe --verbose -style=file -i *.c *.h
write-host 
