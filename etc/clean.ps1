write-host "== Cleaning up directories =="
$clean_files = @('*.res', '*.obj', '*.o', '*~', '*.orig', '*.exe', 
                 '*.ilk', '*.pdb', '*.orig', '*.gch')
get-childitem -recurse $clean_files | resolve-path -relative | remove-item 
resolve-path $clean_files -ErrorAction SilentlyContinue | remove-item 
