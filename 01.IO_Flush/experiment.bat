@echo off

gcc bufferization.c -o bufferization
                    
rem params: use_linebreaks / use_flush / use_file_redirect     

rem console experiment
echo [console] use_linebreaks=false, use_flush=false
bufferization 0 0 0 & echo. & echo.
echo [console] use_linebreaks=false, use_flush=true
bufferization 0 1 0 & echo. & echo.
echo [console] use_linebreaks=true, use_flush=false
bufferization 1 0 0 & echo.
echo [console] use_linebreaks=true, use_flush=true
bufferization 1 1 0 & echo.

rem file experiment
break>output.txt
echo [output.txt] use_linebreaks=false, use_flush=false >> output.txt
bufferization 0 0 1 & echo.>>output.txt & echo.>>output.txt
echo [output.txt] use_linebreaks=false, use_flush=true >> output.txt
bufferization 0 1 1 & echo.>>output.txt & echo.>>output.txt
echo [output.txt] use_linebreaks=true, use_flush=false >> output.txt
bufferization 1 0 1 & echo.>>output.txt
echo [output.txt] use_linebreaks=true, use_flush=true >> output.txt
bufferization 1 1 1 

pause