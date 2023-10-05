# Report
## Software
- OS: Windows 10
- Compiler: gcc 13.1.0

## Usage
`.\experiment`

## Results
### Console
```
[console] use_linebreaks=false, use_flush=false
STDERRSTDOUT 

[console] use_linebreaks=false, use_flush=true
STDOUTSTDERR 

[console] use_linebreaks=true, use_flush=false
STDERR
STDOUT

[console] use_linebreaks=true, use_flush=true
STDOUT
STDERR
```

### File
```
[output.txt] use_linebreaks=false, use_flush=false 
STDOUTSTDERR 

[output.txt] use_linebreaks=false, use_flush=true 
STDOUTSTDERR 

[output.txt] use_linebreaks=true, use_flush=false 
STDOUT
STDERR

[output.txt] use_linebreaks=true, use_flush=true 
STDOUT
STDERR
```

## Cleanup
`.\cleanup`