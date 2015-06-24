##CSS-Compressor

## usage:

`
./compressor.out style.css
`


**style.css**
```css
span:before {
  content: 'Hello, what is \'Big Ban\'?';
}
```

**min.style.css**
```css
span:before{content:'Hello, what is \'Big Ban\'?';}
```

###output:
`
Compressed: min.style.css
  | base: 58 bytes
  | min:  51 bytes
  | diff: 7 bytes
`

<hr>

##you can use -m flag to rewrite soure file

`
./compressor.out style.css -m
`
