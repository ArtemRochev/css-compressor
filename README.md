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
  border: 1px solid red;
}
```

**min.style.css**
```css
span:before{content:'What is \'Big Ban\'?';}li .block{border:1px solid red;}
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
you can use -a flag to compress all CSS files in current dir

`
./compressor.out -a
`
result:
```
  | min
  |  | min.menu.css
  |  | min.sidebar.css
  |  | min.footer.css
  | menu.css
  | sidebar.css
  | footer.css
```
<hr>

you can use -m flag to rewrite soure file

`
./compressor.out style.css -m
`
