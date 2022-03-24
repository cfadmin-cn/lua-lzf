# lzf

  lzf is a very small data compression library.


## Usage

```lua
local lzf = require "llzf"

local text = "this's text and tell me how to use lzf lib."
```

### Deflate

```lua
local enc = lzf.compress(text)
```


### Inflate

```lua
local dec = lzf.uncompress(enc)
```

### validation


```lua
assert(dec == text)
```
