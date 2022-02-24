# DPlusPlus
:zap: ¤ D++ programming language written in Pawn.

# Introduction to `D++`
- D++ is a simple and small programming language written in Pawn.

## Quick Start
- To start, we're going to make simple "Hello World" program in `script.dpp`.
- `script.dpp`:
```pawn
using::console.Print,"Hello World";
```
Output:
```
[14:05:43]                                         
[14:05:43] |======================================|
[14:05:43]                                         
[14:05:43]             The D++ Language            
[14:05:43]           System is loading...          
[14:05:43]                                         
[14:05:43]                By: DEntisT              
[14:05:43]                                         
[14:05:43] |======================================|
[14:05:43]                                         
[14:05:43]                                         
[14:05:43]                                         
[14:05:43] =====================[script.dpp]=====================
[14:05:43] Hello World
[14:05:43] =====================[EOS]=====================
```
- We can also import other files.
- `include.dpp`
```pawn
using::console.Print,"include.dpp is imported";
```

- `script.dpp`
```pawn
import::file,"include";

option::debug,1;

using::console.Print,"Hello World";
using::console.Print,"I am really cool string";
```

- Enable a debug mode using `option` keyword.

Output:
```
[14:05:43]                                         
[14:05:43] |======================================|
[14:05:43]                                         
[14:05:43]             The D++ Language            
[14:05:43]           System is loading...          
[14:05:43]                                         
[14:05:43]                By: DEntisT              
[14:05:43]                                         
[14:05:43] |======================================|
[14:05:43]                                         
[14:05:43]                                         
[14:05:43]                                         
[14:05:43] =====================[script.dpp]=====================
[14:05:43] include.dpp is imported
[14:05:43] [D++]: (info) - Processing: ' using::console.Print,"Hello World"'
[14:05:43] [D++]: (info) - funcgrp: 'using::console Print'
[14:05:43] Hello World
[14:05:43] [D++]: (info) - Processing: ' using::console.Print,"I am really cool string"'
[14:05:43] [D++]: (info) - funcgrp: 'using::console Print'
[14:05:43] I am really cool string
[14:05:43] =====================[EOS]=====================
```
