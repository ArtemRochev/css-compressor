##CSS-Compressor
>O(N) time

**usage:**

`
./compressor.out style.css
`


**style.css**
```css
span:before {
  content: 'What is \'Big Ban\'?';
}

li .block {
  background: red;
}
```

**min.style.css**
```css
span:before{content:'What is \'Big Ban\'?';}li .block{color:red;}
```

<hr>

**output:**
```
Compressed: min.style.css
  | base: 58 bytes
  | min:  51 bytes
  | diff: 7 bytes
```

<hr>

you can use -m flag to rewrite soure file

`
./compressor.out style.css -m
`
