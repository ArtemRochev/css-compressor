`
./compressor.out style.css
`


soure:
```css
span:before {
  content: 'Hello, what is \'Big Ban\'?';
}
```

output:
```css
span:before{content:'Hello, what is \'Big Ban\'?';}
```

`
Compressed: min.style.css
  | base: 58 bytes
  | min:  51 bytes
  | diff: 7 bytes
`

you can use -m flag to rewrite soure file
`
./compressor.out style.css -m
`
